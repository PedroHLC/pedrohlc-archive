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

#ifndef OW_PC_H_
#define OW_PC_H_

#include "ow_core.h"
#include "ow_events.h"

/* Connects surfaces to PC's video outputs
 * (int) BASEZ: Initial Z position of all surfaces
 * (owCList) SURFACES: owCList with all surfaces
 * (owVideo_fn_display) DISPLAY: Function that draw surfaces
 * (int) W: Screen width in pixels
 * (int) H: Screen height in pixels
 * (_Bool) FULLSCREEN: Is video full screen?
 * (_Bool) FULLSCREEN: Is video looping?
 * (int) WINDOW: Window identification
 */
typedef struct {
	double baseZ;
	owcList surfaces;
	owVideo_fn_display display;
	int w, h;
	_Bool fullScreen, looping;
	int window;
} owPCVideo;

/* Sets the full screen state of a PC video
 * (owPCVideo*) TARGET: The targeted video
 * (_Bool) STATE: New full screen state
 * (_Bool) FILLDISP: Will video fill displays?
 */
extern void owPCVideo_setFullScreen (owPCVideo *target, _Bool state);

/* Hear window
 * (owPCVideo*) TARGET: The targeted video
 * - When not looping owPCVideo generic "display" calls this automatically
 */
extern void owPCVideo_hear (owPCVideo *target);

/* Create PC's video output
 * (owPCVideo) TARGET: The targeted video
 * (_Bool) SHOW: Will window be showed or hided?
 */
extern owPCVideo owPCVideo_create (int w, int h, char *title, double baseZ);

/* Destroy and free a PC's video output
 * (owPCVideo) TARGET: The targeted video
 */
extern void owPCVideo_destroy (owPCVideo *target);

/* Puts video in loop
 * (owPCVideo) TARGET: The targeted video
 */
extern void owPCVideo_loop (owPCVideo *target);

/* Initialize owPC requirements
 * (int*) ARGC: Pointer to number of arguments
 * (char**) ARGV: Arguments
 */
extern void owPC_init (int *argc, char **argv);

/* Holds event type and data when video is resized
 * (owEventType) TYPE: Event's type
 * (uint) OLD_W: Video's width before resizing
 * (uint) OLD_H: Video's height before resizing
 * (uint) NEW_W: Video's width after resizing
 * (uint) NEW_H: Video's height after resizing
 * (int) WINDOW: Window identification
 */
typedef struct {
	owEventType type;
	unsigned int new_w, new_h;
	int window;
} owePCVideoResizedEvent;

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
	int window;
} owePCKeyPressedEvent;

#endif /* OW_PC_H_ */
