// HelpDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapClient.h"
#include "HelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg ダイアログ


CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelpDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelpDlg)
                // メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialog)
	//{{AFX_MSG_MAP(CHelpDlg)
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_SEECHAT97HP, OnSeechat97hp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg メッセージ ハンドラ

void CHelpDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	OnCancel();
}

void CHelpDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	OnCancel();
}

void CHelpDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	OnCancel();
}

BOOL CHelpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString v(NOW_VERSION);
	v=v.Left(4)+"/"+v.Mid(4,2)+"/"+v.Mid(6)+"版";
	GetDlgItem(IDC_VERSION)->SetWindowText(v);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CHelpDlg::OnSeechat97hp() 
{
	CString s="[InternetShortcut]\nURL=http://www.oosama.com/chat";
	CFile fp;
	fp.Open("tmp.URL",CFile::modeCreate|CFile::modeReadWrite);
	fp.Write(s,s.GetLength());
	fp.Close();

	ShellExecute(m_hWnd,"open","tmp.URL",NULL,NULL,SW_SHOW);
}
