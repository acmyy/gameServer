// gameServer.cpp : �������̨Ӧ�ó������ڵ㡣
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
