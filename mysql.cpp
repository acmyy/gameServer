#include "mysql.h"


mysql::mysql()
{
	conn = NULL;
	hostname = NULL;
	username = "root";
	userpwd = "123u123u";
	socketname = NULL;
	dbname = "test";
	flags = 0; 
	portnum = 0;  
}

mysql::~mysql()
{

}

bool mysql::init()
{
	conn = mysql_init(NULL);

	if (mysql_real_connect(conn, hostname, 
		username, userpwd, dbname, 
		portnum, socketname, flags) == NULL)
	{
		return false;
	}
	return true;
}

bool mysql::unInit()
{
	mysql_close(conn);
}

int mysql::queryData(const char* Username, const char* Userpwd)
{
	char s[1000];
	sprintf(s,"select * from UserInformation where username = '%s'",Username);
	if (mysql_query(conn, s))
	{
		return 0;
	}
	else
	{
		MYSQL_RES* resSet;
		resSet = mysql_store_result(conn);
		if (resSet == NULL)
		{
			return 0;
		}
		else
		{
			MYSQL_ROW row;
			uint i;
			while (row = mysql_fetch_row(resSet))
			{
            	if (strcmp(row[1], Userpwd) == 0)
            	{
            		return 1;
            	}
			}
		}
	}
	if (mysql_errno(conn) != 0)
	{
		return false;
	}
	return 0;
}


int mysql::queryData(std::vector<NetPacket_Score* >& scoreVec)
{
	char s[1000];
	sprintf(s,"select * from UserInformation ORDER BY score DESC");
	if (mysql_query(conn, s))
	{
		return 0;
	}
	else
	{
		MYSQL_RES* resSet;
		resSet = mysql_store_result(conn);
		if (resSet == NULL)
		{
			return 0;
		}
		else
		{
			MYSQL_ROW row;
			uint i = 0;
			while (row = mysql_fetch_row(resSet))
			{
				scoreVec.push_back(new NetPacket_Score(row[0], *(int *)row[2]));
				i++;
				if (i >= 10)
				{
					break;
				}
			}
		}
	}
	if (mysql_errno(conn) != 0)
	{
		return false;
	}
	return 0;
}


bool mysql::insertData(const char* Username, const char* Userpwd)
{
	char s[1000];
	sprintf(s, "insert into UserInformation (username, userpwd) values ('%s','%s')",
		Username, Userpwd);
	printf("%s\n",s);
	if (mysql_query(conn, s))
	{
		return false;
	}
	return true;
}

bool mysql::UpdateData(const char* Username, int nScore)
{
	char cmd[1024];
	sprintf(cmd, "update UserInformation set score = %d where name = '%s'", nScore, Username);
	int ret = mysql_query(conn, cmd);
	if (ret != 0)
	{
		return false;
	}
	return true;
}
