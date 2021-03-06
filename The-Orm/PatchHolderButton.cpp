/*
   Copyright (c) 2020 Christof Ruch. All rights reserved.

   Dual licensed: Distributed under Affero GPL license by default, an MIT license is available for purchase
*/

#include "PatchHolderButton.h"

#include "ColourHelpers.h"

Colour PatchHolderButton::buttonColourForPatch(midikraft::PatchHolder &patch, Component *componentForDefaultBackground) {
	Colour color = ColourHelpers::getUIColour(componentForDefaultBackground, LookAndFeel_V4::ColourScheme::widgetBackground);
	auto cats = patch.categories();
	if (!cats.empty()) {
		// Random in case the patch has multiple categories
		color = cats.cbegin()->color.darker();
	}
	return color;
}

void PatchHolderButton::setPatchHolder(midikraft::PatchHolder *holder, bool active, bool showSynthName)
{
	setActive(active);
	Colour color = ColourHelpers::getUIColour(this, LookAndFeel_V4::ColourScheme::widgetBackground);
	if (holder) {
		setButtonText(holder->name());
		setSubtitle((showSynthName && holder->synth()) ? holder->synth()->getName() : "");
		setColour(TextButton::ColourIds::buttonColourId, buttonColourForPatch(*holder, this));
		setFavorite(holder->isFavorite());
		setHidden(holder->isHidden());
	}
	else {
		setButtonText("");
		setSubtitle("");
		setColour(TextButton::ColourIds::buttonColourId, color);
		setFavorite(false);
		setHidden(false);
	}
}
