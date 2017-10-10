//Basic Client

#define self client_list[iCid]
#define setselfvar(var) self.var = var

class Client {
	public:
		HANDLE hThread;
		DWORD dwThread;
		sockaddr_in saCin; 
		#ifdef XPCOMPATIBILITY
			char *addr;
		#else
			char addr[15];
		#endif
		bool logged, on, notenoughtcash, working;
		char *username, *realname;
		void connect(int, SOCKET);
		void disconect();
		void received(char*);
		void addrupdate();
		void sendmsg(char*, ...);
		void gotwork(int clientcid);
		void gotworker(int clientcid);
		int getlid();
		int getltype();
	public:
		int iCid, iLid, iLType, gender, tickets, partner;
		SOCKET hCSockt;
	private:
		void login(char*, char*);
		void logoff();
		void userregister(char*, char*);
};

int Client::getlid(){	return iLid;	}
int Client::getltype(){	return iLType;	}


void Client::connect(int niCid, SOCKET nhSockt){
	setselfvar(iCid) = niCid;
	setselfvar(hCSockt) = nhSockt;
	setselfvar(on) = true;
	logoff();
}

void Client::addrupdate(){
	if(on != true) return;
	#ifdef XPCOMPATIBILITY
		addr = inet_ntoa(saCin.sin_addr);
	#else
		inet_ntop(AF_INET, &saCin.sin_addr, addr, 32);
	#endif
	setselfvar(addr);
}

void Client::disconect(){
	if(on==true){
		setselfvar(on) = false;
		closesocket(hCSockt);
	}
}

/*Client::register
	smysql.query("INSERT INTO users(login_name,login_pass) VALUES(\"%s\",\"%s\")", tusername, tpassword);
	char lid[5];
	smysql.query_result(lid, "SELECT login_id FROM users WHERE login_name=\"%s\"", tusername);
	iLid = atoi(lid);
	iLType = 0;
	debug_printf("Cliente IP %s registrou-se!\n", addr);
}*/

void Client::login(char* tusername, char* tpassword){
	logoff();
	char upass[33];
	bool exist = smysql.query_result(upass, "SELECT login_pass FROM users WHERE login_name=\"%s\"", tusername);
	if(exist == false){
		sendmsg("l\1-", 0);
		debug_printf("Cliente IP %s tentou logar como \"%s\" usando a senha \"%s\".\n", addr, tusername, tpassword);
	}else if(strcmp(upass, tpassword) != 0){
		sendmsg("l\1-", 0);
		debug_printf("Cliente IP %s tentou logar como \"%s\" usando a senha \"%s\".\n", addr, tusername, tpassword);
		return;
	}else{
		char lid[5];
		smysql.query_result(lid, "SELECT login_id FROM users WHERE login_name=\"%s\"", tusername);
		setselfvar(iLid) = atoi(lid);
		char type[2];
		smysql.query_result(type, "SELECT type FROM users WHERE login_id=\"%i\"", iLid);
		setselfvar(iLType) = atoi(type);
		char stickets[11];
		smysql.query_result(stickets, "SELECT tickets FROM users WHERE login_id=\"%i\"", iLid);
		setselfvar(tickets) = atoi(stickets);
		self.realname = (char*) malloc(sizeof(char) * 65);
		smysql.query_result(self.realname, "SELECT name FROM users WHERE login_id=\"%i\"", iLid);
		self.username = (char*) malloc(sizeof(char) * 65);
		strcpy(self.username, tusername);
		setselfvar(logged) = true;
		sendmsg("l\1%i\1%i\1%i", iLid, iLType, tickets);
		debug_printf("Cliente IP %s logou como \"%s\"(%i).\n", addr, tusername, iLid);
		if((tickets < 1) & (iLType < 8))
			setselfvar(notenoughtcash) = true;
	}
}

void Client::sendmsg(char* msgformat, ...){
	char msg[256];
	va_list ap;
	va_start(ap, msgformat);
	vsprintf_s(msg, msgformat, ap);
	strcat(msg, "\n");
	va_end(ap);
	send(hCSockt, msg, strlen(msg), 0);
}

void Client::logoff(){
	setselfvar(partner) = -1;
	setselfvar(iLid) = -1;
	setselfvar(iLType) = 0;
	setselfvar(tickets) = 0;
	debug_printf("Cliente IP %s deslogou.\n", addr);
}


void Client::gotwork(int clientid){
	setselfvar(partner) = clientid;
	sendmsg("W\1%s", getname(clientid));
}

void Client::gotworker(int workerid){
	setselfvar(partner) = workerid;
	if(workerid >= 0){
		sendmsg("W\1%s", getname(workerid));
	}else{
		sendmsg("W\1-");
	}
}



void Client::received(char* packet){
	if(notenoughtcash){
		debug_printf("%s Pobretão\n", addr);
		disconect();
	}
	switch(packet[0]){
		case 'C':
			if(self.partner >= 0)
				client_list[self.partner].sendmsg(packet);
			packet[0] = 'c';
			sendmsg(packet);
			break;
		case 'W':
			if(iLType < 8)
				findmeadesker(iCid);
			break;
		case 'D':
			disconect();
			break;
		case '8':
			sendmsg("8");
			break;
		case 'l':
			if(packet[3]=='#') logoff();
			else{
				char tusername[33], tpassword[33];
				sscanf(packet, "l\1%[^'\1']\1%s", tusername, tpassword);
				this->login(tusername, tpassword);
			}
			break;
		default:
			break;
	}
	return;
}