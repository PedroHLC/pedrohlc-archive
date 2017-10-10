/* Replace "dll.h" with the name of your header */
#include "dll.h"
#include <windows.h>
#include <winsock2.h>

#define DLL_EXTERN extern "C" __declspec(dllexport)

DLL_EXTERN LPHOSTENT FAR brg_gethostbyname(const char *name){
           WSADATA wsaData;
           if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
              MessageBoxA(0, "FALHOU.1", "", 0);
           if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
              MessageBoxA(0, "FALHOU.2", "", 0);
           //WSACleanup();
           LPHOSTENT result = gethostbyname(name);
           if (!result)
              MessageBoxA(0, "FALHOU.3", "", 0);
           return result;
}
