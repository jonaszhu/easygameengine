#pragma once

#include "AsyncSocketFile.h"
#include "Mole2dClientCommon.h"
#include "resource.h"

#include <string>

// CDebugServerDlg 对话框

class CDebugServerDlg : public CDialog
{
	DECLARE_DYNAMIC(CDebugServerDlg)

public:
	CDebugServerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDebugServerDlg();

	/// 打印服务器工作日志
	void PrintLog(std::string log);

// 对话框数据
	enum { IDD = IDD_SER_DIALOG };

private:
	CAsyncSocketFile *m_fileClient;
	SerParamStru pSerParam;
	CEdit        m_logEdit;                         /**< 打印日志 */

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSet();
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnUpdate();
	afx_msg void OnBnClickedBtnRestart();
	afx_msg void OnBnClickedBtnClear();
};
