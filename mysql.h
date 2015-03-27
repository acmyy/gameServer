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
	int queryData(std::vector<NetPacket_Score* >& scoreVec);
	bool insertData(char* Username, char* Userpwd);	
	bool UpdateData(char* Username, int nScore);
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
