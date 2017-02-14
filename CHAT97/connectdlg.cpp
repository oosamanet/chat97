// ConnectDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MapClient.h"
#include "ConnectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg ダイアログ


CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectDlg)
                // メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	//{{AFX_MSG_MAP(CConnectDlg)
	ON_BN_CLICKED(IDC_EDITSERVER, OnEditserver)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg メッセージ ハンドラ

void CConnectDlg::OnOK() 
{
	CMapClientApp*pApp=(CMapClientApp*)AfxGetApp();

	CComboBox*pList=(CComboBox*)GetDlgItem(IDC_SERVERLIST);
	int n=pList->GetCurSel();
	CString name;
	name.Format("Shost%d",n+1);
	m_host=pApp->GetProfileString("CHAT97",name,DEFAULT_HOST);
	name.Format("Sport%d",n+1);
	m_port=pApp->GetProfileInt("CHAT97",name,DEFAULT_PORT);

	GetDlgItem(IDC_HANDLE)->GetWindowText(m_handle);
	GetDlgItem(IDC_MAIL)->GetWindowText(m_mail);
	GetDlgItem(IDC_HOMEPAGE)->GetWindowText(m_homepage);
	GetDlgItem(IDC_PROFILE)->GetWindowText(m_profile);
	m_handle.TrimLeft();
	m_handle.TrimRight();
	for (int i=0;i<m_handle.GetLength();)
	{
		int c1=m_handle[i]&0xff;
		int c2=0;
		if (i<m_handle.GetLength()-1)
			c2=m_handle[i+1]&0xff;
		if ((c1==0x81)&&
			(c2==0x40))
			m_handle=m_handle.Left(i)+m_handle.Mid(i+2);
		else if (c1<=0x20)
			m_handle=m_handle.Left(i)+m_handle.Mid(i+1);
		else
			i++;
	}
	CString temp=m_handle;
	((CMapClientApp*)AfxGetApp())->CutESC(temp);
	if (1>temp.GetLength())
	{
		CString s;
		GetDlgItem(IDC_HANDLE)->SetWindowText(s);
		AfxMessageBox("ハンドルをちゃんと入れてね");
		return;
	}
	pApp->WriteProfileString("CHAT97","Handle",m_handle);
	pApp->WriteProfileString("CHAT97","Mail",m_mail);
	pApp->WriteProfileString("CHAT97","HomaPage",m_homepage);
	pApp->WriteProfileString("CHAT97","Profile",m_profile);
	CDialog::OnOK();
}

BOOL CConnectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CMapClientApp*pApp=(CMapClientApp*)AfxGetApp();

	m_handle=pApp->GetProfileString("CHAT97","Handle","");
	GetDlgItem(IDC_HANDLE)->SetWindowText(m_handle);
	m_mail=pApp->GetProfileString("CHAT97","Mail","");
	GetDlgItem(IDC_MAIL)->SetWindowText(m_mail);
	m_homepage=pApp->GetProfileString("CHAT97","HomaPage","");
	GetDlgItem(IDC_HOMEPAGE)->SetWindowText(m_homepage);
	m_profile=pApp->GetProfileString("CHAT97","Profile","");
	GetDlgItem(IDC_PROFILE)->SetWindowText(m_profile);

	int m_Scount=pApp->GetProfileInt("CHAT97","Scount",0);
	CComboBox*pList=(CComboBox*)GetDlgItem(IDC_SERVERLIST);
	if (m_Scount==0)
	{	m_Scount=getCGI();
	}
	for (int i=0;i<m_Scount;i++)
	{
		CString name;
		name.Format("Sname%d",i+1);
		CString s=pApp->GetProfileString("CHAT97",name,DEFAULT_NAME);
		pList->AddString(s);
	}

	pList->SetCurSel(0);

	return FALSE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
}

int CConnectDlg::getCGI() 
{	CSocket socket;
	CArchive*in;
	CArchive*out;
	CSocketFile* pFile;

	if (!socket.Create())
	{
		return 1;
	}

	while (!socket.Connect(GETCGI_HOST,GETCGI_PORT))
	{
		return 1;
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
	CMapClientApp*pApp=(CMapClientApp*)AfxGetApp();
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
		CString name;
		name.Format("Sname%d",count+1);
		pApp->WriteProfileString("CHAT97",name,n);
		name.Format("Shost%d",count+1);
		pApp->WriteProfileString("CHAT97",name,h);
		name.Format("Sport%d",count+1);
		pApp->WriteProfileInt("CHAT97",name,atoi(p));

		count++;
	}
	in->Close();
	out->Close();
	pFile->Close();
	socket.Close();
	pApp->WriteProfileInt("CHAT97","Scount",count);

	delete out;
	delete in;
	delete pFile;
	return count;
}

void CConnectDlg::OnEditserver() 
{
	CEditServer dlg;
	if (IDCANCEL==dlg.DoModal())
		return;
	CMapClientApp*pApp=(CMapClientApp*)AfxGetApp();
	int m_Scount=pApp->GetProfileInt("CHAT97","Scount",1);
	CComboBox*pList=(CComboBox*)GetDlgItem(IDC_SERVERLIST);
	pList->ResetContent();
	for (int i=0;i<m_Scount;i++)
	{
		CString name;
		name.Format("Sname%d",i+1);
		CString s=pApp->GetProfileString("CHAT97",name,DEFAULT_NAME);
		pList->AddString(s);
	}
	pList->SetCurSel(0);
}

