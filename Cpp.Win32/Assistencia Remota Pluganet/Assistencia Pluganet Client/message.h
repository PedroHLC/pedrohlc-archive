#pragma once

#include "stdafx.h"

HWND actualWID;
#define showalert showalertW
#define showalertf showalertfA
using namespace System;

void String2CharPtr(String ^orig, char *&out)
{
	unsigned int length = orig->Length;
	out = new char[length+1];
	for(unsigned int i=0;i<length;i++)
		out[i] = (char) orig[i];
	out[length] = '\0';
}

void showalertA(char* message){
	MessageBoxA(actualWID, message, "Assistencia Remota Pluganet", 0);
}

void showalertW(wchar_t* message){
	MessageBoxW(actualWID, message, L"Assistência Remota Pluganet", 0);
}

void showalertfA(char* messagebase, ...){
	char message[1024];
	va_list ap;
	va_start(ap, messagebase);
	vsprintf_s(message, messagebase, ap);
	va_end(ap);
	MessageBoxA(actualWID, message, "Assistencia Remota Pluganet", 0);
}