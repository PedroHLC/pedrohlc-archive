/*
 * welcome.c
 *
 *  Created on: 04/02/2013
 *      Author: Pedro Henrique Lara Campos,
 *				Christian Ferraz Lemos de Sousa
 */

#include <paintwall.h>
#include "dstates.h"
#include "ui_language.h"

void UI_WELCOME_onClickOK () {
	UI_SetState (&defaultUIStates[COMMON_UI]);
}

void UI_WELCOME_Draw () {
	int w = 300, h = 220,
	 	basex = (defaultUI.screen->w - w) / 2,
		basey = (defaultUI.screen->h - h) / 2;
	UI_DrawWindow (defaultUI.screen, basex, basey, w, h);

	SDL_Surface *titleText = TTF_RenderText_Blended(defaultUI.titleFont, LANG_UI_WELCOME, defaultUI.textColor);
	UI_RenderText_Blended_MultiLine(defaultUI.textFont, LANG_UI_WELCOME_MSG, defaultUI.textColor, w -32, h -32, basex + 32, basey +32 + titleText->h);

	SDL_BlitSurface(titleText, NULL, defaultUI.screen, &((SDL_Rect){basex + 32, basey +32 , 0, 0}));

	SDL_FreeSurface (titleText);

	BUTTON *btns = defaultUIStates[WELCOME_UI].buttons;
	btns[0].x = basex + (w - 32 - btns[0].w); btns[0].y = basey + (h - 32 - btns[0].h);
	btns[1].x = (btns[0].x - 16 - btns[1].w); btns[1].y = btns[0].y;

	BUTTONS_Draw (btns, defaultUIStates[WELCOME_UI].buttonsNum);
}

void UI_WELCOME_Create () {
	defaultUIStates[WELCOME_UI].Draw = &UI_WELCOME_Draw;
	const int btn_w=64, btn_h=24, buttonsNum=2;
	defaultUIStates[WELCOME_UI].buttonsNum = buttonsNum;
	defaultUIStates[WELCOME_UI].buttons = (BUTTON*) malloc (sizeof(BUTTON)*buttonsNum);
	defaultUIStates[WELCOME_UI].buttons[0] = (BUTTON) {0, 0, 0, btn_w, btn_h,
		&defaultUI.buttonPositive, 1, &UI_WELCOME_onClickOK, LANG_UI_OK, NULL};
	defaultUIStates[WELCOME_UI].buttons[1] = (BUTTON) {0, 0, 0, btn_w, btn_h,
		&defaultUI.buttonNegative, 1, &MAIN_Close, LANG_UI_QUIT, NULL};
}

void UI_WELCOME_Free () {
	if (defaultUIStates[WELCOME_UI].buttons != NULL) { //4SAFITY;
		defaultUIStates[WELCOME_UI].buttonsNum = 0;
		free(defaultUIStates[WELCOME_UI].buttons);
		defaultUIStates[WELCOME_UI].buttons = NULL;
	}
}
