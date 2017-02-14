// RoomStc.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapClient.h"
#include "Panel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomStc

CRoomStc::CRoomStc(int room)
{
	m_room=room;
}

CRoomStc::~CRoomStc()
{
}


BEGIN_MESSAGE_MAP(CRoomStc, CStatic)
	//{{AFX_MSG_MAP(CRoomStc)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomStc メッセージ ハンドラ

void CRoomStc::OnMouseMove(UINT nFlags, CPoint point) 
{
	((CPanel*)GetParent())->OnMouseMove(GetDlgCtrlID(),point);
	
	CStatic::OnMouseMove(nFlags, point);
}

void CRoomStc::OnRButtonUp(UINT nFlags, CPoint point) 
{
	GetParent()->SendMessage(WM_COMMAND,IDM_ROOMNAME,0);
	
	CStatic::OnRButtonUp(nFlags, point);
}
