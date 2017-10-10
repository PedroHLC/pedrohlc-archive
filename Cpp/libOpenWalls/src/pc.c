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

#include <stdlib.h>
#include <ow_core.h>
#include <ow_PC.h>
#include <ow_ccomplement.h>
#include <GL/freeglut.h>

void owPC_exit () {
	glutExit ();
}

void owPC_init (int *argc, char **argv) {
	glutInit(argc, argv);
	atexit (owPC_exit);
}

void owPCVideo_display (void *target) {
	glutSetWindow (((owPCVideo*)target)->window);

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity ();

	unsigned int surface_i;
	owcList *surfaces = &((owVideo*)target)->surfaces;
	owSurface *surface;

	double sx, sy, ex, ey, z;

	glEnable (owTextureType);
	for (surface_i=0; surface_i < surfaces->elemNums ; surface_i++)
		if ((surface = (owSurface*)(surfaces->elems[surface_i])) != 0) {
			glBindTexture (owTextureType, surface->output);
			//glEnable (GL_TEXTURE_RECTANGLE);
			//glPushMatrix();
			glBegin (GL_QUADS);
			sx = surface->x / (double)((owPCVideo*)target)->w * 2 - 1;
			sy = 1 - surface->y / (double)((owPCVideo*)target)->h * 2;
			ex = (surface->x + (double)surface->source->w) / (double)((owPCVideo*)target)->w * 2 - 1;
			ey = 1 - (surface->y + (double)surface->source->h) / (double)((owPCVideo*)target)->h * 2;
			z = ((owVideo*)target)->baseZ + surface->extraZ;
			glTexCoord2d(0.0,0.0); glVertex3f (sx, sy, z);
			glTexCoord2d(1.0,0.0); glVertex3f (ex, sy, z);
			glTexCoord2d(1.0,1.0); glVertex3f (ex, ey, z);
			glTexCoord2d(0.0,1.0); glVertex3f (sx, ey, z);
			glEnd ();
			//glPopMatrix();
			//printf ("Drawing a surface %i: %f,%f,%f,%f,%f!\n", surface->output, sx, sy, ex, ey, (float)z);
		}

	glDisable (owTextureType);
	if (!((owPCVideo*)target)->looping)
		glutMainLoopEvent ();
	glutSwapBuffers (); //TODO only when double-buffered
}

void owPCVideo_onReshape (int w, int h){
	glViewport (0, 0, w, h);
	owePCVideoResizedEvent eventData = (owePCVideoResizedEvent){
		oweVideoResized, w, h, glutGetWindow ()
	};
	owEvent_throw ((oweAnyEvent*)&eventData);
}

void owPCVideo_KeyboardCallback (unsigned char key, int x, int y){
	owePCKeyPressedEvent eventData = (owePCKeyPressedEvent){
		oweKeyPressed, oweSourceKeyboard, key, x, y, glutGetWindow ()
	};
	owEvent_throw ((oweAnyEvent*)&eventData);
}

owPCVideo owPCVideo_create (int w, int h, char *title, double baseZ) {
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (w, h);
	int resultWnd = glutCreateWindow (title);

	glutSetWindow (resultWnd);
	glutReshapeFunc (owPCVideo_onReshape);
	glutKeyboardFunc (owPCVideo_KeyboardCallback);

	glEnable (GL_DEPTH_TEST);
	glClearColor (0.0, 0.0, 0.0, 1.0);

	return (owPCVideo){baseZ, owcList_new, &owPCVideo_display, w, h, 0, 0, resultWnd};
}

void owPCVideo_setFullScreen (owPCVideo *target, _Bool state) {
	glutSetWindow (target->window);
	if (state) {
		glutFullScreen ();
	}else {
		glutReshapeWindow (target->w, target->h);
		//glutLeaveFullScreen ();
	}
	target->fullScreen = state;
}

void owPCVideo_destroy (owPCVideo *target) {
	glutDestroyWindow (target->window);
}

void owPCVideo_hear (owPCVideo *target) {
	glutSetWindow (target->window);
	glutMainLoopEvent ();
}

void owPCVideo_loop (owPCVideo *target) {
	glutSetWindow (target->window);
	glutMainLoop ();
}
