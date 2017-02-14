#if !defined(AFX_SRVSOCKET_H__ECADFD73_3748_11D1_9B33_0040051AF39C__INCLUDED_)
#define AFX_SRVSOCKET_H__ECADFD73_3748_11D1_9B33_0040051AF39C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SrvSocket.h : ヘッダー ファイル
//



/////////////////////////////////////////////////////////////////////////////
// CSrvSocket コマンド ターゲット

class CSrvSocket : public CSocket
{
// アトリビュート
public:

// オペレーション
public:
	CSrvSocket();
	virtual ~CSrvSocket();

// オーバーライド
public:
	CWnd* m_pWnd;
	CPtrList m_client;
	BOOL Connect(CWnd*pWnd,CString host,int port);
	BOOL Init(int port);
	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CSrvSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSrvSocket)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG

// インプリメンテーション
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SRVSOCKET_H__ECADFD73_3748_11D1_9B33_0040051AF39C__INCLUDED_)
