// Send.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSend ウィンドウ

#ifdef CHAT97_USERICHEDIT
class CSend : public CRichEditCtrl
#else
class CSend : public CEdit
#endif
{
// コンストラクション
public:
	void CopyClip(CString&str);
	CSend();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CSend)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	COLORREF SetBackgroundColor(BOOL bSysColor,COLORREF cr);
	virtual ~CSend();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CSend)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
