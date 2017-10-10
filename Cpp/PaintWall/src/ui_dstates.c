/*
 * ui_2.c
 *
 *  Created on: 03/02/2013
 *      Author: Pedro Henrique Lara Campos,
 *				Christian Ferraz Lemos de Sousa
 */

#include <paintwall.h>
#include "language.h"
#include "uistates/dstates.h"

void UI_STATES_CreateDefaults () {
	defaultUIStates[WELCOME_UI] = UI_STATES_Initialize (UI_WELCOME);
	defaultUIStates[COMMON_UI] = UI_STATES_Initialize (UI_COMMON);

	UI_SetState (&defaultUIStates[WELCOME_UI]);
}
