// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
