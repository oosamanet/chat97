// SendMes.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "Chat97Server.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendMes �_�C�A���O


CSendMes::CSendMes(CString&handle,int clientno,int room)
	: CDialog(CSendMes::IDD, NULL)
{
	m_handle=handle;
	m_clientno=clientno;
	m_room=room;
	//{{AFX_DATA_INIT(CSendMes)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CSendMes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendMes)
                // ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendMes, CDialog)
	//{{AFX_MSG_MAP(CSendMes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendMes ���b�Z�[�W �n���h��

BOOL CSendMes::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString s="�P�Q�R�S�T�U�V�W�X10";
	s=s.Mid(m_room*2,2);
	s+="������";
	s+=m_handle;
	s+="����ɓd��𑗂�܂�";
	GetDlgItem(IDC_SENDTITLE)->SetWindowText(s);
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CSendMes::OnOK() 
{
	GetDlgItem(IDC_SENDMESSAGE)->GetWindowText(mes);
	CDialog::OnOK();
}