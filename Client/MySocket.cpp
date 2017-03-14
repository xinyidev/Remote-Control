// MySocket.cpp: implementation of the CMySocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "MySocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMySocket::CMySocket()
{

}

CMySocket::~CMySocket()
{

}

void CMySocket::Clean()
{
    ::WSACleanup();
}

int CMySocket::SendCommand(SOCKET socket,const char* buf,int bytes)
{
    const char *b = buf;
	while(bytes > 0) 
	{ 
		int r = send(socket,b,bytes,0); 
		if(r < 0) 
		{ 
			return r; 
		} 
		else if(r == 0)
		{
			break;
		} 
		bytes -= r; 
		b += r; 
	} 
	return b - (char*)buf;
}

int CMySocket::RecvCommand(SOCKET socket,char* buf,int bytes)
{
    char *b = (char*)buf;
    while(bytes > 0)
    {
        int r = recv(socket,b,bytes,0);
        if(r < 0)
        {
            return 0;
        }
        else if(r == 0)
        {
            break;
        }
        bytes = bytes - r;
        b = b + r;
    }
    return b - (char*)buf;
}