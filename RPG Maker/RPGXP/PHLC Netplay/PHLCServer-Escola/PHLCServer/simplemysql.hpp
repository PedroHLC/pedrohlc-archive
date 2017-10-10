//Criei pra realmente simplificar o uso da MySQL :P

#define MYSQL_FETCHLEN unsigned long*

class SimpleMysql{
	public:
		void init();
		void connect(char*, char*, char*, char*, int);
		void query(const char*, ...);
		bool query_result(char*, const char*, ...);
		int query_rowresult(MYSQL_ROW*, MYSQL_FETCHLEN*, const char*, ...);
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

int SimpleMysql::query_rowresult(MYSQL_ROW* finalrow, MYSQL_FETCHLEN* finalflen, const char* query_s, ...){
	int num_field=0;
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
	while((row = mysql_fetch_row(res)) != NULL){
		fetch_lenghts = mysql_fetch_lengths(res);
		memcpy(finalrow, row, sizeof(row));
		memcpy(finalflen, fetch_lenghts, sizeof(fetch_lenghts));
		break;
	}
	num_field = mysql_num_fields(res);
	mysql_free_result(res);
	return num_field;
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