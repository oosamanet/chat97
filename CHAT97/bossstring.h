#if !defined(AFX_BOSSSTRING_H__C87EBE81_35F1_11D1_9B31_0040051AF39C__INCLUDED_)
#define AFX_BOSSSTRING_H__C87EBE81_35F1_11D1_9B31_0040051AF39C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BossString.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// BossString ダイアログ

class BossString : public CDialog
{
// コンストラクション
public:
	CString m_bossstring;
	BossString(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(BossString)
	enum { IDD = IDD_BOSSSTRING };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(BossString)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(BossString)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BOSSSTRING_H__C87EBE81_35F1_11D1_9B31_0040051AF39C__INCLUDED_)
