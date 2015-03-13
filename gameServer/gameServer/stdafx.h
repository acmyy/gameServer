// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

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

typedef struct ConnectionClient
{
	int m_iClientFd;
	char m_szClientIP[16];
	unsigned short m_usClientPort;
}ConnectionClient;


  
//////////////////////////////////////////////////////////////////////////  
  
#endif



// TODO: 在此处引用程序需要的其他头文件
