// Member.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CMember ウィンドウ

class CMember : public CListBox
{
// コンストラクション
public:
	CMember();
// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CMember)
	public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CMember();
//	CImageList m_listicon;

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CMember)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchange();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。
