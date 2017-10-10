/*
 * language.h
 *
 *  Created on: 30/01/2013
 *      Author: Pedro Henrique Lara Campos,
 *				Christian Ferraz Lemos de Sousa
 */

#ifndef LANGUAGE_H_
#define LANGUAGE_H_

#include "uistates/ui_language.h"

char *LANG_APPTITLE,
	*LANG_EXITING,
	*LANG_ERROR,
	*LANG_ERROR_NOMODE,
	*LANG_ERROR_UICREATION,
	*LANG_ERROR_POPUPCREATION,
	*LANG_ERROR_MEMORYFAIL,
	*LANG_ERROR_JSONCORRUPTED,
	*LANG_ERROR_TTF_LOADFAIL,
	*LANG_ERROR_DETAILS
		;

void CONST_LoadDefaultLanguage ();

#endif /* LANGUAGE_H_ */
