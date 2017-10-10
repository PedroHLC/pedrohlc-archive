/*
 * paintwall.c
 *
 *  Created on: 29/01/2013
 *      Author: Pedro Henrique Lara Campos,
 *				Christian Ferraz Lemos de Sousa
 */

#include <stdio.h>
#include <stdlib.h>
#include <paintwall.h>
#include "language.h"

void CRITICAL (PWERROR code, char *extraMessage) {
	if (extraMessage == 0)
		printf ("%s! (#%x)\n%s...\n", LANG_ERROR, code, LANG_EXITING);
	else
		printf ("%s (#%x): %s.\n%s...\n", LANG_ERROR, code, extraMessage, LANG_EXITING);
	exit (code);
}

/*long ETC_FileRead (char *buffer, char *fname) {
	FILE *file;
	file = fopen (fname, "r");

	if (file == NULL)
		return 0;

	fseek (file, 0, SEEK_END);
	long size = ftell (file);
	rewind (file);

	long readedn = fread (buffer, 1, size, file);

	fclose (file);
	return readedn;
}*/

void MAIN_ReadConfigs () {
	/*char *buffer = (char*) malloc(2048),
			*uiJSON_s;
	long num;

	num = CONFIG_READ (buffer, CONFIG_JSONFILE_UI, JSON_UI);
	uiJSON_s = (char*) malloc(num+1);
	memcpy (uiJSON_s, buffer, num+1);
	free (buffer);*/

	FILE *file = fopen (CONFIG_JSONFILE_UI, "rb");
	if (file == NULL ||
			NULL == (defaultConfig = json_loadf(file, 0, &defaultConfigLastError)))
		defaultConfig = json_loads (JSON_UI, strlen(JSON_UI), &defaultConfigLastError);

	if (defaultConfig == NULL)
			CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x1, LANG_ERROR_JSONCORRUPTED);
}

void MAIN_Quit () {
	SDL_Quit ();
	TTF_Quit ();
}

void MAIN_Close () {
	exit (0);
}

MAIN {
	// SO Needed
	OS_FixPath ();

	// Constantes
	CONST_LoadDefaultLanguage ();
	CONST_LoadDefaultConfigurations ();

	// Config
	MAIN_ReadConfigs ();

	// Lib Intializatation
	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		CRITICAL (ERROR_SDLINITFAIL, "Couldn't load VIDEO");
	atexit(MAIN_Quit);

	if (TTF_Init() != 0) {
		CRITICAL (ERROR_SDLINITFAIL, "Couldn't load TTF");
	}

	SDL_WM_SetCaption(LANG_APPTITLE, LANG_APPTITLE);

	UI_Create ();
	UI_Draw ();

	// Now, just play :D

	SDL_Event event;
	while(SDL_WaitEvent(&event)){
		UI_Update (event);
	}

	return 0;
}
