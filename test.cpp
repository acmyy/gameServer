#include "stdafx.h"
#include "serverSocket.h"
#include "serverThread.h"


int main()
{
	serverSocket server;
	server.init();
	
	serverThread* pServerThread = serverThread::getInstance();
    pServerThread->PoolInit();
	printf("server is ready\n");

	while (1)
	{
		connection_desc_t* pConn = server.Accept();

		if (pConn != NULL)
		{
			printf("port:%d Accept Success\n", pConn->m_usClientPort);
			pServerThread->PoolAddWorker((void*)pConn);		
		}
	}

	return 0;	
}
