/**
    Copyright (C) 2013 Pedro Henrique Lara Campos

    This file is part of libOpenWalls.

    libOpenWalls is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your option) 
    any later version.

    libOpenWalls is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with libOpenWalls.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OW_EVENTS_H_
#define OW_EVENTS_H_

// Enumeration of all event types
typedef enum  {
	oweVideoResized,
	oweKeyPressed
} owEventType;

/* Holds an event type
 * (owEventType) TYPE: Event's type
 */
typedef struct {
	owEventType type;
} oweAnyEvent;

/* Calls a function when event happens
 * (void*) EVENT: The happened event
 */
typedef void (*oweListener_fn_call) (oweAnyEvent *event);

/* Waits an event to happen
 * (owEventType) TYPE: Event's type
 * (oweListener_fn_call) CALL: Function to be called when event happens
 */
typedef struct {
	owEventType type;
	oweListener_fn_call call;
} oweListener;

// TODO Add EXPLANTATION
extern int oweListener_staticCreate (owEventType type, oweListener_fn_call call);

// Initialize needed variables
extern void oweListeners_init ();

// TODO Add EXPLANTATION
extern void oweListener_free ();

// TODO Add EXPLANTATION
owcList oweListenersList;

// TODO Add EXPLANTATION
extern void owEvent_throw (oweAnyEvent *event);

/* Holds event type and data when video is resized
 * (owEventType) TYPE: Event's type
 * (uint) NEW_W: Video's width after resizing
 * (uint) NEW_H: Video's height after resizing
 */
typedef struct {
	owEventType type;
	unsigned int new_w, new_h;
} oweVideoResizedEvent;

// Enumeration of  key sources
typedef enum  {
	oweSourcePointer,
	oweSourceKeyboard,
	oweSourceSpecial,
	oweSourceJoystick
} oweKeySource;

/* Holds event type when key is pressed
 * (owEventType) TYPE: Event's type
 * (oweKeySource) SOURCE: Key's source
 * (uchar) KEY: Pressed key
 * (uint) X: Cursor horizontal position
 * (uint) Y: Cursor vertical position
 */
typedef struct {
	owEventType type;
	oweKeySource source;
	unsigned char key;
	unsigned int x, y;
} oweKeyPressedEvent;

#endif /* OW_EVENTS_H_ */
