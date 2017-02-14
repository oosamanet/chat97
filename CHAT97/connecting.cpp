// Connecting.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapClient.h"
#include "Connecting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnecting ダイアログ


CConnecting::CConnecting(CWnd*pParent,CChatSocket*sock,CString&host,int port)
	: CDialog(CConnecting::IDD, pParent)
{
	m_pParent=pParent;

	m_pSocket=sock;
	m_host=host;
	m_port=port;
	m_timer=0;
	//{{AFX_DATA_INIT(CConnecting)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CConnecting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnecting)
                // メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnecting, CDialog)
	//{{AFX_MSG_MAP(CConnecting)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnecting メッセージ ハンドラ

void CConnecting::OnOK() 
{
}

void CConnecting::OnCancel() 
{
	if (m_timer!=0)
		KillTimer(m_timer);
	
	CDialog::OnCancel();
}

BOOL CConnecting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_pSocket->Connect(m_pParent,m_host,m_port);
	CDialog::OnOK();
//	m_timer=SetTimer(1,100,NULL);

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CConnecting::OnTimer(UINT nIDEvent) 
{
	KillTimer(m_timer);
	m_timer=0;
	m_pSocket->Connect(m_pParent,m_host,m_port);
	CDialog::OnOK();
}
