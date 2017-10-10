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
	LANG_ERROR_NOMODE = "PaintWall requires video resolution with at least 640x480, and 32 bytes of color";
	LANG_ERROR_UICREATION = "Failed to create UI Interface";
	LANG_ERROR_POPUPCREATION = "Failed to create UI Pop-Up";
	LANG_ERROR_MEMORYFAIL = "Failed to copy to memory";
	LANG_ERROR_JSONCORRUPTED = "Some configuration couldn't be loaded";
}

void CONST_LoadDefaultConfigurations (){
	CONFIG_JSONFILE_UI = "../res/ui.json";
	JSON_UI = "{\"window\":{\"file\":\"../res/skin.png\",\"decoration-pattern\":32}}";
}
