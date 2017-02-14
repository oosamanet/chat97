#include "stdafx.h"
#include "chat97server.h"

CUser::CUser(CString&handle,CString&profile,int clientno)
{	SetHandle(handle);
	SetProfile(profile);
	SetClientNo(clientno);
}

CUserList::CUserList()
{
	m_select=-1;
}

CUserList::~CUserList()
{
	clearDelete();
}

void CUserList::clearDelete()
{
	while (getCount()>0)
	{	CUser*p=(CUser*)getData(0);
		delete p;
		del(p);
	}
}

void CUserList::Add(CString&handle,CString&profile,int clientno)
{
	CUser*p=new CUser(handle,profile,clientno);
	add(p);
}

BOOL CUserList::Del(int clientno)
{
	for (int i=0;i<getCount();i++)
	{	CUser*p=(CUser*)getData(i);
		if (clientno==p->GetClientNo())
		{
			if (clientno==m_select)
				m_select=-1;
			del(p);
			delete p;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CUserList::Search(CString*handle,CString*profile,int clientno)
{
	for (int i=0;i<getCount();i++)
	{	CUser*p=(CUser*)getData(i);
		if (clientno==p->GetClientNo())
		{
			*handle=p->GetHandle();
			*profile=p->GetProfile();
			return TRUE;
		}
	}
	return FALSE;
}

void CUserList::SearchSet(CString handle,CString profile,int clientno)
{
	for (int i=0;i<getCount();i++)
	{	CUser*p=(CUser*)getData(i);
		if (clientno==p->GetClientNo())
		{
			p->SetHandle(handle);
			p->SetProfile(profile);
		}
	}
}

