#pragma once

#include "PropertyGrid/PropertyGrid.h"

// CServerSetDlg �Ի���
#include "MolServerCom.h"

class CServerSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CServerSetDlg)

public:
	CServerSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CServerSetDlg();

	/// ���÷���������
	inline void SetServerParam(ServerSet *set) { m_ServerSet = set; } 
	/// ��ʾ����������
	void DisplayServerSet(ServerSet *pServerSet);

private:
	CPropertyGrid m_PropertyGrid;               /**< �������÷����� */
	ServerSet *m_ServerSet;
	HITEM hitems[27];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnProcessPropertyGridChanged(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
