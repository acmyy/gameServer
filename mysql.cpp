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

int mysql::queryData(char* Username, char* Userpwd)
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
				/*for(i = 0; i < mysql_num_fields(resSet); i++)
				{
					if (i > 0)
                		fputc('\t',stdout);
            		printf("%s",row[i] != NULL ? row[i] : "NULL");
        		}*/
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

bool mysql::insertData(char* Username, char* Userpwd)
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

