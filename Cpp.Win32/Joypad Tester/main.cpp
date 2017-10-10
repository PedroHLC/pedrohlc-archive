//Por PedroHLC;

#include <stdio.h>
#include <windows.h>

// Variaveis globais
    UINT joypads_size;
    JOYINFOEX joypad_info; 
    int joy_ID=0;

//Testa os joysticks
main(){
    joypads_size = joyGetNumDevs();
    if(joypads_size > 0){
       printf("Joypads founded: %i\n", joypads_size);
       while(true){
          joypad_info.dwSize = 52;
          joypad_info.dwFlags = 255;
          if(joyGetPosEx(0, &joypad_info) != JOYERR_UNPLUGGED){
             if(joypad_info.dwButtons > 0) printf("Keys pressed: %i\n", joypad_info.dwButtons);
          }
       }
       Sleep(200);
    }
}
