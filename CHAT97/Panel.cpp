// panel.cpp : アプリケーションのメイン ヘッダー ファイル
//

#include "stdafx.h"
#include "MapClient.h"
#include "Panel.h"
#include "ConnectDlg.h"
#include "SendMes.h"
#include "RoomName.h"
#include "HelpDlg.h"

#define WM_NOTIFYICON		(WM_USER+100)

#define SECURITY_ROOT	0
#define SECURITY_SYSOP	10
#define SECURITY_LEADER	100
#define SECURITY_USER	1000

/////////////////////////////////////////////////////////////////////////////
// CPanel

IMPLEMENT_DYNAMIC(CPanel, CFrameWnd)

BEGIN_MESSAGE_MAP(CPanel, CFrameWnd)
	//{{AFX_MSG_MAP(CPanel)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND(IDM_CHATBACK_COLOR_, OnChatbackColor)
	ON_COMMAND(IDM_CHATCHARCOLOR, OnChatcharcolor)
	ON_COMMAND(IDM_CHATHANDLECOLOR, OnChathandlecolor)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(IDM_SAVE, OnSave)
	ON_COMMAND(IDM_FONT, OnFont)
	ON_WM_TIMER()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_SENDMESSAGE, OnSendmessage)
	ON_COMMAND(IDM_ROOMNAME, OnRoomname)
	ON_COMMAND(IDM_MEMBERDOWN, OnMemberdown)
	ON_COMMAND(IDM_MEMBERUP, OnMemberup)
	ON_COMMAND(IDM_NEXTROOM, OnNextroom)
	ON_COMMAND(IDM_HELP, OnHelp)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(IDM_ENTERSOUND, OnEntersound)
	ON_COMMAND(IDM_EXITSOUND, OnExitsound)
	ON_WM_LBUTTONUP()
	ON_COMMAND(IDM_MAILCOPY, OnMailcopy)
	ON_COMMAND(IDM_BOSS, OnBoss)
	ON_COMMAND(IDM_ISBOSS, OnIsboss)
	ON_COMMAND(IDM_GETIP, OnGetip)
	ON_COMMAND(IDM_DISCONNECTSOUND, OnDisconnectsound)
	ON_COMMAND(IDM_ENTERROOMSOUND, OnEnterroomsound)
	ON_COMMAND(IDM_TELEGRAMSOUND, OnTelegramsound)
	ON_COMMAND(IDM_EXITROOMSOUND, OnExitroomsound)
	ON_COMMAND(IDM_ISTOOLBAR, OnIstoolbar)
	ON_COMMAND(IDM_SAMEROOM, OnSameroom)
	ON_COMMAND(IDM_LOGCLEAR, OnLogclear)
	ON_COMMAND(IDM_ISLOGCLEAR, OnIslogclear)
	ON_COMMAND(IDM_SEEHOMEPAGE, OnSeehomepage)
	ON_COMMAND(IDM_BACKROOM, OnBackroom)
	ON_COMMAND(IDM_KILL, OnKill)
	ON_COMMAND(IDM_SETHANDLE, OnSethandle)
	ON_COMMAND(IDM_BOSSSTRING, OnBossstring)
	ON_WM_CLOSE()
	ON_COMMAND_RANGE(IDM_COLOR0,IDM_COLOR9, OnColor)
	ON_COMMAND(IDM_TIMEDISP, OnTimedisp)
	ON_COMMAND(IDM_PREVHISTORY, OnPrevhistory)
	ON_COMMAND(IDM_NEXTHISTORY, OnNexthistory)
	ON_COMMAND(IDM_RIGHTHANDLE, OnRighthandle)
	ON_COMMAND(IDM_LEFTHANDLE, OnLefthandle)
	ON_COMMAND(ID_HELP, OnHelp2)
	ON_COMMAND(IDM_SERVERSTATUS, OnServerstatus)
	ON_WM_KILLFOCUS()
	ON_COMMAND(IDM_omae, OnOMAE)
	ON_NOTIFY( EN_LINK, IDC_RECV, OnRichEditExLink )
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_CONNECT, OnConnectButton)
	ON_COMMAND(IDM_DISCONNECT, OnDisconnectButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanel クラスの構築/消滅

CPanel::CPanel()
{
	CWinApp*pApp=AfxGetApp();

	m_bossstring=pApp->GetProfileString("CHAT97","BossString",BOSSSTRING);

	m_chatBackColor=pApp->GetProfileInt("CHAT97","BackColor",RGB(0x0,0x0,0x0));
	m_chatHandleColor=pApp->GetProfileInt("CHAT97","HandleColor",RGB(0x80,0xff,0xff));
	m_chatCharColor=pApp->GetProfileInt("CHAT97","CharColor",RGB(0xff,0xff,0xff));

	m_enterSound=pApp->GetProfileString("CHAT97","EnterSound","none");
	m_exitSound=pApp->GetProfileString("CHAT97","ExitSound","none");
	m_enterRoomSound=pApp->GetProfileString("CHAT97","EnterRoomSound","none");
	m_exitRoomSound=pApp->GetProfileString("CHAT97","ExitRoomSound","none");
	m_telegramSound=pApp->GetProfileString("CHAT97","TelegramSound","none");
	m_disconnectSound=pApp->GetProfileString("CHAT97","DisconnectSound","none");

	m_isBoss=pApp->GetProfileInt("CHAT97","Boss",0);
	m_isToolBar=pApp->GetProfileInt("CHAT97","ToolBar",1);
	m_isLogClear=pApp->GetProfileInt("CHAT97","LogClear",0);
	m_isTimeDisp=pApp->GetProfileInt("CHAT97","TimeDisp",0);

	m_isConnect=FALSE;
	m_lpszClassName = NULL;
	m_clientno=-1;
	m_socket=NULL;
	m_hisStart=0;
	m_hisEnd=0;
	m_hisNow=0;
	m_isFlash=FALSE;
	m_nowroom=0;
	m_timer=0;
	m_LED=0;
}

CPanel::~CPanel()
{
//	if (!m_isConnect)
//		return;
	if (m_socket)
	{	m_socket->Close();
		delete m_socket;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPanelメッセージ ハンドラ
BOOL CPanel::Create(CPanel* pWnd,LPCTSTR pClassName,int x,int y,int w,int h)
{
	BOOL bReturn;
	m_lpszClassName=pClassName;
	m_pParent=pWnd;
	// TODO: Add your specialized code here and/or call the base class
	bReturn= CreateEx(WS_EX_MDICHILD|WS_EX_CONTROLPARENT,
		m_lpszClassName, _T(""), 
		WS_CHILD|WS_VISIBLE|WS_BORDER|WS_CLIPCHILDREN,
		x*80,y*60,10*80,20*60,
		pWnd->GetSafeHwnd(), NULL, NULL );
	return bReturn;
}

BOOL CPanel::Create(int room)
{
	static char NEAR c_szName[] = "CHAT97Class";
	if (!((CMapClientApp*)AfxGetApp())->m_isDebug)
	{	CWnd*pPanel;
		if (pPanel=FindWindow(c_szName,NULL))
		{	pPanel->SetForegroundWindow();
			return FALSE;
		}
	}
	CConnectDlg dlg;
	BOOL ret=dlg.DoModal();
	if (ret==IDCANCEL)
		return FALSE;
	m_nowroom=room;
	m_lookroom=room;
	m_handle=dlg.m_handle;
	m_profile=dlg.m_profile;
	m_mail=dlg.m_mail;
	m_homepage=dlg.m_homepage;
	m_host=dlg.m_host;
	m_port=dlg.m_port;
	CRect rect(0, 80, 500, 480);

    // Register a class with no cursor
	if (m_lpszClassName == NULL)
	{
		WNDCLASS c_wndclass;
		HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_DEADCHAT97);
    	m_lpszClassName = AfxRegisterWndClass(CS_DBLCLKS,
			::LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW)),0,
			m_hIcon);
		GetClassInfo(AfxGetInstanceHandle(), m_lpszClassName, &c_wndclass);
		c_wndclass.lpszClassName = c_szName;
		RegisterClass(&c_wndclass);
	}

	int x=AfxGetApp()->GetProfileInt("CHAT97","x",50);
	int y=AfxGetApp()->GetProfileInt("CHAT97","y",50);

	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	if (w <= x)
		x=50;
	if (h <= y)
		y=50;
	if (x<=0)
		x=50;
	if (y<=0)
		y=50;
	m_menu.LoadMenu(IDR_CHAT97);
	// TODO: Add your specialized code here and/or call the base class
	CreateEx(WS_EX_CONTROLPARENT, c_szName, _T("CHAT97"), 
		WS_CLIPCHILDREN|WS_VISIBLE|WS_OVERLAPPEDWINDOW|WS_BORDER,
		x, y, rect.Width(), rect.Height(), 
		NULL, m_menu.m_hMenu);
	LoadAccelTable(MAKEINTRESOURCE(IDR_CHAT97));
	SetTimer(1,125,NULL);
	CWinApp* pApp=AfxGetApp();
	int height=pApp->GetProfileInt("CHAT97","FontHeight",-13);
	TRACE("font height=%d\n",height);
	CString face=pApp->GetProfileString("CHAT97","FontFace","ＭＳ Ｐゴシック");
	m_topfont.CreateFont(-12,0,0,0,FW_NORMAL,FALSE,FALSE,0,
		SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,"ＭＳ Ｐゴシック");
#ifdef CHAT97_USERICHEDIT
	CFont font;
	font.CreateFont(height,0,0,0,FW_NORMAL,FALSE,FALSE,0,
		SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,face);
	font.GetLogFont(&m_logfont);
	m_recv.SetFont(&font);
#endif
	return TRUE;
}

