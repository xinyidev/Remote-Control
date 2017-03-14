// SystemInfo.cpp: implementation of the CSystemInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemInfo::CSystemInfo()
{

}

CSystemInfo::~CSystemInfo()
{

}

int CSystemInfo::GetSys_ver()
{
    OSVERSIONINFO osver = {sizeof(OSVERSIONINFO)};
	GetVersionEx(&osver);
    int t;
	if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0)
	{
		t = 0;
	}
	
	else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)
	{
		t = 1;
	}
	
    else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0)
    {
        t = 2;
    }
	
	else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)
    {
		t = 3;
    }
	else t = 4;
    return t;
}

void CSystemInfo::SendSysinfo(SOCKET sock)
{
    SYSTEMINFO_S system;
    system.os = GetSys_ver();
    system.ver = 0.1; //°æ±¾ºÅ
    system.Cam = false;
    MSGINFO_S msg;
    memset(&msg,0,sizeof(MSGINFO_S));
    msg.Msg_id = SYSINFO;
    memcpy(msg.context,&system,sizeof(SYSTEMINFO_S));
    m_sock.MySend(sock,(char*)&msg,sizeof(MSGINFO_S));
}