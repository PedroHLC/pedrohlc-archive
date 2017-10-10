//Criei pra realmente simplificar o uso da MySQL :P

#define MYSQL_FETCHLEN unsigned long*

class SimpleMysql{
	public:
		void init();
		void connect(char*, char*, char*, char*, int);
		void query(const char*, ...);
		bool query_result(char*, const char*, ...);
		bool query_multiresult(char*, const char*, const char*, ...);
		void close();
	private:
		MYSQL* mysql_conn;
};

void SimpleMysql::query(const char* query_s, ...){
	char query[1024];
	va_list ap;
	va_start(ap, query_s);
	vsprintf_s(query, query_s, ap);
	va_end(ap);
	if (mysql_query(mysql_conn, query)) {
      printf("MySQL-Erro: %s\n", mysql_error(mysql_conn));
	  finish();
	}
}

bool SimpleMysql::query_multiresult(char* result, const char* separator, const char* query_s, ...){
	char query[1024];
	va_list ap;
	va_start(ap, query_s);
	vsprintf_s(query, query_s, ap);
	va_end(ap);
	if (mysql_query(mysql_conn, query)) {
      printf("MySQL-Erro: %s\n", mysql_error(mysql_conn));
	  finish();
	}
	MYSQL_RES* res = mysql_use_result(mysql_conn);
	MYSQL_ROW row;
	unsigned long* fetch_lenghts;
	strcpy(result, "");
	bool returnvalue = false;
	while((row = mysql_fetch_row(res)) != NULL){
		fetch_lenghts = mysql_fetch_lengths(res);
		int num_field = mysql_num_fields(res);
		if(num_field >= 1){
			for(int i=0; i < num_field; i++){
				if(row[i] == NULL)
					strcat(result, "(null)");
				else
					strcat(result, row[i]);
				strcat(result, separator);
			}
			result[strlen(result)-strlen(separator)] = '\0';
			returnvalue = true;
		}
	}
	mysql_free_result(res);
	return returnvalue;
}

bool SimpleMysql::query_result(char* result, const char* query_s, ...){
	char query[1024];
	va_list ap;
	va_start(ap, query_s);
	vsprintf_s(query, query_s, ap);
	va_end(ap);
	if (mysql_query(mysql_conn, query)) {
      printf("MySQL-Erro: %s\n", mysql_error(mysql_conn));
	  finish();
	}
	MYSQL_RES* res = mysql_use_result(mysql_conn);
	MYSQL_ROW row;
	bool returnval = false;
	unsigned long* fetch_lenghts;
	while((row = mysql_fetch_row(res)) != NULL){
		fetch_lenghts = mysql_fetch_lengths(res);
		strncpy(result, row[0], fetch_lenghts[0]+1);
		returnval = true;
		break;
	}
	mysql_free_result(res);
	return returnval;
}

void SimpleMysql::init(){
	mysql_conn = mysql_init(mysql_conn);
}

void SimpleMysql::close(){
	mysql_close(mysql_conn);
}

void SimpleMysql::connect(char* addr_s, char* user_s, char* pass_s, char* database_s, int port_i){
	if (!mysql_real_connect(mysql_conn, addr_s, user_s, pass_s, database_s, port_i, NULL, 0)) {
      printf("MySQL-Erro: %s\n", mysql_error(mysql_conn));
	  finish();
	}
	return;
}