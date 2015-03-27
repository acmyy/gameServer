#include "netpacket.h"

NETPacket::NETPacket()
{

}

NETPacket::~NETPacket()
{

}
  
bool NETPacket::GetData(int clientFd, char* pDataBuffer, const unsigned int& nDataSize )  
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
    	ret = recv(clientFd, p + (nDataSize - len), nDataSize - returnlen, 0);
    	if (ret == -1 || ret == 0)
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
    int ret = ::send(clientFd, pDataBuffer, nDataSize, 0);  
    return (ret > 0) ? true : false;  
}  