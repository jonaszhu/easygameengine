// RegisterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RegisterDlg.h"


// CRegisterDlg �Ի���

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialog)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterDlg::IDD, pParent)
{

}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CRegisterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRegisterDlg ��Ϣ�������

void CRegisterDlg::OnBnClickedOk()
{
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_password);
	if(m_password.GetLength() <= 0)
	{
		MessageBox("ע���벻��Ϊ�գ����������룡");
		return;
	}

	OnOK();
}
