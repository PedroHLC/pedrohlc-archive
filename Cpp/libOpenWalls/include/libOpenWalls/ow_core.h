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

#ifndef CORE_H_
#define CORE_H_

#include <GL/gl.h>
#include "ow_ccomplement.h"
#include "ow_events.h"

// 3 pixels - RGB
typedef unsigned short int owRGBColor;

// 4 pixels - RGBA
typedef unsigned int owRGBAColor;

/* owRect
 * x = Rectangle Position X (Horizontal)
 * y = Rectangle Position Y (Vertical)
 * w = Rectangle Width
 * h = Rectangle Height
 */
typedef struct {
	int x, y;
	unsigned int w, h;
} owRect;

// Graphics card texture identification
typedef GLuint owTexture;
#define owTextureType GL_TEXTURE_RECTANGLE

//owPaint

	/* Holds manipulable pixels
	 * (uint) W: Paint width in pixels
	 * (uint) H: Paint height in pixels
	 * (_Bool) ALPHA: When TRUE uses RGBA instead of RGB
	 * (void*) PIXELS: Each pixel color respectively
	 * - After creation, W and H shouldn't be changed
	 */
	typedef struct {
		unsigned int w, h; //NEVER SHOULD BE CHANGED
		_Bool alpha;
		void *pixels;
	} owPaint;

	/* Create and return a owPaint, uses arguments:
	 * (uint) W: Paint width in pixels
	 * (uint) H: Paint height in pixels
	 * (_Bool) ALPHA: When TRUE uses RGBA instead of RGB
	 * returns (owPaint) PAINTING
	 */
	extern owPaint owPaint_create (unsigned int w, unsigned int h, _Bool alpha);

	/* Fill an owPaint, uses arguments:
	 * (owPaint*) TARGET: The targeted painting
	 * (owRGBAColor) COLOR: Color to be used
	 */
	extern void owPaint_fill (owPaint *target, owRGBAColor color);

	/* Fill an owPaint, uses arguments:
	 * (owPaint*) TARGET: The targeted painting
	 * (owRect) RECT: Selection to be filled
	 * (owRGBAColor) COLOR: Color to be used
	 */
	extern void owPaint_fillRect (owPaint *target, owRect rect, owRGBAColor color);

	/* Free the memory space allocated
	 * for an owPaint, uses arguments:
	 * (owPaint*) TARGET: The targeted painting
	 */
	//void owPaint_free (owPaint *target);
	#define owPaint_dispose(target) free(( target ).pixels);

//owSurface

	/* Connects a painting to a graphic texture
	 * (double) X: Surface horizontal position in pixels
	 * (double) Y: Surface vertical position in pixels
	 * (owPaint*) SOURCE: Pixels and size source
	 * (owTexture) OUTPUT: ID from output texture
	 * (double) EXTRAZ: Surface additional Z Position
	 * - After creation, SOURCE shouldn't be changed
	 * - If you want to create a static surface,
	 * 	create it, than change SOURCE to NULL
	 * 	and never update it again.
	 */
	typedef struct {
		double x, y;
		owPaint *source;
		owTexture output;
		double extraZ;
	} owSurface;

	/* Create and return a owSurface, uses arguments:
	 * (double) X: Surface horizontal position in pixels
	 * (double) Y: Surface vertical position in pixels
	 * (double) EXTRAZ: Surface additional Z Position
	 * (owPaint*) SOURCE: Pixels and size source
	 * returns (owSurface) SURFACE
	 * - If you plan to not update the surface, you can free the painting
	 */
	extern owSurface owSurface_create (double x, double y, double extraZ, owPaint *source);

	/* Updates a surface by gathering new pixels from source
	 * and inserting then on it's texture, uses arguments:
	 * (owSurface*) TARGET: The targeted surface
	 */
	extern void owSurface_update (owSurface *target);

	/* Free the memory space allocated
	 * for an owSurface, uses arguments:
	 * (owSurface*) TARGET: The targeted surface
	 */
	extern void owSurface_free (owSurface *target);

// owVideo

	/* Display surfaces in video output
	 * (void*) TARGET: The targeted video
	 */
	typedef void (*owVideo_fn_display) (void *target);

	/* Connects surfaces to video outputs
	 * (int) BASEZ: Initial Z position of all surfaces
	 * (owCList) SURFACES: owCList with all surfaces
	 * (owVideo_fn_display) DISPLAY: Function that draw surfaces
	 */
	typedef struct {
		double baseZ;
		owcList surfaces;
		owVideo_fn_display display;
	} owVideo;
#endif /* CORE_H_ */
