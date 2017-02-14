//#define SERVICE 1

#ifndef __UTIL_H__
#define __UTIL_H__

class cLinkList : public CObject
{
public:
	cLinkList();
	cLinkList(cLinkList*prev,cLinkList*next);
	~cLinkList();
	void*getData()		{	return m_pData;	}
	cLinkList*getPrev()	{	return m_prev;	}
	cLinkList*getNext()	{	return m_next;	}
	void setData(void*p)		{	m_pData=p;	}
	void setPrev(cLinkList*p)	{	m_prev=p;	}
	void setNext(cLinkList*p)	{	m_next=p;	}
protected:
	cLinkList* m_prev;
	cLinkList* m_next;
	void*m_pData;
};

class cPtrList : public CObject
{
public:
	cPtrList();
	~cPtrList();
	void*getData(int n);
	int getCount()		{	return m_count;	}
	cLinkList* getPtr()	{	return m_pData;	}
	void add(void*data);
	BOOL del(void*data);
	void clear();
	void clearDelete();
protected:
	int m_count;
	cLinkList* m_pData;
};

#endif
