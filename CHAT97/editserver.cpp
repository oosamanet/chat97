// EditServer.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapClient.h"
//#include "EditServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditServer ダイアログ


CEditServer::CEditServer(CWnd* pParent /*=NULL*/)
	: CDialog(CEditServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditServer)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CEditServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditServer)
	DDX_Control(pDX, IDC_SVLIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditServer, CDialog)
	//{{AFX_MSG_MAP(CEditServer)
	ON_BN_CLICKED(IDC_SVADD, OnSvadd)
	ON_BN_CLICKED(IDC_SVDEL, OnSvdel)
	ON_BN_CLICKED(IDC_SVDOWN, OnSvdown)
	ON_BN_CLICKED(IDC_SVUP, OnSvup)
	ON_BN_CLICKED(IDC_GETCGI, OnGetcgi)
	ON_BN_CLICKED(IDC_EDITCHANGE, OnEditchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditServer メッセージ ハンドラ

void CEditServer::OnSvadd() 
{
	if (m_count>=16)
		return;
	CAddServer dlg;
	dlg.m_port=8000;
	if (IDOK!=dlg.DoModal())
		return;
	m_name[m_count]=dlg.m_name;
	m_host[m_count]=dlg.m_address;
	m_port[m_count]=dlg.m_port;
	m_count++;
	UpdateList();
}

void CEditServer::OnSvdel() 
{
	int now=m_list.GetCurSel();
	if ((m_count<=1)||(now==LB_ERR))
		return;
	m_count--;
	for (int i=now;i<m_count;i++)
	{
		m_name[i]=m_name[i+1];
		m_host[i]=m_host[i+1];
		m_port[i]=m_port[i+1];
	}
	UpdateList();
	m_list.SetCurSel(now);
}

void CEditServer::OnSvdown() 
{
	int now=m_list.GetCurSel();
	if ((now>=m_count-1)||(now==LB_ERR))
		return;
	CString n,h;
	int p;
	n=m_name[now+1];
	h=m_host[now+1];
	p=m_port[now+1];
	m_name[now+1]=m_name[now];
	m_host[now+1]=m_host[now];
	m_port[now+1]=m_port[now];
	m_name[now]=n;
	m_host[now]=h;
	m_port[now]=p;
	UpdateList();
	m_list.SetCurSel(now+1);
}

void CEditServer::OnSvup() 
{
	int now=m_list.GetCurSel();
	if ((now==0)||(now==LB_ERR))
		return;
	CString n,h;
	int p;
	n=m_name[now-1];
	h=m_host[now-1];
	p=m_port[now-1];
	m_name[now-1]=m_name[now];
	m_host[now-1]=m_host[now];
	m_port[now-1]=m_port[now];
	m_name[now]=n;
	m_host[now]=h;
	m_port[now]=p;
	UpdateList();
	m_list.SetCurSel(now-1);
}

void CEditServer::OnOK() 
{
	CMapClientApp*pApp=(CMapClientApp*)AfxGetApp();
	pApp->WriteProfileInt("CHAT97","Scount",m_count);
	for (int i=0;i<m_count;i++)
	{
		CString name;
		name.Format("Sname%d",i+1);
		pApp->WriteProfileString("CHAT97",name,m_name[i]);
		name.Format("Shost%d",i+1);
		pApp->WriteProfileString("CHAT97",name,m_host[i]);
		name.Format("Sport%d",i+1);
		pApp->WriteProfileInt("CHAT97",name,m_port[i]);
	}
	
	CDialog::OnOK();
}

BOOL CEditServer::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CMapClientApp*pApp=(CMapClientApp*)AfxGetApp();
	m_count=pApp->GetProfileInt("CHAT97","Scount",1);
	for (int i=0;i<m_count;i++)
	{
		CString name;
		name.Format("Sname%d",i+1);
		m_name[i]=pApp->GetProfileString("CHAT97",name,DEFAULT_NAME);
		name.Format("Shost%d",i+1);
		m_host[i]=pApp->GetProfileString("CHAT97",name,DEFAULT_HOST);
		name.Format("Sport%d",i+1);
		m_port[i]=pApp->GetProfileInt("CHAT97",name,DEFAULT_PORT);
	}
	UpdateList();
	m_list.SetCurSel(0);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}


void CEditServer::OnGetcgi() 
{
	CSocket socket;
	CArchive*in;
	CArchive*out;
	CSocketFile* pFile;

	if (!socket.Create())
	{
		return;
	}

	while (!socket.Connect(GETCGI_HOST,GETCGI_PORT))
	{
		return;
	}
	pFile = new CSocketFile(&socket);
	in = new CArchive(pFile,CArchive::load);
	out = new CArchive(pFile,CArchive::store);

	CString str= "GET ";
	str += GETCGI_PATH;
	str += " HTTP/1.0\n\n";

	out->Write(str, str.GetLength());
    out->Flush();

	CString line;
	int count=0;
	CString n,h,p;
	while (in->ReadString(line)) {
		int c=line.Find("####");
		if (c==-1)
			continue;
		n=line.Left(c);
		line=line.Mid(c+4);
		c=line.Find("####");
		if (c==-1)
			continue;
		h=line.Left(c);
		p=line.Mid(c+4);
		m_name[count]=n;
		m_host[count]=h;
		m_port[count]=atoi(p);
		count++;
	}
	if (count!=0)
		m_count=count;
	in->Close();
	out->Close();
	pFile->Close();
	socket.Close();

	delete out;
	delete in;
	delete pFile;
	UpdateList();
	m_list.SetCurSel(0);
	return;
}

void CEditServer::UpdateList()
{
	m_list.ResetContent();
	CString str;
	for (int i=0;i<m_count;i++)
	{	str.Format("%s-%s:%d",m_name[i],m_host[i],m_port[i]);
		m_list.AddString(str);
	}
}

void CEditServer::OnEditchange() 
{
	int now=m_list.GetCurSel();
	if (now==LB_ERR)
		return;
	CAddServer dlg;
	dlg.m_port=m_port[now];
	dlg.m_name=m_name[now];
	dlg.m_address=m_host[now];
	if (IDOK!=dlg.DoModal())
		return;
	m_name[now]=dlg.m_name;
	m_host[now]=dlg.m_address;
	m_port[now]=dlg.m_port;
	UpdateList();
}
