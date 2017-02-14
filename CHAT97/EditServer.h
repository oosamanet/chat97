#if !defined(AFX_EDITSERVER_H__9C481413_59AB_11D1_9B6C_0040051AF39C__INCLUDED_)
#define AFX_EDITSERVER_H__9C481413_59AB_11D1_9B6C_0040051AF39C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EditServer.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CEditServer ダイアログ

class CEditServer : public CDialog
{
// コンストラクション
public:
	void UpdateList();
	int m_port[16];
	CString m_host[16];
	CString m_name[16];
	int m_count;
	CEditServer(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CEditServer)
	enum { IDD = IDD_EDITSERVER };
	CListBox	m_list;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CEditServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CEditServer)
	afx_msg void OnSvadd();
	afx_msg void OnSvdel();
	afx_msg void OnSvdown();
	afx_msg void OnSvup();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnGetcgi();
	afx_msg void OnEditchange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_EDITSERVER_H__9C481413_59AB_11D1_9B6C_0040051AF39C__INCLUDED_)
