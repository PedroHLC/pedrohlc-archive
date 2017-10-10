#include "dll.h"
#include <windows.h>

extern "C" __declspec(dllexport) char* getKeyboard(){
    //Vars
    char fkeysState[255];
    //Keyboard
    for (int key = 0; key < 256; key++){
        if(GetAsyncKeyState(key) >> 8)
           fkeysState[key] = 0;
        else
           fkeysState[key] = 1;
    }
    //Return
    return(fkeysState);
}

extern "C" __declspec(dllexport) int* getMouse(HWND windowsID){
    //Vars
    POINT mousePos;
    int fmousePOS[1];
    //Cursor
    GetCursorPos(&mousePos);
    if(windowsID > 0) ScreenToClient(windowsID, &mousePos);
    fmousePOS[0] = mousePos.x;
    fmousePOS[1] = mousePos.y;
    free(&mousePos);
    //Return
    return(fmousePOS);
}

extern "C" __declspec(dllexport) int getJoypad(){
    //Temp Vars
    POINT mousePos;
    UINT joypadsSize;
    JOYINFOEX joypadInfo;
    int fjoypadKeys;
    //Joypad
    joypadsSize = joyGetNumDevs();
    if(joypadsSize > 0){
       free(&joypadsSize);
       joypadInfo.dwSize = 52;
       joypadInfo.dwFlags = 255;
       if(joyGetPosEx(0, &joypadInfo) != JOYERR_UNPLUGGED){
          fjoypadKeys = joypadInfo.dwButtons;
          free(&joypadInfo);
       }
    }
    //Return
    return(fjoypadKeys);
}
