// ThreadMain.h: interface for the CThreadMain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADMAIN_H__8EE10E5A_B035_4513_91D8_851CD5DCF459__INCLUDED_)
#define AFX_THREADMAIN_H__8EE10E5A_B035_4513_91D8_851CD5DCF459__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Common.h"
#include "MySocket.h"
#include "SystemInfo.h"

class CThreadMain  
{
public:
	CThreadMain();
	virtual ~CThreadMain();

	SOCKET Run();
	void GetInfo();
	bool RunFlag;
	void Command(SOCKET Sock);	
	
private:
	
	
	void ExecCommand(MSGINFO_S msg,SOCKET l_Socket);
	CMySocket m_sock;
	char Address[160];
	SOCKET m_Socket;
	int Time;
	CSystemInfo m_sys;
};

#endif // !defined(AFX_THREADMAIN_H__8EE10E5A_B035_4513_91D8_851CD5DCF459__INCLUDED_)
