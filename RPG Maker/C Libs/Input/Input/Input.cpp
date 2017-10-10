// Input.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

//Por(By) PedroHLC
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Mmsystem.h>
#include <windows.h>

#define DLLEXTERN extern "C" __declspec (dllexport)

#define Qfalse ((VALUE)0)
#define Qtrue  ((VALUE)2)
#define Qnil   4
#define FIXNUM_FLAG 0x01
#define INT2FIX(i) ((VALUE)(((long)(i))<<1 | FIXNUM_FLAG))

typedef unsigned long VALUE;

struct RBasic{
    unsigned long flags;
    VALUE klass;
};

typedef struct{
    RBasic basic;
    long len;
    union {
		   long capa;
		   VALUE shared;
    } aux;
    VALUE *ptr;
} RArray;

typedef struct {
    struct RBasic basic;
    long len;
    char *ptr;
    union {
        long capa;
        VALUE shared;
    } aux;
} RString;

DLLEXTERN int getInput (long rbkeyboard_id,
						long rbkeys_id,
						long rboldkeys_id,
						long rbstates_id,
						long rbjoystick_id,
						long rbmousepos_id,
						long rbchar_id,
						long windowid){
		
		//Ruby Vars Links
		VALUE *rbkeyboard_arr = ((RArray*)(rbkeyboard_id << 1))->ptr;
		VALUE *rbkeys_arr = ((RArray*)(rbkeys_id << 1))->ptr;
		VALUE *rboldkeys_arr = ((RArray*)(rboldkeys_id << 1))->ptr;
		VALUE *rbstates_arr = ((RArray*)(rbstates_id << 1))->ptr;
		VALUE *rbjoysticks_arr = ((RArray*)(rbjoystick_id << 1))->ptr;
		VALUE *rbmousepos_arr = ((RArray*)(rbmousepos_id << 1))->ptr;
		RString *rbchar_string = ((RString*)(rbchar_id << 1));
		char *rbchar_chars = rbchar_string->ptr;
		long rchar_len = rbchar_string->len;

		//Char Vars
		bool settedchar = false;
		if(rchar_len >= 2){
			rbchar_chars[1] = 1;
			rbchar_chars[0] = 1;
		}

		//Keyboard Vars
		const BYTE state[256] = {NULL};
		GetKeyboardState((PBYTE)state);

		//Old Keys + Keys + Keyboard + Char (FOR)
		for (int keycode = 0; keycode < 256; keycode++){
			//Old Keys
			rboldkeys_arr[keycode] = (rbkeys_arr[keycode] == Qtrue ? Qtrue : Qfalse);

			//Keyboard
			rbkeyboard_arr[keycode] = (state[keycode] > 0 ? Qtrue : Qfalse);

			//Key
			rbkeys_arr[keycode] = ((GetAsyncKeyState(keycode) >> 8) ? Qtrue : Qfalse);

			//Char
			if(state[keycode] & !settedchar & (keycode >= 8) & (keycode <= 190)){
				UINT uScanCode = MapVirtualKey(keycode, MAPVK_VK_TO_VSC);
				WORD cresult[2];
				int cchBuff;
				int lresult = ToAscii(keycode, uScanCode, state, cresult, 0);
				if((lresult > 0) &
						(strlen((char*)cresult) > 0)){
					rbchar_chars[0] = cresult[0];
					if((lresult == 2) & (rchar_len >= 2))
						rbchar_chars[1] = cresult[1];
					else
						rbchar_chars[1] = '\0';
						rchar_len = 1;
				}
			}
		}
		
		//States
		rbstates_arr[0] = (GetKeyState(0x14)? Qtrue : Qfalse);
		rbstates_arr[1] = (GetKeyState(0x90)? Qtrue : Qfalse);
		rbstates_arr[2] = (GetKeyState(0x91)? Qtrue : Qfalse);

		//Mouse
		POINT input_MousePos;
		GetCursorPos(&input_MousePos);
		HWND hWnd = (HWND)windowid;
		ScreenToClient(hWnd, &input_MousePos);
		
		rbmousepos_arr[0] = INT2FIX(input_MousePos.x);
		rbmousepos_arr[1] = INT2FIX(input_MousePos.y);
		
		//Joystick
		if (joyGetNumDevs() > 0){
			JOYINFOEX input_JoypadInfo; 
			input_JoypadInfo.dwSize = 52;
			input_JoypadInfo.dwFlags = 255;
			if (joyGetPosEx(0, &input_JoypadInfo) != JOYERR_UNPLUGGED){
				rbjoysticks_arr[0] = INT2FIX(input_JoypadInfo.dwButtons);
				rbjoysticks_arr[1] = INT2FIX(input_JoypadInfo.dwXpos);
				rbjoysticks_arr[2] = INT2FIX(input_JoypadInfo.dwYpos);
				rbjoysticks_arr[3] = INT2FIX(input_JoypadInfo.dwPOV);
			}else{
				rbjoysticks_arr[0] = Qnil;
				rbjoysticks_arr[1] = Qnil;
				rbjoysticks_arr[2] = Qnil;
				rbjoysticks_arr[3] = Qnil;
			}
		}

		return 0;
}