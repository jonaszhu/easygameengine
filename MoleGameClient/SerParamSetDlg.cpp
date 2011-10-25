// SerParamSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Mole2dGameClient.h"
#include "SerParamSetDlg.h"

#include "resource.h"

// CSerParamSetDlg �Ի���

IMPLEMENT_DYNAMIC(CSerParamSetDlg, CDialog)

CSerParamSetDlg::CSerParamSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerParamSetDlg::IDD, pParent),pSerParam(NULL)
{

}

CSerParamSetDlg::~CSerParamSetDlg()
{
}

void CSerParamSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSerParamSetDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSerParamSetDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CSerParamSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(pSerParam)
	{
		GetDlgItem(IDC_EDIT1)->SetWindowText(pSerParam->IPAddress);
		CString tempStr;
		tempStr.Format("%d",pSerParam->Port);
		GetDlgItem(IDC_EDIT2)->SetWindowText(tempStr);
		GetDlgItem(IDC_EDIT3)->SetWindowText(pSerParam->Password);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSerParamSetDlg::OnBnClickedOk()
{
	if(pSerParam == NULL) 
		return;

	CString tempStr;
	GetDlgItem(IDC_EDIT1)->GetWindowText(tempStr);
	if(tempStr.IsEmpty())
	{
		MMessageBox("������IP��ַ����Ϊ�գ���������д��","��¼ʧ��",MB_OK);
		GetDlgItem(IDC_EDIT1)->SetFocus();	
		return;
	}

	strcpy(pSerParam->IPAddress,tempStr.GetBuffer());

	GetDlgItem(IDC_EDIT2)->GetWindowText(tempStr);
	if(tempStr.IsEmpty())
	{
		MMessageBox("�������˿ڲ���Ϊ�գ���������д��","��¼ʧ��",MB_OK);
		GetDlgItem(IDC_EDIT2)->SetFocus();	
		return;
	}

	pSerParam->Port = atoi(tempStr.GetBuffer());

	GetDlgItem(IDC_EDIT3)->GetWindowText(tempStr);
	if(tempStr.IsEmpty())
	{
		MMessageBox("�������������벻��Ϊ�գ���������д��","��¼ʧ��",MB_OK);
		GetDlgItem(IDC_EDIT3)->SetFocus();	
		return;
	}

	strcpy(pSerParam->Password,tempStr.GetBuffer());

	OnOK();
}
