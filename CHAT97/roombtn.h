// RoomBtn.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CRoomBtn ウィンドウ

class CRoomBtn : public CButton
{
// コンストラクション
public:
	CRoomBtn(int room);

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CRoomBtn)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CRoomBtn();

	// 生成されたメッセージ マップ関数
protected:
	int m_room;
	//{{AFX_MSG(CRoomBtn)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
