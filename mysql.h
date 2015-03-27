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
	int queryData(char* Username, char* Userpwd);
	bool insertData(char* Username, char* Userpwd);	
private:
	MYSQL* conn;
	char* hostname;
	char* username;
	char* userpwd;
	char* socketname;
	char* dbname;
	int portnum;
	uint flags ; 
};
