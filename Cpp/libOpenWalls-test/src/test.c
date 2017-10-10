/**
    Copyright (C) 2013 Pedro Henrique Lara Campos

    This file is part of libOpenWalls-test.

    libOpenWalls-test is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your option) 
    any later version.

    libOpenWalls-test is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with libOpenWalls-test.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libOpenWalls/ow_ccomplement.h>
#include <libOpenWalls/ow_core.h>
#include <libOpenWalls/ow_events.h>
#include <libOpenWalls/ow_PC.h>

#define FALSE 0
#define TRUE 1

owPCVideo mainVideo;

void onVideoResize (oweAnyEvent *event) { //Prevent Stretch
	if (((owePCVideoResizedEvent*)event)->window == mainVideo.window){
		mainVideo.w = ((owePCVideoResizedEvent*)event)->new_w;
		mainVideo.h = ((owePCVideoResizedEvent*)event)->new_h;
		printf ("Screen resized to: %dx%d !\n", mainVideo.w, mainVideo.h);
		mainVideo.display (&mainVideo);
	}
}

void onKeyDown (oweAnyEvent *event_) {
	owePCKeyPressedEvent *event = (owePCKeyPressedEvent*)event_;
	if (event->window == mainVideo.window){
		if (event->key == 'q')
			exit (0);
		printf ("Key pressed: %c at %dx%d\n", event->key, event->x, event->y);
	}
}

int main (int argsnum, char **args) {
	// INICIA MÓDULOS NECESSÁRIOS
	oweListeners_init ();
	owPC_init (&argsnum, args);

	// TESTE DE VIDEO
	mainVideo = owPCVideo_create (640, 480, "WOOHOO!", 0);

	// TESTE DE SURFACE
	owPaint paint1 = owPaint_create (320, 240, TRUE);
	owPaint_fill (&paint1, 0xff0000ff);
	owSurface surface1 = owSurface_create (0, 0, -1, &paint1);
	free (paint1.pixels);//owPaint_dispose (paint1);

	owPaint paint2 = owPaint_create (340, 260, TRUE);
	owPaint_fill (&paint2, 0x0000ffff);
	owSurface surface2 = owSurface_create (0, 0, 0, &paint2);
	free (paint2.pixels);//owPaint_dispose (paint2);

	owcList_addElem (&mainVideo.surfaces, &surface1);
	owcList_addElem (&mainVideo.surfaces, &surface2);

	// TESTE DE EVENTUAIS
	oweListener_staticCreate (oweVideoResized, onVideoResize);
	oweListener_staticCreate (oweKeyPressed, onKeyDown);

	// OK Let's Play...
	printf ("Checkpoint: %d\n", glGetError());
	mainVideo.display (&mainVideo);
	owPCVideo_setFullScreen (&mainVideo, FALSE);
	while(1){
		surface2.x++;
		if (surface2.x >= (double)mainVideo.w){
			puts ("Restarting...");
			surface2.x = -(double)paint2.w;
		}
		mainVideo.display (&mainVideo);
	}


	// TESTE DE LIBERTAÇÃO DE RECURSOS
	owPCVideo_destroy (&mainVideo);


	// TESTE DE ERRO CRITICO
	owcCritical (0, 0, "Just testing libOpenWalls error handler!");

	return 0;
}
