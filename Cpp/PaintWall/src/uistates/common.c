/*
 * common.c
 *
 *  Created on: 05/02/2013
 *      Author: Pedro Henrique Lara Campos,
 *				Christian Ferraz Lemos de Sousa
 */

#include <paintwall.h>
#include "dstates.h"
#include "ui_language.h"

const int common_h = 48;

void UI_COMMON_Draw () {
	int w, basex;
	w = ((double)defaultUI.screen->w * 0.8);
	basex = (defaultUI.screen->w - w) / 2;
	UI_DrawWindow (defaultUI.screen, basex, -(defaultUI.windowSkinMask[0][1].h), w, common_h);

	BUTTON* btns = defaultUIStates[COMMON_UI].buttons;
	btns[0].x = basex + 16;

	BUTTONS_Draw (btns, defaultUIStates[COMMON_UI].buttonsNum);
}

void UI_COMMON_Create () {
	defaultUIStates[COMMON_UI].buttonsNum = 1;
	defaultUIStates[COMMON_UI].buttons = (BUTTON*) malloc (sizeof(BUTTON) * defaultUIStates[COMMON_UI].buttonsNum);
	defaultUIStates[COMMON_UI].buttons[0] = (BUTTON) {0, 0, 4, 32, 32,
		NULL, 1, NULL, "A", NULL};
}

void UI_COMMON_Free () {
	if (defaultUIStates[COMMON_UI].buttons != NULL) { //4SAFITY;
		defaultUIStates[COMMON_UI].buttonsNum = 0;
		free(defaultUIStates[COMMON_UI].buttons);
		defaultUIStates[COMMON_UI].buttons = NULL;
	}
}
