/*
 * ui.c
 *
 *  Created on: 29/01/2013
 *      Author: Pedro Henrique Lara Campos,
 *				Christian Ferraz Lemos de Sousa
 */

#include <cJSON.h>
#include <math.h>
#include <stdlib.h>
#include <paintwall.h>
#include "language.h"

#define ddp 32

SDL_Rect readRect (SDL_Rect* rect, char* data){
	int x=0, y=0, width=0, height=0;
	sscanf (data, "%dx%d,%dx%d", &x, &y, &width, &height);
	rect[0].x = x; rect[0].y = y;
	rect[0].w = width; rect[0].h = height;
	return rect[0];
}

/*void printRects (SDL_Rect* rects, int num){
	int i;
	SDL_Rect rect;
	for(i=0; i<num; i++){
		rect = rects[i];
		printf ("%dx%d,%dx%d\n", rect.x, rect.y, rect.w, rect.h);
	}
}*/

void UI_Create () {
	cJSON *__temp,
			*__window = cJSON_GetObjectItem (defaultConfig.ui, "window");
	if (__window == NULL)
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x2, LANG_ERROR_JSONCORRUPTED);

	int windowWidth=0, windowHeight=0;
	if ((__temp = cJSON_GetObjectItem (__window, "width")) != NULL)
		windowWidth = __temp->valueint;
	if ((__temp = cJSON_GetObjectItem (__window, "height")) != NULL)
		windowHeight = __temp->valueint;

	Uint32 flags = SDL_RESIZABLE | SDL_HWSURFACE | SDL_DOUBLEBUF;
	SDL_Surface *tUI;
	if (windowWidth > 0 && windowHeight > 0 &&
			(tUI = SDL_SetVideoMode (windowWidth, windowHeight, ddp, flags)) != NULL)
		defaultUI.screen = tUI;
	else if ((tUI = SDL_SetVideoMode (1280, 720, ddp, flags)) != NULL)
		defaultUI.screen = tUI;
	else if ((tUI = SDL_SetVideoMode (800, 600, ddp, flags))	!= NULL)
		defaultUI.screen = tUI;
	else if ((tUI = SDL_SetVideoMode (640, 480, ddp, flags))	!= NULL)
		defaultUI.screen = tUI;
	else
		CRITICAL (ERROR_SDLNOMODE, LANG_ERROR_NOMODE);

	defaultUI.interface = SDL_CreateRGBSurface (SDL_HWSURFACE,
			tUI->w, tUI->h, ddp, 0, 0, 0, 0);
	defaultUI.subWindow = SDL_CreateRGBSurface (SDL_HWSURFACE,
				tUI->w, tUI->h, ddp, 0, 0, 0, 0);
	SDL_FillRect (defaultUI.subWindow, NULL, 0x000000);

	if(defaultUI.interface == NULL || defaultUI.subWindow == NULL)
		CRITICAL (COMPLEX_ERROR_SDLUNEXPECTED+0x1, LANG_ERROR_UICREATION);

	cJSON *__skinFile = cJSON_GetObjectItem (__window,"skin");
	if (__skinFile == NULL)
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x3, LANG_ERROR_JSONCORRUPTED);

	bitmapRespurces.windowSkin = IMG_Load (
			__skinFile->valuestring
			);
	if (bitmapRespurces.windowSkin == NULL)
			CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x4, LANG_ERROR_JSONCORRUPTED);


	cJSON *__windowPattern, *__windowMask;
	if((__windowPattern = cJSON_GetObjectItem (__window,"decoration-pattern")) != NULL) {
		int v = __windowPattern->valueint, xi, yi;
		for (xi=0; xi < 3; xi++){
			for (yi=0; yi < 3; yi++){
				 defaultUI.windowSkinMask[yi][xi] = (SDL_Rect){v * xi, v * yi, v, v};
			}
		}
	}else if((__windowMask = cJSON_GetObjectItem (__window,"decoration-mask")) != NULL) {
		readRect (&defaultUI.windowSkinMask[0][0],
				cJSON_GetObjectItem (__windowMask,"top-left")->valuestring);
		readRect (&defaultUI.windowSkinMask[0][1],
						cJSON_GetObjectItem (__windowMask,"top")->valuestring);
		readRect (&defaultUI.windowSkinMask[0][2],
						cJSON_GetObjectItem (__windowMask,"top-right")->valuestring);
		readRect (&defaultUI.windowSkinMask[1][0],
						cJSON_GetObjectItem (__windowMask,"left")->valuestring);
		readRect (&defaultUI.windowSkinMask[1][1],
						cJSON_GetObjectItem (__windowMask,"center")->valuestring);
		readRect (&defaultUI.windowSkinMask[1][2],
						cJSON_GetObjectItem (__windowMask,"right")->valuestring);
		readRect (&defaultUI.windowSkinMask[2][0],
						cJSON_GetObjectItem (__windowMask,"bottom-left")->valuestring);
		readRect (&defaultUI.windowSkinMask[2][1],
						cJSON_GetObjectItem (__windowMask,"bottom")->valuestring);
		readRect (&defaultUI.windowSkinMask[2][2],
						cJSON_GetObjectItem (__windowMask,"bottom-right")->valuestring);
	}else {
		CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x5, LANG_ERROR_JSONCORRUPTED);
	}
	//DEBUG: printRects (defaultUI.windowSkinMask, 9);
}

