#if !defined(AFX_SETHANDLE_H__96E2F7E1_3454_11D1_9B2E_0040051AF39C__INCLUDED_)
#define AFX_SETHANDLE_H__96E2F7E1_3454_11D1_9B2E_0040051AF39C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SetHandle.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSetHandle ダイアログ

class CSetHandle : public CDialog
{
// コンストラクション
public:
	CString m_homepage;
	CString m_mail;
	CString m_profile;
	CString m_handle;
	CSetHandle(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSetHandle)
	enum { IDD = IDD_SETHANDLE };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CSetHandle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSetHandle)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SETHANDLE_H__96E2F7E1_3454_11D1_9B2E_0040051AF39C__INCLUDED_)
