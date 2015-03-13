#include"serverSocket.h"

serverSocket::serverSocket():m_serverSocketFd(-1)
{
	
}

serverSocket::~serverSocket()
{
	close(m_serverSocketFd);
}

int serverSocket::init()
{

	if (m_serverSocketFd != -1)
	{
		close(m_serverSocketFd);
		m_serverSocketFd = -1;	
	}

	m_serverSocketFd = ::socket(AF_INET, SOCK_STREAM, 0);

	if (-1 == m_serverSocketFd)
	{
		return (-1);	
	}
	
	struct sockaddr_in stBindAddr;
	stBindAddr.sin_family = AF_INET;
	stBindAddr.sin_port = htons(8888);
	stBindAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (::bind(m_serverSocketFd,
		(struct sockaddr*)&stBindAddr,
		sizeof(stBindAddr)
		) == -1
	)
	{
		return (-1);
	}

	if (::listen(m_serverSocketFd, 1024) == -1)
	{
		return (-1);	
	}

	return m_serverSocketFd;
}

ConnectionClient* serverSocket::Accept()
{
	ConnectionClient* pConn = NULL;
	struct sockaddr_in stClientAddr;
	socklen_t uiClientAddrLen = sizeof(stClientAddr);
	int iClientFd = ::accept(m_serverSocketFd, (struct sockaddr*)&stClientAddr, &uiClientAddrLen);

	if (iClientFd < 0)
	{
		return NULL;	
	}
	else
	{
		pConn = new ConnectionClient();
		inet_ntop(AF_INET, 
			&(stClientAddr.sin_addr), 
			pConn->m_szClientIP, 
			sizeof(pConn->m_szClientIP));
		pConn->m_iClientFd = iClientFd;
		pConn->m_usClientPort = ntohs(stClientAddr.sin_port);
	}
	return (pConn);

}

