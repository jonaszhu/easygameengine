// MolServerSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MolServer.h"
#include "MolServerSetDlg.h"
#include ".\molserversetdlg.h"


// CServerSetDlg �Ի���

IMPLEMENT_DYNAMIC(CServerSetDlg, CDialog)
CServerSetDlg::CServerSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SERVER_SET_DLG, pParent),m_ServerSet(NULL)
{
}

CServerSetDlg::~CServerSetDlg()
{

}

void CServerSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CServerSetDlg, CDialog)
	ON_WM_CREATE()
	ON_MESSAGE(WM_PG_ITEMCHANGED,&CServerSetDlg::OnProcessPropertyGridChanged)
END_MESSAGE_MAP()

/**
 * ��ʾ����������
 *
 * @param pServerSet Ҫ��ʾ�ķ���������
 */
void CServerSetDlg::DisplayServerSet(ServerSet *pServerSet)
{
	if(pServerSet == NULL || m_PropertyGrid.GetSafeHwnd() == NULL) return;

	m_PropertyGrid.ResetContents();

	HSECTION m_secservconfig = m_PropertyGrid.AddSection("��Ϸ����������");
	//hitems[0] = m_PropertyGrid.AddStringItem(m_secservconfig,"����������:",pServerSet->ServerName);
	hitems[1] = m_PropertyGrid.AddStringItem(m_secservconfig,"������IP:",pServerSet->ServerIp);
	hitems[2] = m_PropertyGrid.AddIntegerItem(m_secservconfig,"�������˿�:",pServerSet->ServerPort);

	HSECTION m_secdbconfig = m_PropertyGrid.AddSection("��Ϸ���ݿ�����");
	hitems[20] = m_PropertyGrid.AddStringItem(m_secdbconfig,"����IP��ַ:",pServerSet->DBServerIp);
	hitems[21] = m_PropertyGrid.AddIntegerItem(m_secdbconfig,"���ݿ�˿�:",pServerSet->DBServerPort);
	hitems[22] = m_PropertyGrid.AddStringItem(m_secdbconfig,"���ݿ�����:",pServerSet->DBName);
	hitems[23] = m_PropertyGrid.AddStringItem(m_secdbconfig,"�û���:",pServerSet->DBUserName);
	hitems[24] = m_PropertyGrid.AddStringItem(m_secdbconfig,"�û�����:",pServerSet->DBUserPassword);

	Invalidate();
}	

LRESULT CServerSetDlg::OnProcessPropertyGridChanged(WPARAM wparam, LPARAM lparam)
{
	if(m_ServerSet == NULL) return 0;

	HITEM pHITEM = (HITEM)wparam;
	
	/*if(pHITEM == hitems[0])                                      // ����������
	{
		std::string servername;
		m_PropertyGrid.GetItemValue(hitems[0],servername);

		strcpy(m_ServerSet->ServerName , servername.c_str());
	}
	else*/ if(pHITEM == hitems[1])                                 // ������IP
	{
		std::string serverip;
		m_PropertyGrid.GetItemValue(hitems[1],serverip);

		strcpy(m_ServerSet->ServerIp , serverip.c_str());
	}
	else if(pHITEM == hitems[2])                                 // �������˿�
	{
		int serverport = 0;
		m_PropertyGrid.GetItemValue(hitems[2],serverport);

		m_ServerSet->ServerPort = serverport;
	}
	else if(pHITEM == hitems[20])                                // ����IP��ַ
	{
		std::string DBServerIp;
		m_PropertyGrid.GetItemValue(hitems[20],DBServerIp);

		strcpy(m_ServerSet->DBServerIp , DBServerIp.c_str());
	}
	else if(pHITEM == hitems[21])                                //���ݿ�˿�
	{
		int DBServerPort = 0;
		m_PropertyGrid.GetItemValue(hitems[21],DBServerPort);

		m_ServerSet->DBServerPort = DBServerPort;
	}
	else if(pHITEM == hitems[22])                                // ���ݿ�����
	{
		std::string DBName;
		m_PropertyGrid.GetItemValue(hitems[22],DBName);

		strcpy(m_ServerSet->DBName , DBName.c_str());
	}
	else if(pHITEM == hitems[23])                                // �û���
	{
		std::string DBUserName;
		m_PropertyGrid.GetItemValue(hitems[23],DBUserName);

		strcpy(m_ServerSet->DBUserName , DBUserName.c_str());
	}
	else if(pHITEM == hitems[24])                               // �û���
	{
		std::string DBUserPassword;
		m_PropertyGrid.GetItemValue(hitems[24],DBUserPassword);

		strcpy(m_ServerSet->DBUserPassword , DBUserPassword.c_str());
	}

	return 0;
}

// CServerSetDlg ��Ϣ�������

int CServerSetDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect pRect;
	GetClientRect(&pRect);

	m_PropertyGrid.Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(5,5,pRect.Width()-5,pRect.Height()-42),this,0);

	if(m_ServerSet)
		DisplayServerSet(m_ServerSet);

	return 0;
}
