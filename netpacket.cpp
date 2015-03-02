#include "netpacket.h"


  
bool NETPacket::GetData( unsigned short nOpcode, const char* pDataBuffer, const unsigned int& nDataSize )  
{  
    NetPacketHeader* pHead = (NetPacketHeader*) m_cbSendBuf;  
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
    return (ret > 0) ? true : false;  
}  
  
bool NETPacket::SendData( unsigned short nOpcode, const char* pDataBuffer, const unsigned int& nDataSize )  
{  
    NetPacketHeader* pHead = (NetPacketHeader*) m_cbSendBuf;  
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
    return (ret > 0) ? true : false;  
}  