// Chat97Server.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "Chat97Server.h"
#include "Chat97ServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChat97ServerApp

BEGIN_MESSAGE_MAP(CChat97ServerApp, CWinApp)
	//{{AFX_MSG_MAP(CChat97ServerApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChat97ServerApp クラスの構築

CChat97ServerApp::CChat97ServerApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CChat97ServerApp オブジェクト

CChat97ServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CChat97ServerApp クラスの初期化

BOOL CChat97ServerApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif
	if (__argc > 1)
	{	m_port=atoi(__argv[1]);
	}else
	{	m_port=PORT;
	}

	CChat97ServerDlg* dlg=new CChat97ServerDlg;
	m_pMainWnd = dlg;
	dlg->Create(IDD_CHAT97SERVER_DIALOG);

	return TRUE;
}

