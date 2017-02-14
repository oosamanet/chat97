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
#include "chat97server.h"
#include "chat97serverdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BOOL CChatSocket::Start(CString &s,CString d)
{
	int len=s.GetLength();
	if (len>d.GetLength())
		len=d.GetLength();
	for (int i=0;i<len;i++)
	{
		if (s[i]!=d[i])
			return FALSE;
	}
	return TRUE;
}

CChatSocket::CChatSocket()
{
	cmd=0;
	seq=0;
	world=0;
	width=10;
	height=1;
	xrange=1;
	yrange=1;
	lap=0;
	x=0;
	y=0;
	Hx=0;
	Hy=0;
	targetclientno=-1;
	isSendOK=FALSE;

	m_pWnd=NULL;
}

BOOL CChatSocket::Connect(CWnd*pWnd,CString url,int port)
{
	m_pWnd=pWnd;

	if (!Create()){
		return FALSE;
	}
	if (!CAsyncSocket::Connect(url,port))
	{
		int iErrorCode = GetLastError();
		if (iErrorCode != WSAEWOULDBLOCK)			// WSAEWOULDBLOCKは接続待機
			return FALSE;
	}
	return TRUE;
}

CChatSocket::~CChatSocket()
{
	Close();
}

void CChatSocket::SendMessage(CString &str)
{
	int nErrorCode = Send(str,str.GetLength(),0);
	if ( nErrorCode < 0)
	{
	}
}

void CChatSocket::SendMessageRange(CString str)
{
	for (int i=0;i<user->getCount();i++)
	{
		CChatSocket*p=(CChatSocket*)user->getData(i);
		if (! p->isSendOK)
			continue;
		if (world!=p->world)
			continue;
		if (lap==0)
		{
			if (abs(x-p->x) >= xrange)
				continue;
			if (abs(y-p->y) >= yrange)
				continue;
		}else{
			int tmp1,d1,d2;
			tmp1=x - p->x;
			d1=(tmp1 + width) % width;
			d2=(-tmp1 + width) % width;
			if (min(d1,d2) >= xrange)
				continue;
			tmp1=y - p->y;
			d1=(tmp1 + height) % height;
			d2=(-tmp1 + height) % height;
			if (min(d1,d2) >= yrange)
				continue;
		}
		p->SendMessage(str);
	}
}

void CChatSocket::SendMessageAll(CString str)
{
	for (int i=0;i<user->getCount();i++)
	{	CChatSocket*p=(CChatSocket*)user->getData(i);
		if ((world==p->world)&&(p->isSendOK))
			p->SendMessage(str);
	}
}

void CChatSocket::OnReceive(int nErrorCode)
{
	if (nErrorCode)
	{
		OnClose(nErrorCode);
		return;
	}

	char buf[8192];
	int len=Receive(buf,8192);
	if ((len==0)||(len==SOCKET_ERROR))
	{
		OnClose(0);
		return;
	}
	for (int i=0;i<len;i++)
	{	BYTE c=buf[i];
		if (c=='\r')
		{	continue;
		}
		else if (c=='\n')
		{	if (FALSE==OnLineReceive())
				return;
		}
		else
		{	m_linebuf+=c;
		}
	}
}

BOOL CChatSocket::OnLineReceive()
{
	m_message+=m_linebuf+"\n";
	if (m_linebuf.GetLength()>4096)
	{	OnClose(0);
		return FALSE;
	}
	if (m_linebuf.GetLength()==0)
	{
		if (seq==SEQ_HEAD)
		{	seq=SEQ_BODY;
		}
		else if (seq==SEQ_BODY)
		{
			if (FALSE==CmdMain())
				return FALSE;
			targetclientno=-1;
			seq=0;
			body.Empty();
			m_message.Empty();
		}
		else
		{	targetclientno=-1;
		}
	}
	else
	{	if (seq==0)
		{	cmd=GetCmd();
			if (cmd==CMD_HTTP)
			{
				CString send,s;
				int count=user->getCount()-1;
				send="<html><head><title>CHAT97status</title></head>";
				send+="<body bgcolor=\"#fcfabd\">";
				s.Format("<h1>現在%d人のユーザがいます</h1>\n",count);
				send+=s;
				send+="</body></html>";
				SendMessage(send);
				OnClose(0);
				return FALSE;
			}
			seq=SEQ_HEAD;
		}
		else if (seq==SEQ_HEAD)
		{	GetHead();
		}
		else if (seq==SEQ_BODY)
		{	body+=m_linebuf;
		}
	}
	m_linebuf.Empty();
	return TRUE;
}

