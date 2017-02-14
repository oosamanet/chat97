// Member.cpp : インプリメンテーション ファイル
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
// CMember

CMember::CMember()
{
}

CMember::~CMember()
{
}

BEGIN_MESSAGE_MAP(CMember, CListBox)
	//{{AFX_MSG_MAP(CMember)
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelchange)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMember メッセージ ハンドラ

void CMember::OnMouseMove(UINT nFlags, CPoint point) 
{
	((CPanel*)GetParent())->OnMouseMove(GetDlgCtrlID(),point);
	
	CListBox::OnMouseMove(nFlags, point);
}

#define ITEM_HEIGHT	16;

void CMember::MeasureItem(LPMEASUREITEMSTRUCT lpMIS) 
{
	lpMIS->itemHeight = ITEM_HEIGHT;
}

extern COLORREF Ncolor[10];

void CMember::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	UINT clientno = (UINT)lpDIS->itemData;
	CPanel*pParent=(CPanel*)GetParent();

TRACE("member:drawItem(%d)\n",clientno);
	pDC->SelectObject(pParent->m_topfont);
	int room=pParent->m_lookroom;
	CString h,p;
	pParent->m_user[room].Search(&h,&p,clientno);

	pDC->SetBkMode(TRANSPARENT);
	if (lpDIS->itemState & ODS_SELECTED)
	{
//		pParent->CutESC(h);
		COLORREF b=RGB(0,0,150);
		pDC->FillSolidRect(&lpDIS->rcItem, b);
	}
	else
	{
		pDC->SetBkMode(TRANSPARENT);
		COLORREF b=pParent->m_chatBackColor;
		pDC->FillSolidRect(&lpDIS->rcItem, b);
	}
	Ncolor[0]=pParent->m_chatCharColor;
	pDC->SetTextColor(Ncolor[0]);
	int x=lpDIS->rcItem.left;
	int y=lpDIS->rcItem.top;
//	m_listicon.Draw(pDC,0,CPoint(x,y),ILD_TRANSPARENT);
//	x+=16;
	if (-1!=h.Find('#'))
	{
		CString send;
		for (int i=0;i<h.GetLength();)
		{	if (_ismbblead((BYTE)h[i]))
			{
				send+=h.Mid(i,2);
				i+=2;
			}else if ((h[i]=='#')&&
				(i<h.GetLength()-1)&&
				(isdigit(h[i+1])))
			{	if (send.GetLength())
				{
					pDC->TextOut(x,y,send);
					CSize sz=pDC->GetTextExtent(send);
					x+=sz.cx;
					send="";
				}
				pDC->SetTextColor(Ncolor[h[i+1]-'0']);
				i+=2;
			}else
			{
				send+=h.Mid(i,1);
				i++;
			}
		}
		if (send.GetLength())
		{	pDC->TextOut(x,y,send);
		}
	}
	else
	{
		pDC->TextOut(x,y,h);
	}
	pDC->SetTextAlign(TA_NOUPDATECP);
/*	if (lpDIS->itemAction & ODA_DRAWENTIRE)
	{
		// 要求された色でカラー アイテムをペイントします。
		CBrush br(cr);
		pDC->FillRect(&lpDIS->rcItem, &br);
	}

	if ((lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		// アイテムは選択されています - フレームをハイライト
		COLORREF crHilite = RGB(255-GetRValue(cr),
						255-GetGValue(cr), 255-GetBValue(cr));
		CBrush br(crHilite);
		pDC->FrameRect(&lpDIS->rcItem, &br);
	}

	if (!(lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & ODA_SELECT))
	{
		// アイテムの選択は取り消されました -- フレームを削除
		CBrush br(cr);
		pDC->FrameRect(&lpDIS->rcItem, &br);
	}
*/
}

int CMember::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;
//	m_listicon.Create(IDB_LISTICON,16,1,RGB(0xff,0xff,0xff));
	CClientDC dc(this); // 描画用のデバイス コンテキスト
TRACE("member:OnPaint(%d)\n",((CPanel*)GetParent())->m_isConnect);
	
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(&rect,((CPanel*)GetParent())->m_chatBackColor);
	return 0;
}


void CMember::OnSelchange() 
{
	CPanel*p=(CPanel*)GetParent();
	int clientno=GetItemData(GetCurSel());
	p->m_user[p->m_lookroom].SetSelect(clientno);
}

BOOL CMember::OnEraseBkgnd(CDC* pDC) 
{
	CPanel*pParent=(CPanel*)GetParent();

	CRect rect;
	GetClientRect(&rect);

	int room=pParent->m_lookroom;
	rect.top+=pParent->m_user[room].getCount()*ITEM_HEIGHT;
	pDC->FillSolidRect(&rect,((CPanel*)GetParent())->m_chatBackColor);

TRACE("member:OnEraseBkgnd(%d)\n",pParent->m_user[room].getCount());

	return TRUE;
}
/*
void CMember::OnPaint() 
{
	if (!((CPanel*)GetParent())->m_isConnect)
	{	CClientDC dc(this); // 描画用のデバイス コンテキスト
TRACE("member:OnPaint(%d)\n",((CPanel*)GetParent())->m_isConnect);
	
		CRect rect;
		GetClientRect(&rect);
		dc.FillSolidRect(&rect,((CPanel*)GetParent())->m_chatBackColor);
	}	
	// 描画用メッセージとして CListBox::OnPaint() を呼び出してはいけません
}
*/