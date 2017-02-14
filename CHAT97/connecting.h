// Connecting.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CConnecting ダイアログ

class CConnecting : public CDialog
{
// コンストラクション
public:
	CConnecting(CWnd*pParent,CChatSocket*sock,CString&host,int port);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CConnecting)
	enum { IDD = IDD_CONNECTING };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CConnecting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	CString m_host;
	int m_port;
	CChatSocket *m_pSocket;
	UINT m_timer;
	CWnd*m_pParent;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CConnecting)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
