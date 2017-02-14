// chatsock.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "MapClient.h"
#include "Panel.h"

#include <stddef.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CChatSocket::CChatSocket()
{
	m_pWnd=NULL;
	m_seq=0;
}

BOOL CChatSocket::Connect(CWnd*pWnd,CString url,int port)
{
	m_pWnd=pWnd;
	if (!Create())
		return FALSE;
	if (!CAsyncSocket::Connect((LPCTSTR)url,port))
	{
		int iErrorCode = GetLastError();
		if (iErrorCode != WSAEWOULDBLOCK)			// WSAEWOULDBLOCKÇÕê⁄ë±ë“ã@
			return FALSE;
	}
	m_url=url;
	m_port=port;

	return TRUE;
}

CChatSocket::~CChatSocket()
{
	Close();
}

void CChatSocket::Close()
{
TRACE("CChatSocket::Close\n");
	if (m_pWnd==NULL)
		return;
//	m_hSocket=INVALID_SOCKET;
	CAsyncSocket::Close();
	((CPanel*)m_pWnd)->m_isConnect=FALSE;
	m_pWnd=NULL;
}

BOOL CChatSocket::SendMessage(CString &mes)
{
	if (m_pWnd==NULL)
		return FALSE;
	if (SOCKET_ERROR==Send(mes,mes.GetLength(),0))
	{
		int iErrorCode = GetLastError();
		if (iErrorCode != WSAEWOULDBLOCK)			// WSAEWOULDBLOCKÇÕê⁄ë±ë“ã@
		{	Close();
			return FALSE;
		}
	}
	return TRUE;
}

void CChatSocket::OnReceive(int nErrorCode)
{
	if (m_pWnd==NULL)
		return;
	int len;
	char buf[8192];
	static char rbuf[8192];
	static BOOL rflag=FALSE;
	int p;

	if (nErrorCode)
		return;
	len=Receive(buf,8192);
	if (len<0)
	{	((CPanel*)m_pWnd)->OnDisconnectButton();
		return;
	}
	buf[len]=0;

//	TRACE(buf);
	p=0;
	for (int i=0;i<len;i++)
	{	if (buf[i]=='\n')
		{	if (p==-1)
				p=i;
			buf[i]=0;
			CString str;
			if (rflag)
			{	str=rbuf;
				rflag=FALSE;
			}
			str+=&buf[p];
			OnLineReceive(str);
			p=-1;
		}
		else if (buf[i]=='\r')
			;
		else if (p==-1)
		{	p=i;
		}
	}
	if (p!=-1)
	{	strcpy(rbuf,&buf[p]);
		rflag=TRUE;
	}
}

void CChatSocket::OnConnect(int nErrorCode)
{
	if (nErrorCode!=0)
		return;
	if (m_pWnd==NULL)
		return;
	((CPanel*)m_pWnd)->OnConnect();
}

void CChatSocket::OnClose(int nErrorCode)
{
	((CPanel*)m_pWnd)->OnDisconnectButton();
}

void CChatSocket::OnLineReceive(CString s)
{
	if (s.GetLength()==0)
	{	if (m_seq==1)		/* head end */
			m_seq=2;
		else if (m_seq==2)	/* body end */
		{
			m_list.AddTail(s);
			((CPanel*)m_pWnd)->OnRecv(m_list);
			m_list.RemoveAll();
			m_seq=0;
			return;
		}
		else
			return;
	}
	else
	{	if (m_seq==0)
			m_seq=1;
	}
	m_list.AddTail(s);
}
