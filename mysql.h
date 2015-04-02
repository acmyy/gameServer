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
	int queryData(const char* Username, const char* Userpwd);
	int queryData(std::vector<NetPacket_Score* >& scoreVec);
	int queryData(const char* Username, int nScore);
	bool insertData(const char* Username, const char* Userpwd);	
	bool UpdateData(const char* Username, int nScore);
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
