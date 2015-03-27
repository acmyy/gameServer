#include "stdafx.h"
#include "server_socket.h"
#include "server_thread.h"

int main()
{
	serverSocket server;
	server.init();
	
	serverThread* pServerThread = serverThread::getInstance();
    	pServerThread->PoolInit();
	printf("server is ready\n");

	while (1)
	{
		connectionSocketData* pConn = server.Accept();

		if (pConn != NULL)
		{
			printf("port:%d Accept Success\n", pConn->m_usClientPort);
			pServerThread->PoolAddWorker((void*)pConn);		
		}
	}

	return 0;	
}
