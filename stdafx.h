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
#include<queue>
#include<errno.h>


#ifndef _TYPEDEF_STRUCT_
#define _TYPEDEF_STRUCT_

#define NET_PACKET_DATA_SIZE 1024   
#define NET_PACKET_SIZE (sizeof(NetPacketHeader) + NET_PACKET_DATA_SIZE) * 10  
  
class serverThread;

typedef struct worker
{
	void* (*process)(void *arg);
	void* arg;
	struct worker* next;
}CThreadWorker;

typedef struct connectionSocketData
{
	int m_iFd;
	char m_szClientIP[16];
	unsigned short m_usClientPort;
}connectionSocketData;

  
/// 网络数据包包头  
struct NetPacketHeader  
{  
    unsigned short      uDataSize;  ///< 数据包大小，包含封包头和封包数据大小  
    unsigned short      uOpcode;    ///< 操作码  
};  
  
  
/// 网络操作码  
enum eNetOpcode  
{  
    REGISTER_CODE         = 1,  
    LOGIN_CODE          = 2,
    SOCRE_CODE          = 3
};  
  
/// 网络数据包定义  
struct NetPacket_Register  
{  
    char username[20];  
    char userpwd[20];
    int nCodeNum;  
};  

struct NetPacket_Result  
{  
    int result;
};  
#endif
