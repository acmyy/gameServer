#include "stdafx.h"
#include "server_socket.h"
#include "server_thread.h"

int main()
{
	serverSocket server;
	if (server.init() == -1)
	{
		printf("Server Failed\n");
		reutrn 1;
	}
	
	serverThread* pServerThread = serverThread::getInstance();
    	pServerThread->PoolInit();
	printf("server is ready\n");

	while (1)
	{
		connectionSocketData* pConn = server.Accept();

		if (pConn != NULL)
		{
			pServerThread->PoolAddWorker((void*)pConn);		
		}
	}
	if (server.UnInit())
	{
		printf("Server Close Error\n");
		return 1;
	}

	return 0;	
}
