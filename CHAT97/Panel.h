// panel.h : アプリケーションのメイン ヘッダー ファイル
//

#include "richeditctrlex.h"

#define IDC_ROOMLEFT		1100
#define IDC_ROOMRIGHT		1101
#define IDC_RECV			1102
#define IDC_SEND			1103
#define IDC_MEMBER			1104
#define IDC_STATUS			1105
#define IDC_ROOMNO			1106
#define IDC_BBS				1107

#define ROOM_MAX	10
class CPanel : public CFrameWnd
{
	DECLARE_DYNAMIC(CPanel)
public:
	void OnGame(int gameno);
	void OnFiletran();
	void MemberStatus(int clientno);
	void StatusRoom(int room);
	void RoomMove(int newroom);
	BOOL Connect();
	void OnLookRoom(int room);
	void SetTitle();
	void SetColor(CWnd*edit,COLORREF color);
	void AddText(CString &str,COLORREF color,BOOL isFormat);
	void AddString(CString &str);
	void UpdateMember(int room);
	void OnSend(CString &s);
	void OnRecv(CStringList&list);
	void SetTray(int cmd,HICON hIcon,CString str);
	BOOL m_isConnect;
	BOOL m_isLogClear;
	BOOL m_isBoss;
	BOOL m_isTimeDisp;
	BOOL m_isToolBar;
	CUserList m_user[ROOM_MAX];
	NOTIFYICONDATA nd;
	int m_nowroom;
	int m_lookroom;
	HCURSOR	m_crLink;
	CFont m_topfont;
	int m_gamecount;
	CStringList m_gamename;
	CStringList m_gamepath;
// アトリビュート
public:
//	CToolTipCtrl m_tooltip;
	CString m_exitSound;			//切断音
	CString m_enterSound;			//ログイン
	CString m_disconnectSound;		//切断音
	CString m_telegramSound;		//電報音
	CString m_enterRoomSound;		//入室音
	CString m_exitRoomSound;		//退室音
	CChatSocket* m_socket;
//	CTCPThread *m_tcpthread;
	CMenu m_menu;
	COLORREF m_chatBackColor;
	COLORREF m_chatHandleColor;
	COLORREF m_chatCharColor;
	LOGFONT m_logfont;
//	CWnd* m_room[ROOM_MAX];
#ifdef CHAT97_USERICHEDIT
	CRichEditCtrlEx m_recv;
#else
	CEdit m_recv;
#endif
	CSend m_send;
	CString m_host;
	int m_port;
	CString m_handle;
	CString m_profile;
	CString m_mail;
	CString m_homepage;
	CMenu m_rmenu;
	int m_clientno;
	int m_level;
	CMember m_member;
	LPCTSTR m_lpszClassName;
	CButton m_roomleft;
	CButton m_roomright;
	CStatic m_roomno;
	CStatic m_bbs;
	CPanel* m_pParent;
	CPtrList m_list;
	CStatusBarCtrl m_status;
//	CSplitterWnd m_splitter1;

	// オペレーション
public:
	BOOL Create(CPanel* pWnd,LPCTSTR pClassName,int x,int y,int w,int h);
	BOOL Create(int room);
	void OnNotifyIcon(WPARAM wParam,LPARAM lParam);
// オーバーライド
	// ClassWizard は仮想関数を生成しオーバーライドします。
	//{{AFX_VIRTUAL(CPanel)
	protected:
	virtual void PostNcDestroy();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void OnRichEditExLink(NMHDR*   in_pNotifyHeader,LRESULT* out_pResult);
	int m_LED;
	int m_timer;
	void controlLED(BOOL onoff,int key);
	void GetGameInfo(void);
	BOOL m_isFlash;
	int m_hisNow;
	int m_hisEnd;
	int m_hisStart;
	CString m_history[HISTORYMAX];
	CString m_bossstring;
	CPanel();
	virtual ~CPanel();
	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	void OnConnect();
	afx_msg void OnConnectButton();
	afx_msg void OnDisconnectButton();

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CPanel)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnChatbackColor();
	afx_msg void OnChatcharcolor();
	afx_msg void OnChathandlecolor();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnSave();
	afx_msg void OnFont();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSendmessage();
	afx_msg void OnRoomname();
	afx_msg void OnMemberdown();
	afx_msg void OnMemberup();
	afx_msg void OnNextroom();
	afx_msg void OnHelp();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnEntersound();
	afx_msg void OnExitsound();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMailcopy();
	afx_msg void OnBoss();
	afx_msg void OnIsboss();
	afx_msg void OnGetip();
	afx_msg void OnDisconnectsound();
	afx_msg void OnEnterroomsound();
	afx_msg void OnTelegramsound();
	afx_msg void OnExitroomsound();
	afx_msg void OnIstoolbar();
	afx_msg void OnSameroom();
	afx_msg void OnLogclear();
	afx_msg void OnIslogclear();
	afx_msg void OnSeehomepage();
	afx_msg void OnBackroom();
	afx_msg void OnKill();
	afx_msg void OnRoom(UINT nID);
	afx_msg void OnSethandle();
	afx_msg void OnBossstring();
	afx_msg void OnClose();
	afx_msg void OnColor(UINT nId);
	afx_msg void OnTimedisp();
	afx_msg void OnPrevhistory();
	afx_msg void OnNexthistory();
	afx_msg void OnRighthandle();
	afx_msg void OnLefthandle();
	afx_msg void OnHelp2();
	afx_msg void OnServerstatus();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnOMAE();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
