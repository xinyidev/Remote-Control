// ThreadMain.cpp: implementation of the CThreadMain class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThreadMain.h"
#include "MySocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThreadMain::CThreadMain()
{

}

CThreadMain::~CThreadMain()
{

}

void CThreadMain::GetInfo()
{
    int Port = 8000;
    this->Time = 60;
    //this->SetupDir = 0;
    //this->AutoFlag = 1;
	m_sock.m_port=Port;
	strcpy(Address,"127.0.0.1");
}

SOCKET CThreadMain::Run()
{
    SOCKET sock;
    while(true)
    {
        sock = m_sock.StartSocket(this->Address);
        if(sock == NULL)
        {
            Sleep(this->Time * 1000);
            printf("Sleep\n");
            continue;
        }
        else
        {
            break;
        }
    }
    return sock;
}

void CThreadMain::Command(SOCKET Sock)
{
    MSGINFO_S msg;
    m_Socket = Sock;
    while(1)
    {
        if(this->RunFlag == false)
        {
            break;
        }
        memset(&msg,0,sizeof(MSGINFO_S));
        if(m_sock.MyRecv(Sock,(char*)&msg,sizeof(MSGINFO_S))==0)
        {
            break;
        }
        ExecCommand(msg,Sock);
    }
    return;
}

void CThreadMain::ExecCommand(MSGINFO_S msg,SOCKET l_Socket)
{
    switch(msg.Msg_id)
	{
	case SYSINFO:
		{
			printf("GetSystemInfo\n");
			m_sys.SendSysinfo(l_Socket);
		}
		break;
	default:
		{
			printf("UnKnow Command\n");
			return;
		}
	}
}