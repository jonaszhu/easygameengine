// MolServerSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MolServer.h"
#include "MolServerSetDlg.h"
#include ".\molserversetdlg.h"


// CServerSetDlg 对话框

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
 * 显示服务器属性
 *
 * @param pServerSet 要显示的服务器设置
 */
void CServerSetDlg::DisplayServerSet(ServerSet *pServerSet)
{
	if(pServerSet == NULL || m_PropertyGrid.GetSafeHwnd() == NULL) return;

	m_PropertyGrid.ResetContents();

	HSECTION m_secservconfig = m_PropertyGrid.AddSection("游戏服务器设置");
	hitems[0] = m_PropertyGrid.AddStringItem(m_secservconfig,"服务器名称:",pServerSet->ServerName);
	hitems[1] = m_PropertyGrid.AddStringItem(m_secservconfig,"服务器IP:",pServerSet->ServerIp);
	hitems[2] = m_PropertyGrid.AddIntegerItem(m_secservconfig,"服务器端口:",pServerSet->ServerPort);
	hitems[26] = m_PropertyGrid.AddBoolItem(m_secservconfig,"是否排队:",pServerSet->isQueueEnter);

	HSECTION m_seccenterserverconfig = m_PropertyGrid.AddSection("中心服务器设置");
	hitems[3] = m_PropertyGrid.AddStringItem(m_seccenterserverconfig,"服务器IP:",pServerSet->CenterServerIp);
	hitems[4] = m_PropertyGrid.AddIntegerItem(m_seccenterserverconfig,"服务器端口:",pServerSet->CenterServerPort);

	HSECTION m_secdebugserverconfig = m_PropertyGrid.AddSection("调试服务器设置");
	hitems[5] = m_PropertyGrid.AddBoolItem(m_secdebugserverconfig,"是否开启调试服务器:",pServerSet->isStartDebug);
	hitems[6] = m_PropertyGrid.AddStringItem(m_secdebugserverconfig,"服务器IP:",pServerSet->DebugServerIP);
	hitems[7] = m_PropertyGrid.AddIntegerItem(m_secdebugserverconfig,"服务器端口:",pServerSet->DebugServerPort);
	hitems[25] = m_PropertyGrid.AddStringItem(m_secdebugserverconfig,"服务器密码:",pServerSet->DebugServerPW);

	HSECTION m_secroomconfig = m_PropertyGrid.AddSection("游戏房间设置");
	hitems[8] = m_PropertyGrid.AddIntegerItem(m_secroomconfig,"游戏ID:",pServerSet->GameId);
	hitems[9] = m_PropertyGrid.AddStringItem(m_secroomconfig,"游戏名称:",pServerSet->GameName);

	std::vector<std::string> comb;
	comb.push_back("金币类型");
	comb.push_back("积分类型");
	comb.push_back("比赛类型");
	comb.push_back("练习类型");
	hitems[10] = m_PropertyGrid.AddComboItem(m_secroomconfig,"游戏类型:",comb,pServerSet->GameType,false);
	hitems[11] = m_PropertyGrid.AddIntegerItem(m_secroomconfig,"桌子数量:",pServerSet->TableCount);
	hitems[12] = m_PropertyGrid.AddIntegerItem(m_secroomconfig,"玩家人数:",pServerSet->PlayerCount);
	hitems[13] = m_PropertyGrid.AddDoubleItem(m_secroomconfig,"税收:",pServerSet->Revenue);
	hitems[14] = m_PropertyGrid.AddIntegerItem(m_secroomconfig,"最少金币:",pServerSet->lastmoney);
	hitems[15] = m_PropertyGrid.AddFolderItem(m_secroomconfig,"脚本路径:",pServerSet->ScriptPath);

	HSECTION m_secrobotconfig = m_PropertyGrid.AddSection("游戏机器人设置");
	hitems[16] = m_PropertyGrid.AddBoolItem(m_secrobotconfig,"是否开启机器人:",pServerSet->isStartRobot);
	hitems[17] = m_PropertyGrid.AddIntegerItem(m_secrobotconfig,"机器人数量:",pServerSet->robotCount);
	hitems[18] = m_PropertyGrid.AddIntegerItem(m_secrobotconfig,"机器人开始ID:",pServerSet->robotStartID);
	hitems[19] = m_PropertyGrid.AddFileItem(m_secrobotconfig,"机器人配置路径:",pServerSet->RobotConfigPath,"机器人配置文件 (*.rob)|*.rob");

	HSECTION m_secdbconfig = m_PropertyGrid.AddSection("游戏数据库设置");
	hitems[20] = m_PropertyGrid.AddStringItem(m_secdbconfig,"数据IP地址:",pServerSet->DBServerIp);
	hitems[21] = m_PropertyGrid.AddIntegerItem(m_secdbconfig,"数据库端口:",pServerSet->DBServerPort);
	hitems[22] = m_PropertyGrid.AddStringItem(m_secdbconfig,"数据库名称:",pServerSet->DBName);
	hitems[23] = m_PropertyGrid.AddStringItem(m_secdbconfig,"用户名:",pServerSet->DBUserName);
	hitems[24] = m_PropertyGrid.AddStringItem(m_secdbconfig,"用户密码:",pServerSet->DBUserPassword);

	Invalidate();
}	