BOOL CChatSocket::Init(int port,CWnd*pWnd)
{
	m_pWnd=pWnd;
	if (FALSE==Create(port))
		return FALSE;
//	if (FALSE==Bind(port))
//		return FALSE;
	if (FALSE==Listen())
		return FALSE;
	return TRUE;
}

void CChatSocket::OnAccept(int nErrorCode)
{
	if (nErrorCode)
		return;
	if (m_pWnd)
		((CChat97ServerDlg*)m_pWnd)->OnAccept();
}

void CChatSocket::OnClose(int nErrorCode)
{
	if (m_pWnd)
	{	((CChat97ServerDlg*)m_pWnd)->OnClose(clientno);
	}
}

int CChatSocket::GetCmd()
{
	cmd=CMD_ELSE;
	if		(Start(m_linebuf,"GET "))			cmd=CMD_HTTP;
	else if (Start(m_linebuf,"GETRANGEXY"))		cmd=CMD_GETRANGEXY;
	else if (Start(m_linebuf,"GETALLXY"))		cmd=CMD_GETALLXY;
	else if (Start(m_linebuf,"LOGIN"))			cmd=CMD_LOGIN;
	else if (Start(m_linebuf,"LOGOUT"))			cmd=CMD_LOGOUT;
	else if (Start(m_linebuf,"ROOM"))			cmd=CMD_ROOM;
	else if (Start(m_linebuf,"MOVE"))			cmd=CMD_MOVE;
	else if (Start(m_linebuf,"SETHOTSPOT"))		cmd=CMD_SETHOTSPOT;
	else if (Start(m_linebuf,"GETALLHOTSPOT"))	cmd=CMD_GETALLHOTSPOT;
	else if (Start(m_linebuf,"KILL"))			cmd=CMD_KILL;
	else if (Start(m_linebuf,"GETIPADDRESS"))	cmd=CMD_GETIPADDRESS;
	else if (Start(m_linebuf,"SETVERSION"))		cmd=CMD_SETVERSION;
	else if (Start(m_linebuf,"CHAT"))			cmd=CMD_CHAT;
	else if (Start(m_linebuf,"SETHANDLE"))		cmd=CMD_SETHANDLE;
	else if (m_linebuf.GetLength()!=0)			cmd=CMD_USER;
	m_cmd=m_linebuf;
	return cmd; 
}

void CChatSocket::GetHead()
{
		if (Start(m_linebuf,"handle:"))					Hhandle=m_linebuf.Mid(8);
		else if (Start(m_linebuf,"world:"))				world=atoi(m_linebuf.Mid(7));
		else if (Start(m_linebuf,"x:"))					Hx=atoi(m_linebuf.Mid(3));
		else if (Start(m_linebuf,"y:"))					Hy=atoi(m_linebuf.Mid(3));
		else if (Start(m_linebuf,"width:"))				width=atoi(m_linebuf.Mid(7));
		else if (Start(m_linebuf,"height:"))			height=atoi(m_linebuf.Mid(8));
		else if (Start(m_linebuf,"xrange:"))			xrange=atoi(m_linebuf.Mid(8));
		else if (Start(m_linebuf,"yrange:"))			yrange=atoi(m_linebuf.Mid(8));
		else if (Start(m_linebuf,"lap:"))				lap=atoi(m_linebuf.Mid(5));
		else if (Start(m_linebuf,"version:"))			version=atoi(m_linebuf.Mid(9));
		else if (Start(m_linebuf,"profile:"))			Hprofile=m_linebuf.Mid(9);
		else if (Start(m_linebuf,"user_agent:"))		useragent=m_linebuf.Mid(12);
		else if (Start(m_linebuf,"room:"))				Hx=atoi(m_linebuf.Mid(6));
		else if (Start(m_linebuf,"hotspot_x:"))			Hx=atoi(m_linebuf.Mid(11));
		else if (Start(m_linebuf,"hotspot_y:"))			Hy=atoi(m_linebuf.Mid(11));
		else if (Start(m_linebuf,"hotspot_profile:"))	profile=m_linebuf.Mid(17);
		else if (Start(m_linebuf,"target_clientno:"))	targetclientno=atoi(m_linebuf.Mid(17));
		else if (Start(m_linebuf,"hotspot_handle:"))	Hhandle=m_linebuf.Mid(16);
		else if (Start(m_linebuf,"level:"))				level=m_linebuf.Mid(7);
}

