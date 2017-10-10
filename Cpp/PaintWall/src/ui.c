/*
 * ui.c
 *
 *  Created on: 29/01/2013
 *      Author: Pedro Henrique Lara Campos,
 *				Christian Ferraz Lemos de Sousa
 */

#include <jansson.h>
#include <math.h>
#include <stdlib.h>
#include <paintwall.h>
#include "language.h"

#define ddp 32

SDL_Rect ETC_ReadRect (SDL_Rect* rect, const char* data) {
	int x=0, y=0, width=0, height=0;
	sscanf (data, "%dx%d,%dx%d", &x, &y, &width, &height);
	(*rect).x = x; (*rect).y = y;
	(*rect).w = width; (*rect).h = height;
	return *rect;
}

SDL_Color ETC_ReadColor (const char* source) {
	int r=0, g=0, b=0;
	sscanf (source, "%dx%dx%d", &r, &g, &b);
	return (SDL_Color) {r, g, b};
}

SDL_Surface *ETC_IMG_AlphedLoad (const char *fname, SDL_PixelFormat *format){
	SDL_Surface *twS, *result;
	twS = IMG_Load (fname);
	if (twS == NULL)
		return NULL;
	result = SDL_ConvertSurface (twS, format, SDL_SWSURFACE | SDL_SRCALPHA);
	SDL_FreeSurface (twS);
	SDL_SetAlpha (result, 0, result->format->alpha);
	return result;
}

void DEBUG_PrintRects (SDL_Rect* rects, int num) {
	int i;
	SDL_Rect rect;
	for(i=0; i<num; i++){
		rect = rects[i];
		printf ("%dx%d,%dx%d\n", rect.x, rect.y, rect.w, rect.h);
	}
}

void UI_RGBAFormat () {
	RGBAFormat = (SDL_PixelFormat) {0,
				32, 4,
				0, 0, 0, 0,
				0, 8, 16, 24,
				UI_chR, UI_chG, UI_chB, UI_chA,
				0, 0};
}

const Uint32 windowFlags = SDL_RESIZABLE | SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN;

