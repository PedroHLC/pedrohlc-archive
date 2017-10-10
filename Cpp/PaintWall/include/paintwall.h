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
#include <SDL_ttf.h>
#include <jansson.h>
#if defined(WIN32)
	#define _WIN32_WINNT 0x0500
	#include <windows.h>
#endif


// ++ERRORS
//COMMONS_ERRORS = 0x0NNN, COMPLEX_ERRORS = 0xNZZZ
typedef enum {
	CLOSED = 0,
	ERROR_SDLINITFAIL = 0x1,
	ERROR_SDLNOMODE = 0x2,
	ERROR_TTFLOADFAIL = 0x3,
	COMPLEX_ERROR_SDLUNEXPECTED = 0x1000,
	COMPLEX_ERROR_CONFIGUNEXPECTED = 0x2000
} PWERROR;

void CRITICAL (PWERROR code, char *extraMessage);

// ++Natives
int OS_RequestOpenFile (char** extensions, char* buffer);
int OS_RequestSaveFile (char** extensions, char* buffer);
_Bool OS_FixPath ();

#if defined(WIN32)
	#define MAIN int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
	#define MAIN int main (int argsnum, char ** args)
#endif

// ++ BUTTONS
typedef void (*BUTTON_fn_OnClick) (void);

typedef struct {
	SDL_Surface *skin;
	SDL_Rect normal[3][3], clicked[3][3], over[3][3];
	_Bool skinFlat;
	SDL_Color textColor;
} BUTTON_DESIGN;

typedef struct {
	int id, x,y,w,h;
	BUTTON_DESIGN *design;
	_Bool enabled;
	BUTTON_fn_OnClick OnClick;
	char *label;
	SDL_Surface *symbol;
} BUTTON;

void BUTTON_Draw (BUTTON*);
_Bool BUTTON_IsMouseOver (BUTTON, int x, int y);
int BUTTON_ReadDesign (json_t *source, BUTTON_DESIGN *design);

BUTTON* BUTTONS_MouseOver (BUTTON *array, int num, int x, int y);
void BUTTONS_Draw (BUTTON *array, int num);

// ++UI
typedef void (*UI_STATE_fn_Draw) ();
typedef void (*UI_STATE_fn_Create) ();
typedef void (*UI_STATE_fn_Free) ();
typedef _Bool (*UI_STATE_fn_IsMouseOver) (int x, int y);

typedef struct {
	BUTTON *buttons;
	int buttonsNum;
	UI_STATE_fn_Draw Draw;
	UI_STATE_fn_Create Create;
	UI_STATE_fn_Free Free;
	UI_STATE_fn_IsMouseOver IsMouseOver;
	void *data, *cache;
} UI_STATE;

typedef enum {
	COMMON_UI=0,
	WELCOME_UI,
	ALERT_UI,

	DEFAULT_UI_STATES_COUNT
} DEFAULT_UI_STATES;

typedef enum {
	OBJ_CANVAS=0,
	OBJ_BUTTON, OBJ_INTERFACE
} INTERATIVE_OBJS;

UI_STATE defaultUIStates[DEFAULT_UI_STATES_COUNT];

typedef struct {
	SDL_Surface *screen;
	SDL_Rect windowSkinMask[3][3], buttonDisabledMask[3][3];
	BUTTON_DESIGN buttonNormal,
		buttonPositive,
		buttonNegative;
	_Bool windowSkinFlat, buttonsSkinFlat, screenClicked;
	UI_STATE *state;
	char *fontName;
	TTF_Font *textFont, *titleFont;
	void *mouseOver;
	INTERATIVE_OBJS mouseOverType;
	SDL_Color textColor;
} UI;

UI defaultUI;
void UI_Create ();
void UI_Draw ();
void UI_Update (SDL_Event);
int UI_MaskRead (json_t *source, SDL_Rect wSM[3][3]);
SDL_Surface *UI_DrawSkin (SDL_Rect wSM[3][3], SDL_Surface *skin, SDL_Surface *surface, int wx, int wy, int w, int h, _Bool stretch, _Bool drawDirectly);
void UI_DrawWindow (SDL_Surface *surface, int wx, int wy, int w, int h);
SDL_Surface *UI_PrepareWindow (int w, int h);
int UI_DrawSurfaceIn (SDL_Surface *origin, SDL_Surface *target, int x, int y);
_Bool UI_IsMouseOver ();
void UI_SetState (UI_STATE *state);
_Bool UI_RenderText_Solid_MultiLine (TTF_Font *font, const char *originalText, SDL_Color fg, int bufferWidth, int bufferHeight, int x, int y);
_Bool UI_RenderText_Shaded_MultiLine (TTF_Font *font, const char *originalText, SDL_Color fg, SDL_Color bg, int bufferWidth, int bufferHeight, int x, int y);
_Bool UI_RenderText_Blended_MultiLine (TTF_Font *font, const char *originalText, SDL_Color fg, int bufferWidth, int bufferHeight, int x, int y);

void UI_STATES_CreateDefaults ();

#define UI_chR 0xFF000000
#define UI_chG 0x00FF0000
#define UI_chB 0x0000FF00
#define UI_chA 0x000000FF

SDL_PixelFormat RGBAFormat;

typedef struct {
	SDL_Surface *windowSkin;
	SDL_Surface *buttonSkin;
} COMMON_BMP_RES;

COMMON_BMP_RES bitmapResources;


// ++ CANVAS
typedef struct {
	char *title;
	SDL_Surface *data;
} CANVAS;

unsigned int indexCanvas;
CANVAS* allCanvas;
SDL_Surface *activeCanvas;
unsigned int numCanvas;

void CANVAS_Create (int width, int height);
void CANVAS_OnClick ();

// ++ CONFIGS
json_t *defaultConfig;
json_error_t defaultConfigLastError;

char* CONFIG_JSONFILE_UI;
char* JSON_UI;

//long CONFIG_READ (char *buffer, char *fname, char *defaultConfig); //buffer will be allocated inside the func. so use "free(buffer)"
void CONST_LoadDefaultConfigurations ();
void MAIN_ReadConfigs ();

// ++ ETC

long ETC_FileRead (char *buffer, const char *fname);
SDL_Rect ETC_ReadRect (SDL_Rect* rect, const char* data);
SDL_Color ETC_ReadColor (const char* source);
SDL_Surface *ETC_IMG_AlphedLoad (const char *fname, SDL_PixelFormat *format);
void MAIN_Close ();

#endif /* PAINTWALL_H_ */
