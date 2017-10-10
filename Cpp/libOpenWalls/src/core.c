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
#include <string.h>
#include <GL/gl.h>

owPaint owPaint_create (unsigned int w, unsigned int h, _Bool alpha) {
	return (owPaint) {
		w, h, alpha,
		malloc (w * h * (alpha ? sizeof(owRGBAColor) : sizeof(owRGBColor)))
	};
}

void owPaint_fill (owPaint *target, owRGBAColor color) {
	unsigned int colorSz = (target->alpha ? sizeof(owRGBAColor) : sizeof(owRGBColor));
	void *end = (void*)(target->pixels + (target->w * target->h * colorSz));
	void *pixel;
	for (pixel = target->pixels; pixel < end; pixel += colorSz)
		memcpy(pixel, &color, colorSz);
}

void owPaint_fillRect (owPaint *target, owRect rect, owRGBAColor color) {
	int colorSz = (target->alpha ? sizeof(owRGBAColor) : sizeof(owRGBColor));
	int *line = 0;
	void *pixels = target->pixels;
	int a, b;
	for (a = rect.y; a < rect.h; a++){
		line = (void*)(a * target->w * colorSz);
		for (b = rect.x; rect.w; b++){
			memcpy((void*)((int)pixels + line + (b * colorSz)),
					&color, colorSz);

		}
	}
}

owSurface owSurface_create (double x, double y, double extraZ, owPaint *source) {
	//TODO Put alpha variable to really make difference...
	owTexture output;
	glGenTextures (1, &output);
	glBindTexture (owTextureType, output);
	glTexImage2D (owTextureType, 0, (source->alpha? 4 : 3), source->w, source->h, 0,
			(source->alpha? GL_RGBA : GL_RGB), GL_UNSIGNED_INT_8_8_8_8,
			source->pixels );
	glTexParameteri(owTextureType,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(owTextureType,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	return (owSurface){
		x, y, source, output, extraZ
	};
}

void owSurface_update (owSurface *target) {
	glBindTexture (owTextureType, target->output);
	glTexImage2D (owTextureType, 0, (target->source->alpha? 4 : 3), target->source->w, target->source->h, 0,
			(target->source->alpha? GL_RGBA : GL_RGB), GL_UNSIGNED_INT_8_8_8_8,
			target->source->pixels );
}

void owSurface_free (owSurface *target) {
	glDeleteTextures (1, &target->output);
}

void owEvent_throw (oweAnyEvent *event) {
	int i;
	if(oweListenersList.elemNums < 0)
		return;
	oweListener *elem;
	for (i=0; i<oweListenersList.elemNums; i++)
		if((elem = (oweListener*)oweListenersList.elems[i]) != 0)
			if (elem->type == event->type){
				elem->call(event);
			}
}

void oweListeners_init () {
	oweListenersList = owcList_new;
}

int oweListener_staticCreate (owEventType type, oweListener_fn_call call) {
	oweListener *listener = (oweListener*) malloc (sizeof(oweListener));
	listener->type = type;
	listener->call = call;
	return owcList_addElem (&oweListenersList, (void*)listener);
}

void oweListeners_free () {
	int i;
	if(oweListenersList.elemNums < 0)
		return;
	void *elem;
	for (i=0; i<oweListenersList.elemNums; i++)
		if((elem = oweListenersList.elems[i]) != 0)
			free (elem);
}
