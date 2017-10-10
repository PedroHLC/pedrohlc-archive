#include <windows.h>

// Variaveis globais
    int pre = 18000;
    int key_vol_down = 256, key_vol_up = 512, key_back = 8, key_next = 2, key_play = 4, key_stop = 1, key_speed = 128;
    HWND hWnd;
    HWND wmp_hWnd;
    UINT joypads_size;
    JOYINFOEX joypad_info; 

// Lê as configurações em um arquivo INI
int read_ini_int(char section[255], char key[255], char file[255]){
    int x=0;
    char y[255]="0";
    GetPrivateProfileString(section, key, "0", y, 255, file);
    x = atoi(y);
    return(x);
}  
void read_cfgs(){
     key_vol_down = read_ini_int("WMP_MM_JOY", "DOWN", ".\\Keys.ini");
     key_vol_up = read_ini_int("WMP_MM_JOY", "UP", ".\\Keys.ini");
     key_back = read_ini_int("WMP_MM_JOY", "BACK", ".\\Keys.ini");
     key_next = read_ini_int("WMP_MM_JOY", "NEXT", ".\\Keys.ini");
     key_play = read_ini_int("WMP_MM_JOY", "PLAY", ".\\Keys.ini");
     key_stop = read_ini_int("WMP_MM_JOY", "STOP", ".\\Keys.ini");
     key_speed = read_ini_int("WMP_MM_JOY", "SPEED", ".\\Keys.ini");
}

//Função principal
int main(){
    while(true){
      wmp_hWnd = FindWindow("WMPApp", NULL);
      if(wmp_hWnd > 0){
        joypads_size = joyGetNumDevs();
        if(joypads_size > 0){
           joypad_info.dwSize = 52;
           joypad_info.dwFlags = 255;
           if(joyGetPosEx(0, &joypad_info) != JOYERR_UNPLUGGED){
              if(joypad_info.dwButtons == key_back) SendMessage(wmp_hWnd, 273, 810 + pre, 0);
              else if(joypad_info.dwButtons == key_next) SendMessage(wmp_hWnd, 273, 811 + pre, 0);
              else if(joypad_info.dwButtons == key_play) SendMessage(wmp_hWnd, 273, 808 + pre, 0);
              else if(joypad_info.dwButtons == key_stop) SendMessage(wmp_hWnd, 273, 809 + pre, 0);
              else if(joypad_info.dwButtons == key_vol_up) SendMessage(wmp_hWnd, 273, 815 + pre, 0);
              else if(joypad_info.dwButtons == key_vol_down) SendMessage(wmp_hWnd, 273, 816 + pre, 0);
              else if(joypad_info.dwButtons == key_speed) SendMessage(wmp_hWnd, 273, 813 + pre, 0);
           }
        }
      }
      Sleep(200);
    }
    return(0);
}
