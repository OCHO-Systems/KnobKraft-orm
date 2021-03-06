# A free MIDI Sysex Librarian - The KnobKraft Orm

[![Build Status](https://dev.azure.com/christof0759/KnobKraft/_apis/build/status/christofmuc.KnobKraft-orm?branchName=master)](https://dev.azure.com/christof0759/KnobKraft/_build/latest?definitionId=1&branchName=master)

If you are looking for a modern, free Sysex Librarian for your synth, you have found the right place! This is the place where the KnobKraft Orm is created, a modern cross-platform Sysex Librarian for your MIDI gear.

Questions / help with implementing new synths wanted, I am trying to get us across many forums in the Internet into one common place, and have created a room on Gitter for that to reach me. If you have found a bug, also feel free to report directly here on Github. 

[![Gitter](https://badges.gitter.im/knobkraft/community.svg)](https://gitter.im/knobkraft/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

Currently natively supported and tested synths as of version 1.8.0:

* Access Virus B
* Kawai K3/K3M
* Korg DW-8000
* Oberheim Matrix 1000
* Sequential/Dave Smith Instruments OB-6
* Sequential/Dave Smith Instruments Prophet Rev2
* Yamaha Reface DX

As adaption currently available and tested

* Oberheim Matrix 6/6R - thanks to @tsantilis for his help!
* Sequential Pro 3 
* Sequential/Dave Smith Instruments Prophet 12

 Already implemented adaptions, which might require further testing, please get back to me and open an issue if you want these done. And if they work fine for you, also drop me a note so I can mark them as tested!

* Korg DW-6000 (untested)
* DSI Pro 2 (untested)
* DSI Prophet 08 (untested)
* Pioneer Toraiz AS-1 (untested)
* Roland JX-8P (untested)
* Sequential Prophet 5 Rev 4 (untested)
* Sequential Prophet 6 (untested)

The adaptions are python scripts for a generic module that let's you hook up other MIDI gear yourself, much in the spirit of the good old SoundDiver adaptions - at least, scripting the MIDI. No custom UI currently is possible or planned. So basically everyone who can read the MIDI spec and can do a little scripting could create new adaptions for more devices! They might not be as powerful or fully integrated as the natively supported synths, but they are done really quickly!

Next up for development are:

* Behringer RD-8
* Roland MKS-80

I made a video to show you the software and the most basic functionality, checkout the YouTube channel for more examples and advanced features as well:

[![](youtube-screenshot.PNG)](https://youtu.be/lPoFOVpTANM)

# Downloading the software

I provide installer builds for Windows and disk images for macOS, they are hosted here in github. To install, just grab the latest installer executable or DMG file from the following page and run it. The Mac version needs to be installed (drag into application folder after opening the DMG) and then run with the CTRL-Click Open command (to ignore unknown source warning, as I do not sign the installers with a certificate).

[https://github.com/christofmuc/KnobKraft-orm/releases](https://github.com/christofmuc/KnobKraft-orm/releases)

Linux is reported to build and run as well, but due to the multitude of possible installations I suggest you follow the build instructions below, it shouldn't be too hard.

You can always use the source to build it yourself, please read on for more instructions.

## Supported platforms

This software is build and run on Windows 10, macOS 10.15, and several Linux distributions. Note that this is not a commercial project, and as I am using Windows mostly expect some hiccups. But I will get back to you if you report a bug and try to resolve it!

# Building the software

## Prerequisites

We use [CMake 3.14](https://cmake.org/). Make sure to have a recent version of cmake installed. 

## Downloading

Clone with submodules from github

    git clone --recurse-submodules https://github.com/christofmuc/KnobKraft-orm

The recursive clone with  submodules is required to retrieve the following additional modules already into the right spot inside the source tree:

1. We use the magnificent [JUCE library](https://juce.com/) to immensly reduce the amount of work we have to do. 
6. [juce-cmake](https://github.com/remymuller/juce-cmake) to allow us to use JUCE and CMake together.
4. The configure step will download (on Windows) the allmighty [boost](https://www.boost.org/) library, sorry for the bloat but I simply had no time to remove the dependency yet. All my professional projects of course rely on boost, so it is a natural to incorporate it here as well.

## Building on Windows

Using CMake and building is a simple step if the prerequisites are fulfilled. Simply open a command line in the downloaded root directory `<KnobKraft-orm>` and run

    cmake -S . -B builds -G "Visual Studio 15 2017 Win64"

This will generate a solution file for Visual Studio in the builds subdirctory. You can build the software to run it immediately with the command

    cmake --build builds --config Release

This will produce the executable in the path `builds\The-Orm\Release`, namely a file called `KnobKraftOrm.exe` which you can double click and launch.

## Building on Linux

See the appveyor.yml file for some hints how the Ubuntu server is doing it. Mainly, you need to install a long list of prerequisites and development libraries:

    sudo apt-get -y update && sudo apt-get install -y libcurl4-openssl-dev pkg-config libtbb-dev libasound2-dev libboost-dev libgtk-3-dev libwebkit2gtk-4.0-dev libglew-dev libjack-dev libicu-dev libpython3-all-dev

and then can use CMake just like on Windows to compile the software:

    cmake -S . -B builds && cmake --build builds

This will produce a single executable `builds/The-Orm/KnobKraftOrm` that you can run.

## Building on macOS

If you are inclined to build on Mac, you know what you're doing. I'd recommend to install the build requisites via homebrew like this

    brew install gtk+3 glew boost python3

and then run CMake to build the software

    cmake -S . -B builds/release -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    cmake --build builds/release 

which will produce a launchable application in a folder called `KnobKraftOrm.app`.
    

## Licensing

As some substantial work has gone into the development of this, I decided to offer a dual license - AGPL, see the LICENSE.md file for the details, for everybody interested in how this works and willing to spend some time her- or himself on this, and a commercial MIT license available from me on request. Thus I can help the OpenSource community without blocking possible commercial applications.

## Contributing

All pull requests and issues welcome, I will try to get back to you as soon as I can. Due to the dual licensing please be aware that I will need to request transfer of copyright on accepting a PR. 

## Acknowledgements

Really big thanks to everybody who contributes and comments on YouTube, here on Github, or any of the other forums out in the Internet to motivate me to continue this work!

Special thanks to @tsantilis for getting the Oberheim Matrix 6/6R adaption to work with restless tests and trials!

The app icon is courtesy of W07 at the Sequential forums, thanks for your contribution!

For the restless Prophet 12 testing thanks and a medal for most comments on a ticket go to @Andy2No!

Thanks also go to @gnidorah for reporting bugs with the RefaceDX implementation, which were fixed!

## About the author

Christof is a lifelong software developer having worked in various industries, and can't stop his programming hobby anyway. 
