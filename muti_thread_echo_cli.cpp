#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include "netpacket.h"

#define LOG_DEBUG std::cout << __FILE__ << ":" << __LINE__ << "{" << __FUNCTION__ << "}|DEBUG|"
#define LOG_ERROR std::cout << __FILE__ << ":" << __LINE__ << "{" << __FUNCTION__ << "}|ERROR|"
int Connect()
{
    int iSockFd = ::socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == iSockFd)
	{
		LOG_ERROR << "socket error|msg:" << ::strerror(errno) << std::endl;
		return (-1);
	}

	struct sockaddr_in stSvrAddr;
   	stSvrAddr.sin_family = AF_INET;
   	stSvrAddr.sin_port = htons(8888);
   	stSvrAddr.sin_addr.s_addr = ::inet_addr("127.0.0.1");
   	if(::connect(iSockFd, (struct sockaddr*)&stSvrAddr, sizeof(stSvrAddr)) == -1)
   	{
   		LOG_ERROR << "connect to server error|msg:" << ::strerror(errno) << std::endl;
                  
   		return (-1);
   	} 

   	return (iSockFd);
}


void* threadEntry(void *arg)
{
	char szBuffer[10];
	int iSockFd = *(int*)arg;
	
	printf("thread entry\n");
	
	while (1)
	{
		ssize_t iReadLen = ::read(iSockFd, szBuffer, sizeof(szBuffer) - 1);
        if (iReadLen < 0)
        {
        	printf("read from server error|msg:");
            break;
        }
        else if(0 == iReadLen)
        {
            printf("server request to close server!\n");
            break;
        } 
        else
        {
           szBuffer[iReadLen] = '\0';
           printf("read message from client |:%s\n" ,szBuffer);
        }
	}
}

bool GetData(int clientFd, char* pDataBuffer, const unsigned int& nDataSize )  
{  
    if (pDataBuffer == NULL)
    {
      return false;
    }

    char *p = pDataBuffer;
    int len = nDataSize;
    int ret = 0;
    int returnlen = 0;

    while (len > 0)
    {
      ret = recv(clientFd, p + (nDataSize - len), nDataSize - returnlen, 0);
      if (ret == -1 || ret == 0)
      {
        return false;
      }
      len -= ret;
      returnlen += ret;
    }
    return returnlen;
}  


int main(int argc, char** argv)
{
    int iSockFd = Connect();
    if(iSockFd < 0)
    {
        return (0);
    }

    char szBuffer[1024];
    char SendBuffer[1024],GetBuffer[1024];
    std::string strName, strPwd;
   	//pthread_t iTid;
  	//pthread_create(&iTid, NULL, threadEntry, (void*)&iSockFd);
    while(1)
    { 
        std::cout << "Username :" << std::endl; 
        std::cin >> strName;

        std::cout << "Userpwd :" << std::endl; 
        std::cin >> strPwd;
        
        if(strName.empty() == false)
        {
            NetPacket_Test1 nettest;
            NetPacketHeader netheader;
            nettest.nCodeNum = 2;
            strcpy(nettest.username, strName.c_str());
            strcpy(nettest.userpwd, strPwd.c_str()); 
            netheader.wDataSize = sizeof(nettest);  ///< 数据包大小，包含封包头和封包数据大小  
            netheader.wOpcode = NET_TEST1; 
            ::write(iSockFd, (char*)&netheader, sizeof(netheader));
            ::write(iSockFd, (char*)&nettest, sizeof(nettest));
        }
        else
        {
            LOG_ERROR << "message is empty!!!" << std::endl;
        }
        NetPacketHeader* pPackageHeader = NULL;
        memset(SendBuffer, 0, sizeof(SendBuffer));
        bool iRet = GetData(iSockFd, SendBuffer, sizeof(NetPacketHeader));
        pPackageHeader = (NetPacketHeader* )SendBuffer;;
        if (iRet == false)
        {
          printf("=== get fialed\n");
          return NULL;
        }
        printf("%d %d",pPackageHeader->wDataSize,pPackageHeader->wOpcode);
        memset(GetBuffer, 0, sizeof(GetBuffer));
        iRet = GetData(iSockFd, GetBuffer, pPackageHeader->wDataSize);
        printf("---%s",GetBuffer);
        std::cin.ignore(1024, '\n');;
    }

    ::close(iSockFd);

    return (0);
}


