#include "stdafx.h"
/* 
	Servidor em C++
	Criado por PedroHLC
	Leia o arquivo "Leia-me.txt"
	Desculpa pela bagunça, queria algo que funcionasse bem e me esqueci de organizar
*/
#define XPCOMPATIBILITY //Comente para usar Ws2tcpip (Apenas suportado por Vista, Win2008 e superiores)
//#define serverappver "0.2"
//char crossdomain[] = "<?xml version=\"1.0\"?>\n<cross-domain-policy xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.adobe.com/xml/schemas/PolicyFileSocket.xsd\">\n<allow-access-from domain=\"*\" to-ports=\"*\" secure=\"false\" />\n<site-control permitted-cross-domain-policies=\"all\" />\n</cross-domain-policy>\n\0";

#include <conio.h>
#include <string>
#ifdef XPCOMPATIBILITY
	#include <WinSock.h>
#else
	#include <Ws2tcpip.h>
#endif
#include <mysql.h>

#define msgs_maxsize 128

SOCKET hSocket;
FILE* pDebugFile;
bool exit_cmd, printdebug, nogetch;
char host_addr[15],	mysql_addr[15], mysql_user[65], mysql_pass[65], mysql_database[65];
int host_port, connect_id, host_maxuser, host_socktype, mysql_cfgport;
HANDLE hSLoopThread;
DWORD dwSLoopThread;
LPVOID pSLoopFunc, pCLientFunc;

char finish_getchmsg[]="Pressione ENTER para finalizar o aplicativo";
void finish(){
	if(!nogetch){
		puts(finish_getchmsg);
		_getch();
	}
    exit(0);
}

int read_inii(char*, char*, char*, const int);
void debug_printf(char*, ...);
void sendall(int, char*, ...);
bool findmeadesker(int);
char* getname(int);

#include "simplemysql.hpp"
SimpleMysql smysql;

class Client;
Client* client_list;
#include "client.cpp"

void debug_printf(char* format, ...){
	va_list ap;
	va_start(ap, format);
	vfprintf(pDebugFile, format, ap);
	if(printdebug == true) vprintf(format, ap);
	va_end(ap);
}

void sendall(int ignorecid, char* msgformat, ...){ //em ignorecid use (-1) para nao ignorar ninguem
	if(connect_id < 1) //Se for <1, vc é 0 (:P)
		return;
	char msgbuffer[256];
	va_list ap;
	va_start(ap, msgformat);
	vsprintf(msgbuffer, msgformat, ap);
	va_end(ap);
	for(int iCid=0; iCid < connect_id; iCid++)
		if(iCid != ignorecid)
			client_list[iCid].sendmsg(msgbuffer);
}

bool findmeadesker(int selfcid){
	if(connect_id < 1){ //Se for <1, vc é 0 (:P)
		client_list[selfcid].gotworker(-1);
		return false;
	}
	for(int iCid=0; iCid < connect_id; iCid++){
		if((iCid != selfcid) & (client_list[iCid].iLid >= 0) &
			(client_list[iCid].iLType > 7) & (!client_list[iCid].working)){
				client_list[iCid].working = true;
				client_list[iCid].gotwork(selfcid);
				client_list[selfcid].gotworker(iCid);
				return true;
			}
	}
	client_list[selfcid].gotworker(-1);
	return false;
}

char* getname(int wcid){
	return client_list[wcid].realname;
}

void clientloop(int iCid){
	Client client = client_list[iCid];
	char msgbuffer[256];
	int recvr;
	debug_printf("Novo cliente: %s/%i.\n", client.addr, iCid);
	while((client.on == true) & (exit_cmd == false)){
		ZeroMemory(msgbuffer,sizeof(msgbuffer));
		recvr = recv(client.hCSockt, msgbuffer, sizeof(msgbuffer), 0);
		if(client.on == true){
			if(recvr == 0){
				debug_printf("Cliente %s/%i fechou conexao.\n", client.addr, iCid);
				client.disconect();
				return;
			}else if(recvr == SOCKET_ERROR){
				debug_printf("Cliente %s/%i desconectado por erro.\n", client.addr, iCid);
				client.disconect();
				return;
			}else{
				debug_printf("Cliente %s/%i enviou mensagem:\n%s\n*Fim da mensagem.\n", client.addr, iCid, msgbuffer);
				client.received(msgbuffer);
			}
		}
	}
	debug_printf("Conexao finalizada por script: IP %s - ID %i.\n", client.addr, iCid);
	return;
}

void serverloop(){
	sockaddr_in saClient;
	saClient.sin_family = AF_INET;
	int client_size = sizeof(saClient);
	while(exit_cmd == false){
		client_list[connect_id].connect(connect_id, accept(hSocket, (struct sockaddr*)&saClient, &client_size));
		if(exit_cmd == true) break;
		memcpy(&client_list[connect_id].saCin, &saClient, sizeof(saClient));
		client_list[connect_id].addrupdate();
		client_list[connect_id].hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pCLientFunc, (LPVOID)connect_id, 0, &client_list[connect_id].dwThread);
		connect_id++;
		if(connect_id > host_maxuser){
			printf("Erro: O servidor esta cheio e nao ira aceitar mais usuarios!\n");
			break;
		}
	}
	return;
}

