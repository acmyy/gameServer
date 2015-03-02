#include<stdio.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>


int Connect()
{
	int iSockFd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == iSockFd)
	{
		return -1;	
	}

	struct sockaddr_in stSvrAddr;
	stSvrAddr.sin_family = AF_INET;
	stSvrAddr.sin_port = htons(8888);
	stSvrAddr.sin_addr.s_addr = ::inet_addr("127.0.0.1");

	if (::connect(iSockFd, (struct sockaddr*)&stSvrAddr, sizeof(stSvrAddr)) == -1)
	{
		return -1;	
	}

	return iSockFd;
}

int main()
{
	int iSockFd = Connect();

	if (iSockFd < 0)
	{
		return 0;	
	}

	char szBuffer[1024];
	std::string strMsg;

	
}



