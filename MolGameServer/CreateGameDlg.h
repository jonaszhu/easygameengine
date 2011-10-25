#pragma once

#include "PropertyGrid/PropertyGrid.h"

// CServerSetDlg �Ի���
#include "MolServerCom.h"

// CCreateGameDlg �Ի���

class CCreateGameDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateGameDlg)

public:
	CCreateGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCreateGameDlg();

// �Ի�������
	enum { IDD = IDD_SERVER_SET_DLG2 };

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
