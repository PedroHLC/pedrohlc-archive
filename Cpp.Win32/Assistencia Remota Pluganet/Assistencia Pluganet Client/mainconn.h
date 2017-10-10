#pragma once

#include "stdafx.h"
#include "message.h"
#include "md5.h"
using namespace System;

char* mainConnHost;
unsigned int mainConnPort = 7755;

SOCKET mainConnSocket = SOCKET_ERROR;
HANDLE mainConnThreadHandle;
DWORD mainConnThread;
void mainConnFunc(void);

unsigned int mainConnConnect(){

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD("2","0"), &wsaData)==0){
		if (LOBYTE(wsaData.wVersion) >= 2){
			mainConnSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (mainConnSocket==INVALID_SOCKET){
				showalert(L"Erro(3): Não foi possivel criar uma socket.\n");
				return 3;
			}else{
				sockaddr_in sa;
				sa.sin_family = AF_INET;
				sa.sin_port = htons(mainConnPort);

				hostent *remoteHost = gethostbyname("pc.pedrohlc.com");
				if (remoteHost == NULL) {
					DWORD dwError = WSAGetLastError();
					if (dwError != 0) {
						if (dwError == WSAHOST_NOT_FOUND) {
							showalert(L"Erro(4): O servidor não pode ser encontrado.\n");
							return 4;
						} else if (dwError == WSANO_DATA) {
							showalert(L"Erro(5): Causa de erro desconhecido.\n");
							return 5;
						}
					}
					showalert(L"Erro(6): Causa de erro desconhecido.\n");
					return 6;
				}
				if (remoteHost->h_addrtype == AF_INET) {
					int i = 0;
					while (remoteHost->h_addr_list[i] != 0) {
						sa.sin_addr.s_addr = *(u_long *) remoteHost->h_addr_list[i++];
					}
				}else{
					showalert(L"Erro(8): Causa de erro desconhecido.\n");
					return 8;
				}

				if(connect(mainConnSocket, (sockaddr*)(&sa), sizeof(sa)) == SOCKET_ERROR){
					showalert(L"Erro(7): Não foi possivel conectar a socket.\n");
					return 7;
				}else{
					return 0;
				}
			}
		}else{
		   showalert(L"Erro(2): Winsock 2.0 ou superior não encontrada.\n");
		   return 2;
	    }
	}else{
		showalert(L"Erro(1): Winsock não pode ser incilizada.\n");
		return 1;
	}
	return 0;
}

boolean mainConnLogin(String ^suser, String ^spass){
	char *user, *pass, msg[128];
	String2CharPtr(suser, user);
	String2CharPtr(spass, pass);
	
	MD5 md5;
	
	sprintf_s(msg, "l\1%s\1%s\n", user, md5.digestString(pass));

	if((user == NULL) | (pass == NULL))
		return false;

	send(mainConnSocket, msg, strlen(msg), 0);
	return true;
}

boolean mainConnSend(char* msg){
	send(mainConnSocket, msg, strlen(msg), 0);
	return true;
}

void chatSend(String ^sspeak){
	char *speak; String2CharPtr(sspeak, speak);
	char *message = (char*) malloc(sizeof(speak) + 4);
	ZeroMemory(message, sizeof(message));
	sprintf(message, "C\1%s\n", speak);
	mainConnSend(message);
}

void mainConnClose(){
	if (mainConnSocket != SOCKET_ERROR)
		closesocket(mainConnSocket);
}