void UI_Create () {
	UI_RGBAFormat ();

	json_t *__temp,
			*__window = json_object_get (defaultConfig, "window");
	if (__window == NULL)
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x2, LANG_ERROR_JSONCORRUPTED);

	int windowWidth=0, windowHeight=0;
	if ((__temp = json_object_get (__window, "width")) != NULL)
		windowWidth = json_number_value (__temp);
	if ((__temp = json_object_get (__window, "height")) != NULL)
		windowHeight = json_number_value (__temp);

	SDL_Surface *tUI;
	if (windowWidth > 0 && windowHeight > 0 &&
			(tUI = SDL_SetVideoMode (windowWidth, windowHeight, ddp, windowFlags)) != NULL)
		defaultUI.screen = tUI;
	else if ((tUI = SDL_SetVideoMode (1280, 720, ddp, windowFlags)) != NULL)
		defaultUI.screen = tUI;
	else if ((tUI = SDL_SetVideoMode (800, 600, ddp, windowFlags))	!= NULL)
		defaultUI.screen = tUI;
	else if ((tUI = SDL_SetVideoMode (640, 480, ddp, windowFlags))	!= NULL)
		defaultUI.screen = tUI;
	else
		CRITICAL (ERROR_SDLNOMODE, LANG_ERROR_NOMODE);

	/*defaultUI.interface = SDL_CreateRGBSurface (SDL_SWSURFACE | SDL_SRCALPHA,
			tUI->w, tUI->h, ddp, UI_chR, UI_chG, UI_chB, UI_chA);
	defaultUI.subWindow = SDL_CreateRGBSurface (SDL_SWSURFACE | SDL_SRCALPHA,
			tUI->w, tUI->h, ddp, UI_chR, UI_chG, UI_chB, UI_chA);
	SDL_FillRect (defaultUI.subWindow, NULL, 0x000000);

	if(defaultUI.interface == NULL || defaultUI.subWindow == NULL)
		CRITICAL (COMPLEX_ERROR_SDLUNEXPECTED+0x, LANG_ERROR_UICREATION);*/

	json_t *__skinFile = json_object_get (__window,"skin");
	if (__skinFile == NULL)
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x3, LANG_ERROR_JSONCORRUPTED);

	bitmapResources.windowSkin = ETC_IMG_AlphedLoad (json_string_value (__skinFile), &RGBAFormat);
	if (bitmapResources.windowSkin == NULL)
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x4, LANG_ERROR_JSONCORRUPTED);

	if (UI_MaskRead (__window, defaultUI.windowSkinMask) == 0)
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x5, LANG_ERROR_JSONCORRUPTED);

	if ((__temp = json_object_get (__window, "skin-flat")) != NULL)
		defaultUI.windowSkinFlat = (json_number_value (__temp) == 0 ? 0 : 1);
	else
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x6, LANG_ERROR_JSONCORRUPTED);

	json_t *__buttons = json_object_get (defaultConfig, "buttons");
	if (__buttons == NULL)
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x7, LANG_ERROR_JSONCORRUPTED);

	if ((__temp = json_object_get (__buttons, "skin")) == NULL)
		bitmapResources.buttonSkin = bitmapResources.windowSkin;
	else {
		bitmapResources.buttonSkin = ETC_IMG_AlphedLoad (json_string_value (__temp), &RGBAFormat);
		if (bitmapResources.buttonSkin == NULL)
			CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x8, LANG_ERROR_JSONCORRUPTED);
	}

	if ((__temp = json_object_get (__buttons, "skin-flat")) != NULL)
		defaultUI.buttonsSkinFlat = (json_number_value (__temp) == 0 ? 0 : 1);
	else
		defaultUI.buttonsSkinFlat = defaultUI.windowSkinFlat;

	if ((__temp = json_object_get (__buttons, "normal")) == NULL ||
			BUTTON_ReadDesign (__temp, &defaultUI.buttonNormal) != 0)
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0xA, LANG_ERROR_JSONCORRUPTED);

	if ((__temp = json_object_get (__buttons, "positive")) == NULL ||
			BUTTON_ReadDesign (__temp, &defaultUI.buttonPositive) != 0)
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0xB, LANG_ERROR_JSONCORRUPTED);

	if ((__temp = json_object_get (__buttons, "negative")) == NULL ||
			BUTTON_ReadDesign (__temp, &defaultUI.buttonNegative) != 0)
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0xC, LANG_ERROR_JSONCORRUPTED);

	if ((__temp = json_object_get (__buttons, "disabled")) == NULL ||
			UI_MaskRead (__temp, defaultUI.buttonDisabledMask) == 0)
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0xD, LANG_ERROR_JSONCORRUPTED);

	if (((__temp = json_object_get (__window, "font")) == NULL) || (!(defaultUI.fontName = (char*)json_string_value (__temp))))
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0xE, LANG_ERROR_JSONCORRUPTED);

	if (((__temp = json_object_get (__window, "text-color")) == NULL))
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0xF, LANG_ERROR_JSONCORRUPTED);
	else
		defaultUI.textColor = ETC_ReadColor(json_string_value (__temp));

	int fontsize = 0;
	if (((__temp = json_object_get (__window, "font-size")) == NULL) || ((fontsize = json_number_value (__temp)) < 1))
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0xE, LANG_ERROR_JSONCORRUPTED);

	if ((defaultUI.textFont = TTF_OpenFont(defaultUI.fontName, fontsize)) == NULL) {
		//DEBUG: printf ("%s: {\"%s\", %i}\n", LANG_ERROR_DETAILS, defaultUI.fontName, fontsize);
		CRITICAL (ERROR_TTFLOADFAIL, LANG_ERROR_TTF_LOADFAIL);
	}

	int titleFontSize = 18;
	if ((defaultUI.titleFont = TTF_OpenFont(defaultUI.fontName, titleFontSize)) == NULL) {
		//printf ("%s: {\"%s\", %i}\n", LANG_ERROR_DETAILS, defaultUI.fontName, titleFontSize);
		CRITICAL (ERROR_TTFLOADFAIL, LANG_ERROR_TTF_LOADFAIL);
	}

	defaultUI.screenClicked = 0;

	UI_STATES_CreateDefaults ();
}

