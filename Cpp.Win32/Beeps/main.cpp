#include <stdio.h>
#include <conio.h>
#include <windows.h>

using namespace std;

int pianin()
{
    int i=100, dur=300;
    while(true){
      printf("%iHz - %iHz\n", 33 * i, 62 *i);
      Beep(33 * i, dur);
      Beep(37 * i, dur);
      Beep(41 * i, dur);
      Beep(44 * i, dur);
      Beep(49 * i, dur);
      Beep(55 * i, dur);
      Beep(62 * i, dur*2);
      Beep(55 * i, dur);
      Beep(49 * i, dur);
      Beep(44 * i, dur);
      Beep(41 * i, dur);
      Beep(37 * i, dur);
      Beep(33 * i, dur);
      i += 1;
    }
    return(0);
}

int todas()
{
    int freq;
    for(freq=0; freq < 99999; freq++){
        printf("%i\n", freq * 10);
        Beep(freq * 10, 220);
    }
    return(0);
}

int harryp()
{
    int fix=1, dur=600;
    while(true){
      Beep(330*  fix, dur);
      Sleep(50);
      Beep(440* fix, dur);
      Sleep(50);
      Beep(523* fix, dur);
      Sleep(50);
      Beep(494* fix, dur);
      Sleep(50);
      Beep(440* fix, dur);
      Sleep(50);
      Beep(659* fix, dur);
      Sleep(50);
      Beep(587* fix, dur);
      Sleep(50);
      Beep(494* fix, dur);
      Sleep(500);
      Beep(440* fix, dur);
      Sleep(50);
      Beep(523* fix, dur);
      Sleep(50);
      Beep(494* fix, dur);
      Sleep(50);
      Beep(440* fix, dur);
      Sleep(50);
      Beep(523* fix, dur);
      Sleep(50);
      Beep(330* fix, dur);
      getch();
    }
    return(0);
}

int cucaracha()
{
    int fix=0, dur=300;
    while(true){
      for(int i=0; i < 2; i++){
        for(int i2=0; i2 < 2; i2++){
          Beep(262+  fix, dur);
          Sleep(50);
        }
        Sleep(20);
        Beep(262+  fix, dur);
        Sleep(50);
        Beep(349+ fix, dur);
        Sleep(20);
        Beep(440+ fix, dur);
        Sleep(300);
      }
      getch();
    }
    return(0);
}

int main()
{
    return cucaracha();//harryp();
}
