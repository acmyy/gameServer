#include "stdafx.h"
#include <mysql/mysql.h>
class mysql
{
public:
	mysql();
	~mysql();
public:
	bool init();
	bool unInit();
	bool queryData(char* Username, char* Userpwd, int numflags);
	bool insertData(char* Username, char* Userpwd);	
private:
	MYSQL* conn;
	char* hostname;
	char* username;
	char* userpwd;
	char* socketname;
	char* dbname;
	uint flags ; 
};