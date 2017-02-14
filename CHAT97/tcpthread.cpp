// TCPThread.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapClient.h"
#include "TCPThread.h"
#include "panel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTCPThread

IMPLEMENT_DYNCREATE(CTCPThread, CWinThread)

CTCPThread::CTCPThread()
{
	m_pSocket=NULL;
}

CTCPThread::~CTCPThread()
{
	AfxEndThread(0);
TRACE("~CTCPThread:this%08lX,m_pWnd%08lXm_pSocket%08lX\n",this,m_pWnd,m_pSocket);
	if (m_pWnd)
	{//	((CPanel*)m_pWnd)->m_tcpthread=NULL;
		m_pWnd=NULL;
	}
	if (m_pSocket)
	{
		CChatSocket*p=m_pSocket;
		m_pSocket=NULL;
		delete p;
	}
//	ExitInstance();
}

void CTCPThread::SetWnd(CWnd*p)
{
	m_pWnd=p;
	m_pMainWnd=p;
}

BOOL CTCPThread::InitInstance()
{
	CPanel*p=(CPanel*)m_pWnd;
//	m_pMainWnd=p;
//	m_pActiveWnd=p;

	m_pSocket=new CChatSocket();
	if (FALSE==m_pSocket->Connect(p,p->m_host,p->m_port))
	{
		return TRUE;
		if (m_pSocket==NULL)
			return TRUE;
TRACE("SOCKET cant connect,m_pSocket%08lX\n",m_pSocket);
		delete m_pSocket;
		m_pSocket=NULL;
//		ExitInstance();
//		AfxEndThread(0);
		return TRUE;
	}
	p->m_socket=m_pSocket;
TRACE("SOCKET connected[%0lX]\n",p->m_socket);
	CString s;
	CString out="LOGIN\n";
	s.Format("world: %d\n",((CMapClientApp*)AfxGetApp())->m_world);
	out+=s;
	s.Format("handle: %s\n",p->m_handle);
	out+=s;
	s.Format("user_agent: win32/CHAT97\n");
	out+=s;
	s.Format("profile: %s####%s####%s\n",p->m_mail,p->m_profile,p->m_homepage);
	out+=s;
	s.Format("version: %s\n",NOW_VERSION);
	out+=s;
	s.Format("room: %d\n",p->m_nowroom);
	out+=s;
	out+="level: rootsakai\n";
	out+="\n";
	out+="\n";
	p->m_socket->SendMessage(out);
	out="GETALLXY\n\n\n";
	p->m_socket->SendMessage(out);
	out="GETALLHOTSPOT\n\n\n";
	p->m_socket->SendMessage(out);
	p->OnConnectTime();

	return TRUE;
}

int CTCPThread::ExitInstance()
{
TRACE("ExitInstance.m_pWnd%08lX,m_pSocket%08lX\n",m_pWnd,m_pSocket);
	if (m_pWnd)
	{	((CPanel*)m_pWnd)->m_tcpthread=NULL;
		m_pWnd=NULL;
	}
	if (m_pSocket)
	{	delete m_pSocket;
		m_pSocket=NULL;
	}
	// TODO: この位置にスレッド単位の初期化コードを追加してください。
//	delete this;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CTCPThread, CWinThread)
	//{{AFX_MSG_MAP(CTCPThread)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCPThread メッセージ ハンドラ

int CTCPThread::Run() 
{
	return CWinThread::Run();
}

