// SendMes.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSendMes ダイアログ

class CSendMes : public CDialog
{
// コンストラクション
public:
	CString mes;
	CSendMes(CString&handle,int clientno,int room);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSendMes)
	enum { IDD = IDD_SENDMESSAGE };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CSendMes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	CString m_handle;
	int m_clientno;
	int m_room;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSendMes)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
