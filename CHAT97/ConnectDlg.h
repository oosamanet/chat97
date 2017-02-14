// ConnectDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg ダイアログ

class CConnectDlg : public CDialog
{
// コンストラクション
public:
	CConnectDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ
	CString m_host;
	int m_port;
	CString m_handle;
	CString m_profile;
	CString m_mail;
	CString m_homepage;
	CString m_room;
	int getCGI();

// ダイアログ データ
	//{{AFX_DATA(CConnectDlg)
	enum { IDD = IDD_CONNECT };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CConnectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CConnectDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnEditserver();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
