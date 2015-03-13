#pragma once
#include "stdafx.h"
class serverSocket
{
public:
	serverSocket(void);
	~serverSocket(void);

public:
	int init();
	ConnectionClient* Accept();
protected:

private:
	int m_serverSocketFd;
};

