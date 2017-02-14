// chatsock.h : interface of the CChatSocket class
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

#ifndef __CHATSOCK_H__
#define __CHATSOCK_H__

class CChatSocket : public CAsyncSocket
{
// Construction
public:
	void OnClose(int nErrorCode);
	CChatSocket();
	BOOL Connect(CWnd*pWnd,CString url,int port);
	~CChatSocket();
	void Close();

// Operations
public:
	int m_seq;
	void OnLineReceive(CString s);
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	BOOL SendMessage(CString &mes);
	CString m_url;
	int m_port;
	CWnd*m_pWnd;
	CStringList m_list;

// Implementation
protected:
};

#endif // __CHATSOCK_H__
