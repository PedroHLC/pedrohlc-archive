/**
 *	@file		RGSS102JEx.cpp
 *
 *	@desc		RGSS102J补丁之 扩展库 实现文件
 *
 *	@author		Syalon
 *
 *	@history	2009/07/04	初版
 */

#include "RGSS102JEx.h"
#include "RubyInterpreter.h"

#include <windows.h>

#ifdef __cplusplus
extern "C"
{
#endif	//	__cplusplus

void Init_win32ole();

#ifdef __cplusplus
}
#endif	//	__cplusplus

VALUE dm_raise(VALUE)
{
	rb_raise(rb_eRuntimeError, "test raise:%d", 7);
	return 4;
}

VALUE dm_text_size(VALUE)
{
	MessageBoxA(NULL, "will get text_size", "title", 0);
	return 4;
}

void Init_RGSS102JEx()
{
	VALUE cBitmapEx = rb_define_class("BitmapEx", rb_cObject);

 	rb_define_method(cBitmapEx, "text_size", (RubyFunc)dm_text_size, 0);
	rb_define_method(cBitmapEx, "raise", (RubyFunc)dm_raise, 0);

// 	rb_raise(rb_eException, "%s %d", "test error:", 5);

	Init_win32ole();
}