void server_main(){
	printf("Criando conexao em %s:%i\n", host_addr, host_port);

	WSADATA wsaData;

	if (WSAStartup(MAKEWORD("2","0"), &wsaData)==0){
		if (LOBYTE(wsaData.wVersion) >= 2){
			if(host_socktype == 0)
				hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			else if(host_socktype == 1)
				hSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

			if (hSocket==INVALID_SOCKET){
				printf("Erro: Nao foi possivel criar uma socket.\n");
				return;
			}else{
				sockaddr_in saSever;
				saSever.sin_family = AF_INET;
				saSever.sin_port = htons(host_port);
				if(strcmp(host_addr,"ANY") != 0){
					#ifdef XPCOMPATIBILITY
						saSever.sin_addr.S_un.S_addr = inet_addr(host_addr);
					#else
						inet_pton(AF_INET, host_addr, &saSever.sin_addr);
					#endif
				}else saSever.sin_addr.S_un.S_addr = INADDR_ANY;

				if(bind(hSocket, (sockaddr*)(&saSever), sizeof(saSever)) == SOCKET_ERROR){
					printf("Erro: Nao foi possivel conectar a socket.\n");
					return;
				}else{
					if((host_socktype == 0) & (listen(hSocket,5) == SOCKET_ERROR)){
						printf("Erro: 'Listen' falhou.\n");
						return;
					}
					printf("Conexao criada com sucesso!\nIniciando recepcao de usuarios...\n");
					pSLoopFunc = &(serverloop);
					pCLientFunc = &(clientloop);
					hSLoopThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pSLoopFunc, NULL, 0, &dwSLoopThread);
					while(exit_cmd == false){
						if((GetAsyncKeyState(122) >> 8) & (GetAsyncKeyState(163) >> 8)) //(122 = Ctrl Direito) + (163 = F11)
							exit_cmd = true;
					}
					printf("Finalizando recepcao de usuarios...\n");
					DWORD lpExitCode=0;
					TerminateThread(hSLoopThread, lpExitCode);
					printf("Recepcao de usuarios finalizada!\n");
					printf("Desconectando os usuarios...\n");
					for(int ci=0; ci < connect_id; ci++){
						lpExitCode = STILL_ACTIVE;
						while(lpExitCode == STILL_ACTIVE){
							client_list[ci].disconect();
							GetExitCodeThread(client_list[ci].hThread, &lpExitCode);
						}
						printf("Usuario %i de %i desconectado!\n", ci, connect_id - 1);
					}
					printf("Todos os usarios foram desconectados com sucesso!\n");
				}
			}
			closesocket(hSocket);
		}else{
		   printf("Erro: E necessario ter no minimo a versao 2.0 da winsock.\n");
		   return;
	    }
	}else{
		printf("Erro: Nao foi possivel inciar a lybrary winsock.\n");
		return;
	}
	return;
}

int read_inii(char* section, char* key, char* file, const int idefault){
    char y[32];
	GetPrivateProfileStringA(section, key, "[RIfail]", y, 32, file);
	if(strcmp(y, "[RIfail]") == 0)
		return idefault;
	else
		return atoi(y);
}

void load_servercfgs(){
	char filename[]=".\\server-cfg.ini";
	GetPrivateProfileStringA("HOST", "ADDR", "ANY", host_addr, 16, filename);
	host_port = read_inii("HOST", "PORT", filename, 3309);
	host_maxuser = read_inii("HOST", "MAXUSERS", filename, 99999);
	host_socktype = read_inii("HOST", "SOCKTYPE", filename, 0);
	GetPrivateProfileStringA("MYSQL", "ADDR", "127.0.0.1", mysql_addr, 16, filename);
	GetPrivateProfileStringA("MYSQL", "USER", "root", mysql_user, 66, filename);
	GetPrivateProfileStringA("MYSQL", "PASS", "", mysql_pass, 66, filename);
	GetPrivateProfileStringA("MYSQL", "DATABASE", "phlcdb", mysql_database, 66, filename);
	mysql_cfgport = read_inii("MYSQL", "PORT", filename, 0);
}

int main(int argc, char* argv[]){
	HWND console_hWnd = GetConsoleWindow();
	EnableMenuItem(GetSystemMenu(console_hWnd, false), SC_CLOSE, MF_GRAYED);
	//
	printdebug = false;
	nogetch = false;
	exit_cmd = false;
	if(argc > 0){
		for(int ai = 0; ai < argc; ai++){
			if (strcmp(argv[ai],"-printdebug") == 0)
				printdebug = true;
			else if(strcmp(argv[ai],"-nogetch") == 0)
				nogetch = true;
		}
	}
	//...
	fopen_s(&pDebugFile, ".\\debug.txt", "w");
	system("cls");
	wprintf(L"*\tAssistência Pluganet\n*\tCriado por PedroHLC\n");
	#ifdef XPCOMPATIBILITY
		puts("O servidor esta utilizando \"winsock\".");
	#else
		puts("O servidor esta utilizando \"ws2tcpip\".");
	#endif
	connect_id = 0;
	load_servercfgs();
	client_list = new Client[host_maxuser];
	printf("Conectando a MySQL via: IP %s PORTA %i USER %s DB %s ...\n", mysql_addr, mysql_cfgport, mysql_user, mysql_database);
	smysql.init();
	smysql.connect(mysql_addr, mysql_user, mysql_pass, mysql_database, 0);
	printf("Conectado a MySQL com sucesso!\nPressione Ctrl(Direito)+F11 para encerrar o servidor!\n");
	try{
		server_main();
		if (WSACleanup()!=0){
			printf("Erro: 'WSACleanup' falhou.\n");
		}
	}catch(char * exception_error){
		printf("Erro: %s.\n", exception_error);
	};
	smysql.close();
	fclose(pDebugFile);
	finish();
	return 0;//O QUE ISSO AINDA FAZENDO AQUI?
}