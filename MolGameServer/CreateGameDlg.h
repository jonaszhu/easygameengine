#pragma once

#include "PropertyGrid/PropertyGrid.h"

// CServerSetDlg 对话框
#include "MolServerCom.h"

// CCreateGameDlg 对话框

class CCreateGameDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateGameDlg)

public:
	CCreateGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCreateGameDlg();

// 对话框数据
	enum { IDD = IDD_SERVER_SET_DLG2 };

	/// 设置服务器参数
	inline void SetServerParam(ServerSet *set) { m_ServerSet = set; } 
	/// 显示服务器属性
	void DisplayServerSet(ServerSet *pServerSet);

private:
	CPropertyGrid m_PropertyGrid;               /**< 用于配置服务器 */
	ServerSet *m_ServerSet;
	HITEM hitems[27];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnProcessPropertyGridChanged(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
