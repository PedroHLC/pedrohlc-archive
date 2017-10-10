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

#ifndef CCOMPLEMENT_H_
#define CCOMPLEMENT_H_

//owcList

	/* Holds an array of elements
	 * (uint) ELEMNUMS: Numbers of elements in array
	 * (ulong) ELEMSSIZE: Size of all elements together
	 * (void*) ELEM: All elements together
	 */
	typedef struct owcList_ {
		unsigned int elemNums;
		unsigned long elemsSize;
		void **elems;
	} owcList;

	/* Creates a list
	 * returns (owcList) LIST
	 */
	//owcList owcList_create ();
	#define owcList_new (owcList){0, 0, (void**){0}}

	/* Get an element from a list
	 * (owcList*) LIST: The list to be used
	 * (uint) INDEX: Element index in list
	 * returns (void*) ELEM
	 */
	//void *owcList_getElem (owcList *list, unsigned int index);
	//#define owcList_elem(list, index) (void*)(( list ).elems[ index ])

	/* Add an element to some list
	 * (owcList*) LIST: The list to be used
	 * (void*) ELEM: The element to be added
	 * returns (uint) INDEX being:
	 * 	the index of ELEM on list
	 */
	extern unsigned int owcList_addElem (owcList *list, void *elem);

	/* Free the memory space allocated
	 * for an owcList, uses arguments:
	 * (owcList*) TARGET: The targeted list
	 */
	//extern void owcList_free (owcList *target);
	#define owcList_dispose(target) free(( target ).elems);

//owcError

	// Enumeration of known possible errors
	typedef enum {
		owcError_unexpected  = 0x0
	} owcError;

	// Raises an critical error
	extern void owcCritical (owcError error, unsigned short int occurence, char *message);

#endif /* CCOMPLEMENT_H_ */