void UI_InterfaceDraw () {
	SDL_FillRect (defaultUI.interface, NULL, 0x000000);
	UI_DrawWindow (defaultUI.interface, 760, 590);
	SDL_UpdateRect (defaultUI.interface, 0, 0, 0, 0);
	SDL_BlitSurface(defaultUI.interface, NULL, defaultUI.screen, NULL);
}

void UI_Draw () {
	SDL_FillRect (defaultUI.screen, NULL, 0x000000);
	if (defaultUI.activeCanvas != NULL) {
		SDL_UpdateRect (defaultUI.activeCanvas, 0, 0, 0, 0);
		SDL_BlitSurface(defaultUI.activeCanvas, NULL, defaultUI.screen, NULL);
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
	switch (event.type) {
		case SDL_QUIT:
			exit (CLOSED);
	}
}

void UI_OnClick () {
	//TODO: was waited? //TODO: Add UI_OperationWaitedClick
	//TODO: was on interface? //TODO: Add UI_OnInterfaceClick
	//TODO: was on canvas? //TODO: Add UI_OnCanvasClick
	//TODO: was on nothing?
}

void UI_OnKeyPress () {
	//TODO: Check for ALL hotkeys :(
}

#define wSM defaultUI.windowSkinMask

void UI_DrawWindow (SDL_Surface *surface, int w, int h) {
	SDL_Surface *window  = SDL_CreateRGBSurface (SDL_SWSURFACE, w, h, ddp, 0, 0, 0, 0);
	if(window == NULL)
			CRITICAL (COMPLEX_ERROR_SDLUNEXPECTED+0x2, LANG_ERROR_POPUPCREATION);

	int x_centerw = (w - wSM[1][0].w) - wSM[1][2].w;
	int y_centery = (h - wSM[0][1].h) - wSM[2][1].h;

	//Center
	double ecnx = (double)x_centerw / (double)wSM[1][1].w,
		ecny = (double)y_centery / (double)wSM[1][1].h,
		fecnx = floor (ecnx),
		fecny = floor (ecny),
		secnx = ecnx - fecnx,
		secny = ecny - fecny;

	//Border-Left
	double eblny = (double)y_centery / (double)wSM[1][0].h,
		feblny = floor (eblny),
		seblny = eblny - feblny;

	//Border-Right
	double ebrny = (double)y_centery / (double)wSM[1][2].h,
		febrny = floor (ebrny),
		sebrny = ebrny - febrny;

	//Border-Top
	double ebtnx = (double)x_centerw / (double)wSM[0][1].w,
		febtnx = floor (ebtnx),
		sebtnx = ebtnx - febtnx;

	//Border-Bottom
	double ebbnx = (double)x_centerw / (double)wSM[2][1].w,
		febbnx = floor (ebbnx),
		sebbnx = ebbnx - febbnx;

	int xi, yi, tw, th, sx, sy;
	double lh, lw;
	SDL_Rect trect, trect2, actual;
	// Draw Center
	actual = wSM[1][1];
	tw = actual.w;
	th = actual.h;
	sx = wSM[0][0].w,
	sy = wSM[0][0].h;

	for (yi=0; yi < fecny; yi++)
		for (xi=0; xi < fecnx; xi++) {
			trect = (SDL_Rect){xi*tw+sx, yi*th+sy, tw, th};
			SDL_BlitSurface (bitmapRespurces.windowSkin, &actual, surface, &trect);
		}

	lh = ceil ((double)th * secny);
	trect2 = (SDL_Rect){actual.x, actual.y, tw, lh};
	for (xi=0; xi < fecnx; xi++) {
		trect = (SDL_Rect){xi*tw+sx, yi*th+sy, tw, lh};
		SDL_BlitSurface (bitmapRespurces.windowSkin, &trect2, surface, &trect);
	}

	lw = ceil ((double)tw * secnx);
	trect2 = (SDL_Rect){actual.x, actual.y, lw, th};
	for (yi=0; yi < fecny; yi++) {
		trect = (SDL_Rect){xi*tw+sx, yi*th+sy, lw, th};
		SDL_BlitSurface (bitmapRespurces.windowSkin, &trect2, surface, &trect);
	}

	trect = (SDL_Rect){xi*tw+sx, yi*th+sy, lw, lh};
	trect2 = (SDL_Rect){actual.x, actual.y, lw, lh};
	SDL_BlitSurface (bitmapRespurces.windowSkin, &trect2, surface, &trect);

	// Draw Borders
	actual = wSM[1][0];
	tw = actual.w;
	th = actual.h;
	sx = 0;
	//sy = sy;

	xi = 0;
	for (yi=0; yi < feblny; yi++){
		trect = (SDL_Rect){0, yi*th+sy, tw, th};
		SDL_BlitSurface (bitmapRespurces.windowSkin, &actual, surface, &trect);
	}
	lh = ceil((double)th * seblny);
	trect = (SDL_Rect){0, yi*th+sy, tw, lh};
	trect2 = (SDL_Rect){actual.x, actual.y, tw, lh};
	SDL_BlitSurface (bitmapRespurces.windowSkin, &trect2, surface, &trect);

	actual = wSM[1][2];
	tw = actual.w;
	th = actual.h;
	sx = w - tw;
	for (yi=0; yi < febrny; yi++){
		trect = (SDL_Rect){sx, yi*th+sy, tw, th};
		SDL_BlitSurface (bitmapRespurces.windowSkin, &actual, surface, &trect);
	}
	lh = ceil ((double)th * sebrny);
	trect = (SDL_Rect){sx, yi*th+sy, tw, lh};
	trect2 = (SDL_Rect){actual.x, actual.y, tw, lh};
	SDL_BlitSurface (bitmapRespurces.windowSkin, &trect2, surface, &trect);


	actual = wSM[0][1];
	tw = actual.w;
	th = actual.h;
	sx = actual.w;
	sy = 0;
	yi = 0;
	for (xi=0; xi < febtnx; xi++) {
		trect = (SDL_Rect){xi*tw+sx, 0, tw, th};
		SDL_BlitSurface (bitmapRespurces.windowSkin, &actual, surface, &trect);
	}
	lw = ceil ((double)tw * sebtnx);
	trect = (SDL_Rect){xi*tw+sx, 0, tw, th};
	trect2 = (SDL_Rect){actual.x, actual.y, lw, th};
	SDL_BlitSurface (bitmapRespurces.windowSkin, &trect2, surface, &trect);

	actual = wSM[2][1];
	tw = actual.w;
	th = actual.h;
	sx = actual.w;
	sy = h - th;
	yi = 0;
	for (xi=0; xi < febtnx; xi++) {
		trect = (SDL_Rect){xi*tw+sx, sy, tw, th};
		SDL_BlitSurface (bitmapRespurces.windowSkin, &actual, surface, &trect);
	}
	lw = ceil ((double)tw * sebbnx);
	trect = (SDL_Rect){xi*tw+sx, sy, tw, th};
	trect2 = (SDL_Rect){actual.x, actual.y, lw, th};
	SDL_BlitSurface (bitmapRespurces.windowSkin, &trect2, surface, &trect);

	// Draw Corners
	actual = wSM[0][0];
	trect = (SDL_Rect){0, 0, actual.w, actual.h};
	SDL_BlitSurface (bitmapRespurces.windowSkin, &actual, surface, &trect);

	actual = wSM[2][0];
	trect = (SDL_Rect){0, h - actual.h, actual.w, actual.h};
	SDL_BlitSurface (bitmapRespurces.windowSkin, &actual, surface, &trect);

	actual = wSM[0][2];
	trect = (SDL_Rect){w - actual.w, 0, actual.w, actual.h};
	SDL_BlitSurface (bitmapRespurces.windowSkin, &actual, surface, &trect);

	actual = wSM[2][2];
	trect = (SDL_Rect){w - actual.w, h - actual.h, actual.w, actual.h};
	SDL_BlitSurface (bitmapRespurces.windowSkin, &actual, surface, &trect);
}
