// SendMes.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "Chat97Server.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendMes ダイアログ


CSendMes::CSendMes(CString&handle,int clientno,int room)
	: CDialog(CSendMes::IDD, NULL)
{
	m_handle=handle;
	m_clientno=clientno;
	m_room=room;
	//{{AFX_DATA_INIT(CSendMes)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CSendMes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendMes)
                // メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendMes, CDialog)
	//{{AFX_MSG_MAP(CSendMes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendMes メッセージ ハンドラ

BOOL CSendMes::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString s="１２３４５６７８９10";
	s=s.Mid(m_room*2,2);
	s+="号室の";
	s+=m_handle;
	s+="さんに電報を送ります";
	GetDlgItem(IDC_SENDTITLE)->SetWindowText(s);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CSendMes::OnOK() 
{
	GetDlgItem(IDC_SENDMESSAGE)->GetWindowText(mes);
	CDialog::OnOK();
}
