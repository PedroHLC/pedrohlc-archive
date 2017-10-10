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

void CRITICAL (ERROR code, char *extraMessage) {
	if (extraMessage == 0)
		printf ("%s! (#%x)\n%s...\n", LANG_ERROR, code, LANG_EXITING);
	else
		printf ("%s (#%x): %s.\n%s...\n", LANG_ERROR, code, extraMessage, LANG_EXITING);
	exit (code);
}

long FILE_READ (char *buffer, char *fname) {
	FILE *file;
	file = fopen (fname, "r");

	if (file == NULL)
		return 0;

	fseek (file, 0, SEEK_END);
	long size = ftell (file);
	rewind (file);

	//buffer = (char*)realloc (buffer, size * sizeof(char));
	long readedn = fread (buffer, 1, size, file);

	fclose (file);
	return readedn;
}

long CONFIG_READ (char *buffer, char *fname, char *defaultConfig) {
	long result;
	result = FILE_READ (buffer, fname);
	if (result > 0)
		return result;

	result = strlen(defaultConfig);
	//buffer = (char*)realloc (buffer, result * sizeof(char));
	strcpy(buffer, defaultConfig);

	return result * sizeof(char);
}

void READ_CONFIGS () {
	char *buffer = (char*) malloc(2048),
			*uiJSON_s;
	long num;

	num = CONFIG_READ (buffer, CONFIG_JSONFILE_UI, JSON_UI);
	uiJSON_s = (char*) malloc(num+1);
	memcpy (uiJSON_s, buffer, num+1);
	free (buffer);

	defaultConfig.ui = cJSON_Parse (uiJSON_s);
	if (defaultConfig.ui == NULL)
			CRITICAL (COMPLEX_ERROR_CONFIGUNEXPECTED+0x1, LANG_ERROR_JSONCORRUPTED);
}

int main (int argsnum, char ** args) {
	puts ("Loading...");

	// Constantes
	CONST_LoadDefaultLanguage ();
	CONST_LoadDefaultConfigurations ();

	// Config
	READ_CONFIGS ();

	// Lib Intializatation
	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		CRITICAL (ERROR_SDLINITFAIL, NULL);
	atexit(SDL_Quit);

	SDL_WM_SetCaption(LANG_APPTITLE, LANG_APPTITLE);

	UI_Create ();
	UI_Draw ();

	// Now, just play :D
	puts ("Ready!");

	SDL_Event event;
	while(SDL_WaitEvent(&event)){
		UI_Update (event);
	}

	return 0;
}
