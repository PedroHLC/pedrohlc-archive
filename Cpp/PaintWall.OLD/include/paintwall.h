/*
 * paintwall.h
 *
 *  Created on: 29/01/2013
 *      Author: Pedro Henrique Lara Campos,
 *				Christian Ferraz Lemos de Sousa
 */

#ifndef PAINTWALL_H_
#define PAINTWALL_H_

// ++INCLUDES
#include <SDL.h>
#include <SDL_image.h>
#include <cJSON.h>


// ++ERRORS
//COMMONS_ERRORS = 0x0NNN, COMPLEX_ERRORS = 0xNZZZ
typedef enum {
	CLOSED = 0,
	ERROR_SDLINITFAIL = 0x1,
	ERROR_SDLNOMODE = 0x2,
	COMPLEX_ERROR_SDLUNEXPECTED = 0x1000,
	COMPLEX_ERROR_CONFIGUNEXPECTED = 0x2000
} ERROR;

void CRITICAL (ERROR code, char *extraMessage);

// ++Natives
int OS_RequestOpenFile (char** extensions, char* buffer);
int OS_RequestSaveFile (char** extensions, char* buffer);

// ++UI
typedef struct {
	SDL_Surface *screen,
		*interface,
		*activeCanvas,
		*subWindow;
	SDL_Rect windowSkinMask[3][3];
} UI;

UI defaultUI;
void UI_Create ();
void UI_Draw ();
void UI_Update (SDL_Event);
void UI_DrawWindow (SDL_Surface *surface, int w, int h);

typedef struct {
	SDL_Surface *windowSkin,
		*okButton;
} COMMON_BMP_RES;

COMMON_BMP_RES bitmapRespurces;


// ++ CANVAS
typedef struct {
	char *title;
	SDL_Surface data;
} CANVAS;

uint indexCanvas;
CANVAS* allCanvas;
uint numCanvas;

void CANVAS_Create (uint width, uint height);

// ++ CONFIGS

typedef struct {
	cJSON *ui;
} CONFIG;

CONFIG defaultConfig;

char* CONFIG_JSONFILE_UI;
char* JSON_UI;

long FILE_READ (char *buffer, char *fname); //buffer will be allocated inside the func. so use "free(buffer)"
long CONFIG_READ (char *buffer, char *fname, char *defaultConfig); //buffer will be allocated inside the func. so use "free(buffer)"
void CONST_LoadDefaultConfigurations ();

#endif /* PAINTWALL_H_ */
