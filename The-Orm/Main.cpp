/*
   Copyright (c) 2020 Christof Ruch. All rights reserved.

   Dual licensed: Distributed under Affero GPL license by default, an MIT license is available for purchase
*/

#include "JuceHeader.h"

#include "MainComponent.h"

#include "Settings.h"
#include "UIModel.h"

#include "GenericAdaptation.h"
#include "embedded_module.h"

#include <memory>

#include "version.cpp"

#ifdef USE_SENTRY
#include "sentry.h"
#include "sentry-config.h"

#ifdef LOG_SENTRY
static void print_envelope(sentry_envelope_t *envelope, void *unused_state)
{
	(void)unused_state;
	size_t size_out = 0;
	char *s = sentry_envelope_serialize(envelope, &size_out);
	// As Sentry will still log during shutdown, in this instance we must really check if logging is still a good idea
	if (SimpleLogger::instance()) {
		SimpleLogger::instance()->postMessage("Sentry: " + std::string(s));
	}
	sentry_free(s);
	sentry_envelope_free(envelope);
}
#endif

static void sentryLogger(sentry_level_t level, const char *message, va_list args, void *userdata) {
	ignoreUnused(level, args, userdata);
	char buffer[2048];
	vsnprintf_s(buffer, 2048, message, args);
	// As Sentry will still log during shutdown, in this instance we must really check if logging is still a good idea
	if (SimpleLogger::instance()) {
		SimpleLogger::instance()->postMessage("Sentry: " + std::string(buffer));
	}
}
#endif

//==============================================================================
class TheOrmApplication  : public JUCEApplication, private ChangeListener
{
public:
    //==============================================================================
	TheOrmApplication() = default;

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
		ignoreUnused(commandLine);

		// This method is where you should put your application's initialization code..
		char *applicationDataDirName = "KnobKraftOrm";
		Settings::setSettingsID(applicationDataDirName);

		// Init python for GenericAdaptation
		knobkraft::GenericAdaptation::startupGenericAdaptation();

		// Init python with the embedded pytschirp module, if the Python init was successful
		if (knobkraft::GenericAdaptation::hasPython()) {
			globalImportEmbeddedModules();
		}

		// Select colour scheme
		auto lookAndFeel = &LookAndFeel_V4::getDefaultLookAndFeel();
		auto v4 = dynamic_cast<LookAndFeel_V4 *>(lookAndFeel);
		if (v4) {
			v4->setColourScheme(LookAndFeel_V4::getMidnightColourScheme());
		}
		mainWindow = std::make_unique<MainWindow> (getWindowTitle()); 

#ifdef USE_SENTRY
		// Initialize sentry for error crash reporting
		sentry_options_t *options = sentry_options_new();
		std::string dsn = getSentryDSN();
		sentry_options_set_dsn(options, dsn.c_str());
		auto sentryDir = File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile(applicationDataDirName).getChildFile("sentry");
		sentry_options_set_database_path(options, sentryDir.getFullPathName().toStdString().c_str());
		std::string releaseName = std::string("KnobKraft Orm Version ") + getOrmVersion();
		sentry_options_set_release(options, releaseName.c_str());
		sentry_options_set_logger(options, sentryLogger, nullptr);
		sentry_options_set_require_user_consent(options, 1);
#ifdef LOG_SENTRY
		sentry_options_set_debug(options, 1);
		sentry_options_set_transport(options, sentry_transport_new(print_envelope));
#endif
		sentry_init(options);

		// Fire a test event to see if Sentry actually works
		//sentry_capture_event(sentry_value_new_message_event(SENTRY_LEVEL_INFO,"custom","Launching KnobKraft Orm"));
#endif

		// Window Title Refresher
		UIModel::instance()->windowTitle_.addChangeListener(this);
    }

	String getWindowTitle() {
		return getApplicationName() + String(" - Sysex Librarian V" + getOrmVersion());
	}

	void changeListenerCallback(ChangeBroadcaster* source) override
	{
		ignoreUnused(source);
		auto mainComp = dynamic_cast<MainComponent *>(mainWindow->getContentComponent());
		if (mainComp) {
			// This is only called when the window title needs to be changed!
			File currentDatabase(mainComp->getDatabaseFileName());
			mainWindow->setName(getWindowTitle() + " (" + currentDatabase.getFileName() + ")");
		}
	}

    void shutdown() override
    {
		// Unregister
		UIModel::instance()->windowTitle_.removeChangeListener(this);

        // Add your application's shutdown code here..
		SimpleLogger::shutdown(); // That needs to be shutdown before deleting the MainWindow, because it wants to log into that!
		
        mainWindow = nullptr; // (deletes our window)

		// The UI is gone, we don't need the UIModel anymore
		UIModel::shutdown();

		// Shutdown MIDI subsystem after all windows are gone
		midikraft::MidiController::shutdown();

		// Shutdown settings subsystem
		Settings::instance().saveAndClose();
		Settings::shutdown();

#ifdef USE_SENTRY
		// Sentry shutdown
		sentry_shutdown();
#endif
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
		// Shut down database (that makes a backup)
		// Do this before calling quit
		auto mainComp = dynamic_cast<MainComponent *>(mainWindow->getContentComponent());
		if (mainComp) {
			// Give it a chance to complete the Database backup
			//TODO - should ask user or at least show progress dialog?
			mainComp->shutdown();
		}
		
		// This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
		ignoreUnused(commandLine);
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Desktop::getInstance().getDefaultLookAndFeel()
                                                                          .findColour (ResizableWindow::backgroundColourId),
                                                    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
           #endif

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };


private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (TheOrmApplication)
