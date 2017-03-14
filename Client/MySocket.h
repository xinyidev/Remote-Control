// MySocket.h: interface for the CMySocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSOCKET_H__13701A5E_00B9_41B0_981B_4E6953FAA645__INCLUDED_)
#define AFX_MYSOCKET_H__13701A5E_00B9_41B0_981B_4E6953FAA645__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMySocket  
{
public:
	CMySocket();
	virtual ~CMySocket();
	
	int RecvCommand(SOCKET socket,char* buf,int bytes);
	int SendCommand(SOCKET socket,const char* buf,int bytes);
	void Clean();
};

#endif // !defined(AFX_MYSOCKET_H__13701A5E_00B9_41B0_981B_4E6953FAA645__INCLUDED_)
