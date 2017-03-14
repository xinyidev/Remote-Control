// MySocket.h: interface for the CMySocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSOCKET_H__F352F8DD_5F8C_4751_8FFA_A97F9EC60C72__INCLUDED_)
#define AFX_MYSOCKET_H__F352F8DD_5F8C_4751_8FFA_A97F9EC60C72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMySocket  
{
public:
	CMySocket();
	virtual ~CMySocket();
	SOCKET StartSocket(char Address[160]);
	int MyRecv(SOCKET socket,char* buf,int bytes);
	int MySend(SOCKET socket,const char* buf,int bytes);
	int m_port;
};

#endif // !defined(AFX_MYSOCKET_H__F352F8DD_5F8C_4751_8FFA_A97F9EC60C72__INCLUDED_)
