#include "stdafx.h"
class serverThread
{

public:
	static serverThread* getInstance();
	static serverThread* m_pServerThread;


public:
	serverThread();
	~serverThread();

	int PoolInit();
	int PoolAddWorker(void *arg);

friend void* ThreadRoutine(void* arg);
friend void* ProcessClient(void* arg);
private:
	pthread_mutex_t m_queueLock;
	pthread_cond_t m_queueReady;
	CThreadWorker* m_queueHead;
	pthread_t* m_ThreadId;
	int m_iShutDown;
	int m_iMaxThreadNum;
	int m_iCurQueueSize;
	connectionSocketData m_stConn[2] ;
	std::map<int ,int > m_SocketMap;
};

