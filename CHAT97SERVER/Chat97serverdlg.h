// Chat97ServerDlg.h : ヘッダー ファイル
//

#if !defined(AFX_CHAT97SERVERDLG_H__2A66FFC7_38A1_11D1_9B33_0040051AF39C__INCLUDED_)
#define AFX_CHAT97SERVERDLG_H__2A66FFC7_38A1_11D1_9B33_0040051AF39C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CChat97ServerDlg dialog

class CChat97ServerDlg : public CDialog
{
// 構築
public:
	CChatSocket* pClient;
	CMenu m_rmenu;
	UINT g_clientno;
	void SetTray(int cmd,HICON hIcon,CString str);
	void SetInfo(BOOL isListRefresh=TRUE);
	NOTIFYICONDATA nd;
	CChatSocket m_server;
	void OnAccept(void);
	void OnClose(int clientno);
	CChat97ServerDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	cPtrList user;
	CString hotspot[10];

// Dialog Data
	//{{AFX_DATA(CChat97ServerDlg)
	enum { IDD = IDD_CHAT97SERVER_DIALOG };
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CChat97ServerDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	virtual void PostNcDestroy();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;
	void OnNotifyIcon(WPARAM wParam,LPARAM lParam);

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CChat97ServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnRoomgo();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnGetipaddress();
	afx_msg void OnSendmessage();
	virtual void OnOK();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnInitMenu(CMenu* pMenu);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CHAT97SERVERDLG_H__2A66FFC7_38A1_11D1_9B33_0040051AF39C__INCLUDED_)
