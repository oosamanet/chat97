// MapClient.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "MapClient.h"
#include "panel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapClientApp

BEGIN_MESSAGE_MAP(CMapClientApp, CWinApp)
	//{{AFX_MSG_MAP(CMapClientApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapClientApp クラスの構築

CMapClientApp::CMapClientApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CMapClientApp オブジェクト

CMapClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMapClientApp クラスの初期化

BOOL CMapClientApp::InitInstance()
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

	m_isAuto=FALSE;
	m_isDebug=TRUE;
	m_isSysOp=FALSE;
	CMapClientApp* pApp=(CMapClientApp*)AfxGetApp();
	m_host=pApp->GetProfileString("CHAT97","Host",DEFAULT_HOST);
	m_port=pApp->GetProfileInt("CHAT97","Port",DEFAULT_PORT);
	m_world=pApp->GetProfileInt("CHAT97","World",DEFAULT_WORLD);

//	m_host=DEFAULT_HOST;
//	m_port=DEFAULT_PORT;
	BOOL m_isHost=FALSE;
	BOOL m_isPort=FALSE;
	for (int i=1;i<__argc;i++)
	{	if (m_isHost)
		{	m_host=__argv[i];
			m_isHost=FALSE;
		}
		else if (m_isPort)
		{	m_port=atoi(__argv[i]);
			m_isPort=FALSE;
		}
		else if (0==strcmpi(__argv[i],"-debug"))
		{	m_isDebug=TRUE;
		}
		else if (0==strcmpi(__argv[i],"-host"))
		{	m_isHost=TRUE;
		}
		else if (0==strcmpi(__argv[i],"-port"))
		{	m_isPort=TRUE;
		}
		else if (0==strcmpi(__argv[i],"-auto"))
		{	m_isAuto=TRUE;
		}
		else if((__argv[i][0]=='-')&&
				(__argv[i][1]=='s')&&
				(__argv[i][2]=='y')&&
				(__argv[i][3]=='s')&&
				(__argv[i][4]=='o')&&
				(__argv[i][5]=='p')&&
				(__argv[i][6]=='s')&&
				(__argv[i][7]=='a')&&
				(__argv[i][8]=='k')&&
				(__argv[i][9]=='a')&&
				(__argv[i][10]=='i'))
		{	m_isSysOp=TRUE;
		}
	}
	CPanel*p=new CPanel;
	if (FALSE==p->Create(0))
	{	delete p;
		return FALSE;
	}
	p->ShowWindow(SW_SHOW);
	m_pMainWnd = p;
	((CPanel*)m_pMainWnd)->Connect();
	return TRUE;
}



int CMapClientApp::Run() 
{
	
	return CWinApp::Run();
}

int CMapClientApp::ExitInstance() 
{
//	if (m_pMainWnd)
//	{	delete (CPanel*)m_pMainWnd;
//		m_pMainWnd=NULL;
//	}

	return CWinApp::ExitInstance();
}

void CMapClientApp::CutESC(CString & str)
{
	if (-1==str.Find('#'))
		return;
	CString ret;
	for (int i=0;i<str.GetLength();)
	{	if (_ismbblead((BYTE)str[i]))
		{
			ret+=str.Mid(i,2);
			i+=2;
		}else if ((str[i]=='#')&&
			(i<str.GetLength()-1)&&
			(isdigit(str[i+1])))
		{
			i+=2;
		}else
		{
			ret+=str.Mid(i,1);
			i++;
		}
	}
	str=ret;
	return;
}

