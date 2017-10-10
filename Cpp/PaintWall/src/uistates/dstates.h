/*
 * dstates.h
 *
 *  Created on: 04/02/2013
 *      Author: Pedro Henrique Lara Campos,
 *				Christian Ferraz Lemos de Sousa
 */

#ifndef DSTATES_H_
#define DSTATES_H_

// WELCOME
void UI_WELCOME_ClickOK ();
void UI_WELCOME_Draw ();
void UI_WELCOME_Create ();
void UI_WELCOME_Free ();

// COMMON
void UI_COMMON_Draw ();
void UI_COMMON_Create ();
void UI_COMMON_Free ();

// YES!
#define UI_STATES_Initialize(prefix) (UI_STATE) {NULL, 0, &( prefix##_Draw ), &( prefix##_Create ), &( prefix##_Free ), NULL, NULL, NULL}

#endif /* DSTATES_H_ */
