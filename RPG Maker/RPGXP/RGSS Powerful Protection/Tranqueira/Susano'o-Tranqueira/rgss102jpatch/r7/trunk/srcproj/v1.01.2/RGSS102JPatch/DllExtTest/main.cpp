
#include "../RGSS102JPatch/Source/RubyInterpreter.h"
#include <windows.h>

#ifdef _DEBUG
#pragma comment(lib, "../debug/RGSS102JPatch.lib")
#else
#pragma comment(lib, "../release/RGSS102JPatch.lib")
#endif	//	_DEBUG

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}

VALUE dm_func1(VALUE)
{
	MessageBoxA(NULL, "func1 from dll", "", 0);
	return 4;
}

extern "C" __declspec(dllexport)  void Init_DllExtTest()
{
	VALUE cClassFromDll = rb_define_class("ClassFromDll", 0);

 	rb_define_method(cClassFromDll, "func1", (RubyFunc)dm_func1, 0);
}