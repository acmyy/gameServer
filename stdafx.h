#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<map>
#ifndef _TYPEDEF_STRUCT_
#define _TYPEDEF_STRUCT_
class serverThread;
typedef struct worker
{
	void* (*process)(void *arg);
	void* arg;
	struct worker* next;
}CThreadWorker;

typedef struct connection_desc_s
{
	int m_iFd;
	char m_szClientIP[16];
	unsigned short m_usClientPort;
}connection_desc_t;

#endif
