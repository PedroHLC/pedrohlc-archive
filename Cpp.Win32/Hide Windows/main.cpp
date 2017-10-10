#include <stdio.h>
#include <windows.h>

int main(){
    HWND windowsID;
    long wid_choose;
    int exit_choose;
    begin:
    printf("Insira a WID da janela que deseja controlar(0: para pesquisar): ");
    scanf("%i", &wid_choose);
    if(wid_choose == 0){
      puts("V\240 at\202 a janela e ent\306o pressione F9");
      while(true){
        if(GetAsyncKeyState(120) >> 8){
           windowsID = GetForegroundWindow();
           printf("Sua WID \202: %i\n", windowsID);
           break;
        }
      }
    }else windowsID = (HWND)(LONG_PTR)wid_choose;
    while(true){
      printf("Digite 1 para mostrar, 0 para esconder, 3 para sair: ");
      scanf("%i", &exit_choose);
      if(exit_choose==0) SetWindowPos(windowsID, 0, 0, 0, 0, 0, 0x0080);
      else if(exit_choose==1) SetWindowPos(windowsID, 0, 0, 0, GetSystemMetrics(0),GetSystemMetrics(1), 0x0040);
      else if(exit_choose==2) {system("cls"); goto begin;}
      else if(exit_choose==3) break;
    }
    return EXIT_SUCCESS;
}
