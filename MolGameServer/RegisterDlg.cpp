// RegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RegisterDlg.h"


// CRegisterDlg 对话框

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


// CRegisterDlg 消息处理程序

void CRegisterDlg::OnBnClickedOk()
{
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_password);
	if(m_password.GetLength() <= 0)
	{
		MessageBox("注册码不能为空，请重新输入！");
		return;
	}

	OnOK();
}
