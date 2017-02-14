// RoomStc.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CRoomStc ウィンドウ

class CRoomStc : public CStatic
{
// コンストラクション
public:
	CRoomStc(int room);

// アトリビュート
public:
	int m_room;

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CRoomStc)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CRoomStc();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CRoomStc)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
