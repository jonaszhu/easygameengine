#pragma once

#include "Mole2dClientCommon.h"

// CSerParamSetDlg �Ի���

class CSerParamSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSerParamSetDlg)

public:
	CSerParamSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSerParamSetDlg();

	/// ���÷���������
	inline void SetServParam(SerParamStru *param) { pSerParam = param; }

// �Ի�������
	enum { IDD = IDD_DLG_SER_SET };

private:
	SerParamStru *pSerParam;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