void CChatSocket::CutESC(CString & str)
{
	if (-1==str.Find('#'))
		return;
	CString ret;
	for (int i=0;i<str.GetLength();)
	{	if (_ismbblead((BYTE)str[i]))
		{
			ret+=str.Mid(i,2);
			i+=2;
		}else if ((str[i]=='#')&&
			(i<str.GetLength()-1)&&
			(isdigit(str[i+1])))
		{
			i+=2;
		}else
		{
			ret+=str.Mid(i,1);
			i++;
		}
	}
	str=ret;
	return;
}

BOOL CChatSocket::CmdMain()
{
	int i;
	CString s;
	CString send;
	if ((cmd==CMD_LOGIN)&&(!isSendOK))
	{
		handle=Hhandle;
		profile=Hprofile;
		CutESC(Hhandle);
		x=Hx;
		y=Hy;
		if ((version<CLIENTVERSION)||
			(Hhandle.GetLength()==0)||
			(Hprofile.GetLength()==0)||
			(Hhandle.Compare("システム")==0)||
			x<0||
			x>=10||
			y!=0)
		{
			send="CHAT\n";
			send+="handle: システム\n";
			send+="user_x: 0\n";
			send+="room: 0\n";
			send+="user_room: 0\n";
			send+="target_clientno: 1\n\n";
			send+="http://www.oosama.com/chatから新しいVersionをダウンロードしてください\n\n";
			SendMessage(send);
			OnClose(0);
			return FALSE;
		}
		send= "YOU\n";
		s.Format("clientno: %d\n\n\n",clientno);
		send+=s;
		SendMessage(send);
		CFile fp;
		if (fp.Open("start.txt",CFile::modeRead))
		{
			send="CHAT\n";
			send+="handle: システム\n";
			send+="user_x: 0\n";
			send+="room: 0\n";
			send+="user_room: 0\n";
			send+="target_clientno: 1\n\n";
			CArchive in(&fp,CArchive::load);
			while (in.ReadString(s))
			{	s.Format(s,clientno);
				send+=s;
				send+="\n";
			}

			send+="\n";
			SendMessage(send);
		}
		send= "LOGIN\n";
		s.Format("clientno: %d\n",clientno);
		send+=s;
		s.Format("handle: %s\n",handle);
		send+=s;
		s.Format("profile: %s\n",profile);
		send+=s;
		s.Format("room: %d\n\n\n",x);
		send+=s;
		SendMessageAll(send);
		if (m_pWnd)
		{
			CListBox*pList=(CListBox*)((CChat97ServerDlg*)m_pWnd)->GetDlgItem(IDC_MEMBER);

			s=handle;
			CString s2="　　　　　　　　　　　　　　　　　　　　　　　　　　　　　";
			s+=s2.Left((50-s.GetLength())&0xffffe);
			int no=pList->AddString(s);
			pList->SetItemData(no,clientno);
		}
	}
	else if (cmd==CMD_GETALLXY)
	{
		send="GETALLXY\n\n";
		for (int i=0;i<user->getCount();i++)
		{	CChatSocket*p=(CChatSocket*)user->getData(i);
			if ((p->handle.GetLength()==0)||
				(p->profile.GetLength()==0)||
				(p->world!=world))
				continue;
			s.Format("%s\n",p->handle);
			send+=s;
			s.Format("%d %d\n",p->x,p->y);
			send+=s;
			s.Format("%s\n",p->profile);
			send+=s;
			s.Format("%d\n",p->clientno);
			send+=s;
		}
		send+="\n";
		SendMessage(send);
	}
	else if (cmd==CMD_GETALLHOTSPOT)
	{	send="GETALLHOTSPOT\n\n";
		for (i=0;i<10;i++)
		{	if (hotspot[i].GetLength())
			{	s.Format("%s\n",hotspot[i]);
				send+=s;
				s.Format("%d\n0\nN\n",i);
				send+=s;
			}
		}
		send+="\n";
		SendMessage(send);
		isSendOK=TRUE;
		((CChat97ServerDlg*)m_pWnd)->SetInfo(FALSE);
	}
	else if (cmd==CMD_SETHOTSPOT)
	{
		if ((Hhandle.GetLength()>0)&&(Hx>=0)&&(Hx<10))
		{
			send="SETHOTSPOT\n";
			hotspot[Hx]=Hhandle;
			s.Format("hotspot_handle: %s\n",hotspot[Hx]);
			send+=s;
			s.Format("hotspot_x: %d\n",Hx);
			send+=s;
			send+="hotspot_y: 0\n\n\n";
			SendMessageAll(send);
		}
	}
	else if (cmd==CMD_ROOM)
	{
		x=Hx;
		send="ROOM\n";
		send+="level: root\n";
		s.Format("clientno: %d\n",clientno);
		send+=s;
		s.Format("room: %d\n\n\n",x);
		send+=s;
		SendMessageAll(send);
	}
	else if (cmd==CMD_CHAT)
	{
		send="CHAT\n";
		if (targetclientno!=-1)
		{	s.Format("target_clientno: %d\n",targetclientno);
			send+=s;
			s.Format("room: %d\n",x);
			send+=s;
		}
		s.Format("clientno: %d\n\n",clientno);
		send+=s;
		s.Format("%s\n\n",body);
		send+=s;
		if (targetclientno!=-1)
		{	CChatSocket*p=Search(targetclientno);
			if (p)
				p->SendMessage(send);
		}
		else
		{	SendMessageRange(send);
		}
	}
	else if (cmd==CMD_GETIPADDRESS)
	{
		CChatSocket*p=Search(targetclientno);
		if (p)
		{	send="GETIPADDRESS\n";
			s.Format("target_clientno: %d\n\n",targetclientno);
			send+=s;
			UINT port;
			if (FALSE==p->GetPeerName(s,port))
				return TRUE;
			s+="\n\n";
			send+=s;
			SendMessage(send);
		}
	}
	else if (cmd==CMD_KILL)
	{
		CChatSocket*p=Search(targetclientno);
		if (p)
		{
			if (m_pWnd)
				((CChat97ServerDlg*)m_pWnd)->OnClose(targetclientno);
			return FALSE;
		}
	}
	else if (cmd==CMD_SETHANDLE)
	{
		handle=Hhandle;
		CutESC(Hhandle);
		if (Hhandle.GetLength()==0)
		{	OnClose(0);
			return FALSE;
		}
		profile=Hprofile;
		send="SETHANDLE\n";
		s.Format("handle: %s\n",handle);
		send+=s;
		s.Format("clientno: %d\n",clientno);
		send+=s;
		s.Format("room: %d\n",x);
		send+=s;
		s.Format("profile: %s\n\n\n",profile);
		send+=s;
		SendMessageAll(send);
	}
	else if (cmd==CMD_USER)		//ユーザ定義メッセージ
	{
		CChatSocket*p=Search(targetclientno);
		if (p)
		{	p->SendMessage(m_message);
		}
		else if (m_cmd.Left(2).CompareNoCase("G_")==0)
		{
			SendMessageAll(m_message);
		}
		else
		{	SendMessageRange(m_message);
		}
	}
	return TRUE;
}

CChatSocket*CChatSocket::Search(int c)
{
	CChatSocket*p,*ret;
	ret=NULL;
	for (int i=0;i<user->getCount();i++)
	{	p=(CChatSocket*)user->getData(i);
		if (c==p->clientno)
		{	ret=p;
			break;
		}
	}
	return ret;
}
