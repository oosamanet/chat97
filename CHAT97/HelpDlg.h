// HelpDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg ダイアログ

class CHelpDlg : public CDialog
{
// コンストラクション
public:
	CHelpDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CHelpDlg)
	enum { IDD = IDD_HELP };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CHelpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CHelpDlg)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnSeechat97hp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
