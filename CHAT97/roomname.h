// RoomName.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CRoomName ダイアログ

class CRoomName : public CDialog
{
// コンストラクション
public:
	CString mes;
	CRoomName(int room);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CRoomName)
	enum { IDD = IDD_ROOMNAME };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CRoomName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	int m_room;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CRoomName)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
