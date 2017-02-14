// BossString.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapClient.h"
#include "BossString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BossString ダイアログ
BossString::BossString(CWnd* pParent /*=NULL*/)
	: CDialog(BossString::IDD, pParent)
{
	//{{AFX_DATA_INIT(BossString)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}

void BossString::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BossString)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(BossString, CDialog)
	//{{AFX_MSG_MAP(BossString)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BossString メッセージ ハンドラ

BOOL BossString::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_BOSSSTRING)->SetWindowText(m_bossstring);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
}

void BossString::OnOK() 
{
	CWinApp*pApp=AfxGetApp();
	GetDlgItem(IDC_BOSSSTRING)->GetWindowText(m_bossstring);
	pApp->WriteProfileString("CHAT97","BossString",m_bossstring);
	CDialog::OnOK();
}
