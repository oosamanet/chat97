// SrvSocket.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapClient.h"
#include "SrvSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSrvSocket

CSrvSocket::CSrvSocket()
{
}

CSrvSocket::~CSrvSocket()
{
}


// ClassWizard が必要とする以下の行を編集しないでください。
#if 0
BEGIN_MESSAGE_MAP(CSrvSocket, CSocket)
	//{{AFX_MSG_MAP(CSrvSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSrvSocket メンバ関数

BOOL CSrvSocket::Init(int port)
{
	if (FALSE==Create(port))
		return FALSE;
	if (FALSE==Bind(port))
		return FALSE;
	if (FALSE==Listen())
		return FALSE;
	return TRUE;
}

void CSrvSocket::OnAccept(int nErrorCode)
{
	CSrvSocket* p=new CSrvSocket();
	Accept(*p);
}

void CSrvSocket::OnReceive(int nErrorCode)
{	char buf[4096];
	Receive(buf,4096);

}

BOOL CSrvSocket::Connect(CWnd * pWnd, CString host, int port)
{
	m_pWnd=pWnd;
	if (FALSE==Create(port))
		return FALSE;
	while (!CAsyncSocket::Connect((LPCTSTR)host,(UINT)port))
	{
		return FALSE;
	}
	return TRUE;
}

void CSrvSocket::OnClose(int nErrorCode) 
{
	Close();
	delete this;
}
