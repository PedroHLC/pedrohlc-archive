//Client Character
class ClientCHAR{
	public:
		int char_id, char_num,
			char_genre, char_class,
			char_exp, char_money, char_guild,
			char_hp, char_maxhpp, char_sp, char_maxspp,
			char_evap, char_pdefp, char_mdefp,
			char_agip, char_atkp, char_strp,
			char_dexp, char_intp,
			mapid, posx, posy, posd;
		char char_nick[32], *char_equiped,
			*char_ivent, char_skills;
};

//Basic Client
class Client {
	public:
		int iCid, iLid, iLType, gender;
		SOCKET hCSockt;
		HANDLE hThread;
		DWORD dwThread;
		sockaddr_in saCin; 
		#ifdef XPCOMPATIBILITY
			char *addr;
		#else
			char addr[15];
		#endif
		ClientCHAR player;
		bool logged, on;
		char username[33], charname[12];
		void connect(int, SOCKET);
		void disconect();
		void received(char*);
		void addrupdate();
		void sendmsg(char*, ...);
	private:
		void login(char*, char*);
		void logoff();
		void userregister(char*, char*);
		void setupmap(int);
		void loadchar(int);
};

void Client::loadchar(int tcharnum){
	if(iLid <= 0) return;
	MYSQL_ROW row;
	unsigned long* fetchs_lenght;
	int num_field = smysql.query_rowresult(&row, &fetchs_lenght, "SELECT * FROM chars WHERE char_num=\"%i\" AND char_owner=\"%i\"", tcharnum, iLid);
	if(num_field <= 1){
		return;
	}
	player.char_id = row[0][0];
	player.char_num = tcharnum;
	memcpy(&player.char_nick, &row[3][0], fetchs_lenght[3]);
	player.char_genre = row[4][0];
	player.char_class = row[5][0];
	player.char_exp = row[6][0];
	player.char_money = row[7][0];
	player.char_hp = row[8][0];
	player.char_maxhpp = row[9][0];
	player.char_sp = row[10][0];
	player.char_maxspp = row[11][0];
	player.char_evap = row[12][0];
	player.char_pdefp = row[13][0];
	player.char_mdefp = row[14][0];
	player.char_agip = row[15][0];
	player.char_atkp = row[16][0];
	player.char_strp = row[17][0];
	player.char_dexp = row[18][0];
	player.char_intp = row[19][0];
	player.mapid = row[20][0];
	player.posx = row[21][0];
	player.posy = row[22][0];
	player.posd = row[23][0];
	player.char_guild = row[24][0];
	memcpy(&player.char_equiped, &row[25][0], fetchs_lenght[256]);
	memcpy(&player.char_ivent, &row[26][0], fetchs_lenght[26]);
	memcpy(&player.char_skills, &row[27][0], fetchs_lenght[27]);
}

void Client::setupmap(int tmapid){
	if(player.char_id <= 0) return;
	client_setupmap(iCid, tmapid);
}

void Client::connect(int niCid, SOCKET nhSockt){
	iCid = niCid;
	iLid = -1;
	hCSockt = nhSockt;
	on = true;
	logoff();
	sendmsg("!\1%s!\0", msgs_motd);
}

void Client::addrupdate(){
	if(on != true) return;
	#ifdef XPCOMPATIBILITY
		addr = inet_ntoa(saCin.sin_addr);
	#else
		inet_ntop(AF_INET, &saCin.sin_addr, addr, 32);
	#endif
}

void Client::disconect(){
	if(on==true){
		on = false;
		closesocket(hCSockt);
	}
}

void Client::login(char* tusername, char* tpassword){
	char upass[33];
	bool exist = smysql.query_result(upass, "SELECT login_pass FROM users WHERE login_name=\"%s\"", tusername);
	if(exist == false){
		smysql.query("INSERT INTO users(login_name,login_pass) VALUES(\"%s\",\"%s\")", tusername, tpassword);
		char lid[5];
		smysql.query_result(lid, "SELECT login_id FROM users WHERE login_name=\"%s\"", tusername);
		iLid = atoi(lid);
		iLType = 0;
		debug_printf("Cliente IP %s registrou-se!\n", addr);
	}else if(strcmp(upass, tpassword) != 0){
		sendmsg("L\1-\0");
		debug_printf("Cliente IP %s tentou logar como \"%s\" usando a senha \"%s\".\n", addr, tusername, tpassword);
		return;
	}else{
		char lid[5];
		smysql.query_result(lid, "SELECT login_id FROM users WHERE login_name=\"%s\"", tusername);
		iLid = atoi(lid);
		char type[2];
		smysql.query_result(type, "SELECT type FROM users WHERE login_id=\"%i\"", iLid);
		iLType = atoi(type);
	}
	strcpy_s(username, tusername);
	logged = true;
	sendmsg("L\1%i\1%i\0", iLType, iLid);
	debug_printf("Cliente IP %s logou como \"%s\".\n", addr, tusername);
}

void Client::sendmsg(char* msgformat, ...){
	char msg[256];
	va_list ap;
	va_start(ap, msgformat);
	vsprintf_s(msg, msgformat, ap);
	va_end(ap);
	send(hCSockt, msg, strlen(msg), 0);
}

void Client::logoff(){
	iLid = 0;
	iLType = 0;
	logged = false;
	player.mapid = 0;
	strcpy_s(charname, "");
}

void Client::received(char* packet){
	switch(packet[0]){
		case '8':
			send(hCSockt, "8", 1, 0);
			break;
		case 'L':
			if(packet[3]=='#') logoff();
			else{
				char tusername[33], tpassword[33];
				sscanf(packet, "L\1%[^'\1']\1%s", tusername, tpassword);
				this->login(tusername, tpassword);
			}
			break;
		case 'P':
			sscanf(packet, "P\1%i\1%i\1%i", player.posx, player.posy, player.posd);
			break;
		case 'M':
			int movtype, movarg1, movarg2;
			switch(packet[3]){
				case '0': //Turn
					sscanf(packet, "M\1%i\1%i", movtype, movarg1);
					sendmap(iCid, player.mapid, "M\1%i\1%i\1%i", iCid, movtype, movarg1);
					player.posd = movarg1;
					break;
				case '1': //Move
					sscanf(packet, "M\1%i\1%i", movtype, movarg1);
					sendmap(iCid, player.mapid, "M\1%i\1%i\1%i", iCid, movtype, movarg1);
					switch(movarg1){
						case 2:
							player.posy += 1;
							break;
						case 4:
							player.posx -= 1;
							break;
						case 6:
							player.posx += 1;
							break;
						case 8:
							player.posy -= 1;
							break;
					}
					break;
				case '2': //Jump - 2 args
					sscanf(packet, "M\1%i\1%i\1%i", movtype, movarg1, movarg2);
					sendmap(iCid, player.mapid, "M\1%i\1%i\1%i\1%i", iCid, movtype, movarg1, movarg2);
					player.posx += movarg1;
					player.posy += movarg2;
					break;
				case '3': //NewMap
					sscanf(packet, "M\1%i\1%i", movtype, movarg1);
					client_setupmap(iCid, movarg1);
					break;
			}
			break;
		default:
			debug_printf("Mensagem desconhecida recebida de %s:\n%s\n*Fim da mensagem\n", addr, packet);
			break;
	}
	return;
}