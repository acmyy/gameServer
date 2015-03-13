// gameServer.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "serverSocket.h"


int main()
{
	serverSocket server;
	server.init();
	
	while (1)
	{
		ConnectionClient* pConn = server.Accept();
		printf("connection success\n");
	}

	return 0;	
}
