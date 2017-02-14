// MapClient.h : MAPCLIENT アプリケーションのメイン ヘッダー ファイルです。
//

#define CHAT97_USERICHEDIT

#define DEFAULT_PORT	8000
#define DEFAULT_WORLD	0
#define DEFAULT_NAME	"RUBYサーバ"
#define DEFAULT_HOST	"chat97.oosama.net"

#define GETCGI_HOST		"www.oosama.net"
#define GETCGI_PATH		"/server.txt"
#define GETCGI_PORT		80
#define NOW_VERSION     "20020710"
#define BOSSSTRING		"#4ボスが来ました～"
#define HISTORYMAX		20
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CMapClientApp:
// このクラスの動作の定義に関しては MapClient.cpp ファイルを参照してください。
//
#include "util.h"
#include "user.h"
#include "ChatSock.h"
#include "Send.h"
#include "sethandle.h"
#include "Member.h"
#include "BossString.h"
#include "editserver.h"
#include "addserver.h"

class CMapClientApp : public CWinApp
{
public:
	CMapClientApp();
	void CutESC(CString &str);
	BOOL m_isDebug;
	BOOL m_isAuto;
	BOOL m_isSysOp;
	CString m_host;
	int	m_port;
	int	m_world;

// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CMapClientApp)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CMapClientApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