int UI_MaskRead (json_t *source, SDL_Rect wSM[3][3]){
	json_t *__sub;
	if((__sub = json_object_get (source,"decoration-pattern")) != NULL) {
		SDL_Rect rect;
		int xi, yi;
		ETC_ReadRect (&rect, json_string_value(__sub));
		for (xi=0; xi < 3; xi++){
			for (yi=0; yi < 3; yi++){
				 wSM[yi][xi] = (SDL_Rect){rect.w * xi + rect.x, rect.h * yi + rect.y, rect.w, rect.h};
			}
		}
		return 1;
	}else if((__sub = json_object_get (source,"decoration-mask")) != NULL) { //NOT SAFE
		// NOT EVEN A LITTLE SAFE //TODO: Make This Safe :D
		ETC_ReadRect (&wSM[0][0],
				json_string_value (json_object_get (__sub,"top-left")));
		ETC_ReadRect (&wSM[0][1],
				json_string_value (json_object_get (__sub,"top")));
		ETC_ReadRect (&wSM[0][2],
				json_string_value (json_object_get (__sub,"top-right")));
		ETC_ReadRect (&wSM[1][0],
				json_string_value (json_object_get (__sub,"left")));
		ETC_ReadRect (&wSM[1][1],
				json_string_value (json_object_get (__sub,"center")));
		ETC_ReadRect (&wSM[1][2],
				json_string_value (json_object_get (__sub,"right")));
		ETC_ReadRect (&wSM[2][0],
				json_string_value (json_object_get (__sub,"bottom-left")));
		ETC_ReadRect (&wSM[2][1],
				json_string_value (json_object_get (__sub,"bottom")));
		ETC_ReadRect (&wSM[2][2],
				json_string_value (json_object_get (__sub,"bottom-right")));
		//DEBUG_PrintRects (wSM, 9);
		return 2;
	}else {
		return 0;
	}
}

void UI_InterfaceDraw () {
	if (defaultUI.state != NULL && (*defaultUI.state).Draw != NULL)
		(*defaultUI.state).Draw ();
}

_Bool UI_IsMouseOver (int x, int y) {
	if (defaultUI.state != NULL)
		return (*defaultUI.state).IsMouseOver (x, y);
	return 0;
}

void UI_Draw () {
	SDL_FillRect (defaultUI.screen, NULL, 0xDDDDDD); //RGB
	if (activeCanvas != NULL) {
		SDL_UpdateRect (activeCanvas, 0, 0, 0, 0);
		SDL_BlitSurface(activeCanvas, NULL, defaultUI.screen, NULL);
	}
	UI_InterfaceDraw ();
	/*if (defaultUI.subWindow != NULL && shoulDrawSubWindow) {
		SDL_UpdateRect (defaultUI.subWindow, 0, 0, 0, 0);
		SDL_BlitSurface(defaultUI.subWindow, NULL, defaultUI.screen, NULL);
	}*/
	SDL_UpdateRect (defaultUI.screen, 0, 0, 0, 0);
	SDL_Flip (defaultUI.screen);
}

