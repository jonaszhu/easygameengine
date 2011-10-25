#pragma once

#include "Mole2dClientCommon.h"

// CSerParamSetDlg 对话框

class CSerParamSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSerParamSetDlg)

public:
	CSerParamSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSerParamSetDlg();

	/// 设置服务器参数
	inline void SetServParam(SerParamStru *param) { pSerParam = param; }

// 对话框数据
	enum { IDD = IDD_DLG_SER_SET };

private:
	SerParamStru *pSerParam;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
