// RoomName.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapClient.h"
#include "RoomName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomName ダイアログ


CRoomName::CRoomName(int room)
	: CDialog(CRoomName::IDD, NULL)
{
	m_room=room;
	//{{AFX_DATA_INIT(CRoomName)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CRoomName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomName)
                // メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRoomName, CDialog)
	//{{AFX_MSG_MAP(CRoomName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomName メッセージ ハンドラ

BOOL CRoomName::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString s;
	CString a="１２３４５６７８９10";
	a=a.Mid(m_room*2,2);
	s.Format("%s号室に名前を付けます",a);
	GetDlgItem(IDC_SENDTITLE)->SetWindowText(s);
	
	return FALSE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CRoomName::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	
	GetDlgItem(IDC_ROOMNAME)->GetWindowText(mes);
	CDialog::OnOK();
}