void UI_Update (SDL_Event event) {
	int x=0, y=0;
	void *theOne=NULL;
	switch (event.type) {
		case SDL_QUIT:
			//TODO: Save Width/Height
			exit (CLOSED);
			break;
		case SDL_VIDEORESIZE:
			x = (event.resize.w < 0 ? 640 : event.resize.w);
			y = (event.resize.h < 0 ? 480 : event.resize.h);

			if ((defaultUI.screen = SDL_SetVideoMode (x, y, ddp, windowFlags)) == NULL)
				CRITICAL (COMPLEX_ERROR_SDLUNEXPECTED+0x1, LANG_ERROR_UICREATION);

			UI_Draw ();
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&x, &y);
			if ((theOne = BUTTONS_MouseOver (defaultUI.state->buttons, defaultUI.state->buttonsNum, x, y)) != NULL) {
				defaultUI.mouseOverType = OBJ_BUTTON;
			}else if (defaultUI.state->IsMouseOver != NULL && defaultUI.state->IsMouseOver (x, y)) {
				theOne = &defaultUI.state;
				defaultUI.mouseOverType = OBJ_INTERFACE;
			}else {
				theOne = NULL;
				defaultUI.mouseOverType = OBJ_CANVAS;
			}
			if (theOne != defaultUI.mouseOver) {
				defaultUI.mouseOver = theOne;
				UI_Draw ();
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				defaultUI.screenClicked = 1;
				UI_Draw ();
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				defaultUI.screenClicked = 0;
				UI_Draw ();
				if (defaultUI.mouseOverType == OBJ_BUTTON)
					if ((*(BUTTON*) defaultUI.mouseOver).OnClick != NULL && (*(BUTTON*) defaultUI.mouseOver).enabled)
						(*(BUTTON*) defaultUI.mouseOver).OnClick ();
			}
			break;
	}
}

void UI_DrawWindow (SDL_Surface *surface, int wx, int wy, int w, int h){
	UI_DrawSkin (defaultUI.windowSkinMask, bitmapResources.windowSkin, surface, wx, wy, w, h, defaultUI.windowSkinFlat, 0);
}

SDL_Surface *UI_PrepareWindow (int w, int h){
	return UI_DrawSkin (defaultUI.windowSkinMask, bitmapResources.windowSkin, NULL, 0, 0, w, h, defaultUI.windowSkinFlat, 0);
}

int UI_DrawSurfaceIn (SDL_Surface *origin, SDL_Surface *target, int x, int y){
	int w = (*origin).w,
		h = (*origin).h;
	SDL_Rect orect = (SDL_Rect){0, 0, w, h},
		trect = (SDL_Rect){x, y, w, h};
	return SDL_BlitSurface(origin, &orect, target, &trect);
}

