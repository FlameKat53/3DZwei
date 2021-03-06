/*
*   This file is part of 3DZwei
*   Copyright (C) 2020 SuperSaiyajinStackZ
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "config.hpp"
#include "credits.hpp"
#include "multiGame.hpp"
#include "mainMenu.hpp"
#include "overlay.hpp"
#include "timePlay.hpp"
#include "uiSettings.hpp"

extern std::unique_ptr<Config> config;
extern bool exiting;
extern bool touching(touchPosition touch, Structs::ButtonPos button);

void MainMenu::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, -2, 0.8f, config->textColor(), "3DZwei - " + Lang::get("MAINMENU"), 390);
	
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
	GFX::DrawBottom();

	for (int i = 0; i < 4; i++) {
		Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, config->buttonColor());
		if (this->Selection == i) {
			GFX::DrawButtonSelector(mainButtons[i].x, mainButtons[i].y);
		}
	}

	Gui::DrawStringCentered(-80, mainButtons[0].y+12, 0.6f, config->textColor(), Lang::get("NEW_GAME"), 130);
	Gui::DrawStringCentered(80, mainButtons[1].y+12, 0.6f, config->textColor(), Lang::get("UI_SETTINGS"), 130);
	Gui::DrawStringCentered(-80, mainButtons[2].y+12, 0.6f, config->textColor(), Lang::get("CREDITS"), 130);
	Gui::DrawStringCentered(80, mainButtons[3].y+12, 0.6f, config->textColor(), Lang::get("GAME_RULES"), 130);
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
}


void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	// Navigation.
	if (hDown & KEY_RIGHT) {
		if (this->Selection < 3) this->Selection++;
	}

	if (hDown & KEY_UP) {
		if (this->Selection > 1) this->Selection -= 2;
	}

	if (hDown & KEY_DOWN) {
		if (this->Selection < 2) this->Selection += 2;
	}

	if (hDown & KEY_LEFT) {
		if (this->Selection > 0) this->Selection--;
	}


	if (hDown & KEY_A) {
		int tempSelect = -1;
		switch(this->Selection) {
			case 0:
				tempSelect = Overlays::SelectGame();

				switch(tempSelect) {
					case 0:
						Gui::setScreen(std::make_unique<MultiGame>(), true, true);
						break;
					case 1:
						Gui::setScreen(std::make_unique<TimePlay>(), true, true);
						break;
				}
				break;
			case 1:
				Gui::setScreen(std::make_unique<UISettings>(), true, true);
				break;
			case 2:
				Gui::setScreen(std::make_unique<Credits>(), true, true);
				break;
			case 3:
				Overlays::ShowRules();
				break;
		}
	}

	if (hDown & KEY_TOUCH) {
		if (touching(touch, mainButtons[0])) {
			int tempSelect = Overlays::SelectGame();

			switch(tempSelect) {
				case 0:
					Gui::setScreen(std::make_unique<MultiGame>(), true, true);
					break;
				case 1:
					Gui::setScreen(std::make_unique<TimePlay>(), true, true);
					break;
			}
			
		} else if (touching(touch, mainButtons[1])) {
			Gui::setScreen(std::make_unique<UISettings>(), true, true);
		} else if (touching(touch, mainButtons[2])) {
			Gui::setScreen(std::make_unique<Credits>(), true, true);
		} else if (touching(touch, mainButtons[3])) {
			Overlays::ShowRules();
		}
	}
	
	if (hDown & KEY_START) {
		fadeout = true;
		fadecolor = 0;
		exiting = true;
	}
}