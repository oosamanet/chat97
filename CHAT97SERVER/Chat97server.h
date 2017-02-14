// Chat97Server.h : CHAT97SERVER アプリケーションのメイン ヘッダー ファイルです。
//

#define NOWVERSION	990919
#define CLIENTVERSION	971108
#define PORT		8000

#define  CMD_ELSE			0
#define  CMD_GETRANGEXY		1
#define  CMD_GETALLXY		2
#define  CMD_LOGIN			3
#define  CMD_LOGOUT			4
#define  CMD_ROOM			5
#define  CMD_MOVE			6
#define  CMD_SETHOTSPOT		7
#define  CMD_GETALLHOTSPOT	8
#define  CMD_KILL			9
#define  CMD_GETIPADDRESS	10
#define  CMD_SETVERSION		11
#define  CMD_CHAT			12
#define  CMD_SETHANDLE		13
#define  CMD_HTTP			99
#define  CMD_USER			999

#define  SEQ_NAME			1
#define  SEQ_HEAD			2
#define  SEQ_BODY			3




#if !defined(AFX_CHAT97SERVER_H__2A66FFC5_38A1_11D1_9B33_0040051AF39C__INCLUDED_)
#define AFX_CHAT97SERVER_H__2A66FFC5_38A1_11D1_9B33_0040051AF39C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル
#include "util.h"
#include "user.h"
#include "chatsock.h"
#include "sendmes.h"

/////////////////////////////////////////////////////////////////////////////
// CChat97ServerApp:
// このクラスの動作の定義に関しては Chat97Server.cpp ファイルを参照してください。
//

class CChat97ServerApp : public CWinApp
{
public:
	CChat97ServerApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CChat97ServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
	int m_port;

	//{{AFX_MSG(CChat97ServerApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CHAT97SERVER_H__2A66FFC5_38A1_11D1_9B33_0040051AF39C__INCLUDED_)
