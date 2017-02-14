// MapClientDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapClient.h"
#include "MapClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapClientDlg ダイアログ

CMapClientDlg::CMapClientDlg(int room)
	: CDialog(CMapClientDlg::IDD, NULL)
{
	m_nowroom=room;
	//{{AFX_DATA_INIT(CMapClientDlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_CHAT97);
}

CMapClientDlg::~CMapClientDlg()
{
	for (int i=0;i<ROOM_MAX;i++)
	{	delete m_room[i];
	}
}

void CMapClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapClientDlg)
		// メモ: この場所には ClassWizard によって DDX と DDV の呼び出しが追加されます。
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMapClientDlg, CDialog)
	//{{AFX_MSG_MAP(CMapClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapClientDlg メッセージ ハンドラ

BOOL CMapClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CMapClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CMapClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CMapClientDlg::OnSize(UINT nType, int cx, int cy) 
{
	CRect rect;
	GetClientRect(&rect);
	int width=rect.right-rect.left+1;
	int height=rect.bottom-rect.top+1;
	for (int i=0;i<ROOM_MAX;i++)
	{
		m_room[i]->SetWindowPos(NULL,
			width*i/ROOM_MAX,	0,
			width/ROOM_MAX-2,		30,
		SWP_NOZORDER);
		m_room[i]->Invalidate();
	}
	m_recv.SetWindowPos(NULL,
		0,	30,
		width-100,		height-50,
		SWP_NOZORDER);
	m_send.SetWindowPos(NULL,
		0,	height-20,
		width,		20,
		SWP_NOZORDER);
	m_send.SetFocus();
	m_member.SetWindowPos(NULL,
		width-100,	30,
		100,		height-50,
		SWP_NOZORDER);
}

int CMapClientDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(&rect);
	int l=rect.left;
	int width=rect.right-rect.left+1;
	rect.bottom=rect.top+30;
	for (int i=0;i<ROOM_MAX;i++)
	{
		rect.left=i*width/ROOM_MAX;
		rect.right=rect.left+width-5;
		if (i==m_nowroom)
		{	m_room[i]=new CStatic();
			((CStatic*)m_room[i])->Create("0",
				WS_VISIBLE|WS_CHILD|
				SS_CENTER|SS_NOTIFY,
				rect,this,IDC_ROOM+i);
		}
		else
		{	m_room[i]=new CButton();
			((CButton*)m_room[i])->Create("0",
				WS_VISIBLE|WS_BORDER|WS_CHILD|
				BS_PUSHBUTTON,
				rect,this,IDC_ROOM+i);
		}
	}
	GetClientRect(&rect);
	rect.top+=30;
	rect.right-=100;
	rect.bottom-=20;
	m_recv.Create(
		WS_VISIBLE|WS_CHILD|WS_BORDER|WS_VSCROLL|
		ES_MULTILINE|ES_WANTRETURN|ES_AUTOVSCROLL|ES_READONLY,
		rect,this,1000);
	GetClientRect(&rect);
	rect.top=rect.bottom-20;
	m_send.Create(
		WS_VISIBLE|WS_CHILD|WS_BORDER|WS_TABSTOP|
		ES_MULTILINE|ES_AUTOHSCROLL|
		ES_AUTOVSCROLL|ES_NOHIDESEL,
		rect,this,1100);
	GetClientRect(&rect);
	rect.top+=30;
	rect.left=rect.right-100;
	rect.bottom-=20;
	m_member.Create(
		WS_VISIBLE|WS_CHILD|WS_BORDER|WS_VSCROLL|
		LBS_HASSTRINGS|LBS_NOINTEGRALHEIGHT,
		rect,this,1101);
//	m_member.ResetContent();
	m_member.AddString("★酒井");
	m_member.AddString("☆Aizawa☆");
	
	return 0;
}

UINT g_message;
WPARAM g_wparam;
LPARAM g_lparam;

BOOL CMapClientDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	int a=IDCANCEL;
	if (wParam==IDCANCEL)
		if (lParam==0)
			return TRUE;
	
	return CDialog::OnCommand(wParam, lParam);
}

void CMapClientDlg::OnCancel() 
{
	CDialog::OnCancel();
}

BOOL CMapClientDlg::PreTranslateMessage(MSG* pMsg) 
{
	g_message=pMsg->message;
	g_wparam=pMsg->wParam;
	g_lparam=pMsg->lParam;
	
	return CDialog::PreTranslateMessage(pMsg);
}
