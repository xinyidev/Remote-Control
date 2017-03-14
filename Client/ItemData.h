// ItemData.h: interface for the CItemData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMDATA_H__B9768FD0_4687_42A6_A875_48CB58833AA1__INCLUDED_)
#define AFX_ITEMDATA_H__B9768FD0_4687_42A6_A875_48CB58833AA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MySocket.h"
#include "Common.h"

class CItemData: public CDialog  
{
public:
	CItemData(UINT id,SOCKET sock,SOCKADDR_IN *addr,HWND m_hWnd);
	virtual ~CItemData();

	void Run();
    SOCKET GetSocket();
	int m_id;
    CString m_IP;
    CString m_Address;
    CString m_OS;
    CString m_Ver;
    bool Cam;	

private:
	SOCKET m_sock;
    void OnBeginListen();
    CMySocket m_Mysocket;
    HWND m_hWnd;
	void GetSysVer(SYSTEMINFO sys);
	static DWORD WINAPI OnListen(LPVOID lp);
};

#endif // !defined(AFX_ITEMDATA_H__B9768FD0_4687_42A6_A875_48CB58833AA1__INCLUDED_)