BOOL CPanel::PreCreateWindow(CREATESTRUCT& cs) 
{
/*    WNDCLASS c_wndclass;
    static char NEAR c_szName[] = "CHAT97Class";
#ifdef _DEBUG
    GetClassInfo(AfxGetInstanceHandle(), "AfxFrameOrView40d", &c_wndclass);
#else
    GetClassInfo(AfxGetInstanceHandle(), "AfxFrameOrView40", &c_wndclass);
#endif
	c_wndclass.lpszMenuName = NULL;
    c_wndclass.lpszClassName = c_szName;
    c_wndclass.hIcon = AfxGetApp()->LoadIcon(IDR_CHAT97);
    RegisterClass(&c_wndclass);
    cs.lpszClass = c_szName;
	cs.hMenu=m_menu.m_hMenu;
*/	return CFrameWnd::PreCreateWindow(cs);
}
void CPanel::PostNcDestroy() 
{
	CWnd::PostNcDestroy();
	delete this;
}


BOOL CPanel::OnCommand(WPARAM wParam, LPARAM lParam)
{
	int wCode=HIWORD(wParam);
	int wID=LOWORD(wParam);
/*	if ((wID>=IDC_ROOM)&&(wID<IDC_ROOM+ROOM_MAX))
	{
		if (!m_isConnect)
			return FALSE;
		int room=wID-1000;
		if (m_nowroom==room)
			return FALSE;
		CString out;
		char tmp[256];
		CRect rect;
		GetClientRect(&rect);
		int width=rect.right-rect.left+1;

		sprintf(tmp,"%d",m_user[m_nowroom].getCount());
		rect.left=width*m_nowroom/ROOM_MAX;
		rect.top=0;
		rect.right=rect.left+width/ROOM_MAX-2;
		rect.bottom=30;

//		m_tooltip.DelTool(m_room[m_nowroom],(m_nowroom==0)?IDS_ROOM1:IDS_ROOMOTHER);

		delete m_room[m_nowroom];
		m_room[m_nowroom]=new CRoomBtn(m_nowroom);
		((CButton*)m_room[m_nowroom])->Create(tmp,
			WS_VISIBLE|WS_BORDER|WS_CHILD|
			BS_PUSHBUTTON,
			rect,this,IDC_ROOM+m_nowroom);
//		m_tooltip.AddTool(m_room[m_nowroom],(m_nowroom==0)?IDS_ROOM1:IDS_ROOMOTHER);

		m_nowroom=room;
		m_lookroom=room;

		sprintf(tmp,"%d",m_user[m_nowroom].getCount());
		rect.left=width*m_nowroom/ROOM_MAX;
		rect.top=0;
		rect.right=rect.left+width/ROOM_MAX-2;
		rect.bottom=30;
//		m_tooltip.DelTool(m_room[m_nowroom],(m_nowroom==0)?IDS_ROOM1:IDS_ROOMOTHER);
		delete m_room[m_nowroom];
		m_room[m_nowroom]=new CRoomStc(m_nowroom);
		((CStatic*)m_room[m_nowroom])->Create(tmp,
				WS_VISIBLE|WS_CHILD|
				SS_CENTER|SS_NOTIFY,
			rect,this,IDC_ROOM+m_nowroom);
//		m_tooltip.AddTool(m_room[m_nowroom],(m_nowroom==0)?IDS_ROOM1:IDS_ROOMOTHER);

//		int len = m_recv.GetWindowTextLength();
//		m_recv.SetSel(0,len);
//		m_recv.ReplaceSel(CString());
		CString s;
		out="ROOM\n";
		s.Format("handle: %s\n",m_handle);
		out+=s;
		s.Format("room: %d\n",m_nowroom);
		out+=s;
		out+="\n\n";
		m_socket->SendMessage(out);
		return FALSE;
	}
*/	if (wID==IDC_ROOMNO)
	{
		OnLookRoom(m_nowroom);
	}
	else if (wID==IDC_ROOMLEFT)
	{
		for (int i=m_lookroom-1;i>=0;i--)
		{	if (m_user[i].getCount()>0)
				break;
		}
		if (i>=0)
			OnLookRoom(i);
	}
	else if (wID==IDC_ROOMRIGHT)
	{
		for (int i=m_lookroom+1;i<ROOM_MAX;i++)
		{	if (m_user[i].getCount()>0)
				break;
		}
		if (i<ROOM_MAX)
			OnLookRoom(i);
	}
	else if (wID==IDC_MEMBER)
	{
	}
	return CFrameWnd::OnCommand(wParam, lParam);
}

void CPanel::OnMemberdown()
{
	int count=m_member.GetCount();
	int sel=m_member.GetCurSel();
	sel++;
	if (sel < count)
	{	m_member.SetCurSel(sel);
		int clientno=m_member.GetItemData(sel);
		m_user[m_lookroom].SetSelect(clientno);
		MemberStatus(clientno);
	}
}

void CPanel::OnMemberup()
{
	int sel=m_member.GetCurSel();
	sel--;
	if (sel >= 0)
	{	m_member.SetCurSel(sel);
		int clientno=m_member.GetItemData(sel);
		m_user[m_lookroom].SetSelect(clientno);
		MemberStatus(clientno);
	}
}

void CPanel::MemberStatus(int clientno)
{
	CString s,h,p,m,hp;
	m_user[m_lookroom].Search(&h,&p,clientno);
	int l=p.Find("####");
	m=p.Left(l);
	p=p.Mid(l+4);
	l=p.Find("####");
	if (l!=-1)
	{	hp=p.Mid(l+4);
		p=p.Left(l);
		l=hp.Find("####");
		if (l!=-1)
			hp=hp.Left(l);
	}
	if (hp.GetLength())
		hp="HP有り";
	else
		hp="HP無し";
	s.Format("%s<%s>%s[%s]",h,m,hp,p);
	((CMapClientApp*)AfxGetApp())->CutESC(s);
	m_status.SetWindowText(s);
}

void CPanel::OnNextroom()
{
	for (int i=m_lookroom+1;i!=m_lookroom;i++)
	{
		if (i>=ROOM_MAX)
			i=0;
		if (m_user[i].getCount()>0)
			break;
	}
	if (i!=m_lookroom)
	{	OnLookRoom(i);
	}
	StatusRoom(i);
	m_send.SetFocus();
}

void CPanel::OnBackroom() 
{
	for (int i=m_lookroom-1;i!=m_lookroom;i--)
	{
		if (i<0)
			i=ROOM_MAX-1;
		if (m_user[i].getCount()>0)
			break;
	}
	if (i!=m_lookroom)
	{	OnLookRoom(i);
	}
	StatusRoom(i);
	m_send.SetFocus();
}

void CPanel::OnLookRoom(int room)
{
	if ((room<0)||(room>=ROOM_MAX))
		return;
	if (m_lookroom!=room)
	{	m_lookroom=room;
		UpdateMember(m_lookroom);
	}
}

#define EHEIGHT	32

void CPanel::OnSize(UINT nType, int cx, int cy) 
{
TRACE("Size:%d,%d,%d,%d,%d,%d\n",nType,
	  SIZE_MAXIMIZED,SIZE_MINIMIZED,SIZE_RESTORED,SIZE_MAXHIDE,SIZE_MAXSHOW);
	if (nType==SIZE_MINIMIZED)
	{
		CString s;
		s.Format("%d人[%s]",
			m_user[m_nowroom].getCount(),
			m_user[m_nowroom].GetName());
		SetWindowText(s);
		m_isFlash=FALSE;
		return;
	}
	else if (nType==SIZE_RESTORED)
	{
		SetTitle();
		m_LED=1;
	}
//	Invalidate(FALSE);
//	CWnd::OnSize(nType,cx,cy);
	CRect rect;
	int statusheight;
	m_status.GetWindowRect(&rect);
	statusheight=rect.bottom-rect.top;
	GetClientRect(&rect);
	rect.bottom-=statusheight;
	int width=rect.right-rect.left+1;
	int height=rect.bottom-rect.top+1;
	int roomheight=20;
	if (!m_isToolBar)
		roomheight=0;
/*	for (int i=0;i<ROOM_MAX;i++)
	{
		m_room[i]->SetWindowPos(NULL,
			width*i/ROOM_MAX,	0,
			width/ROOM_MAX-2,		30,
		SWP_NOZORDER);
		m_room[i]->Invalidate();
	}
*/	m_recv.SetWindowPos(NULL,
		0,	roomheight,
		width-150,		height-(EHEIGHT+roomheight),
		SWP_NOZORDER);
	m_member.SetWindowPos(NULL,
		width-150,	20+roomheight,
		150,		height-(20+EHEIGHT+roomheight),
		SWP_NOZORDER);
//	m_member.Invalidate();
	m_send.SetWindowPos(NULL,
		0,	height-EHEIGHT,
		width,		EHEIGHT,
		SWP_NOZORDER);
	m_send.SetFocus();
	m_roomleft.SetWindowPos(NULL,
		width-150,	roomheight,
		40,		20,
		SWP_NOZORDER);
	m_roomright.SetWindowPos(NULL,
		width-40,	roomheight,
		40,		20,
		SWP_NOZORDER);
	m_roomno.SetWindowPos(NULL,
		width-110,	roomheight,
		70,		20,
		SWP_NOZORDER);
	m_status.SetWindowPos(NULL,
		0,	height,
		width,		statusheight,
		SWP_NOZORDER);
/*	m_bbs.SetWindowPos(NULL,
		width-32,	height-48,
		32,		32,
		SWP_NOZORDER);
*/
	Invalidate(FALSE);
}

int CPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
//	EnableToolTips(TRUE);
	CRect rect;
	GetClientRect(&rect);

	m_crLink = AfxGetApp()->LoadIcon(IDC_LINKHAND);

	m_rmenu.LoadMenu(IDR_RMENU);
	rect.top=rect.bottom-30;
//	m_tooltip.Create(this,WS_VISIBLE);
//	m_tooltip.Activate(TRUE);
	m_status.Create(CCS_BOTTOM|SBARS_SIZEGRIP|
		WS_VISIBLE|WS_CHILD,rect,this,IDC_STATUS);

	GetClientRect(&rect);
	int l=rect.left;
	int width=rect.right-rect.left+1;
	rect.bottom=rect.top+30;
/*	for (int i=0;i<ROOM_MAX;i++)
	{
		rect.left=i*width/ROOM_MAX;
		rect.right=rect.left+width-5;
		if (i==m_nowroom)
		{	m_room[i]=new CRoomStc(i);
			((CStatic*)m_room[i])->Create("0",
				WS_VISIBLE|WS_CHILD|WS_CLIPSIBLINGS|
				SS_CENTER|SS_NOTIFY,
				rect,this,IDC_ROOM+i);
//			m_tooltip.AddTool(m_room[i],IDS_ROOM1,rect,IDC_ROOM+i);
		}
		else
		{	m_room[i]=new CRoomBtn(i);
			((CButton*)m_room[i])->Create("0",
				WS_VISIBLE|WS_BORDER|WS_CHILD|WS_CLIPSIBLINGS|
				BS_PUSHBUTTON,
				rect,this,IDC_ROOM+i);
//			m_tooltip.AddTool(m_room[i],IDS_ROOMOTHER,rect,IDC_ROOM+i);
 		}
	}
*/	GetClientRect(&rect);
	rect.top+=30;
	rect.right-=101;
	rect.bottom-=20;
	m_recv.Create(
		WS_BORDER|WS_VISIBLE|WS_CHILD|WS_VSCROLL|WS_CLIPSIBLINGS|
		ES_MULTILINE|ES_WANTRETURN|ES_READONLY|ES_NOHIDESEL,
		rect,this,IDC_RECV);
#ifdef CHAT97_USERICHEDIT
	m_recv.SetBackgroundColor(FALSE,m_chatBackColor);
	m_recv.SetTargetDevice(NULL,0);
	m_recv.SetEventMask(ENM_SELCHANGE | ENM_CHANGE | ENM_SCROLL | ENM_LINK );
	m_recv.AutoURLDetect( TRUE ) ;
#endif
	int a=m_recv.GetLimitText();
	m_recv.LimitText(1000000);
	int b=m_recv.GetLimitText();
	GetClientRect(&rect);
	rect.top=rect.bottom-20;
	
	m_send.Create(
		WS_VISIBLE|WS_CHILD|WS_BORDER|WS_TABSTOP|WS_CLIPSIBLINGS|
		ES_AUTOHSCROLL|ES_NOHIDESEL,
		rect,this,IDC_SEND);
	m_send.SetBackgroundColor(FALSE,m_chatBackColor);
	SetColor(&m_send,m_chatCharColor);
	GetClientRect(&rect);
	rect.top+=30;
	rect.left=rect.right-100;
	rect.bottom-=20;
	m_member.Create(
		WS_VISIBLE|WS_CHILD|WS_BORDER|WS_HSCROLL|WS_VSCROLL|WS_TABSTOP|WS_CLIPSIBLINGS|
		LBS_HASSTRINGS|LBS_NOINTEGRALHEIGHT|LBS_NOTIFY|LBS_OWNERDRAWFIXED,
		rect,this,IDC_MEMBER);
	m_status.SetText("上にあるボタンが各部屋を表してます。数字がそこに居る人数です。",0,0);
	m_roomleft.Create("←",
			WS_VISIBLE|WS_CHILD|WS_CLIPSIBLINGS|
				BS_PUSHBUTTON,
				rect,this,IDC_ROOMLEFT);
	m_roomright.Create("→",
			WS_VISIBLE|WS_CHILD|WS_CLIPSIBLINGS|
				BS_PUSHBUTTON,
				rect,this,IDC_ROOMRIGHT);

	m_roomno.Create("１号室",
			WS_VISIBLE|WS_CHILD|WS_CLIPSIBLINGS|
				SS_CENTER|SS_NOTIFY,
				rect,this,IDC_ROOMNO);
/*	m_bbs.Create(NULL,
			WS_VISIBLE|WS_CHILD|WS_CLIPSIBLINGS|
				SS_CENTER|SS_NOTIFY|SS_ICON,
				rect,this,IDC_BBS);
*/
	GetGameInfo();
	return 0;
}

void CPanel::OnPaint()
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	CRect rect;
	dc.SelectObject(&m_topfont);
	GetClientRect(rect);
	int width=rect.right-rect.left;
//	dc.SelectStockObject(LTGRAY_BRUSH);
//	CBrush brush(RGB(180,180,180));
	dc.FillRect(&rect,CBrush::FromHandle((HBRUSH)::GetStockObject(LTGRAY_BRUSH)));
	CPen light,dark;
	light.CreatePen(PS_SOLID,2,RGB(240,240,240));
	dark.CreatePen(PS_SOLID,2,RGB(100,100,100));
	dc.SetBkMode(TRANSPARENT);
	for (int i=0;i<ROOM_MAX;i++)
	{
		int l=width*i/ROOM_MAX;
		int r=width*(i+1)/ROOM_MAX-1;
		if (i==m_nowroom)
		{
//			dc.SelectStockObject(WHITE_BRUSH);
//			CBrush brush(RGB(220,220,220));
			CRect rect(l,0,r,20);
			dc.FillRect(&rect,CBrush::FromHandle((HBRUSH)::GetStockObject(LTGRAY_BRUSH)));
		}
		else
		{
			dc.SelectObject(&light);
			dc.MoveTo(l,0);
			dc.LineTo(r-1,0);
			dc.MoveTo(l,0);
			dc.LineTo(l,18);

			dc.SelectObject(&dark);
			dc.MoveTo(l,18);
			dc.LineTo(r-1,18);
			dc.MoveTo(r-1,0);
			dc.LineTo(r-1,18);
		}
		CString s;
		s.Format("%d人",m_user[i].getCount());
		dc.TextOut(l+4,2,s);
	}
}

