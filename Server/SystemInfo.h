// SystemInfo.h: interface for the CSystemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMINFO_H__56C58DB3_4FD9_4F67_AD98_98F4696A6CD0__INCLUDED_)
#define AFX_SYSTEMINFO_H__56C58DB3_4FD9_4F67_AD98_98F4696A6CD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MySocket.h"
#include "Common.h"

class CSystemInfo  
{
public:
	CSystemInfo();
	virtual ~CSystemInfo();
	int GetSys_ver();
	void SendSysinfo(SOCKET sock);
	CMySocket m_sock;
};

#endif // !defined(AFX_SYSTEMINFO_H__56C58DB3_4FD9_4F67_AD98_98F4696A6CD0__INCLUDED_)
