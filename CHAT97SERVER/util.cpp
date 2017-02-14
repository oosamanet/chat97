#include "stdafx.h"
#include "chat97server.h"

cLinkList::cLinkList()
{
	setPrev(NULL);
	setNext(NULL);
}

cLinkList::cLinkList(cLinkList*prev,cLinkList*next)
{
	setPrev(prev);
	setNext(next);
	setData(NULL);
}

cLinkList::~cLinkList()
{
}
//////////////////////////////////////////
cPtrList::cPtrList()
{
	m_pData=NULL;
	m_count=0;
}

cPtrList::~cPtrList()
{
	clear();
	if (m_pData)
		delete m_pData;
}

void cPtrList::clear()
{
	while (getCount()>0)
	{	void *p=getData(0);
		del(p);
	}
}

void cPtrList::clearDelete()
{
	while (getCount()>0)
	{	void *p=getData(0);
		delete p;
		del(p);
	}
}

void cPtrList::add(void*data)
{
	/***LOCK***/
	CCriticalSection lock;
	if (m_pData)
	{
		cLinkList*p=m_pData;
		for (;p->getNext()!=NULL;p=p->getNext())
			;
		cLinkList*q=new cLinkList(p,NULL);
		q->setData(data);
		p->setNext(q);
		m_count++;
	}
	else
	{
		m_pData=new cLinkList(NULL,NULL);
		m_pData->setData(data);
		m_count++;
	}
}

BOOL cPtrList::del(void*data)
{
	if (!m_pData)
	{	return FALSE;
	}
	/***LOCK***/
	CCriticalSection lock;

	cLinkList*p=m_pData;
	for (;;p=p->getNext())
	{	if (p->getData()==data)
		{
			if (NULL==p->getPrev())	/* リストの先頭 */
			{	m_pData=p->getNext();
				if (m_pData)	/* 先頭のみ */
					m_pData->setPrev(NULL);
			}
			else	/* リストの途中 */
			{	p->getPrev()->setNext(p->getNext());
				if (p->getNext())	/* 最後 */
					p->getNext()->setPrev(p->getPrev());
			}
			delete p;
			m_count--;
			break;
		}
		if (p->getNext()==NULL)
			break;
	}
	/***LOCK***/
	return TRUE;
}

void *cPtrList::getData(int n)
{
	void *pRet=NULL;
	if (m_pData)
	{
		/***LOCK***/
		CCriticalSection lock;
		cLinkList*p=m_pData;
		for (;;p=p->getNext())
		{
			if (n==0)
			{	pRet=p->getData();
				break;
			}
			n--;
			if (p->getNext()==NULL)
				break;
		}
		/***LOCK***/
	}
	return pRet;
}
/* EOF */
