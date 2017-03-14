// ClientDlg.h : header file
//

#if !defined(AFX_CLIENTDLG_H__1B358F72_1C1C_4A91_8719_8546507DA0EB__INCLUDED_)
#define AFX_CLIENTDLG_H__1B358F72_1C1C_4A91_8719_8546507DA0EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

class CClientDlg : public CDialog
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CToolBar m_toolbar;
	CImageList m_imagelist;
	CStatusBar m_statusbar;
	CBitmap m_subbmp[6];
	CImageList m_mainicon;
	void UpdateMain(int port);
	
	UINT m_port;
	UINT m_max;
	UINT m_Sound;

	CRect m_rect;
	SOCKET s;
	bool InitSocket();
	static DWORD WINAPI OninitSocket(LPVOID self);
	void AddHost(SOCKET sock,SOCKADDR_IN addr);
	void GetNewItemData(SOCKET sock,SOCKADDR_IN addr);
	LRESULT OnAddHost(WPARAM wparam,LPARAM lparam);
	LRESULT OnOffLine(WPARAM wparam,LPARAM lparam);
	void ShowOnLine();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__1B358F72_1C1C_4A91_8719_8546507DA0EB__INCLUDED_)
