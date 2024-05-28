/**
 *	@file		RubyInterpreterDefines.h
 *
 *	@desc		Ruby��������һЩ���͡���ȵĶ����ļ�
 *
 *	@author		Syalon
 *
 *	@history	2009/07/05	����
 */

#ifndef __RUBY_INTERPRETER_DEFINES_H__
#define __RUBY_INTERPRETER_DEFINES_H__

#include <stdio.h>
#include <windows.h>

#include "Types.h"

typedef unsigned long VALUE;
typedef unsigned long ID;

typedef unsigned long st_data_t;

#ifdef __cplusplus
#	define ANYARGS ...
#else
#	define ANYARGS
#endif

typedef VALUE	(*RubyFunc)(ANYARGS);
typedef void	(*RubyDataFunc)(void*);

#define pid_t   int

#endif	//	__RUBY_INTERPRETER_DEFINES_H__