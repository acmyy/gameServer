#include "stdafx.h"

class serverSocket
{
public:	
	serverSocket();
	~serverSocket();

	int init();
	connection_desc_t* Accept();
protected:

private:
	int m_socketFd;
};
