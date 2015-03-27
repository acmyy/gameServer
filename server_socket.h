#include "stdafx.h"

class serverSocket
{
public:	
	serverSocket();
	~serverSocket();

	int init();
	connectionSocketData* Accept();
protected:

private:
	int m_socketFd;
};
