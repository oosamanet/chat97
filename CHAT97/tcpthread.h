#if !defined(AFX_TCPTHREAD_H__ECADFD74_3748_11D1_9B33_0040051AF39C__INCLUDED_)
#define AFX_TCPTHREAD_H__ECADFD74_3748_11D1_9B33_0040051AF39C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TCPThread.h : ヘッダー ファイル
//



/////////////////////////////////////////////////////////////////////////////
// CTCPThread スレッド

class CTCPThread : public CWinThread
{
	DECLARE_DYNCREATE(CTCPThread)
public:
	CTCPThread();           // 動的生成に使用されるプロテクト コンストラクタ
	void SetWnd(CWnd*pWnd);

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CTCPThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	CChatSocket* m_pSocket;
	CWnd* m_pWnd;
	virtual ~CTCPThread();

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CTCPThread)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_TCPTHREAD_H__ECADFD74_3748_11D1_9B33_0040051AF39C__INCLUDED_)
