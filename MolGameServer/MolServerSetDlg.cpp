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
	hitems[0] = m_PropertyGrid.AddStringItem(m_secservconfig,"����������:",pServerSet->ServerName);
	hitems[1] = m_PropertyGrid.AddStringItem(m_secservconfig,"������IP:",pServerSet->ServerIp);
	hitems[2] = m_PropertyGrid.AddIntegerItem(m_secservconfig,"�������˿�:",pServerSet->ServerPort);
	hitems[26] = m_PropertyGrid.AddBoolItem(m_secservconfig,"�Ƿ��Ŷ�:",pServerSet->isQueueEnter);

	HSECTION m_seccenterserverconfig = m_PropertyGrid.AddSection("���ķ���������");
	hitems[3] = m_PropertyGrid.AddStringItem(m_seccenterserverconfig,"������IP:",pServerSet->CenterServerIp);
	hitems[4] = m_PropertyGrid.AddIntegerItem(m_seccenterserverconfig,"�������˿�:",pServerSet->CenterServerPort);

	HSECTION m_secdebugserverconfig = m_PropertyGrid.AddSection("���Է���������");
	hitems[5] = m_PropertyGrid.AddBoolItem(m_secdebugserverconfig,"�Ƿ������Է�����:",pServerSet->isStartDebug);
	hitems[6] = m_PropertyGrid.AddStringItem(m_secdebugserverconfig,"������IP:",pServerSet->DebugServerIP);
	hitems[7] = m_PropertyGrid.AddIntegerItem(m_secdebugserverconfig,"�������˿�:",pServerSet->DebugServerPort);
	hitems[25] = m_PropertyGrid.AddStringItem(m_secdebugserverconfig,"����������:",pServerSet->DebugServerPW);

	HSECTION m_secroomconfig = m_PropertyGrid.AddSection("��Ϸ��������");
	hitems[8] = m_PropertyGrid.AddIntegerItem(m_secroomconfig,"��ϷID:",pServerSet->GameId);
	hitems[9] = m_PropertyGrid.AddStringItem(m_secroomconfig,"��Ϸ����:",pServerSet->GameName);

	std::vector<std::string> comb;
	comb.push_back("�������");
	comb.push_back("��������");
	comb.push_back("��������");
	comb.push_back("��ϰ����");
	hitems[10] = m_PropertyGrid.AddComboItem(m_secroomconfig,"��Ϸ����:",comb,pServerSet->GameType,false);
	hitems[11] = m_PropertyGrid.AddIntegerItem(m_secroomconfig,"��������:",pServerSet->TableCount);
	hitems[12] = m_PropertyGrid.AddIntegerItem(m_secroomconfig,"�������:",pServerSet->PlayerCount);
	hitems[13] = m_PropertyGrid.AddDoubleItem(m_secroomconfig,"˰��:",pServerSet->Revenue);
	hitems[14] = m_PropertyGrid.AddIntegerItem(m_secroomconfig,"���ٽ��:",pServerSet->lastmoney);
	hitems[15] = m_PropertyGrid.AddFolderItem(m_secroomconfig,"�ű�·��:",pServerSet->ScriptPath);

	HSECTION m_secrobotconfig = m_PropertyGrid.AddSection("��Ϸ����������");
	hitems[16] = m_PropertyGrid.AddBoolItem(m_secrobotconfig,"�Ƿ���������:",pServerSet->isStartRobot);
	hitems[17] = m_PropertyGrid.AddIntegerItem(m_secrobotconfig,"����������:",pServerSet->robotCount);
	hitems[18] = m_PropertyGrid.AddIntegerItem(m_secrobotconfig,"�����˿�ʼID:",pServerSet->robotStartID);
	hitems[19] = m_PropertyGrid.AddFileItem(m_secrobotconfig,"����������·��:",pServerSet->RobotConfigPath,"�����������ļ� (*.rob)|*.rob");

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
	
	if(pHITEM == hitems[0])                                      // ����������
	{
		std::string servername;
		m_PropertyGrid.GetItemValue(hitems[0],servername);

		strcpy(m_ServerSet->ServerName , servername.c_str());
	}
	else if(pHITEM == hitems[1])                                 // ������IP
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
	else if(pHITEM == hitems[3])                                 // ���ķ�����IP
	{
		std::string serverip;
		m_PropertyGrid.GetItemValue(hitems[3],serverip);

		strcpy(m_ServerSet->CenterServerIp , serverip.c_str());
	}
	else if(pHITEM == hitems[4])                                //  ���ķ������˿�  
	{
		int serverport = 0;
		m_PropertyGrid.GetItemValue(hitems[4],serverport);

		m_ServerSet->CenterServerPort = serverport;
	}
	else if(pHITEM == hitems[5])                                 // �Ƿ�ʹ�õ��Է�����
	{
		bool isStartDebug = false;
		m_PropertyGrid.GetItemValue(hitems[5],isStartDebug);

		m_ServerSet->isStartDebug = isStartDebug;
	}
	else if(pHITEM == hitems[6])                                //  ���Է�����IP
	{
		std::string serverip;
		m_PropertyGrid.GetItemValue(hitems[6],serverip);

		strcpy(m_ServerSet->DebugServerIP , serverip.c_str());
	}
	else if(pHITEM == hitems[7])                                //  ���Է������˿�  
	{
		int serverport = 0;
		m_PropertyGrid.GetItemValue(hitems[7],serverport);

		m_ServerSet->DebugServerPort = serverport;
	}
	else if(pHITEM == hitems[8])                                // ��ϷID 
	{
		int gameId = 0;
		m_PropertyGrid.GetItemValue(hitems[8],gameId);

		m_ServerSet->GameId = gameId;
	}
	else if(pHITEM == hitems[9])                                // ��Ϸ����
	{
		std::string gameName;
		m_PropertyGrid.GetItemValue(hitems[9],gameName);

		strcpy(m_ServerSet->GameName,gameName.c_str());
	}
	else if(pHITEM == hitems[10])                                // ��Ϸ����
	{
		int gameType = 0;
		m_PropertyGrid.GetItemValue(hitems[10],gameType);

		m_ServerSet->GameType = gameType;
	}
	else if(pHITEM == hitems[11])                                // ��������
	{
		int tableCount = 0;
		m_PropertyGrid.GetItemValue(hitems[11],tableCount);

		m_ServerSet->TableCount = tableCount;
	}
	else if(pHITEM == hitems[12])                                // �������
	{
		int playerCount = 0;
		m_PropertyGrid.GetItemValue(hitems[12],playerCount);

		m_ServerSet->PlayerCount = playerCount;
	}
	else if(pHITEM == hitems[13])                                // ˰��
	{
		double shuishou = 0.0f;
		m_PropertyGrid.GetItemValue(hitems[13],shuishou);

		m_ServerSet->Revenue = (float)shuishou;
	}
	else if(pHITEM == hitems[14])                                // ��С���
	{
		int lastmoney = 0;
		m_PropertyGrid.GetItemValue(hitems[14],lastmoney);

		m_ServerSet->lastmoney = lastmoney;
	}
	else if(pHITEM == hitems[15])                                // �ű�·��
	{
		std::string scriptpath;
		m_PropertyGrid.GetItemValue(hitems[15],scriptpath);

		strcpy(m_ServerSet->ScriptPath , scriptpath.c_str());
	}
	else if(pHITEM == hitems[16])                                 // �Ƿ�ʹ�û�����
	{
		bool isStartRobot = false;
		m_PropertyGrid.GetItemValue(hitems[16],isStartRobot);

		m_ServerSet->isStartRobot = isStartRobot;
	}
	else if(pHITEM == hitems[17])                                // ����������
	{
		int robotcount = 0;
		m_PropertyGrid.GetItemValue(hitems[17],robotcount);

		m_ServerSet->robotCount = robotcount;
	}
	else if(pHITEM == hitems[18])                                // �����˿�ʼID
	{
		int robotstartid = 0;
		m_PropertyGrid.GetItemValue(hitems[18],robotstartid);

		m_ServerSet->robotStartID = robotstartid;
	}
	else if(pHITEM == hitems[19])                                // �����������ļ�
	{
		std::string RobotConfigPath;
		m_PropertyGrid.GetItemValue(hitems[19],RobotConfigPath);

		strcpy(m_ServerSet->RobotConfigPath , RobotConfigPath.c_str());
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
	else if(pHITEM == hitems[25])                                // ����������
	{
		std::string password;
		m_PropertyGrid.GetItemValue(hitems[25],password);

		strcpy(m_ServerSet->DebugServerPW , password.c_str());
	}
	else if(pHITEM == hitems[26])                                 // �Ƿ��Ŷӽ���
	{
		bool isQueueEnter = false;
		m_PropertyGrid.GetItemValue(hitems[26],isQueueEnter);

		m_ServerSet->isQueueEnter = isQueueEnter;
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
