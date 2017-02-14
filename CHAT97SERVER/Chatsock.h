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
	BOOL Init(int port,CWnd*pWnd);
	void OnAccept(int nErrorCode);
	void OnClose(int nErrorCode);
	CChatSocket();
	BOOL Connect(CWnd*pWnd,CString url,int port);
	CChatSocket* Search(int c);
	void CutESC(CString &str);
	BOOL Start(CString &s,CString d);
	~CChatSocket();
	int clientno;
	CString handle;
	CString profile;
	CString useragent;
	int version;
	int x,y,width,height,xrange,yrange,lap;
	int targetclientno;
	CString m_cmd;
	CString m_message;
	int cmd;
	int seq;
	int Hx,Hy;
	CString Hhandle,Hprofile;
	CString level;

// Operations
public:
	CString *hotspot;
	cPtrList*user;
	int world;
	BOOL isSendOK;
	CWnd*m_pWnd;
	CString body;
	CString m_linebuf;

	BOOL CmdMain();
	void GetHead();
	int GetCmd();
	BOOL OnLineReceive();
	virtual void OnReceive(int nErrorCode);
	void SendMessage(CString &str);
	void SendMessageAll(CString str);
	void SendMessageRange(CString str);

// Implementation
protected:
};

#endif // __CHATSOCK_H__
