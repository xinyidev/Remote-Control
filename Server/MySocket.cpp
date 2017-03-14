// MySocket.cpp: implementation of the CMySocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMySocket::CMySocket()
{

}

CMySocket::~CMySocket()
{

}

SOCKET CMySocket::StartSocket(char Address[160])
{
    WSADATA data;
    WORD w=MAKEWORD(2,2);
    ::WSAStartup(w,&data);
    SOCKET s;
    s=::socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    addr.sin_addr.S_un.S_addr = inet_addr(Address);
    if(::connect(s,(sockaddr*)&addr,sizeof(addr))==SOCKET_ERROR)
    {
        printf("Connect Error\n");
        DWORD e = GetLastError();
        printf("LastError:%d\n",e);
        s = NULL;
    }
    else
    {
        printf("Connect Success!\n");
    }
    return s;
}

int CMySocket::MySend(SOCKET socket,const char* buf,int bytes)
{
	const char *b = buf;
	while(bytes > 0) 
	{ 
		int r = send(socket,b,bytes,0); 
		if(r < 0) 
		{
            printf("Socket_Error\n");
			return r; 
		} 
		else if(r == 0)
		{
            printf("Socket_Error\n");
			break;
		} 
		bytes -= r; 
		b += r; 
	} 
	return b - (char*)buf; 
}

int CMySocket::MyRecv(SOCKET socket,char* buf,int bytes)
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