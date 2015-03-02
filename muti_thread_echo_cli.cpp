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

int main(int argc, char** argv)
{
    int iSockFd = Connect();
    if(iSockFd < 0)
    {
        return (0);
    }

    char szBuffer[1024];
    std::string strMsg;
   	pthread_t iTid;
  	pthread_create(&iTid, NULL, threadEntry, (void*)&iSockFd);
    while(1)
    { 
        std::cout << "Chat :" << std::endl; 
        std::cin >> strMsg;
        if(strMsg.empty() == false)
        {
            ::write(iSockFd, strMsg.c_str(), strMsg.size());
        }
        else
        {
            LOG_ERROR << "message is empty!!!" << std::endl;
        }

        std::cin.ignore(1024, '\n');;
    }

    ::close(iSockFd);

    return (0);
}