void CPanel::OnRecv(CStringList&list)
{
	CString cmd;
	POSITION pos;
	CString handle;
	CString profile;
	CString hotspothandle;
	int x;
	int y;
	int hotspotx;
	int hotspoty;
	int clientno;
	int targetclientno=-1;
	int level;
	int isTarget=FALSE;

	pos = list.GetHeadPosition();
	if (pos==NULL)
		return;
	cmd=list.GetNext(pos);
cmd_start:;
	CString h;
	for(; pos != NULL;)
	{
		h = list.GetNext(pos);
		if (h.GetLength()==0)
			break;
		if (0==h.Left(7).Compare("handle:"))
			handle=h.Mid(8);
		else if (0==h.Left(8).Compare("profile:"))
			profile=h.Mid(9);
		else if (0==h.Left(2).Compare("x:"))
		{	x=atoi(h.Mid(3));
			if ((x<0)||(x>=10))
			{	return;
			}
		}
		else if (0==h.Left(5).Compare("room:"))
		{	x=atoi(h.Mid(6));
			if ((x<0)||(x>=10))
			{	return;
			}
		}
		else if (0==h.Left(2).Compare("y:"))
			y=atoi(h.Mid(3));
		else if (0==h.Left(6).Compare("level:"))
		{	if (0==h.Mid(7).Compare("leader"))
				level=SECURITY_LEADER;
			else if (0==h.Mid(7).Compare("sysop"))
				level=SECURITY_SYSOP;
			else if (0==h.Mid(7).Compare("root"))
				level=SECURITY_ROOT;
			else
				level=SECURITY_USER;
		}
		else if (0==h.Left(9).Compare("clientno:"))
			clientno=atoi(h.Mid(10));
		else if (0==h.Left(16).Compare("target_clientno:"))
		{
			targetclientno=atoi(h.Mid(17));
			isTarget=TRUE;
		}
		else if (0==h.Left(15).Compare("hotspot_handle:"))
			hotspothandle=h.Mid(16);
		else if (0==h.Left(10).Compare("hotspot_x:"))
			hotspotx=atoi(h.Mid(11));
		else if (0==h.Left(10).Compare("hotspot_y:"))
			hotspoty=atoi(h.Mid(11));
	}
	int bodyline=0;
	CString s1,s2,s3,s4;
	while (1)
	{
		if (pos==NULL)
			break;
		CString b = list.GetNext(pos);
		if (b.GetLength()==0)
			break;
		if (0==cmd.Compare("CHAT"))
		{
			CTime t = CTime::GetCurrentTime();
			CString time;
			time.Format("%02d:%02d ",t.GetHour(),t.GetMinute());
			CString h,p;
			if (isTarget)
			{
				if (!m_user[x].Search(&h,&p,clientno))
					h=handle;
				else
				{	m_LED=12;
				}
				{	CFileStatus sts;
					if (0!=CFile::GetStatus(m_telegramSound,sts))
					{	PlaySound(m_telegramSound,NULL,
						SND_FILENAME|SND_ASYNC|SND_NODEFAULT);
					}
				}
				CString str;
				str.Format("%s%d号室の[%s#4]さんから電報が届きました\r\n",time,x+1,h);
				AddText(str,RGB(255,0,0),TRUE);
				isTarget=FALSE;
				b+="\r\n";
				AddText(b,RGB(255,0,0),TRUE);
			}
			else
			{
SCROLLINFO si;
if (TRUE==m_recv.GetScrollInfo(SB_VERT,&si))
{
TRACE("  pos:%d page:%d add:%d max:%d\n",si.nPos,si.nPage,si.nPos+si.nPage,si.nMax);
}
				if (m_user[m_nowroom].Search(&h,&p,clientno))
				{	if (m_isTimeDisp)
						AddText(time,m_chatCharColor,FALSE);
					
					AddText(h,m_chatHandleColor,TRUE);
					CString str=" : ";
					AddText(str,m_chatCharColor,FALSE);
					b+="\r\n";
					AddText(b,m_chatCharColor,TRUE);
				}
if (TRUE==m_recv.GetScrollInfo(SB_VERT,&si))
{
TRACE("==pos:%d page:%d add:%d max:%d\n",si.nPos,si.nPage,si.nPos+si.nPage,si.nMax);
}
long _s,_e;
m_recv.GetSel(_s,_e);
TRACE("__s=%ld,e=%ld\n",_e,_s);

			}
		}
		else if (0==cmd.Compare("GETIPADDRESS"))
		{
			if (isTarget)
			{
				CString str;
				CString h,p;
				if (m_user[m_lookroom].Search(&h,&p,targetclientno))
				{	str="["+h+"] ";
				}
				str+=b+"\r\n";
				AddText(str,RGB(255,0,255),FALSE);
				isTarget=FALSE;
			}
		}
		else if (0==cmd.Compare("SETHANDLE"))
		{
			if (isTarget)
			{
				m_user[x].SearchSet(handle,profile,clientno);
				isTarget=FALSE;
			}
		}
		else if (0==cmd.Compare("GETALLXY"))
		{	bodyline%=4;
			if (bodyline==0)
				s1=b;	//handle;
			else if (bodyline==1)
				s2=b;	//x;
			else if (bodyline==2)
				s3=b;	//y;
			else if (bodyline==3)
			{	s4=b;	//clientno
				m_user[atoi(s2)%ROOM_MAX].Add(s1,s3,atoi(s4));
			}
		}
		else if (0==cmd.Compare("GETALLHOTSPOT"))
		{	bodyline%=4;
			if (bodyline==0)
				s1=b;	//name;
			else if (bodyline==1)
				s2=b;	//x;
			else if (bodyline==2)
			{	s3=b;	//y
				int room=atoi(s2);
				if (room<ROOM_MAX)
					m_user[room].SetName(s1);
				if (room==m_nowroom)
					SetTitle();
			}
			else if (bodyline==3)
			{
			}
		}
		bodyline++;
	}
	if (0==cmd.Compare("YOU"))
	{
		m_clientno=clientno;
	}
	if (0==cmd.Compare("GETALLHOTSPOT"))
	{	m_isConnect=TRUE;
	}
	else if (0==cmd.Compare("LOGIN"))
	{
		if (m_clientno!=clientno)
		{	m_user[x].Add(handle,profile,clientno);
			UpdateMember(x);
		}

		CString fname;
		int aaa;
		fname=handle;
		((CMapClientApp*)AfxGetApp())->CutESC(fname);
		if (-1!=(aaa=fname.Find('@')))
		{	fname=fname.Left(aaa);
		}
		fname+=".wav";

		CFileStatus sts;
		if (0!=CFile::GetStatus(fname,sts))
		{
			PlaySound(fname,NULL,
			SND_FILENAME|SND_ASYNC|SND_NODEFAULT);
		}
		else if (0==CFile::GetStatus(m_enterSound,sts))
		{
			PlaySound((char*)IDR_LOGINSOUND,NULL,
				SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
		}
		else
		{
			PlaySound(m_enterSound,NULL,
				SND_FILENAME|SND_ASYNC|SND_NODEFAULT);
		}
	}
	else if (0==cmd.Compare("LOGOUT"))
	{
		for (int i=0;i<ROOM_MAX;i++)
		{	if (m_user[i].Search(&handle,&profile,clientno))
			{	m_user[i].Del(clientno);
				UpdateMember(i);
				break;
			}
		}
		CString fname;
		int aaa;
		fname=handle;
		((CMapClientApp*)AfxGetApp())->CutESC(fname);
		if (-1!=(aaa=fname.Find('@')))
		{	fname=fname.Left(aaa);
		}
		fname="_"+fname+".wav";

		CFileStatus sts;
		if (0!=CFile::GetStatus(fname,sts))
		{
			PlaySound(fname,NULL,
			SND_FILENAME|SND_ASYNC|SND_NODEFAULT);
		}
		else if (0!=CFile::GetStatus(m_exitSound,sts))
		{
			PlaySound(m_exitSound,NULL,
				SND_FILENAME|SND_ASYNC|SND_NODEFAULT);
		}
	}
	else if (0==cmd.Compare("ROOM"))
	{
		if (clientno==m_clientno)
			m_level=level;
		else if (x==m_nowroom)
		{	CFileStatus sts;
			if (0!=CFile::GetStatus(m_enterRoomSound,sts))
			{	PlaySound(m_enterRoomSound,NULL,
					SND_FILENAME|SND_ASYNC|SND_NODEFAULT);
			}
		}

		CString h,p;

		for (int i=0;i<ROOM_MAX;i++)
		{	if (m_user[i].Search(&h,&p,clientno))
			{	m_user[i].Del(clientno);
				m_user[x].Add(h,p,clientno);
				UpdateMember(i);
				UpdateMember(x);
				if ((i=m_nowroom)&&(clientno!=m_clientno))
				{	CFileStatus sts;
					if (0!=CFile::GetStatus(m_exitRoomSound,sts))
					{	PlaySound(m_exitRoomSound,NULL,
						SND_FILENAME|SND_ASYNC|SND_NODEFAULT);
					}
				}
				break;
			}
		}
	}
	else if (0==cmd.Compare("SETHOTSPOT"))
	{
		if (hotspotx<ROOM_MAX)
		{	m_user[hotspotx].SetName(hotspothandle);
			SetTitle();
		}
	}
	else if (0==cmd.Compare("SETHANDLE"))
	{
		CString h,p;

		if (m_user[x].Search(&h,&p,clientno))
		{	m_user[x].Del(clientno);
			m_user[x].Add(handle,profile,clientno);
			UpdateMember(x);
		}
	}
	else if (0==cmd.Compare("GETALLXY"))
	{	for (int i=0;i<ROOM_MAX;i++)
			UpdateMember(i);
	}
	while (pos!=NULL)
	{
		CString b = list.GetNext(pos);
		if (pos==NULL)
			break;
		if (b.GetLength()!=0)
		{	cmd=b;
			goto cmd_start;
		}
	}
/*	int len = m_recv.GetWindowTextLength();
	if (len>29000)
	{	m_recv.SetSel(0,len-29000);
		m_recv.ReplaceSel(CString());
		m_recv.SetModify(FALSE);
	}
*/
}

void CPanel::OnSend(CString &s)
{
	SetColor(&m_send,m_chatCharColor);
	if (m_clientno==-1)
		return;
	if (!m_isConnect)
		return;
	s.TrimLeft();
	s.TrimRight();
	if (s.GetLength()==0)
		return;
	CString out="CHAT\n\n";
	out+=s;
	out+="\n\n";
	m_socket->SendMessage(out);
	m_hisNow=m_hisEnd;
	for (int i=m_hisStart;i!=m_hisEnd;i=(i+1)%HISTORYMAX)
	{	if (0==m_history[i].Compare(s))
		{	for (int j=i;j!=m_hisEnd;j=(j+1)%HISTORYMAX)
			{	m_history[j]=m_history[(j+1)%HISTORYMAX];
			}
			m_history[(m_hisEnd+HISTORYMAX-1)%HISTORYMAX]=s;
			return;		//重複したhistoryが見つかった
		}
	}
	m_history[m_hisEnd]=s;
	m_hisEnd=(m_hisEnd+1)%HISTORYMAX;
	if (m_hisEnd==m_hisStart)
		m_hisStart=(m_hisStart+1)%HISTORYMAX;
	m_hisNow=m_hisEnd;
}

void CPanel::UpdateMember(int room)
{
	if (room==m_lookroom)
	{
		CString s="１２３４５６７８９10";
		s=s.Mid(m_lookroom*2,2);
		if (!m_isBoss)
			s+="号室";
		m_roomno.SetWindowText(s);
		SetTitle();
		m_member.ResetContent();
		for (int i=0;;i++)
		{
			CUser *p=(CUser*)m_user[room].getData(i);
			if (p==NULL)
				break;
			CString s;
			s=p->GetHandle();
			((CMapClientApp*)AfxGetApp())->CutESC(s);
			m_member.AddString(s);
			m_member.SetItemData(i,p->GetClientNo());
			if (p->GetClientNo()==m_user[room].GetSelect())
				m_member.SetCurSel(i);
		}
		int sel=m_member.GetCurSel();
		if (sel==LB_ERR)
		{	m_member.SetCurSel(0);
			int clientno=m_member.GetItemData(0);
			m_user[m_lookroom].SetSelect(clientno);
		}
//		m_member.Invalidate(FALSE);
	}
	CString s;
	s.Format("%d",m_user[room].getCount());
//	m_room[room]->SetWindowText(s);
	Invalidate(FALSE);
}

void CPanel::OnChatbackColor()
{
	CColorDialog dlg(m_chatBackColor,0,this);
	int ret=dlg.DoModal();
	if (ret==IDOK)
	{	m_chatBackColor=dlg.GetColor();
#ifdef CHAT97_USERICHEDIT
		m_recv.SetBackgroundColor(FALSE,m_chatBackColor);
		m_send.SetBackgroundColor(FALSE,m_chatBackColor);
#endif
		CWinApp*pApp=AfxGetApp();
		pApp->WriteProfileInt("CHAT97","BackColor",m_chatBackColor);
	}
	m_member.Invalidate(TRUE);
}

void CPanel::OnChatcharcolor() 
{
	CColorDialog dlg(m_chatCharColor,0,this);
	int ret=dlg.DoModal();
	if (ret==IDOK)
	{	m_chatCharColor=dlg.GetColor();
		CWinApp*pApp=AfxGetApp();
		pApp->WriteProfileInt("CHAT97","CharColor",m_chatCharColor);
		SetColor(&m_send,m_chatCharColor);
	}
	m_member.Invalidate(TRUE);
}

void CPanel::OnChathandlecolor()
{
	CColorDialog dlg(m_chatHandleColor,0,this);
	int ret=dlg.DoModal();
	if (ret==IDOK)
	{	m_chatHandleColor=dlg.GetColor();
		CWinApp*pApp=AfxGetApp();
		pApp->WriteProfileInt("CHAT97","HandleColor",m_chatHandleColor);
	}
	m_member.Invalidate(TRUE);
}

void CPanel::SetColor(CWnd*edit,COLORREF color)
{
#ifdef CHAT97_USERICHEDIT
	CRichEditCtrl*e=(CRichEditCtrl*)edit;
	CHARFORMAT cf;
	e->GetDefaultCharFormat(cf);
	cf.dwMask|=CFM_COLOR;
	cf.dwMask|=(CFM_SIZE|CFM_FACE);
	cf.crTextColor=color;
	cf.dwEffects&=~CFE_AUTOCOLOR;
	e->SetWordCharFormat(cf);
#endif
}

void CPanel::AddString(CString& str)
{
	long len = m_recv.GetWindowTextLength();
	m_recv.SetSel(len,len);
	m_recv.ReplaceSel(str);
}

COLORREF Ncolor[10]={
	RGB(0,0,0),			//0=黒
	RGB(0,0,255),		//1=青
	RGB(0,255,0),		//2=緑
	RGB(0,255,255),		//3=水
	RGB(255,0,0),		//4=赤
	RGB(255,0,255),		//5=紫
	RGB(255,255,0),		//6=黄
	RGB(255,100,200),	//7=ピンク
	RGB(255,128,0),		//8=橙
	RGB(0xfc,0xfa,0xbd)	//9=王
};

void CPanel::AddText(CString& str,COLORREF color,BOOL isFormat)
{
#ifdef CHAT97_USERICHEDIT
	long start=0,end=0;
#else
	int start=0,end=0;
#endif
	m_recv.GetSel(start,end);
	long len = m_recv.GetWindowTextLength();
	m_recv.SetSel(len,len);
	m_isFlash=TRUE;
	BOOL isScroll=TRUE;
	SCROLLINFO si;
	if (TRUE==m_recv.GetScrollInfo(SB_VERT,&si))
	{	if (si.nPos+(int)si.nPage<si.nMax)
			isScroll=FALSE;
//		TRACE("pos:%d page:%d add:%d max:%d\n",si.nPos,si.nPage,si.nPos+si.nPage,si.nMax);
	}

	Ncolor[0]=color;
	SetColor(&m_recv,color);
	int startline=m_recv.GetLineCount();
	if ((isFormat)&&(-1!=str.Find('#')))
	{
		CString send;
		for (int i=0;i<str.GetLength();)
		{	if (_ismbblead((BYTE)str[i]))
			{
				send+=str.Mid(i,2);
				i+=2;
			}else if ((str[i]=='#')&&
				(i<str.GetLength()-1)&&
				(isdigit(str[i+1])))
			{	if (send.GetLength())
				{	AddString(send);
					send="";
				}
				SetColor(&m_recv,Ncolor[str[i+1]-'0']);
				i+=2;
			}else
			{
				send+=str.Mid(i,1);
				i++;
			}
		}
		if (send.GetLength())
		{	AddString(send);
		}
	}
	else
	{
		AddString(str);
	}
#ifdef CHAT97_USERICHEDIT
	int endline=m_recv.GetLineCount();
//	if (TRUE==m_recv.GetScrollInfo(SB_VERT,&si)&&
//		(si.nMax!=0)&&(isScroll))
	if (isScroll)
	{
		m_recv.LineScroll(endline-startline);
	}
	else{
//		if (start!=end)
			m_recv.SetSel(start,end);
	}
#endif
}

void CPanel::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	if (m_isConnect)
	{
		GetMenu()->EnableMenuItem(IDM_CONNECT,MF_GRAYED);
		GetMenu()->EnableMenuItem(IDM_DISCONNECT,MF_ENABLED);
	}
	else
	{
		GetMenu()->EnableMenuItem(IDM_CONNECT,MF_ENABLED);
		GetMenu()->EnableMenuItem(IDM_DISCONNECT,MF_GRAYED);
	}
	if (m_isLogClear)
		GetMenu()->CheckMenuItem(IDM_ISLOGCLEAR,MF_CHECKED);
	else
		GetMenu()->CheckMenuItem(IDM_ISLOGCLEAR,MF_UNCHECKED);
	if (m_isTimeDisp)
		GetMenu()->CheckMenuItem(IDM_TIMEDISP,MF_CHECKED);
	else
		GetMenu()->CheckMenuItem(IDM_TIMEDISP,MF_UNCHECKED);
	if (m_isBoss)
	{	GetMenu()->CheckMenuItem(IDM_ISBOSS,MF_CHECKED);
		GetMenu()->EnableMenuItem(IDM_BOSSSTRING,MF_ENABLED);
	}
	else
	{	GetMenu()->CheckMenuItem(IDM_ISBOSS,MF_UNCHECKED);
		GetMenu()->EnableMenuItem(IDM_BOSSSTRING,MF_GRAYED);
	}
	if (m_isToolBar)
		GetMenu()->CheckMenuItem(IDM_ISTOOLBAR,MF_CHECKED);
	else
		GetMenu()->CheckMenuItem(IDM_ISTOOLBAR,MF_UNCHECKED);
	if ((m_level<SECURITY_USER)&&(m_nowroom!=0))
		GetMenu()->EnableMenuItem(IDM_ROOMNAME,MF_ENABLED);
	else
		GetMenu()->EnableMenuItem(IDM_ROOMNAME,MF_GRAYED);
}

