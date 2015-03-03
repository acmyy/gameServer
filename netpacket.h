#include "stdafx.h"

class NETPacket  
{  
public:  
    NETPacket();  
    virtual ~NETPacket();  
  
public:  
    
    ///接收数据
    bool GetData(int clientFd, const char* pDataBuffer, const unsigned int& nDataSize);  
  
    /// 发送数据  
    bool SendData(int clientFd, const char* pDataBuffer, const unsigned int& nDataSize);  
  
/*private:  
    SOCKET      mServerSocket;  ///< 服务器套接字句柄  
    sockaddr_in mServerAddr;    ///< 服务器地址  
  
    SOCKET      mAcceptSocket;  ///< 接受的客户端套接字句柄  
    sockaddr_in mAcceptAddr;    ///< 接收的客户端地址  
  
    char        m_cbSendBuf[NET_PACKET_SIZE];  */
};  