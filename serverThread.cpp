#include "serverThread.h"
#include "netpacket.h"

serverThread* serverThread::m_pServerThread = NULL;

serverThread::serverThread()
{
	m_SocketMap.clear();
}

serverThread::~serverThread()
{
	
}

serverThread* serverThread::getInstance()
{
	if (m_pServerThread == NULL)
	{
		m_pServerThread = new serverThread();
	}
	return m_pServerThread;
}

void* ProcessClient(void* pConn)
{
	connection_desc_t stConn = *((connection_desc_t*)pConn);

	printf("%s %u\n",stConn.m_szClientIP, stConn.m_usClientPort);
    serverThread* pServerThread = serverThread::getInstance();
	char packageHead[1024];
	char packageContext[2048];

	NetPacketHeader* pPackageHeader = NULL;
	NETPacket netdata;

	memset(packageHead, 0, sizeof(packageHead));
	ssize_t iRet = netdata.GetData(stConn.m_iFd, packageHead, sizeof(NetPacketHeader));
	if (iRet == false)
	{
		printf("=== get fialed\n");
		return NULL;
	}
	
	pPackageHeader = (NetPacketHeader* )packageHead;
	memset(packageContext, 0, sizeof(packageContext));
	if (pPackageHeader->wDataSize > 0)
	{
		iRet = netdata.GetData(stConn.m_iFd, packageContext, pPackageHeader->wDataSize);
		if (iRet == false)
		{
			printf("=== get fialed\n");
			return NULL;
		}
		switch (pPackageHeader->wOpcode)
		{
			case NET_TEST1:
			{
				NetPacket_Test1* test1 = (NetPacket_Test1* )packageContext;
				printf("%s %s\n", test1->username, test1->userpwd); 
				break;
			}
			default:
			break;
		}
	}
	else
	{
		printf("getfialed\n");
	}
}

void* ThreadRoutine(void* arg)
{
	printf("starting thread %lu\n",pthread_self());
	
	serverThread* pServerThread = serverThread::getInstance();
	while (1)
	{
		pthread_mutex_lock(&pServerThread->m_queueLock);	
		
		while (pServerThread->m_iCurQueueSize == 0 
			&& !pServerThread->m_iShutDown)
		{
			printf("thread %lu is waittihng\n",pthread_self());
			pthread_cond_wait(&(pServerThread->m_queueReady), 
			&pServerThread->m_queueLock);
		}

		if (pServerThread->m_iShutDown)
		{
			pthread_mutex_unlock(&(pServerThread->m_queueLock));
			pthread_exit(NULL);
		}

		printf("thread %lu will exit\n",pthread_self());
		
		pServerThread->m_iCurQueueSize--;
		CThreadWorker* worker = pServerThread->m_queueHead;
        pServerThread->m_queueHead = worker->next;
		pthread_mutex_unlock(&(pServerThread->m_queueLock));

		(*(worker->process))(worker->arg);
		free(worker);
		worker = NULL;
	}
	pthread_exit(NULL);
}

int serverThread::PoolInit()
{
	int maxThreadNum = 16;
	pthread_mutex_init(&(m_queueLock), NULL);
	pthread_cond_init(&m_queueReady, NULL);

	m_queueHead = NULL;
	m_iMaxThreadNum = maxThreadNum;
	m_iCurQueueSize = 0;
	m_iShutDown = 0;

	m_ThreadId = (pthread_t* )malloc(m_iMaxThreadNum * sizeof(pthread_t));

	for (int index = 0; index  < m_iMaxThreadNum; ++index)
	{
		pthread_create(&(m_ThreadId[index]), NULL, ThreadRoutine, NULL);
	}

	return 1;
}

int serverThread::PoolAddWorker(void *arg)
{
	CThreadWorker *newWorker = (CThreadWorker*)malloc(sizeof(CThreadWorker));
	newWorker->process = ProcessClient;
	newWorker->arg = arg;
	newWorker->next = NULL;

	connection_desc_t stConn = *((connection_desc_t*)arg);
	m_SocketMap[stConn.m_iFd] = stConn.m_iFd;
	pthread_mutex_lock(&m_queueLock);

	CThreadWorker* member = m_queueHead;

	if (member != NULL)
	{
		while (member->next != NULL)
		{
			member = member->next;	
		}
		member->next = newWorker;
	}
	else
	{
		m_queueHead = newWorker;	
	}

	m_iCurQueueSize++;

	pthread_mutex_unlock(&m_queueLock);
	pthread_cond_signal(&m_queueReady);
	return 0;
}