SDL_Surface *UI_DrawSkin (SDL_Rect wSM[3][3], SDL_Surface *skin, SDL_Surface *surface, int wx, int wy, int w, int h, _Bool stretch, _Bool drawDirectly) {
	SDL_Surface *window;
	int dx, dy;

	if(!drawDirectly){
		dx = (surface? 0 : wx);
		dy = (surface? 0 : wy);
		window  = SDL_CreateRGBSurface (SDL_SWSURFACE | SDL_SRCALPHA,
			w+dx, h+dy, ddp, UI_chR, UI_chG, UI_chB, UI_chA);
		SDL_FillRect (window, NULL, 0); //RGBA
		if(window == NULL)
			CRITICAL (COMPLEX_ERROR_SDLUNEXPECTED+0x2, LANG_ERROR_POPUPCREATION);
	}else{
		window = surface;
		dx = wx;
		dy = wy;
	}

	int x_centerw = w - wSM[1][0].w - wSM[1][2].w,
		y_centery = h - wSM[0][1].h - wSM[2][1].h;

	SDL_Rect trect, trect2, actual;

	if(stretch) {
		//Draw Center
		actual = wSM[1][1];
		trect = (SDL_Rect) {dx+ wSM[0][0].w, dy+ wSM[0][0].h, x_centerw, y_centery};
		SDL_SoftStretch (skin, &actual, window, &trect);

		//Draw Borders
		actual = wSM[1][0];
		trect = (SDL_Rect) {dx, dy+ wSM[0][0].h, actual.w, y_centery};
		SDL_SoftStretch (skin, &actual, window, &trect);

		actual = wSM[1][2];
		trect = (SDL_Rect) {dx+ w - wSM[1][2].w, dy+ wSM[0][2].h, actual.w, y_centery};
		SDL_SoftStretch (skin, &actual, window, &trect);

		actual = wSM[0][1];
		trect = (SDL_Rect) {dx+ wSM[0][0].w, dy, x_centerw, actual.h};
		SDL_SoftStretch (skin, &actual, window, &trect);

		actual = wSM[2][1];
		trect = (SDL_Rect) {dx+ wSM[2][0].w, dy+ h - wSM[2][1].h, x_centerw, actual.h};
		SDL_SoftStretch (skin, &actual, window, &trect);
	}else {
		//Calc. Center
		double ecnx = (double)x_centerw / (double)wSM[1][1].w,
			ecny = (double)y_centery / (double)wSM[1][1].h,
			fecnx = floor (ecnx),
			fecny = floor (ecny),
			secnx = ecnx - fecnx,
			secny = ecny - fecny;

		//Calc. Border-Left
		double eblny = (double)y_centery / (double)wSM[1][0].h,
			feblny = floor (eblny),
			seblny = eblny - feblny;

		//Calc. Border-Right
		double ebrny = (double)y_centery / (double)wSM[1][2].h,
			febrny = floor (ebrny),
			sebrny = ebrny - febrny;

		//Calc. Border-Top
		double ebtnx = (double)x_centerw / (double)wSM[0][1].w,
			febtnx = floor (ebtnx),
			sebtnx = ebtnx - febtnx;

		//Calc. Border-Bottom
		double ebbnx = (double)x_centerw / (double)wSM[2][1].w,
			febbnx = floor (ebbnx),
			sebbnx = ebbnx - febbnx;

		int xi, yi, tw, th, sx, sy;
		double lh, lw;

		// Draw Center
		actual = wSM[1][1];
		tw = actual.w;
		th = actual.h;
		sx = dx+ wSM[0][0].w,
		sy = dy+ wSM[0][0].h;

		for (yi=0; yi < fecny; yi++)
			for (xi=0; xi < fecnx; xi++) {
				trect = (SDL_Rect){xi*tw+sx, yi*th+sy, tw, th};
				SDL_BlitSurface (skin, &actual, window, &trect);
			}

		lh = ceil ((double)th * secny);
		trect2 = (SDL_Rect){actual.x, actual.y, tw, lh};
		for (xi=0; xi < fecnx; xi++) {
			trect = (SDL_Rect){xi*tw+sx, yi*th+sy, tw, lh};
			SDL_BlitSurface (skin, &trect2, window, &trect);
		}

		lw = ceil ((double)tw * secnx);
		trect2 = (SDL_Rect){actual.x, actual.y, lw, th};
		for (yi=0; yi < fecny; yi++) {
			trect = (SDL_Rect){xi*tw+sx, yi*th+sy, lw, th};
			SDL_BlitSurface (skin, &trect2, window, &trect);
		}

		trect = (SDL_Rect){xi*tw+sx, yi*th+sy, lw, lh};
		trect2 = (SDL_Rect){actual.x, actual.y, lw, lh};
		SDL_BlitSurface (skin, &trect2, window, &trect);

		// Draw Borders
		actual = wSM[1][0];
		tw = actual.w;
		th = actual.h;
		sx = dx;
		//sy = sy;

		xi = 0;
		for (yi=0; yi < feblny; yi++){
			trect = (SDL_Rect){0, yi*th+sy, tw, th};
			SDL_BlitSurface (skin, &actual, window, &trect);
		}
		lh = ceil((double)th * seblny);
		trect = (SDL_Rect){0, yi*th+sy, tw, lh};
		trect2 = (SDL_Rect){actual.x, actual.y, tw, lh};
		SDL_BlitSurface (skin, &trect2, window, &trect);

		actual = wSM[1][2];
		tw = actual.w;
		th = actual.h;
		sx = dx+ w - tw;
		for (yi=0; yi < febrny; yi++){
			trect = (SDL_Rect){sx, yi*th+sy, tw, th};
			SDL_BlitSurface (skin, &actual, window, &trect);
		}
		lh = ceil ((double)th * sebrny);
		trect = (SDL_Rect){sx, yi*th+sy, tw, lh};
		trect2 = (SDL_Rect){actual.x, actual.y, tw, lh};
		SDL_BlitSurface (skin, &trect2, window, &trect);


		actual = wSM[0][1];
		tw = actual.w;
		th = actual.h;
		sx = actual.w;
		sy = dx;
		yi = dy;
		for (xi=0; xi < febtnx; xi++) {
			trect = (SDL_Rect){xi*tw+sx, 0, tw, th};
			SDL_BlitSurface (skin, &actual, window, &trect);
		}
		lw = ceil ((double)tw * sebtnx);
		trect = (SDL_Rect){xi*tw+sx, 0, tw, th};
		trect2 = (SDL_Rect){actual.x, actual.y, lw, th};
		SDL_BlitSurface (skin, &trect2, window, &trect);

		actual = wSM[2][1];
		tw = actual.w;
		th = actual.h;
		sx = dx+ actual.w;
		sy = dy+ h - th;
		yi = 0;
		for (xi=0; xi < febtnx; xi++) {
			trect = (SDL_Rect){xi*tw+sx, sy, tw, th};
			SDL_BlitSurface (skin, &actual, window, &trect);
		}
		lw = ceil ((double)tw * sebbnx);
		trect = (SDL_Rect){xi*tw+sx, sy, tw, th};
		trect2 = (SDL_Rect){actual.x, actual.y, lw, th};
		SDL_BlitSurface (skin, &trect2, window, &trect);
	}

	// Draw Corners
	actual = wSM[0][0];
	trect = (SDL_Rect){dx, dy, actual.w, actual.h};
	SDL_BlitSurface (skin, &actual, window, &trect);

	actual = wSM[2][0];
	trect = (SDL_Rect){dx, dy+ h - actual.h, actual.w, actual.h};
	SDL_BlitSurface (skin, &actual, window, &trect);

	actual = wSM[0][2];
	trect = (SDL_Rect){dx+ w - actual.w, dy, actual.w, actual.h};
	SDL_BlitSurface (skin, &actual, window, &trect);

	actual = wSM[2][2];
	trect = (SDL_Rect){dx+ w - actual.w, dy+ h - actual.h, actual.w, actual.h};
	SDL_BlitSurface (skin, &actual, window, &trect);

	SDL_UpdateRect (window, dx, dy, w, h);

	if (surface != NULL && drawDirectly != 1){
		int result = UI_DrawSurfaceIn (window, surface, wx, wy);
		SDL_FreeSurface (window);
		if (result != 0)
			CRITICAL (COMPLEX_ERROR_SDLUNEXPECTED+0x3, LANG_ERROR_POPUPCREATION);
		return NULL;
	}else
		return window;
}

