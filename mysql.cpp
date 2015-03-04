#include "mysql.h"
#include <mysql.h>

mysql::mysql()
{
	opt_host_name = NULL;        /*服务器主机名称 默认为localhost*/
	opt_user_name = "root";        /*数据库用户名 默认为当前登录名*/
	opt_password = "123u123u";        /*密码 默认为空*/
	opt_port_num = 0;            /*端口 使用内建值*/
	opt_socket_name = NULL;    /*socket name (use build-in value)*/
	opt_db_name = "test";        /*数据库 名称 默认为空*/
	opt_flags = 0;      
}

mysql::~mysql()
{

}

bool mysql::init()
{
	if (conn = mysql_init(NULL) == NULL)
	{
		return false;
	}

	if (mysql_real_connect(conn, 
						hostname, 
						username, 
						userpwd, 
						dbname, 
						protnum, 
						socketname, 
						flags) == NULL)
	{
		return false;
	}
	return true;
}

bool mysql::unInit()
{
	mysql_close(conn);
}

bool mysql::queryData(char* Username, char* Userpwd, int numflags)
{
	char s[1000];
	sprintf(s,"select * from UserInformation where username = '%s'",Username);
	if (mysql_query(conn, s))
	{
		return false;
	}
	else
	{
		MYSQL_RES* resSet;
		resSet = mysql_store_result(conn);
		if (resSet == NULL)
		{
			//if (numflags == 1)
				//return false;
			//else
				return true;
		}
		else
		{
			MYSQL_ROW row;
			uint i;
			while (row = mysql_fetch_row(resSet) != NULL)
			{
				for(i = 0; i < mysql_num_fields(res_set); i++)
				{
					if (i > 0)
                		fputc('\t',stdout);
            		printf("%s",row[i] != NULL ? row[i] : "NULL");
        		}
			}
		}
	}
	if (mysql_errno(conn) != 0)
	{
		return false;
	}
}

bool mysql::insertData(char* Username, char* Userpwd)
{
	char s[1000];
	sprintf(s, "\"insert into UserInforkmation (username, userpwd) values ('%s','%s')\"",
		Username, Userpwd);
	if (mysql_query(conn, s))
	{
		return false;
	}
	return true;
}

int main()
{
	mysql temp;
	temp.init();
	temp.queryData("accept", "123456", 1);
	temp.unInit();
}