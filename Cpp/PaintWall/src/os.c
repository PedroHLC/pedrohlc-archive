/*
 * os.c
 *
 *  Created on: 06/02/2013
 *      Author: Pedro Henrique Lara Campos,
 *				Christian Ferraz Lemos de Sousa
 */

#include <paintwall.h>
#include <limits.h>
#include <unistd.h>
#if defined(WIN32)
	#include <windows.h>
#endif

_Bool OS_FixPath (){
	char path[PATH_MAX], *dir_end;
#if defined(WIN32)
	HWND hwndConsole = (HWND) GetConsoleWindow();
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwndConsole, GWL_HINSTANCE);
	GetModuleFileNameA(hInstance, path, sizeof (path));
	dir_end = strrchr (path, '\\');
#else
	if (readlink ("/proc/self/exe", path, sizeof (path)) <= 0)
	    return 0;
	dir_end = strrchr (path, '/');
#endif
	if (dir_end == 0)
		return 0;
	dir_end++;
	*dir_end = '\0';

	if (chdir (path) < 0)
		return 0;
	return 1;
}
