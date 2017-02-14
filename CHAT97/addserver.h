#if !defined(AFX_ADDSERVER_H__9C481414_59AB_11D1_9B6C_0040051AF39C__INCLUDED_)
#define AFX_ADDSERVER_H__9C481414_59AB_11D1_9B6C_0040051AF39C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AddServer.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CAddServer ダイアログ

class CAddServer : public CDialog
{
// コンストラクション
public:
	void SetData(CString name,CString host,UINT port);
	CAddServer(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAddServer)
	enum { IDD = IDD_ADDSERVER };
	CString	m_address;
	CString	m_name;
	UINT	m_port;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CAddServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAddServer)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ADDSERVER_H__9C481414_59AB_11D1_9B6C_0040051AF39C__INCLUDED_)
