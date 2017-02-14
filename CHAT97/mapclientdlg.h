// MapClientDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CMapClientDlg dialog

#define ROOM_MAX	10

class CMapClientDlg : public CDialog
{
// 構築
public:
	CMapClientDlg(int room);	// 標準のコンストラクタ
	~CMapClientDlg();	// 標準のコンストラクタ
	CWnd* m_room[ROOM_MAX];
	CEdit m_recv;
	CEdit m_send;
	CListBox m_member;
	int m_nowroom;

// Dialog Data
	//{{AFX_DATA(CMapClientDlg)
	enum { IDD = IDD_MAPCLIENT_DIALOG };
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CMapClientDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMapClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

