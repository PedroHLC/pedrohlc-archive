#include <stdio.h>
#include <windows.h>

#define PRGetAValue(col) ((col >> 24) & 0xFF)
#define PRGetRValue(col) ((col >> 16) & 0xFF)
#define PRGetGValue(col) ((col >> 8) & 0xFF)
#define PRGetBValue(col) (col & 0xFF)

COLORREF PHLC_GetPixel(long x, long y){
      HWND hWnd = GetDesktopWindow();
      HDC hDC = GetWindowDC(hWnd);
      COLORREF c = GetPixel(hDC, x, y);
      ReleaseDC(hWnd, hDC);
      return(c);
}

void click_Button(long button){
  keybd_event(button, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void unclick_Button(long button){
  keybd_event(button, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
}

int main(){
    HWND windowsID;
    long wid_choose;
    int exit_choose;
    begin:
    puts("V\240 at\202 a janela e ent\306o pressione F9");
    while(true){
      if(GetAsyncKeyState(120) >> 8){
         windowsID = GetForegroundWindow();
         Sleep(800);
         break;
      }
    }
    //
    puts("V\240 at\202 a janela, pare o mouse sobre o circulo da mesa verde, e ent\306o pressione F9");
    POINT grePos;
    while(true){
      if(GetAsyncKeyState(120) >> 8){
         GetCursorPos(&grePos);
         Sleep(800);
         break;
      }
    }
    printf("%i,%i\n", grePos.x, grePos.y);
    puts("V\240 at\202 a janela, pare o mouse sobre o circulo da mesa vermelha, e ent\306o pressione F9");
    POINT redPos;
    while(true){
      if(GetAsyncKeyState(120) >> 8){
         GetCursorPos(&redPos);
         Sleep(800);
         break;
      }
    }
    printf("%i,%i\n", redPos.x, redPos.y);
    puts("V\240 at\202 a janela, pare o mouse sobre o circulo da mesa amarela, e ent\306o pressione F9");
    POINT yelPos;
    while(true){
      if(GetAsyncKeyState(120) >> 8){
         GetCursorPos(&yelPos);
         Sleep(800);
         break;
      }
    }
    printf("%i,%i\n", yelPos.x, yelPos.y);
    puts("V\240 at\202 a janela, pare o mouse sobre o circulo da mesa azul, e ent\306o pressione F9");
    POINT bluPos;
    while(true){
      if(GetAsyncKeyState(120) >> 8){
         GetCursorPos(&bluPos);
         Sleep(800);
         break;
      }
    }
    printf("%i,%i\n", bluPos.x, bluPos.y);
    puts("V\240 at\202 a janela, pare o mouse sobre o circulo da mesa laranja, e ent\306o pressione F9");
    POINT oraPos;
    while(true){
      if(GetAsyncKeyState(120) >> 8){
         GetCursorPos(&oraPos);
         Sleep(800);
         break;
      }
    }
    printf("%i,%i\n", oraPos.x, oraPos.y);
    puts("Pronto para jogar...");
    //
    COLORREF TempPixel;
    COLORREF TempPixel2;
    while(true){
      TempPixel2 = PHLC_GetPixel(grePos.x, grePos.y);
      TempPixel = PHLC_GetPixel(grePos.x, grePos.y + 1);
      if(TempPixel2 < 1 & PRGetRValue(TempPixel >= 0) & PRGetGValue(TempPixel >= 152) & PRGetBValue(TempPixel >= 0))
        click_Button(0x41);
      TempPixel2 = PHLC_GetPixel(redPos.x, redPos.y);
      TempPixel = PHLC_GetPixel(redPos.x, redPos.y + 1);
      if(TempPixel2 < 1 & PRGetRValue(TempPixel >= 255) & PRGetGValue(TempPixel >= 0) & PRGetBValue(TempPixel >= 0))
        click_Button(0x53);
      TempPixel2 = PHLC_GetPixel(yelPos.x, yelPos.y);
      TempPixel = PHLC_GetPixel(yelPos.x, yelPos.y + 1);
      if(TempPixel2 < 1 & PRGetRValue(TempPixel >= 244) & PRGetGValue(TempPixel >= 244) & PRGetBValue(TempPixel >= 0))
        click_Button(0x4A);
      TempPixel2 = PHLC_GetPixel(bluPos.x, bluPos.y);
      TempPixel = PHLC_GetPixel(bluPos.x, bluPos.y + 1);
      if(TempPixel2 < 1 & PRGetRValue(TempPixel >= 0) & PRGetGValue(TempPixel >= 152) & PRGetBValue(TempPixel >= 255))
        click_Button(0x4B);
      TempPixel2 = PHLC_GetPixel(oraPos.x, oraPos.y);
      TempPixel2 = PHLC_GetPixel(oraPos.x, oraPos.y + 1);
      if(TempPixel2 < 1 & PRGetRValue(TempPixel >= 255) & PRGetGValue(TempPixel >= 101) & PRGetBValue(TempPixel >= 0))
        click_Button(0x4C);
      
      Sleep(1);
      unclick_Button(0x41);
      unclick_Button(0x53);
      unclick_Button(0x4A);
      unclick_Button(0x4B);
      unclick_Button(0x4C);
      Sleep(1);
    }
    //
    return EXIT_SUCCESS;
}
