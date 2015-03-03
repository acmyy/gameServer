#include "netpacket.h"

NETPacket::NETPacket()
{

}

NETPacket::~NETPacket()
{

}
  
bool NETPacket::GetData(int clientFd, const char* pDataBuffer, const unsigned int& nDataSize )  
{  
    if (pDataBuffer == NULL)
    {
    	return false;
    }

    char *p = pDataBuffer;
    int len = nDataSize;
    int ret = 0;
    int returnlen = 0;

    while (len > 0)
    {
    	ret = recv(clientFd, p + (iLen - len), iLen - returnlen, 0);
    	if (ret ==  SOCKET_ERROR || ret == 0)
    	{
    		return false;
    	}
    	len -= ret;
    	returnlen += ret;
    }
    return returnlen;
}  
  
bool NETPacket::SendData( int clientFd, const char* pDataBuffer, const unsigned int& nDataSize )  
{  
   /* NetPacketHeader* pHead = (NetPacketHeader*) m_cbSendBuf;  
    pHead->wOpcode = nOpcode;//操作码  
  
    // 数据封包  
    if ( (nDataSize > 0) && (pDataBuffer != 0) )  
    {  
        CopyMemory(pHead+1, pDataBuffer, nDataSize);   
    }  
  
    // 发送消息  
    const unsigned short nSendSize = nDataSize + sizeof(NetPacketHeader);//包的大小事发送数据的大小加上包头大小  
    pHead->wDataSize = nSendSize;//包大小  
    int ret = ::send(mAcceptSocket, m_cbSendBuf, nSendSize, 0);  
    return (ret > 0) ? true : false;  */
    return false;
}  