void CPanel::SetTitle()
{
	CString roomname=m_user[m_nowroom].GetName();
	((CMapClientApp*)AfxGetApp())->CutESC(roomname);

	if (m_isBoss)
	{
		CString s;
		s.Format("%d[%d]",
			m_nowroom+1,
			m_user[m_nowroom].getCount());
		SetWindowText(s);
		return;
	}
	if (IsIconic())
	{
		CString s;
		s.Format("%d人[%s]",
			m_user[m_nowroom].getCount(),
			roomname);
		SetWindowText(s);
		return;
	}
//	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAILCHAT97);
//	m_bbs.SetIcon(m_hIcon);
	CString s,s2;
	s.Format("%d:[%s] ",m_nowroom+1,roomname);
	for (int i=0;;i++)
	{	CUser*p=(CUser*)m_user[m_nowroom].getData(i);
		if (p==NULL)
			break;
		s2=p->GetHandle();
		((CMapClientApp*)AfxGetApp())->CutESC(s2);
		s+=s2;
		s+=" ";
	}
	SetWindowText(s);
}

DWORD CALLBACK OnSaveCallBack(DWORD dwCookie, 
    LPBYTE pbBuff, LONG cb, LONG FAR *pcb); 

void CPanel::OnSave() 
{
#ifdef CHAT97_USERICHEDIT
	CTime t=CTime::GetCurrentTime();
	int month=t.GetMonth();
	int day=t.GetDay();
	int hour=t.GetHour();
	CString fname;
	fname.Format("%0d%0d-%0d.txt",month,day,hour);
	CFileDialog dlg(FALSE,NULL,fname,0,NULL,this);
	int ret=dlg.DoModal();
	if (ret!=IDOK)
		return;
	CString path=dlg.GetPathName();
	CFile fp;
	if (FALSE==fp.Open(path,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite))
		return;
	EDITSTREAM es;
	es.dwCookie=(DWORD)&fp;
	es.pfnCallback=OnSaveCallBack;
	TRACE("Save start\n");
	m_recv.StreamOut(SF_TEXT,es);
	TRACE("Save end\n");
#endif
}