LRESULT CServerSetDlg::OnProcessPropertyGridChanged(WPARAM wparam, LPARAM lparam)
{
	if(m_ServerSet == NULL) return 0;

	HITEM pHITEM = (HITEM)wparam;
	
	if(pHITEM == hitems[0])                                      // 服务器名称
	{
		std::string servername;
		m_PropertyGrid.GetItemValue(hitems[0],servername);

		strcpy(m_ServerSet->ServerName , servername.c_str());
	}
	else if(pHITEM == hitems[1])                                 // 服务器IP
	{
		std::string serverip;
		m_PropertyGrid.GetItemValue(hitems[1],serverip);

		strcpy(m_ServerSet->ServerIp , serverip.c_str());
	}
	else if(pHITEM == hitems[2])                                 // 服务器端口
	{
		int serverport = 0;
		m_PropertyGrid.GetItemValue(hitems[2],serverport);

		m_ServerSet->ServerPort = serverport;
	}
	else if(pHITEM == hitems[3])                                 // 中心服务器IP
	{
		std::string serverip;
		m_PropertyGrid.GetItemValue(hitems[3],serverip);

		strcpy(m_ServerSet->CenterServerIp , serverip.c_str());
	}
	else if(pHITEM == hitems[4])                                //  中心服务器端口  
	{
		int serverport = 0;
		m_PropertyGrid.GetItemValue(hitems[4],serverport);

		m_ServerSet->CenterServerPort = serverport;
	}
	else if(pHITEM == hitems[5])                                 // 是否使用调试服务器
	{
		bool isStartDebug = false;
		m_PropertyGrid.GetItemValue(hitems[5],isStartDebug);

		m_ServerSet->isStartDebug = isStartDebug;
	}
	else if(pHITEM == hitems[6])                                //  调试服务器IP
	{
		std::string serverip;
		m_PropertyGrid.GetItemValue(hitems[6],serverip);

		strcpy(m_ServerSet->DebugServerIP , serverip.c_str());
	}
	else if(pHITEM == hitems[7])                                //  调试服务器端口  
	{
		int serverport = 0;
		m_PropertyGrid.GetItemValue(hitems[7],serverport);

		m_ServerSet->DebugServerPort = serverport;
	}
	else if(pHITEM == hitems[8])                                // 游戏ID 
	{
		int gameId = 0;
		m_PropertyGrid.GetItemValue(hitems[8],gameId);

		m_ServerSet->GameId = gameId;
	}
	else if(pHITEM == hitems[9])                                // 游戏名称
	{
		std::string gameName;
		m_PropertyGrid.GetItemValue(hitems[9],gameName);

		strcpy(m_ServerSet->GameName,gameName.c_str());
	}
	else if(pHITEM == hitems[10])                                // 游戏类型
	{
		int gameType = 0;
		m_PropertyGrid.GetItemValue(hitems[10],gameType);

		m_ServerSet->GameType = gameType;
	}
	else if(pHITEM == hitems[11])                                // 桌子数量
	{
		int tableCount = 0;
		m_PropertyGrid.GetItemValue(hitems[11],tableCount);

		m_ServerSet->TableCount = tableCount;
	}
	else if(pHITEM == hitems[12])                                // 玩家人数
	{
		int playerCount = 0;
		m_PropertyGrid.GetItemValue(hitems[12],playerCount);

		m_ServerSet->PlayerCount = playerCount;
	}
	else if(pHITEM == hitems[13])                                // 税收
	{
		double shuishou = 0.0f;
		m_PropertyGrid.GetItemValue(hitems[13],shuishou);

		m_ServerSet->Revenue = (float)shuishou;
	}
	else if(pHITEM == hitems[14])                                // 最小金币
	{
		int lastmoney = 0;
		m_PropertyGrid.GetItemValue(hitems[14],lastmoney);

		m_ServerSet->lastmoney = lastmoney;
	}
	else if(pHITEM == hitems[15])                                // 脚本路径
	{
		std::string scriptpath;
		m_PropertyGrid.GetItemValue(hitems[15],scriptpath);

		strcpy(m_ServerSet->ScriptPath , scriptpath.c_str());
	}
	else if(pHITEM == hitems[16])                                 // 是否使用机器人
	{
		bool isStartRobot = false;
		m_PropertyGrid.GetItemValue(hitems[16],isStartRobot);

		m_ServerSet->isStartRobot = isStartRobot;
	}
	else if(pHITEM == hitems[17])                                // 机器人数量
	{
		int robotcount = 0;
		m_PropertyGrid.GetItemValue(hitems[17],robotcount);

		m_ServerSet->robotCount = robotcount;
	}
	else if(pHITEM == hitems[18])                                // 机器人开始ID
	{
		int robotstartid = 0;
		m_PropertyGrid.GetItemValue(hitems[18],robotstartid);

		m_ServerSet->robotStartID = robotstartid;
	}
	else if(pHITEM == hitems[19])                                // 机器人配置文件
	{
		std::string RobotConfigPath;
		m_PropertyGrid.GetItemValue(hitems[19],RobotConfigPath);

		strcpy(m_ServerSet->RobotConfigPath , RobotConfigPath.c_str());
	}
	else if(pHITEM == hitems[20])                                // 数据IP地址
	{
		std::string DBServerIp;
		m_PropertyGrid.GetItemValue(hitems[20],DBServerIp);

		strcpy(m_ServerSet->DBServerIp , DBServerIp.c_str());
	}
	else if(pHITEM == hitems[21])                                //数据库端口
	{
		int DBServerPort = 0;
		m_PropertyGrid.GetItemValue(hitems[21],DBServerPort);

		m_ServerSet->DBServerPort = DBServerPort;
	}
	else if(pHITEM == hitems[22])                                // 数据库名称
	{
		std::string DBName;
		m_PropertyGrid.GetItemValue(hitems[22],DBName);

		strcpy(m_ServerSet->DBName , DBName.c_str());
	}
	else if(pHITEM == hitems[23])                                // 用户名
	{
		std::string DBUserName;
		m_PropertyGrid.GetItemValue(hitems[23],DBUserName);

		strcpy(m_ServerSet->DBUserName , DBUserName.c_str());
	}
	else if(pHITEM == hitems[24])                               // 用户名
	{
		std::string DBUserPassword;
		m_PropertyGrid.GetItemValue(hitems[24],DBUserPassword);

		strcpy(m_ServerSet->DBUserPassword , DBUserPassword.c_str());
	}
	else if(pHITEM == hitems[25])                                // 服务器密码
	{
		std::string password;
		m_PropertyGrid.GetItemValue(hitems[25],password);

		strcpy(m_ServerSet->DebugServerPW , password.c_str());
	}
	else if(pHITEM == hitems[26])                                 // 是否排队进入
	{
		bool isQueueEnter = false;
		m_PropertyGrid.GetItemValue(hitems[26],isQueueEnter);

		m_ServerSet->isQueueEnter = isQueueEnter;
	}

	return 0;
}

// CServerSetDlg 消息处理程序

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
