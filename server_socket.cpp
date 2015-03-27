#include"serverSocket.h"
#include"serverThread.h"
serverSocket::serverSocket():m_socketFd(-1)
{
	
}

serverSocket::~serverSocket()
{
	close(m_socketFd);
}

int serverSocket::init()
{

	if (m_socketFd != -1)
	{
		close(m_socketFd);
		m_socketFd = -1;	
	}

	m_socketFd = ::socket(AF_INET, SOCK_STREAM, 0);

	if (-1 == m_socketFd)
	{
		return (-1);	
	}
	
	struct sockaddr_in stBindAddr;
	stBindAddr.sin_family = AF_INET;
	stBindAddr.sin_port = htons(8888);
	stBindAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (::bind(m_socketFd,
		(struct sockaddr*)&stBindAddr,
		sizeof(stBindAddr)
		) == -1
	)
	{
		return (-1);
	}

	if (::listen(m_socketFd, 1024) == -1)
	{
		return (-1);	
	}

	return m_socketFd;
}

connectionSocketData* serverSocket::Accept()
{
	connectionSocketData* pConn = NULL;
	struct sockaddr_in stClientAddr;
	socklen_t uiClientAddrLen = sizeof(stClientAddr);
	int iClientFd = ::accept(m_socketFd, (struct sockaddr*)&stClientAddr, &uiClientAddrLen);

	if (iClientFd < 0)
	{
		return NULL;	
	}
	else
	{
		pConn = new connectionSocketData();
		inet_ntop(AF_INET, 
			&(stClientAddr.sin_addr), 
			pConn->m_szClientIP, 
			sizeof(pConn->m_szClientIP));
		pConn->m_iFd = iClientFd;
		pConn->m_usClientPort = ntohs(stClientAddr.sin_port);
	}
	return (pConn);

}