DWORD CALLBACK OnSaveCallBack(DWORD dwCookie, 
    LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
{
	CFile*fp=(CFile*)dwCookie;
	fp->Write(pbBuff,cb);
	return cb;
} 

void CPanel::OnFont() 
{
	CFontDialog dlg(&m_logfont,
		CF_SCREENFONTS|
		CF_NOVERTFONTS|CF_NOVECTORFONTS);
	if (IDOK==dlg.DoModal())
	{
		dlg.GetCurrentFont(&m_logfont);
		CFont font;
		font.CreateFontIndirect(&m_logfont);
		m_recv.SetFont(&font);
		CWinApp*pApp=AfxGetApp();
		pApp->WriteProfileInt("CHAT97","FontHeight",m_logfont.lfHeight);
		pApp->WriteProfileString("CHAT97","FontFace",m_logfont.lfFaceName);
#ifdef CHAT97_USERICHEDIT
		CHARFORMAT cf;
		m_recv.GetDefaultCharFormat(cf);
		cf.dwMask=(CFM_SIZE|CFM_FACE);
		m_recv.SetDefaultCharFormat(cf);
#endif
	}
}

int g_dec=1;

void CPanel::OnTimer(UINT nIDEvent) 
{
	if ((m_timer&3)==0)
	{	if ((m_isFlash)&&(IsIconic())&&(!m_isBoss))
		{	FlashWindow(TRUE);
			m_LED=99999999;
		}
	}
	if (m_LED){
		m_LED--;
		if (m_LED==0)
			controlLED(0,VK_SCROLL);
		else
			controlLED(m_LED&1,VK_SCROLL);
	}
	m_timer++;
	CWnd::OnTimer(nIDEvent);
}

void CPanel::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	m_send.SetFocus();
}

void CPanel::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CRect rect;
	CPoint c=point;
	ScreenToClient(&c);
	if (c.y<=20)
	{
		GetClientRect(&rect);
		int width=rect.right-rect.left;
		int room=(c.x)/(width/ROOM_MAX);
		if (room!=m_nowroom)
			return;
		OnRoomname();
		return;
	}

	m_recv.GetWindowRect(&rect);
	if ((rect.left<=point.x)&&
		(rect.right>=point.x)&&
		(rect.top<=point.y)&&
		(rect.bottom>=point.y))
	{	m_recv.Copy();
		return;
	}
	m_member.GetWindowRect(&rect);
	if ((rect.left>point.x)||
		(rect.right<point.x)||
		(rect.top>point.y)||
		(rect.bottom<point.y))
		return;
	c.x=point.x-rect.left;
	c.y=point.y-rect.top;
	for (int i=0;i<m_member.GetCount();i++)
	{	m_member.GetItemRect(i,&rect);
		if ((rect.left<=c.x)&&
			(rect.right>=c.x)&&
			(rect.top<=c.y)&&
			(rect.bottom>=c.y))
		{	break;
		}
	}
	if (i>=m_member.GetCount())
		return;

	int clientno=m_member.GetItemData(i);
	CString s,h,p,m,hp;
	m_user[m_lookroom].Search(&h,&p,clientno);
	int l=p.Find("####");
	m=p.Left(l);
	p=p.Mid(l+4);
	l=p.Find("####");
	if (l!=-1)
	{	hp=p.Mid(l+4);
		p=p.Left(l);
		l=hp.Find("####");
		if (l!=-1)
			hp=hp.Left(l);
	}
	if (hp.GetLength())
		m_rmenu.GetSubMenu(0)->EnableMenuItem(IDM_SEEHOMEPAGE,MF_ENABLED);
	else
		m_rmenu.GetSubMenu(0)->EnableMenuItem(IDM_SEEHOMEPAGE,MF_GRAYED);
	if (m.GetLength())
		m_rmenu.GetSubMenu(0)->EnableMenuItem(IDM_MAILCOPY,MF_ENABLED);
	else
		m_rmenu.GetSubMenu(0)->EnableMenuItem(IDM_MAILCOPY,MF_GRAYED);

	ScreenToClient(&point);
	point.y-=14;

	ClientToScreen(&point);
	m_member.SetCurSel(i);
	clientno=m_member.GetItemData(i);
	m_user[m_lookroom].SetSelect(clientno);

	m_rmenu.GetSubMenu(0)->TrackPopupMenu(
		TPM_CENTERALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,
		point.x,point.y,this);
}

void CPanel::OnKill() 
{
	if (!((CMapClientApp*)AfxGetApp())->m_isSysOp)
		return;
	if (m_clientno==-1)
		return;
	if (!m_isConnect)
		return;
	int no=m_member.GetCurSel();
	if (no==LB_ERR)
		return;
	int clientno=m_member.GetItemData(no);
	CString s;
	CString out="KILL\n";
	s.Format("target_clientno: %d\n\n",clientno);
	out+=s;
	out+="\n\n";
	m_socket->SendMessage(out);
}

void CPanel::OnSendmessage() 
{
	if (m_clientno==-1)
		return;
	if (!m_isConnect)
		return;
	int no=m_member.GetCurSel();
	if (no==LB_ERR)
		return;
	int clientno=m_member.GetItemData(no);
	CString handle;
	m_member.GetText(no,handle);
	CSendMes dlg(handle,clientno,m_lookroom);
	if (IDOK==dlg.DoModal())
	{
		CString mes=dlg.mes;
		mes.TrimLeft();
		mes.TrimRight();
		if (mes.GetLength()){
			CString s;
			CString out="CHAT\n";
			s.Format("target_clientno: %d\n\n",clientno);
			out+=s;
			out+=mes;
			out+="\n\n";
			m_socket->SendMessage(out);
			mes="→"+handle+"："+mes+"\r\n";
			AddText(mes,RGB(255,0,0),TRUE);
		}
	}
	m_send.SetFocus();
}

void CPanel::OnFiletran() 
{
	if (m_clientno==-1)
		return;
	if (!m_isConnect)
		return;
	int no=m_member.GetCurSel();
	if (no==LB_ERR)
		return;
	int clientno=m_member.GetItemData(no);
	CString handle;
	m_member.GetText(no,handle);
	CSendMes dlg(handle,clientno,m_lookroom);
	if (IDOK==dlg.DoModal())
	{
		CString mes=dlg.mes;
		CString s;
		CString out="CHAT\n";
		s.Format("target_clientno: %d\n\n",clientno);
		out+=s;
		out+=mes;
		out+="\n\n";
		m_socket->SendMessage(out);
	}
	m_send.SetFocus();
}
void CPanel::OnRoomname()
{
	if (m_clientno==-1)
		return;
	if (!m_isConnect)
		return;
	if (m_nowroom==0)
	{	AfxMessageBox("入り口だけは、名前を変更できません");
		return;
	}
	if (m_level>=SECURITY_USER)
		return;
	CRoomName dlg(m_nowroom);
	if (IDOK!=dlg.DoModal())
		return;
	CString out,s;
	out="SETHOTSPOT\n";
	s.Format("hotspot_handle: %s\n",dlg.mes);
	out+=s;
	s.Format("hotspot_x: %d\n",m_nowroom);
	out+=s;
	out+="hotspot_y: 0\n";
	out+="\n\n";
	m_socket->SendMessage(out);
}

void CPanel::OnHelp() 
{
	CHelpDlg dlg;
	dlg.DoModal();	
}

void CPanel::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
//	CFrameWnd::OnGetMinMaxInfo(lpMMI);
	lpMMI->ptMinTrackSize.x=300;
	lpMMI->ptMinTrackSize.y=240;

}

void CPanel::OnEntersound()
{
	CFileDialog dlg(TRUE,"wav",m_enterSound,0,"WAVファイル(*.wav)|*.wav||",this);
	if (IDOK!=dlg.DoModal())
		return;
	m_enterSound=dlg.GetPathName();
	AfxGetApp()->WriteProfileString("CHAT97","EnterSound",m_enterSound);
}

void CPanel::OnExitsound()
{
	CFileDialog dlg(TRUE,"wav",m_exitSound,0,"WAVファイル(*.wav)|*.wav||",this);
	if (IDOK!=dlg.DoModal())
		return;
	m_exitSound=dlg.GetPathName();
	AfxGetApp()->WriteProfileString("CHAT97","ExitSound",m_exitSound);
}

void CPanel::OnConnect()
{
	m_isConnect=TRUE;
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_CHAT97);
	SetIcon(m_hIcon,FALSE);

	CString s;
	CString out="LOGIN\n";
	s.Format("world: %d\n",((CMapClientApp*)AfxGetApp())->m_world);
	out+=s;
	s.Format("handle: %s\n",m_handle);
	out+=s;
	s.Format("user_agent: win32/CHAT97\n");
	out+=s;
	s.Format("profile: %s####%s####%s\n",m_mail,m_profile,m_homepage);
	out+=s;
	s.Format("version: %s\n",NOW_VERSION);
	out+=s;
	s.Format("room: %d\n",m_nowroom);
	out+=s;
	out+="level: rootsakai\n";
	out+="\n";
	out+="\n";
	m_socket->SendMessage(out);
	out="GETALLXY\n\n\n";
	m_socket->SendMessage(out);
	out="GETALLHOTSPOT\n\n\n";
	m_socket->SendMessage(out);
}

void CPanel::OnConnectButton()
{
	if (m_isConnect)
		return;
	Connect();
}

void CPanel::OnDisconnectButton()
{
	if (!m_isConnect)
		return;

	CFileStatus sts;
	if (0!=CFile::GetStatus(m_disconnectSound,sts))
	{	PlaySound(m_disconnectSound,NULL,
			SND_FILENAME|SND_ASYNC|SND_NODEFAULT);
	}

	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_DEADCHAT97);
	SetIcon(m_hIcon,FALSE);
	if (m_socket)
	{	m_socket->Close();
		delete m_socket;
		m_socket=NULL;
	}
	m_isConnect=FALSE;
	for (int i=0;i<ROOM_MAX;i++)
	{	m_user[i].clearDelete();
		UpdateMember(i);
	}
	SetTitle();
}

