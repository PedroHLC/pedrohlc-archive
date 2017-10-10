//Por PedroHLC
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

HWND hWnd = GetActiveWindow();
bool input_KeysState[255];
POINT input_MousePos;
UINT input_JoypadsSize;
JOYINFOEX input_JoypadInfo; 
DWORD input_JoypadKeys;

void input_keyboardUpdate(){
    for (int key = 0; key < 256; key++){
        input_KeysState[key] = false;
        if(GetAsyncKeyState(key) >> 8) input_KeysState[key] = true;
    }
}

void input_MouseUpdate(bool global){
    GetCursorPos(&input_MousePos);
    if(global == true) ScreenToClient(hWnd, &input_MousePos);
}

void input_JoypadUpdate(){
    input_JoypadsSize = joyGetNumDevs();
    if(input_JoypadsSize > 0){
       input_JoypadInfo.dwSize = 52;
       input_JoypadInfo.dwFlags = 255;
       if(joyGetPosEx(0, &input_JoypadInfo) != JOYERR_UNPLUGGED){
          input_JoypadKeys = input_JoypadInfo.dwButtons;
       }
    }
}

int test(){
    int key;
    input_keyboardUpdate();
    for (key = 0; key < 256; key++){ if(input_KeysState[key] == true) printf("Keyboard key pressed: %i\n", key); }
    input_MouseUpdate(false);
    //printf("Mouse pos: %i-%i\n", input_MousePos.x, input_MousePos.y);
    Sleep(100);
}

main(){
    while(true) test();
}
