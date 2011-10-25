#pragma once

#include "AsyncSocketFile.h"
#include "Mole2dClientCommon.h"
#include "resource.h"

#include <string>

// CDebugServerDlg �Ի���

class CDebugServerDlg : public CDialog
{
	DECLARE_DYNAMIC(CDebugServerDlg)

public:
	CDebugServerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDebugServerDlg();

	/// ��ӡ������������־
	void PrintLog(std::string log);

// �Ի�������
	enum { IDD = IDD_SER_DIALOG };

private:
	CAsyncSocketFile *m_fileClient;
	SerParamStru pSerParam;
	CEdit        m_logEdit;                         /**< ��ӡ��־ */

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSet();
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnUpdate();
	afx_msg void OnBnClickedBtnRestart();
	afx_msg void OnBnClickedBtnClear();
};
