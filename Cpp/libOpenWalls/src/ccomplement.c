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


#include <ow_ccomplement.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int owcList_addElem (owcList *list, void *elem) {
	//unsigned long oldElemsSize = list->elemsSize;
	list->elemsSize += sizeof(void*);

	//void **oldElems = list->elems;
	void **newElems = (void**) realloc (list->elems, list->elemsSize);

	//*(newElems + oldElemsSize) = elem;
	newElems[list->elemNums] = elem;

	//free (oldElems);
	list->elems = newElems;
	return list->elemNums++;
}

void owcList_free (owcList *target) {
	free (target->elems);
}

void owcCritical (owcError error, unsigned short int occurence, char *message) {
	printf ("ERROR (#%x.%x): %s\nExiting...\n", error, occurence, message);

	exit (error);
}
