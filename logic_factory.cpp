#include "logic_factory.h"
#include "stdafx.h"
LogicFactory::LogicFactory(connectionSocketData* pConn)
{
	m_mysqltest.init();
	m_pConn = pConn;
}

LogicFactory::~LogicFactory()
{
	m_mysqltest.unInit();
}


bool LogicFactory::loginOperator()
{
	NetPacketResult nettest;
    NetPacketHeader netheader;
	NetPacket_Register* test1 = (NetPacket_Register* )packageContext;
	printf("%s %s\n", test1->username, test1->userpwd); 
	int nCode = m_mysqltest.queryData(test1->username, test1->userpwd);
	
	if (nCode == 1)
	{
		nettest.result = 1;
        printf( "登陆成功");
        netheader.uDataSize = sizeof(nettest);  ///< 数据包大小，包含封包头和封包数据大小  
        netheader.uOpcode = RESULT_CODE; 
	}
	else
	{
		nettest.result = 0;
        NetPacketHeader netheader;
        printf("您输入的用户名不存在或者密码错误");
        netheader.uDataSize = sizeof(nettest);  ///< 数据包大小，包含封包头和封包数据大小  
        netheader.uOpcode = RESULT_CODE; 
	}
    netdata.SendData(m_pConn->m_iFd, (char*)&netheader, sizeof(netheader));
    netdata.SendData(m_pConn->m_iFd, (char*)&nettest, sizeof(nettest));
}

bool LogicFactory::registerOperator()
{
	NetPacketResult nettest;
    NetPacketHeader netheader;
	NetPacket_Register* test1 = (NetPacket_Register* )packageContext;
	printf("%s %s\n", test1->username, test1->userpwd); 
	bool nCode = m_mysqltest.insertData(test1->username, test1->userpwd);
	
	if (nCode)
	{
		nettest.result = 1;
        printf( "注册成功\n");
        netheader.uDataSize = sizeof(nettest);  ///< 数据包大小，包含封包头和封包数据大小  
        netheader.uOpcode = RESULT_CODE; 
	}
	else
	{
		nettest.result = 0;
        NetPacketHeader netheader;
        printf("您输入的用户名不存在或者密码错误\n");
        netheader.uDataSize = sizeof(nettest);  ///< 数据包大小，包含封包头和封包数据大小  
        netheader.uOpcode = RESULT_CODE; 
	}
    netdata.SendData(m_pConn->m_iFd, (char*)&netheader, sizeof(netheader));
    netdata.SendData(m_pConn->m_iFd, (char*)&nettest, sizeof(nettest));
}

bool LogicFactory::getSocre()
{
	//int nCode = m_mysqltest.queryData(test1->username, test1->userpwd);
}

bool LogicFactory::setSocre()
{
	NetPacket_Score* test1 = (NetPacket_Score* )packageContext;
//	printf("%s %s\n", test1->username, test1->userpwd); 
	//int nCode = m_mysqltest.insertData(test1->username, test1->userpwd);
}

bool LogicFactory::operatorMenu()
{
	NetPacketHeader* pPackageHeader = NULL;
	unsigned int uOpcode;
	memset(packageHead, 0, sizeof(packageHead));
	ssize_t iRet = netdata.GetData(m_pConn->m_iFd, 
					packageHead, sizeof(NetPacketHeader));
	
	if (iRet == false)
	{
		printf("=== get fialed\n");
		return NULL;
	}
	
	pPackageHeader = (NetPacketHeader* )packageHead;
	memset(packageContext, 0, sizeof(packageContext));
	uOpcode = pPackageHeader->uOpcode;

	if (pPackageHeader->uDataSize > 0)
	{
		iRet = netdata.GetData(m_pConn->m_iFd, 
				packageContext, pPackageHeader->uDataSize);
		
		if (iRet == false)
		{
			printf("=== get fialed\n");
			return NULL;
		}
	}

	switch (uOpcode)
	{
		case REGISTER_CODE:
		{
			registerOperator();
			break;
		}
		case LOGIN_CODE:
		{
			loginOperator();
			break;
		}
    	case GET_SCORE_CODE:
    	{
    		getSocre();
    		break;
    	}  
    	case SCORE_CODE:
    	{
    		setSocre();
    		break;
    	}
    	default:
		break;
	}
}
	