BOOL CPanel::Connect()
{
	m_nowroom=0;
	m_clientno=-1;
	m_nowroom=0;
	m_lookroom=0;
	m_level=SECURITY_USER;

	if (m_socket)
		delete m_socket;
	m_socket=new CChatSocket();
	if (FALSE==m_socket->Connect(this,m_host,m_port))
	{	delete m_socket;
		m_socket=NULL;
		return FALSE;
	}
	return TRUE;
}

void CPanel::OnMouseMove(UINT nFlag,CPoint point)
{
	if (nFlag==IDC_MEMBER)
	{
		CRect rect;
		for (int i=0;i<m_member.GetCount();i++)
		{	m_member.GetItemRect(i,&rect);
			if ((rect.left<=point.x)&&
				(rect.right>=point.x)&&
				(rect.top<=point.y)&&
				(rect.bottom>=point.y))
			{	break;
			}
		}
		if (i>=m_member.GetCount())
				return;
		int clientno=m_member.GetItemData(i);
		MemberStatus(clientno);
	}
	else
	{
		if (point.y>20)
			return;
		CRect rect;
		GetClientRect(&rect);
		int width=rect.right-rect.left;
		int room=point.x/(width/ROOM_MAX);
		room%=ROOM_MAX;
		StatusRoom(room);
		return;
	}
}
/*
BOOL CPanel::OnToolTip( UINT id, NMHDR * pTTTStruct, LRESULT * pResult )
{
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pTTTStruct;
	UINT nID =pTTTStruct->idFrom;
	if (pTTT->uFlags & TTF_IDISHWND)
	{
		// idFrom is actually the HWND of the tool
		nID = ::GetDlgCtrlID((HWND)nID);
		if(nID)
		{
			if (nID==IDC_ROOM)
				nID=IDS_ROOM1;
			else if ((nID>IDC_ROOM)&&(nID<IDC_ROOM+ROOM_MAX))
				nID=IDS_ROOMOTHER;
			else
				return(FALSE);
			pTTT->lpszText = MAKEINTRESOURCE(nID);
			pTTT->hinst = AfxGetResourceHandle();
			return(TRUE);
		}
	}
	return(FALSE);
}
*/
void CPanel::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_clientno==-1)
		return;
	if (point.y>20)
		return;
	CRect rect;
	GetClientRect(&rect);
	int width=rect.right-rect.left;
	int room=point.x/(width/ROOM_MAX);
	room%=ROOM_MAX;

	RoomMove(room);

	CFrameWnd::OnLButtonUp(nFlags, point);
}

void CPanel::RoomMove(int room)
{
	if (m_clientno==-1)
		return;
	if (!m_isConnect)
		return;
	if (m_nowroom==room)
		return;
	CString out,s;

	m_nowroom=room;
	m_lookroom=room;

	out="ROOM\n";
	s.Format("handle: %s\n",m_handle);
	out+=s;
	s.Format("room: %d\n",m_nowroom);
	out+=s;
	out+="\n\n";
	m_socket->SendMessage(out);

	if (m_isLogClear)
		OnLogclear();
	Invalidate(FALSE);
}

void CPanel::OnMailcopy() 
{
	int no=m_member.GetCurSel();
	if (no==LB_ERR)
		return;
	int clientno=m_member.GetItemData(no);
	CString h,p;
	m_user[m_lookroom].Search(&h,&p,clientno);
	int pos=p.Find("####");
	p=p.Left(pos);
	if (p.GetLength()==0)
		return;
	CString s;
	s.Format("[InternetShortcut]\nURL=mailto:%s",p);
	CFile fp;
	fp.Open("tmp.URL",CFile::modeCreate|CFile::modeReadWrite);
	fp.Write(s,s.GetLength());
	fp.Close();

	ShellExecute(m_hWnd,"open","tmp.URL",NULL,NULL,SW_SHOW);
}

void CPanel::SetTray(int cmd,HICON hIcon, CString str)
{
	nd.cbSize=sizeof(NOTIFYICONDATA);
	nd.hWnd=m_hWnd;
	nd.uID=1001;
	nd.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
	nd.uCallbackMessage=WM_NOTIFYICON;
	if (hIcon==NULL)
		nd.hIcon=AfxGetApp()->LoadIcon(IDR_CHAT97);
	else
		nd.hIcon=hIcon;
	strcpy(nd.szTip,str);
	Shell_NotifyIcon(cmd,&nd);
}

void CPanel::OnNotifyIcon(WPARAM wParam,LPARAM lParam)
{
	if ((lParam==WM_LBUTTONDOWN)||(lParam==WM_RBUTTONDOWN))
	{
//		ShowWindow(SW_RESTORE);
		ShowWindow(SW_SHOW);
		SetTray(NIM_DELETE,NULL,"22");
	}
}

void CPanel::OnBoss() 
{
	if (m_isBoss)
	{	if (m_bossstring.GetLength())
		{
			CString out="CHAT\n\n";
			out+=m_bossstring;
			out+="\n\n";
			m_socket->SendMessage(out);
		}
//		ShowWindow(SW_MINIMIZE);
		ShowWindow(SW_HIDE);
		SetTray(NIM_ADD,NULL,"クリックすると復活だよん");
	}
}

void CPanel::OnIsboss() 
{
	if (m_isBoss)
		m_isBoss=FALSE;
	else
		m_isBoss=TRUE;
	AfxGetApp()->WriteProfileInt("CHAT97","Boss",m_isBoss);
}

void CPanel::OnGetip() 
{
	int no=m_member.GetCurSel();
	if (no==LB_ERR)
		return;
	int clientno=m_member.GetItemData(no);
	CString out="GETIPADDRESS\n";
	CString s;
	s.Format("target_clientno: %d\n\n\n",clientno);
	out+=s;
	m_socket->SendMessage(out);
}


void CPanel::OnDisconnectsound() 
{
	CFileDialog dlg(TRUE,"wav",m_disconnectSound,0,"WAVファイル(*.wav)|*.wav||",this);
	if (IDOK!=dlg.DoModal())
		return;
	m_disconnectSound=dlg.GetPathName();
	AfxGetApp()->WriteProfileString("CHAT97","DisconnectSound",m_disconnectSound);
}

void CPanel::OnEnterroomsound() 
{
	CFileDialog dlg(TRUE,"wav",m_enterRoomSound,0,"WAVファイル(*.wav)|*.wav||",this);
	if (IDOK!=dlg.DoModal())
		return;
	m_enterRoomSound=dlg.GetPathName();
	AfxGetApp()->WriteProfileString("CHAT97","EnterRoomSound",m_enterRoomSound);
}

void CPanel::OnTelegramsound() 
{
	CFileDialog dlg(TRUE,"wav",m_telegramSound,0,"WAVファイル(*.wav)|*.wav||",this);
	if (IDOK!=dlg.DoModal())
		return;
	m_telegramSound=dlg.GetPathName();
	AfxGetApp()->WriteProfileString("CHAT97","TelegramSound",m_telegramSound);
}

void CPanel::OnExitroomsound() 
{
	CFileDialog dlg(TRUE,"wav",m_exitRoomSound,0,"WAVファイル(*.wav)|*.wav||",this);
	if (IDOK!=dlg.DoModal())
		return;
	m_exitRoomSound=dlg.GetPathName();
	AfxGetApp()->WriteProfileString("CHAT97","ExitRoomSound",m_exitRoomSound);
}

void CPanel::OnTimedisp() 
{
	m_isTimeDisp=1-m_isTimeDisp;
	AfxGetApp()->WriteProfileInt("CHAT97","TimeDisp",m_isTimeDisp);
}

void CPanel::OnIstoolbar() 
{
	if (m_isToolBar)
		m_isToolBar=FALSE;
	else
		m_isToolBar=TRUE;
	AfxGetApp()->WriteProfileInt("CHAT97","ToolBar",m_isToolBar);
}

void CPanel::OnSameroom() 
{
	RoomMove(m_lookroom);
}

void CPanel::StatusRoom(int room)
{
	CString s,s2;
	CString roomname=m_user[room].GetName();
	((CMapClientApp*)AfxGetApp())->CutESC(roomname);
	s.Format("%d:[%s] ",room+1,roomname);
	for (int j=0;;j++)
	{	CUser*p=(CUser*)m_user[room].getData(j);
		if (p==NULL)
			break;
		s2=p->GetHandle();
		((CMapClientApp*)AfxGetApp())->CutESC(s2);
		s+=s2;
		s+=" ";
	}
	m_status.SetWindowText(s);
}

void CPanel::OnLogclear() 
{
	m_recv.SetWindowText("");
}

void CPanel::OnIslogclear() 
{
	if (m_isLogClear)
		m_isLogClear=FALSE;
	else
		m_isLogClear=TRUE;
	AfxGetApp()->WriteProfileInt("CHAT97","LogClear",m_isLogClear);
}

void CPanel::OnSeehomepage() 
{
	int no=m_member.GetCurSel();
	if (no==LB_ERR)
		return;
	int clientno=m_member.GetItemData(no);
	CString h,p;
	m_user[m_lookroom].Search(&h,&p,clientno);
	int pos=p.Find("####");
	p=p.Mid(pos+4);
	pos=p.Find("####");
	if (pos==-1)
		return;
	p=p.Mid(pos+4);
	pos=p.Find("####");
	if (pos!=-1)
		p=p.Left(pos);
	if (p.GetLength()==0)
		return;
	if (-1==p.Find("http://"))
		p="http://"+p;
	CString s;
	s.Format("[InternetShortcut]\nURL=%s",p);
	CFile fp;
	fp.Open("tmp.URL",CFile::modeCreate|CFile::modeReadWrite);
	fp.Write(s,s.GetLength());
	fp.Close();

	ShellExecute(m_hWnd,"open","tmp.URL",NULL,NULL,SW_SHOW);
}

