
class CUser : public CObject
{
public:
	CUser(CString&handle,CString&profile,int clientno);
	CString&GetHandle()	{return m_handle;}
	void SetHandle(CString&s)	{ m_handle=s;}
	void SetProfile(CString&s)	{ m_profile=s;}
	int GetClientNo()	{return m_clientno;	}
	CString&GetProfile()	{return m_profile;	}
	void SetClientNo(int c)	{	m_clientno=c;	}
protected:
	CString m_handle;
	CString m_profile;
	int m_clientno;
};

class CUserList : public cPtrList
{
public:
	void Add(CString&handle,CString&profile,int clientno);
	BOOL Search(CString*handle,CString*profile,int clientno);
	void SearchSet(CString handle,CString profile,int clientno);
	BOOL Del(int clientno);
	CUserList();
	~CUserList();
	void SetName(CString&s)	{	m_name=s;	}
	CString&GetName()	{	return m_name;	}
	int GetSelect()	{	return m_select;	}
	void SetSelect(int s)	{	m_select=s;	}
	void clearDelete();
protected:
	int m_select;
	CString m_name;
};