// RoomBtn.cpp : インプリメンテーション ファイル
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
// CRoomBtn

CRoomBtn::CRoomBtn(int room)
{
	m_room=room;
}

CRoomBtn::~CRoomBtn()
{
}


BEGIN_MESSAGE_MAP(CRoomBtn, CButton)
	//{{AFX_MSG_MAP(CRoomBtn)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomBtn メッセージ ハンドラ

void CRoomBtn::OnMouseMove(UINT nFlags, CPoint point) 
{
	((CPanel*)GetParent())->OnMouseMove(GetDlgCtrlID(),point);
	
	CButton::OnMouseMove(nFlags, point);
}