void CPanel::OnRoom(UINT nID) 
{
	RoomMove(nID-IDM_ROOM1);
}

void CPanel::OnSethandle() 
{
	if (m_clientno==-1)
		return;
	if (!m_isConnect)
		return;
	CSetHandle dlg;
	dlg.m_handle=m_handle;
	dlg.m_mail=m_mail;
	dlg.m_profile=m_profile;
	dlg.m_homepage=m_homepage;
	if (IDOK!=dlg.DoModal())
		return;
	m_handle=dlg.m_handle;
	m_mail=dlg.m_mail;
	m_profile=dlg.m_profile;
	m_homepage=dlg.m_homepage;
	CMapClientApp*pApp=(CMapClientApp*)AfxGetApp();
	pApp->WriteProfileString("CHAT97","Handle",m_handle);
	pApp->WriteProfileString("CHAT97","Mail",m_mail);
	pApp->WriteProfileString("CHAT97","HomaPage",m_homepage);
	pApp->WriteProfileString("CHAT97","Profile",m_profile);
	CString s;
	CString out;
	out="SETHANDLE\n";
	s.Format("room: %d\n",m_nowroom);
	out+=s;
	s.Format("handle: %s\n",m_handle);
	out+=s;
	s.Format("profile: %s####%s####%s\n\n\n",m_mail,m_profile,m_homepage);
	out+=s;
	m_socket->SendMessage(out);
}

void CPanel::OnBossstring()
{
	BossString dlg(this);
	dlg.m_bossstring=m_bossstring;
	if (IDCANCEL==dlg.DoModal())
	{	return;
	}
	m_bossstring=dlg.m_bossstring;
}

void CPanel::OnClose() 
{
	CRect rect;
	GetWindowRect(&rect);

	if (m_LED)
		controlLED(0,VK_SCROLL);
	if ((rect.left>0)&&(rect.top>0))
	{	AfxGetApp()->WriteProfileInt("CHAT97","x",rect.left);
		AfxGetApp()->WriteProfileInt("CHAT97","y",rect.top);
	}
	CFrameWnd::OnClose();
}

void CPanel::OnColor(UINT nID)
{
	CString s;
	s.Format("#%d",nID-=IDM_COLOR0);
	m_send.ReplaceSel(s);
}

void CPanel::OnPrevhistory() 
{
	if (m_hisEnd==m_hisStart)
		return;
	if (m_hisNow==m_hisStart)
		return;
	m_hisNow=(m_hisNow+HISTORYMAX-1)%HISTORYMAX;
	m_send.SetWindowText(m_history[m_hisNow]);
	int len=m_send.GetWindowTextLength();
	m_send.SetSel(len,len);
}

void CPanel::OnNexthistory() 
{
	if (m_hisEnd==m_hisStart)
		return;
	if (m_hisNow==m_hisEnd)
		return;
	m_hisNow=(m_hisNow+1)%HISTORYMAX;
	m_send.SetWindowText(m_history[m_hisNow]);
	int len=m_send.GetWindowTextLength();
	m_send.SetSel(len,len);
}

void CPanel::OnRighthandle() 
{
	int sel=m_member.GetCurSel();
	int c;
	c=m_member.GetItemData(sel);
	CString h,p;
	m_user[m_lookroom].Search(&h,&p,c);
	h="＞"+h;
	m_send.ReplaceSel(h);
}

void CPanel::OnLefthandle() 
{
	int sel=m_member.GetCurSel();
	CString str;
	m_member.GetText(sel,str);
	str="＜"+str;
	m_send.ReplaceSel(str);
}

void CPanel::OnHelp2()
{
	ShellExecute(m_hWnd,"open","chat97.hlp",NULL,NULL,SW_SHOW);
}

void CPanel::OnServerstatus() 
{
	CString s="[InternetShortcut]\nURL=http://www.oosama.net/chat97status.html\n";
	CFile fp;
	fp.Open("tmp.URL",CFile::modeCreate|CFile::modeReadWrite);
	fp.Write(s,s.GetLength());
	fp.Close();

	ShellExecute(m_hWnd,"open","tmp.URL",NULL,NULL,SW_SHOW);
}

void CPanel::GetGameInfo()
{
	HKEY hkey;
	char type[256];
	DWORD typesize;
	char name[256];
	DWORD namesize;
	FILETIME ft;
	LONG ret;

	ret=RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		"SOFTWARE\\oosama.com\\chat97",0,
		KEY_READ,
		&hkey
		);
	name[0]=0;
	type[0]=0;
	namesize=256;
	typesize=256;
	DWORD index=0; 
	m_gamepath.RemoveAll();
	m_gamename.RemoveAll();
	while (ret==ERROR_SUCCESS)
	{	ret=RegEnumKeyEx(
		hkey,index,
		name,
		&namesize,NULL,
		type,
		&typesize,
		&ft);
		if (ret!=ERROR_SUCCESS)
			break;
		
		DWORD dwtype;
		DWORD datasize=256;
		BYTE data[256];
		HKEY subhkey;
		ret=RegOpenKeyEx(
			hkey,
			name,0,
			KEY_READ,
			&subhkey
			);
		RegQueryValueEx(
			subhkey,"",NULL,&dwtype,data,&datasize
			);
		m_gamepath.AddTail((char *)data);
		RegQueryValueEx(
			subhkey,"Name",NULL,&dwtype,data,&datasize
			);
		m_gamename.AddTail((char *)data);
		index++;
		RegCloseKey(subhkey);
	}
	m_gamecount=index;
	if (m_gamecount)
		m_rmenu.GetSubMenu(0)->AppendMenu(MF_SEPARATOR);
	POSITION pos=m_gamename.GetHeadPosition();
	for (int i=0;i<m_gamecount;i++)
	{
		CString name=m_gamename.GetNext(pos);
		name+="をやる";
		m_rmenu.GetSubMenu(0)->AppendMenu(MF_STRING,IDM_GAME+i,name);
	}
	RegCloseKey(hkey);
}

void CPanel::OnGame(int gameno)
{
	gameno-=IDM_GAME;

	int no=m_member.GetCurSel();
	if (no==LB_ERR)
		return;
	POSITION pos=m_gamename.GetHeadPosition();
	CString n;
	for (int i=0;i<=gameno;i++)
	{
		n=m_gamename.GetNext(pos);
	}

	int clientno=m_member.GetItemData(no);
	CString out;
	out.Format("M_GAMEPLAY\ntarget_clientno: %d\nname: %s\n\n\n",clientno,(const char *)n);
	m_socket->SendMessage(out);
}


LRESULT CPanel::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message==WM_NOTIFYICON)
	{	OnNotifyIcon(wParam,lParam);
	}
	
	return CFrameWnd::WindowProc(message, wParam, lParam);
}

//VK_CAPITAL,VK_NUMLOCK,VK_SCROLL
void CPanel::controlLED(BOOL onoff, int key)
{
	static BYTE pbKeyState[256];
	UINT MachineCode;

	GetKeyboardState(pbKeyState);
	if (pbKeyState[key] != onoff)   //  現在の状態が bLockmode と違う場合
	{
		//  マシンコードの取得
		MachineCode = MapVirtualKey(key,0);

		//  キーを押す
		keybd_event((BYTE)key, (BYTE)MachineCode, KEYEVENTF_EXTENDEDKEY, 0l);

		//  キーを放す
		keybd_event((BYTE)key, (BYTE)MachineCode, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0l);
	}
}

void CPanel::OnKillFocus(CWnd* pNewWnd) 
{
	CFrameWnd::OnKillFocus(pNewWnd);

	controlLED(0,VK_SCROLL);
}

void CPanel::OnOMAE() 
{
	if (!((CMapClientApp*)AfxGetApp())->m_isSysOp)
		return;
	CString s1="　　　 ∧ ∧ 　　／￣￣￣￣";
	CString s2="　　　(, ﾟдﾟ)　＜ ｵﾏｴﾓﾅｰ";
	CString s3="　　ヽ/　 　|　　＼＿＿＿＿";
	CString s4="　　（__∪∪）";
	OnSend(s1);
	OnSend(s2);
	OnSend(s3);
	OnSend(s4);
}

void CPanel::OnRichEditExLink(NMHDR *in_pNotifyHeader, LRESULT *out_pResult)
{
	ENLINK* l_pENLink = ( ENLINK* )in_pNotifyHeader ;
	*out_pResult = 0 ;

	switch( l_pENLink->msg )
	{
		default:
		{
		}
		break ;

		case WM_SETCURSOR:
		{
			if( m_crLink != NULL )
			{
			    ::SetCursor( m_crLink ) ;

				*out_pResult = 1 ;
			}
		}
		break ;

		case WM_LBUTTONDOWN:
		{
			CString l_URL ;
			CHARRANGE l_CharRange ;

			m_recv.GetSel( l_CharRange ) ;
			m_recv.SetSel( l_pENLink->chrg ) ;
			l_URL = m_recv.GetSelText() ;
			m_recv.SetSel( l_CharRange ) ;

			CWaitCursor l_WaitCursor ;

			ShellExecute( this->GetSafeHwnd(), _T( "open" ), l_URL, NULL, NULL, SW_SHOWNORMAL ) ;

			*out_pResult = 1 ;
		}
		break ;

		case WM_LBUTTONUP:
		{
			*out_pResult = 1 ;
		}
		break ;
	}
}