void UI_SetState (UI_STATE *state) {
	if (defaultUI.state != NULL){
		defaultUI.state->Free ();
	}
	defaultUI.state = state;
	defaultUI.state->Create ();
	defaultUI.screenClicked = 0;
	UI_Draw ();
}

int BUTTON_ReadDesign (json_t *source, BUTTON_DESIGN *design) {
	json_t *__sub;
	if ((__sub = json_object_get (source, "skin")) == NULL)
		(*design).skin = bitmapResources.buttonSkin;
	else {
		(*design).skin = ETC_IMG_AlphedLoad (json_string_value (__sub), &RGBAFormat);
		if ((*design).skin == NULL)
			CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x8, LANG_ERROR_JSONCORRUPTED);
	}

	if ((__sub = json_object_get (source, "skin-flat")) != NULL)
		(*design).skinFlat = (json_number_value(__sub) == 0 ? 0 : 1);
	else
		(*design).skinFlat = defaultUI.buttonsSkinFlat;

	if (((__sub = json_object_get (source, "default")) == NULL) ||
			UI_MaskRead (__sub, (*design).normal) == 0)
		return 1;

	if (((__sub = json_object_get (source, "over")) == NULL) ||
			UI_MaskRead (__sub, (*design).over) == 0)
		return 2;

	if (((__sub = json_object_get (source, "clicked")) == NULL) ||
			UI_MaskRead (__sub, (*design).clicked) == 0)
		return 3;

	if ((__sub = json_object_get (source, "text-color")) == NULL){
		design->textColor = ETC_ReadColor(json_string_value (__sub));
	}else
		design->textColor = defaultUI.textColor;

	return 0;
}

