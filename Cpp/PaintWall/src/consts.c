/*
 * consts.c
 *
 *  Created on: 31/01/2013
 *      Author: Pedro Henrique Lara Campos,
 *				Christian Ferraz Lemos de Sousa
 */

#include <paintwall.h>
#include "language.h"

void CONST_LoadDefaultLanguage (){
	LANG_APPTITLE = "PaintWall";
	LANG_EXITING = "Exiting";
	LANG_ERROR = "Error occurred";
	LANG_ERROR_DETAILS = "Error Details:";
	LANG_ERROR_NOMODE = "PaintWall requires video resolution with at least 640x480, and 32 bytes of color";
	LANG_ERROR_UICREATION = "Failed to create UI Interface";
	LANG_ERROR_POPUPCREATION = "Failed to create UI Pop-Up";
	LANG_ERROR_MEMORYFAIL = "Failed to copy to memory";
	LANG_ERROR_JSONCORRUPTED = "Some configuration couldn't be loaded";
	LANG_ERROR_TTF_LOADFAIL = "Some font couldn't be loaded",

	LANG_UI_OK ="OK";
	LANG_UI_CANCEL = "Cancel",
	LANG_UI_QUIT = "Quit",
	LANG_UI_WELCOME = "Welcome!",
	LANG_UI_WELCOME_MSG = "Thanks for testing this pre-alpha\nversion of PaintWall.\nHey, look! I've added multi-line! (*-*)\n\nBut... The next screen is not ready yet.\n";
}

const char* const_JSON_UI = "";

void CONST_LoadDefaultConfigurations (){
	CONFIG_JSONFILE_UI = "../data/cfg/ui.json";
	JSON_UI = (char*)const_JSON_UI; //TODO: Add content
}
