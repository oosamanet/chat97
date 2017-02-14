// Send.cpp : インプリメンテーション ファイル
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
// CSend

CSend::CSend()
{
}

CSend::~CSend()
{
}

#ifdef CHAT97_USERICHEDIT
BEGIN_MESSAGE_MAP(CSend, CRichEditCtrl)
#else
BEGIN_MESSAGE_MAP(CSend, CEdit)
#endif
	//{{AFX_MSG_MAP(CSend)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSend メッセージ ハンドラ

void CSend::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ((nChar != VK_RETURN) || (nRepCnt!=1))
	{
#ifdef CHAT97_USERICHEDIT
		CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
#else
		CEdit::OnChar(nChar, nRepCnt, nFlags);
#endif
		return;
	}
	else
	{
		CString str;
		GetWindowText(str);
		SetWindowText(CString());
		((CPanel*)GetParent())->OnSend(str);
	}
}

void CSend::CopyClip(CString&str)
{
	CString s;
	GetWindowText(s);
	SetWindowText(str);
	SetSel(0,-1);
	Copy();
	SetWindowText(s);
	SetSel(s.GetLength(),s.GetLength());
}


COLORREF CSend::SetBackgroundColor(BOOL bSysColor, COLORREF cr)
{
#ifdef CHAT97_USERICHEDIT
	return CRichEditCtrl::SetBackgroundColor(bSysColor,cr);
#else
	return cr;
#endif
}