void BUTTON_Draw (BUTTON *_button){
	BUTTON button = *_button;
	if (!button.enabled) {
		UI_DrawSkin (defaultUI.buttonDisabledMask, defaultUI.buttonNormal.skin,
			defaultUI.screen, button.x, button.y, button.w, button.h, defaultUI.buttonNormal.skinFlat, 0);
	}else if (button.design){
		if (_button == defaultUI.mouseOver && defaultUI.screenClicked) {
			UI_DrawSkin (button.design->clicked, button.design->skin,
				defaultUI.screen, button.x, button.y, button.w, button.h, button.design->skinFlat, 0);
		}else if (_button == defaultUI.mouseOver) {
			UI_DrawSkin (button.design->over, button.design->skin,
					defaultUI.screen, button.x, button.y, button.w, button.h, button.design->skinFlat, 0);
		}else {
			UI_DrawSkin (button.design->normal, button.design->skin,
					defaultUI.screen, button.x, button.y, button.w, button.h, button.design->skinFlat, 0);
		}
	}

	if ((button.symbol != NULL) && (button.label != NULL)) {
		int both_w, sx, sx2;
		SDL_Surface *lblText = TTF_RenderText_Blended(defaultUI.textFont, button.label, button.design->textColor);
		both_w = button.symbol->w + lblText->w;
		sx = button.x + ((button.w - both_w) / 2);
		sx2 = sx + button.symbol->w;
		SDL_Rect irect = (SDL_Rect){0, 0, (*button.symbol).w, (*button.symbol).h};
		SDL_Rect orect = (SDL_Rect){sx, button.y + ((button.h - (*button.symbol).h) / 2), (*button.symbol).w, (*button.symbol).h};
		SDL_BlitSurface (button.symbol, &irect, defaultUI.screen, &orect);
		irect = (SDL_Rect){0, 0, (*lblText).w, (*lblText).h};
		orect = (SDL_Rect){sx2, button.y + ((button.h - (*lblText).h) / 2), (*lblText).w, (*lblText).h};
		SDL_BlitSurface (lblText, &irect, defaultUI.screen, &orect);
		SDL_FreeSurface (lblText);
	}else if (button.symbol != NULL) {
		SDL_Rect irect = (SDL_Rect){0, 0, (*button.symbol).w, (*button.symbol).h};
		SDL_Rect orect = (SDL_Rect){button.x + ((button.w - (*button.symbol).w) / 2), button.y + ((button.h - (*button.symbol).h) / 2), (*button.symbol).w, (*button.symbol).h};
		SDL_BlitSurface (button.symbol, &irect, defaultUI.screen, &orect);
	}else if (button.label != NULL) {
		SDL_Surface *lblText;
		if (button.design == NULL)
			lblText = TTF_RenderText_Blended(defaultUI.textFont, button.label, defaultUI.textColor);
		else
			lblText = TTF_RenderText_Blended(defaultUI.textFont, button.label, button.design->textColor);
		SDL_Rect irect = (SDL_Rect){0, 0, (*lblText).w, (*lblText).h};
		SDL_Rect orect = (SDL_Rect){button.x + ((button.w - (*lblText).w) / 2), button.y + ((button.h - (*lblText).h) / 2), (*lblText).w, (*lblText).h};
		SDL_BlitSurface (lblText, &irect, defaultUI.screen, &orect);
		SDL_FreeSurface (lblText);
	}
}

void BUTTONS_Draw (BUTTON *array, int num){
	if (array == NULL || num < 1)
			return;
	int i;
	for (i=0; i<num; i++)
		BUTTON_Draw (&array[i]);
}

_Bool BUTTON_IsMouseOver (BUTTON button, int x, int y) {
	return (x > button.x &&
			x < (button.x + button.w) &&
			y > button.y &&
			y < (button.y + button.h) );
}

BUTTON* BUTTONS_MouseOver (BUTTON *array, int num, int x, int y) {
	if (array == NULL || num < 1)
		return NULL;
	int i;
	for (i=0; i < num; i++)
		if (BUTTON_IsMouseOver (array[i], x, y))
			return &(array[i]);
	return NULL;
}
