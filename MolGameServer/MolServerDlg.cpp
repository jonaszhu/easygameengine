// MolServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MolServer.h"
#include "MolServerDlg.h"
#include ".\molserverdlg.h"
#include "AsyncSocketFile.h"
#include "MolMesDistributer.h"
#include "CreateGameDlg.h"

#include "tinyxml/tinyxml.h"
#include "libcrashrpt/MolCrashRpt.h"

#include "RoomManager.h"
#include "GameFrameManager.h"
#include "PlayerManager.h"

#include "RegisterDlg.h"
#include "SerialManager.h"
#include "DBOperator.h"
#include "defines.h"

extern "C"
{
#include "miracl.h"
#include "mirdef.h"
}

//#pragma comment( lib, "ms32.lib" ) 

#include "HDID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

initialiseSingleton(CMolServerDlg);

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMolServerDlg 对话框



CMolServerDlg::CMolServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MOLSERVER_DIALOG, pParent),m_TrayIcon(10),m_curPlayerCount(0),m_isStartSuc(false),
	m_ServerSocket(NULL),m_isRegistered(false),m_maxPlayerCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	memset(&m_ServerSet,0,sizeof(m_ServerSet));
}

CMolServerDlg::~CMolServerDlg()
{
	if(m_ServerSocket)
		delete m_ServerSocket;
	m_ServerSocket = NULL;

	m_CenterServer.CloseConnect();

	CleanMolNet();

	delete RoomManager::getSingletonPtr();
	delete GameFrameManager::getSingletonPtr();
	delete PlayerManager::getSingletonPtr();
	delete DBOperator::getSingletonPtr();
}

void CMolServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOG,m_logEdit);	
}

BEGIN_MESSAGE_MAP(CMolServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(IDM_TRAY_NOTIFY_MSG,OnTrayIconNotify)
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_BTN_CLOSE, OnBnClickedBtnClose)
	ON_BN_CLICKED(ID_BTN_START_SERVER, OnStartServer)
	ON_COMMAND(ID_START_SERVER, OnStartServer)
	ON_BN_CLICKED(ID_BTN_STOP_SERVER, OnStopServer)
	ON_COMMAND(ID_STOP_SERVER, OnStopServer)
	ON_BN_CLICKED(ID_BTN_RELOAD_SCRIPT, OnReloadScript)
	ON_COMMAND(ID_RELOAD_SCRIPT, OnReloadScript)
	ON_BN_CLICKED(ID_BTN_SERVER_SET, OnServerSet)
	ON_COMMAND(ID_SERVER_SET, OnServerSet)
	ON_BN_CLICKED(ID_BTN_CLEAR_LOG, OnClearLog)
	ON_COMMAND(ID_CLEAR_LOG, OnClearLog)
	ON_COMMAND(ID_CLOSE_SERVER, OnCloseServer)
	ON_BN_CLICKED(ID_BTN_START_SERVER2, OnBnClickedBtnStartServer2)
	ON_COMMAND(ID_MOLSERVER_32784, OnMolserver32784)
	ON_BN_CLICKED(ID_BTN_GET_ROBOTID, OnBnClickedBtnGetRobotID)
	ON_BN_CLICKED(ID_BTN_REGISTER, OnBnClickedBtnRegister)
	ON_BN_CLICKED(ID_BTN_CREATE_ROOM, OnBnClickedBtnCreateRoom)
END_MESSAGE_MAP()

/**
 * 保存服务器配置文件
 */
void CMolServerDlg::SaveServerConfig(std::string filepath)
{
	//if(m_curGameConfigFile.empty()) return;

	// 输出XML文件
	TiXmlDocument doc(filepath.empty() ? m_curGameConfigFile.c_str() : filepath.c_str());
	TiXmlDeclaration Declaration( "1.0","UTF-8", "" );
	doc.InsertEndChild( Declaration ); // 写入基本的XML头结构

	TiXmlElement ServerConfig("ServerConfig");

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TiXmlElement GameServerConfig("GameServerConfig");

	TiXmlElement Configure("Configure");
	Configure.SetAttribute("Name","ServerName");
	std::string pServerName = std::string(m_ServerSet.ServerName) + "END";
	Configure.SetAttribute("Value",pServerName.c_str());
	GameServerConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","ServerIp");
	Configure.SetAttribute("Value",m_ServerSet.ServerIp);
	GameServerConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","ServerPort");
	Configure.SetAttribute("Value",m_ServerSet.ServerPort);
	GameServerConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","isQueueEnter");
	Configure.SetAttribute("Value",m_ServerSet.isQueueEnter);
	GameServerConfig.InsertEndChild(Configure);

	ServerConfig.InsertEndChild(GameServerConfig);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TiXmlElement CenterServerConfig("CenterServerConfig");

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","ServerIp");
	Configure.SetAttribute("Value",m_ServerSet.CenterServerIp);
	CenterServerConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","Port");
	Configure.SetAttribute("Value",m_ServerSet.CenterServerPort);
	CenterServerConfig.InsertEndChild(Configure);

	ServerConfig.InsertEndChild(CenterServerConfig);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TiXmlElement DebugServerConfig("DebugServerConfig");

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","IsStart");
	Configure.SetAttribute("Value",m_ServerSet.isStartDebug);
	DebugServerConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","ServerIp");
	Configure.SetAttribute("Value",m_ServerSet.DebugServerIP);
	DebugServerConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","Port");
	Configure.SetAttribute("Value",m_ServerSet.DebugServerPort);
	DebugServerConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","Password");
	Configure.SetAttribute("Value",m_ServerSet.DebugServerPW);
	DebugServerConfig.InsertEndChild(Configure);

	ServerConfig.InsertEndChild(DebugServerConfig);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TiXmlElement GameRoomConfig("GameRoomConfig");

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","GameId");
	Configure.SetAttribute("Value",m_ServerSet.GameId);
	GameRoomConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","GameName");
	std::string pGameName = std::string(m_ServerSet.GameName) + "END";
	Configure.SetAttribute("Value",pGameName.c_str());
	GameRoomConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","GameType");
	Configure.SetAttribute("Value",m_ServerSet.GameType);
	GameRoomConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","PlayerCount");
	Configure.SetAttribute("Value",m_ServerSet.PlayerCount);
	GameRoomConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","TableCount");
	Configure.SetAttribute("Value",m_ServerSet.TableCount);
	GameRoomConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","Revenue");
	Configure.SetAttribute("Value",m_ServerSet.Revenue);
	GameRoomConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","LastMoney");
	Configure.SetAttribute("Value",m_ServerSet.lastmoney);
	GameRoomConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","RobotCount");
	Configure.SetAttribute("Value",m_ServerSet.robotCount);
	GameRoomConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","ScriptPath");
	Configure.SetAttribute("Value",m_ServerSet.ScriptPath);
	GameRoomConfig.InsertEndChild(Configure);

	ServerConfig.InsertEndChild(GameRoomConfig);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TiXmlElement RobotConfig("RobotConfig");

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","isStartRobot");
	Configure.SetAttribute("Value",m_ServerSet.isStartRobot);
	RobotConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","RobotCount");
	Configure.SetAttribute("Value",m_ServerSet.robotCount);
	RobotConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","robotStartID");
	Configure.SetAttribute("Value",m_ServerSet.robotStartID);
	RobotConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","RobotConfigPath");
	Configure.SetAttribute("Value",m_ServerSet.RobotConfigPath);
	RobotConfig.InsertEndChild(Configure);

	ServerConfig.InsertEndChild(RobotConfig);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TiXmlElement GameDataBaseConfig("GameDataBaseConfig");

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","ServerIp");
	Configure.SetAttribute("Value",m_ServerSet.DBServerIp);
	GameDataBaseConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","ServerPort");
	Configure.SetAttribute("Value",m_ServerSet.DBServerPort);
	GameDataBaseConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","DataBaseName");
	Configure.SetAttribute("Value",m_ServerSet.DBName);
	GameDataBaseConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","UserName");
	Configure.SetAttribute("Value",m_ServerSet.DBUserName);
	GameDataBaseConfig.InsertEndChild(Configure);

	Configure = TiXmlElement("Configure");
	Configure.SetAttribute("Name","UserPassword");
	Configure.SetAttribute("Value",m_ServerSet.DBUserPassword);
	GameDataBaseConfig.InsertEndChild(Configure);

	ServerConfig.InsertEndChild(GameDataBaseConfig);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	doc.InsertEndChild(ServerConfig);
	doc.SaveFile();
}

/** 
 * 开启游戏机器人
 */
void CMolServerDlg::StartGameRobots(void)
{
	if(m_ServerSet.isStartRobot == false || m_ServerSet.robotCount <= 0)
		return;

	// 导入所有的机器人
	LoadRobotConfig();

	// 如果机器人导入成功，开始定时器
	if(ServerPlayerManager.GetRobotCount() > 0)
		SetTimer(IDD_START_ROBOT_TIMER,5000,NULL);
}

/// 开启调试服务器
void CMolServerDlg::StartDebugServer(void)
{
	if(m_ServerSet.isStartDebug == false ||
		m_ServerSet.ServerPort == m_ServerSet.DebugServerPort) return;

	if(m_ServerSocket == NULL)
	{
		m_ServerSocket = new CAsyncSocketFile();
		m_ServerSocket->SetMainDlg(this);
	}

	long lEvent = FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE;
	if(m_ServerSocket->Create(m_ServerSet.DebugServerPort,SOCK_STREAM,lEvent,m_ServerSet.DebugServerIP))
	{
		if(m_ServerSocket->Listen())
		{
			m_ServerSocket->SetPassword(m_ServerSet.DebugServerPW);
			m_ServerSocket->OpenFile(m_ServerSet.ScriptPath);
			m_ServerSocket->SendDirection(m_ServerSet.ScriptPath);
			m_ServerSocket->GetWorkFileCount();

			CString tempStr;
			tempStr.Format("【系统】 调试服务器启动成功,IP地址:%s 端口:%d 密码:%s 脚本目录:%s\n",
				m_ServerSet.DebugServerIP,
				m_ServerSet.DebugServerPort,
				m_ServerSet.DebugServerPW,
				m_ServerSet.ScriptPath);
			PrintLog(tempStr.GetBuffer());
			return;
		}
	}

	PrintLog("【系统】 调试服务器启动失败,请认真检查！\n");
}

/** 
 * 导入机器人配置文件
 */
void CMolServerDlg::LoadRobotConfig(void)
{
	TiXmlDocument doc;

	if(!doc.LoadFile(m_ServerSet.RobotConfigPath))
	{
		PrintLog("【系统】 机器人配置文件导入失败!\n");
		return;
	}

	TiXmlElement *RobotConfig = doc.FirstChildElement("RobotConfig");
	if(RobotConfig == NULL) return;

	int count = 0;
	TiXmlElement *Robot = RobotConfig->FirstChildElement();
	while(Robot)
	{
		Player *pPlayer = new Player(m_ServerSet.robotStartID+count,-1);
		pPlayer->SetType(PLAYERTYPE_ROBOT);
		pPlayer->SetName(Robot->Attribute("Name"));
		pPlayer->SetMoney(_atoi64(Robot->Attribute("Money")));
		pPlayer->SetLevel(atoi(Robot->Attribute("Level")));
		pPlayer->SetExperience(atol(Robot->Attribute("Experience")));
		pPlayer->SetUserAvatar(Robot->Attribute("UserAvatar"));
		pPlayer->SetTotalBureau(atoi(Robot->Attribute("TotalBureau")));
		pPlayer->SetSuccessBureau(atoi(Robot->Attribute("SBureau")));
		pPlayer->SetFailBureau(atoi(Robot->Attribute("FailBureau")));
		pPlayer->SetSuccessRate(atof(Robot->Attribute("SuccessRate")));
		pPlayer->SetRunawayrate(atof(Robot->Attribute("RunawayRate")));

		ServerPlayerManager.AddRobot(pPlayer);

		if(count++ > m_ServerSet.robotCount)
			break;

		Robot = Robot->NextSiblingElement();
	}

	CString tempStr;
	tempStr.Format("【系统】 机器人启动成功,机器人数量:%d,开始ID:%d\n",count,m_ServerSet.robotStartID);
	PrintLog(tempStr.GetBuffer());
}

/**
 * 导入服务器配置文件
 *
 * @param filepath 要导入的配置文件路径
 */
bool CMolServerDlg::LoadServerConfig(std::string filepath)
{
	if(filepath.empty())
		filepath = IDD_SERVER_CONFIG_FILE;

	m_curGameConfigFile = filepath;

	TiXmlDocument doc;

	if(!doc.LoadFile(filepath.c_str()))
	{
		PrintLog("【系统】 服务器配置文件导入失败!\n");
		return false;
	}

	TiXmlElement *ServerConfig = doc.FirstChildElement("ServerConfig");
	if(ServerConfig == NULL) return false;

	TiXmlElement *configs = ServerConfig->FirstChildElement();
	while(configs)
	{
		std::string configtype = configs->Value();
		if(configtype == "GameServerConfig")
		{
			TiXmlElement *configure = configs->FirstChildElement("Configure");

			while(configure)
			{
				std::string name = configure->Attribute("Name");
				std::string value = configure->Attribute("Value");

				if(name == "ServerName")
				{
					std::string temp = value.substr(0,value.length()-3);
					strcpy(m_ServerSet.ServerName , temp.c_str());
					
					CString realCaption;
					if(m_isRegistered)
						realCaption.Format("%s - 已注册",m_ServerSet.ServerName);
					else
						realCaption.Format("%s %s",m_ServerSet.ServerName,IDD_REGISTER_TIP);

					SetWindowText(realCaption);
				}
				else if(name == "ServerIp")
				{
					strcpy(m_ServerSet.ServerIp , value.c_str());
				}
				else if(name == "ServerPort")
				{
					m_ServerSet.ServerPort = atoi(value.c_str());
				}
				else if(name == "isQueueEnter")
				{
					m_ServerSet.isQueueEnter = atoi(value.c_str()) > 0 ? true : false;
				}

				configure = configure->NextSiblingElement();
			}
		}
		else if(configtype == "CenterServerConfig")
		{
			TiXmlElement *configure = configs->FirstChildElement("Configure");

			while(configure)
			{
				std::string name = configure->Attribute("Name");
				std::string value = configure->Attribute("Value");

				if(name == "ServerIp")
				{
					strcpy(m_ServerSet.CenterServerIp , value.c_str());
				}
				else if(name == "Port")
				{
					m_ServerSet.CenterServerPort = atoi(value.c_str());
				}

				configure = configure->NextSiblingElement();
			}
		}
		else if(configtype == "DebugServerConfig")
		{
			TiXmlElement *configure = configs->FirstChildElement("Configure");

			while(configure)
			{
				std::string name = configure->Attribute("Name");
				std::string value = configure->Attribute("Value");

				if(name == "IsStart")
				{
					m_ServerSet.isStartDebug = atoi(value.c_str()) > 0 ? true : false;
				}
				else if(name == "ServerIp")
				{
					strcpy(m_ServerSet.DebugServerIP , value.c_str());
				}
				else if(name == "Port")
				{
					m_ServerSet.DebugServerPort = atoi(value.c_str());
				}
				else if(name == "Password")
				{
					strcpy(m_ServerSet.DebugServerPW , value.c_str());
				}

				configure = configure->NextSiblingElement();
			}
		}
		else if(configtype == "GameRoomConfig")
		{
			TiXmlElement *configure = configs->FirstChildElement("Configure");

			while(configure)
			{
				std::string name = configure->Attribute("Name");
				std::string value = configure->Attribute("Value");

				if(name == "GameId")
				{
					m_ServerSet.GameId = atoi(value.c_str());
				}
				else if(name == "GameName")
				{
					std::string temp = value.substr(0,value.length()-3);
					strcpy(m_ServerSet.GameName , temp.c_str());
				}
				else if(name == "GameType")
				{
					m_ServerSet.GameType = atoi(value.c_str());
				}
				else if(name == "PlayerCount")
				{
					m_ServerSet.PlayerCount = atoi(value.c_str());
				}
				else if(name == "TableCount")
				{
					m_ServerSet.TableCount = atoi(value.c_str());
				}
				else if(name == "Revenue")
				{
					m_ServerSet.Revenue = (float)atof(value.c_str());
				}
				else if(name == "LastMoney")
				{
					m_ServerSet.lastmoney = atol(value.c_str());
				}
				else if(name == "ScriptPath")
				{
					strcpy(m_ServerSet.ScriptPath ,value.c_str());
				}

				configure = configure->NextSiblingElement();
			}
		}
		else if(configtype == "RobotConfig")
		{
			TiXmlElement *configure = configs->FirstChildElement("Configure");

			while(configure)
			{
				std::string name = configure->Attribute("Name");
				std::string value = configure->Attribute("Value");

				if(name == "isStartRobot")
				{
					m_ServerSet.isStartRobot = atoi(value.c_str()) > 0 ? true : false;
				}
				else if(name == "RobotCount")
				{
					m_ServerSet.robotCount = atoi(value.c_str());
				}
				else if(name == "robotStartID")
				{
					m_ServerSet.robotStartID = atoi(value.c_str()); 
				}
				else if(name == "RobotConfigPath")
				{
					strcpy(m_ServerSet.RobotConfigPath , value.c_str());
				}

				configure = configure->NextSiblingElement();
			}
		}
		else if(configtype == "GameDataBaseConfig")
		{
			TiXmlElement *configure = configs->FirstChildElement("Configure");

			while(configure)
			{
				std::string name = configure->Attribute("Name");
				std::string value = configure->Attribute("Value");

				if(name == "ServerIp")
				{
					strcpy(m_ServerSet.DBServerIp , value.c_str());
				}
				else if(name == "ServerPort")
				{
					m_ServerSet.DBServerPort = atoi(value.c_str());
				}
				else if(name == "DataBaseName")
				{
					strcpy(m_ServerSet.DBName , value.c_str());
				}
				else if(name == "UserName")
				{
					strcpy(m_ServerSet.DBUserName , value.c_str());
				}
				else if(name == "UserPassword")
				{
					strcpy(m_ServerSet.DBUserPassword , value.c_str());
				}

				configure = configure->NextSiblingElement();
			}
		}

		configs = configs->NextSiblingElement();
	}

	PrintLog("【系统】 游戏配置文件导入成功!\n");

	return true;
}

// CMolServerDlg 消息处理程序

BOOL CMolServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 初始MolCrashRpt
	InitMolCrashRpt();

	if(IsRegistered())
	{
		m_isRegistered = true;

		GetDlgItem(ID_BTN_GET_ROBOTID)->EnableWindow(FALSE);
		GetDlgItem(ID_BTN_REGISTER)->EnableWindow(FALSE);

		CString caption;
		GetWindowText(caption);
		SetWindowText(caption+" - 已注册");

		// 开始启动服务器
		InitMolNet(2001);
		m_maxPlayerCount=2000;
	}
	else
	{
		m_isRegistered = false;

		CString caption,tempStr;
		GetWindowText(caption);
		tempStr.Format("%s %s",caption.GetBuffer(),IDD_REGISTER_TIP);
		SetWindowText(tempStr);

		// 开始启动服务器
		InitMolNet(51);
		m_maxPlayerCount=50;
	}

	//建立任务栏图标
	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_TrayIcon.SetNotifyWnd(this,IDM_TRAY_NOTIFY_MSG);//将主对话框和开始状态栏上的icon联系上
	m_TrayIcon.SetIcon(hIcon,"MolGameServer");
	m_TrayIcon.ShowBalloonTip("正在启动游戏服务器，请稍后...   ","MolGameServer");
	SetIcon(hIcon,FALSE);
	DestroyIcon(hIcon);

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetCurrentDirectory(256,m_ProcessDir);

	m_CenterServer.SetBaseFrame(this);

	// 设置我们游戏使用的日志文件
	CMolLogger::setLogFile("molserver.txt");

	new RoomManager();
	new PlayerManager();
	new GameFrameManager();
	new DBOperator();

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CMolServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		if(nID == SC_MINIMIZE)
		{
			ShowWindow(SW_HIDE);
			return;
		}

		CDialog::OnSysCommand(nID, lParam);
	}
}

/**
 * 打印服务器工作日志
 *
 * @param log 要打印的服务器日志
 */
void CMolServerDlg::PrintLog(std::string log)
{
	if(log.empty() || !m_logEdit.GetSafeHwnd()) return;

	if(m_cAsyncSocketFile) 
		m_cAsyncSocketFile->SendLogInfo(log.c_str());

	LOG_INFO(log);

	log += "\r\n";

	if(m_logEdit.GetLineCount() > 250)
		m_logEdit.SetWindowText("");

	int len = m_logEdit.GetWindowTextLength();
	m_logEdit.SetSel(len,len);
	m_logEdit.ReplaceSel(log.c_str());
	m_logEdit.ScrollWindow(0,0);
}

/** 
 * 初始MolCrashRpt
 */
void CMolServerDlg::InitMolCrashRpt(void)
{
	MolCrash_Initiation();
	MolCrash_SetProjectName("MolGameServer");
	MolCrash_SetEmailSender("akinggw@sina.com");
	MolCrash_SetEmailReceiver("akinggw@126.com");
	MolCrash_DeleteSended(true);
	MolCrash_SetSmtpServer("smtp.sina.com");
	MolCrash_SetSmtpUser("akinggw");
	MolCrash_SetSmtpPassword("akinggw12");
}

//任务栏图标消息
LRESULT CMolServerDlg::OnTrayIconNotify(WPARAM wID, LPARAM lEvent)
{
	switch (lEvent)
	{
	case WM_LBUTTONDOWN:	//双击事件
		{
			ShowWindow(SW_NORMAL);//弹出显示
			SetForegroundWindow();
			return 1;
		}
		break;
	case WM_RBUTTONUP:
		{
			CMenu Menu;
			Menu.LoadMenu(IDR_MENU1);
			CMenu *pSubMenu = Menu.GetSubMenu(0);
			CPoint MousePoint;
			::GetCursorPos(&MousePoint);
			SetForegroundWindow();
			::TrackPopupMenu(pSubMenu->GetSafeHmenu(),0,
				MousePoint.x,MousePoint.y,0,GetSafeHwnd(),NULL);
			return 1;
		}
		break;
	}

	return 0;
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMolServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMolServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMolServerDlg::OnClose()
{
	int state = MessageBox("你确定要退出游戏服务器吗?","退出服务器",MB_ICONWARNING|MB_OKCANCEL);
	if(state != 1)
		return;

	CDialog::OnClose();
}

void CMolServerDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == IDD_SENDMAIL_TIMER)
	{
		KillTimer(IDD_SENDMAIL_TIMER);
		ShowWindow(SW_HIDE);
	}
	else if(nIDEvent == IDD_SENDHEART_TIMER)
	{
		ServerPlayerManager.SendAllPlayersHeartJitter();
	}
	else if(nIDEvent == IDD_HEARTPROCESS_TIMER)
	{
		ServerPlayerManager.OnProcessAllPlayersHeart();		
	}
	else if(nIDEvent == IDD_ROOMTIMER_TIMER)
	{
		DWORD time = GetTickCountEx();

		// 更新房间
		ServerRoomManager.Update(time);
	}
	else if(nIDEvent == IDD_START_ROBOT_TIMER)
	{
		Player *pPlayer = ServerPlayerManager.GetFreeRobot();
		if(pPlayer == NULL)
		{
			CDialog::OnTimer(nIDEvent);
			return;
		}

		//// 如果机器人没钱的话，就自动给它加钱
		//if(pPlayer->GetMoney() < m_ServerSet.lastmoney) 
		//	pPlayer->SetMoney(m_ServerSet.lastmoney);

		ServerGameFrameManager.JoinPlayerToGameRoom(pPlayer);

		// 如果玩家加入房间成功话，马上设置成准备状态
		if(pPlayer->GetRoomId() >= 0 && pPlayer->GetRoomIndex() >= 0)
			ServerGameFrameManager.PlayerReadyStartGame(pPlayer);
	}
	if(nIDEvent == IDD_TIMER_DEBUG_SERVER)
	{
		if(m_cAsyncSocketFile)
		{
			if((DWORD)time(NULL) - m_cAsyncSocketFile->GetCurTime() > 10 && !m_cAsyncSocketFile->IsLoginOk())
			{
				m_cAsyncSocketFile->Close();
				delete m_cAsyncSocketFile;
				m_cAsyncSocketFile = NULL;
			}
		}
	}
	else if(nIDEvent == IDD_CENTER_SERVER_UPDATE)                // 更新中心服务器信息
	{
		int playerCount = ServerPlayerManager.GetTotalCount();

		if(m_curPlayerCount != playerCount)
		{
			CMolMessageOut out(IDD_MESSAGE_UPDATE_GAME_SERVER);
			out.writeLong(m_ServerSet.GameId);
			out.writeLong(playerCount);

			//if(m_CenterServer.IsConnected())
			m_CenterServer.Send(out);

			m_curPlayerCount = playerCount;
		}
	}

	CDialog::OnTimer(nIDEvent);
}

/**
 * 得到系统时间
 */
DWORD CMolServerDlg::GetTickCountEx(void)
{
    SYSTEMTIME st;
    GetSystemTime(&st);

    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);
    // 100-nanoseconds since 1601
    ULONGLONG ull = ((ULONGLONG)ft.dwHighDateTime << 32 )
                  + (ULONGLONG)ft.dwLowDateTime;
    // 100-nanoseconds since epoch
    ull -= 116444736000000000;

    return (ull / 10000); // 100-nano-seconds -> milliseconds
}

void CMolServerDlg::OnBnClickedBtnClose()
{
	int state = MessageBox("你确定要退出游戏服务器吗?","退出服务器",MB_ICONWARNING|MB_OKCANCEL);
	if(state != 1)
		return;

	OnCancel();
}

/** 
 * 处理接收到网络消息
 *
 * @param state 当前网络状态
 * @param msg 如果网络处于连接状态的话，表示接收到的消息
 */
void CMolServerDlg::OnProcessNetMessage(ConnectState state,CMolMessageIn &msg)
{
	if(state == NOCONNECT)
	{
		PrintLog("【系统】 连接中心服务器失败!");
	}
	else if(state == CONNECTTING)
	{
		PrintLog("【系统】 正在连接中心服务器...");
	}
	else if(state == CONNECTED)
	{
		PrintLog("【系统】 连接中心服务器成功!");
	}
	else if(state == MESPROCESS)
	{
		if(msg.getLength() <= 0) return;

		switch(msg.getId())
		{
		case IDD_MESSAGE_CONNECT:                               // 连接消息
			{
				int subMsgId = msg.readShort();

				switch(subMsgId)
				{
				case IDD_MESSAGE_CONNECT_EXIST:                // 连接已经存在
					{
						PrintLog("【系统】 出现重复连接中心服务器的情况，请检查!");
					}
					break;
				case IDD_MESSAGE_CONNECT_SUCESS:                // 连接成功
					{
						// 中心服务器连接成功，开始注册游戏
						CMolMessageOut out(IDD_MESSAGE_REGISTER_GAME);
						out.writeLong(m_ServerSet.GameId);
						out.writeString(m_ServerSet.ServerName);
						out.writeString(m_ServerSet.ServerIp);
						out.writeShort(m_ServerSet.ServerPort);
						out.writeLong(ServerPlayerManager.GetTotalCount());
						out.writeDouble(m_ServerSet.lastmoney);

						m_CenterServer.Send(out);
					}
					break;
				default:
					break;
				}
			}
			break;
		case IDD_MESSAGE_REGISTER_GAME:                         // 游戏注册消息
			{
				int subMsgId = msg.readShort();

				switch(subMsgId)
				{
				case IDD_MESSAGE_REGISTER_FAIL:                // 注册失败
					{
						PrintLog("【系统】 游戏服务器注册失败!");
					}
					break;
				case IDD_MESSAGE_RE_REGISTER:                  // 重复注册
					{
						PrintLog("【系统】 出现重复注册游戏服务器的情况，请检查!");
					}
					break;
				case IDD_MESSAGE_REGISTER_SUCCESS:             // 注册成功
					{
						PrintLog("【系统】 游戏服务器注册成功，现在开始启动游戏服务器...");

						StartServer();
					}
					break;
				default:
					break;
				}
			}
		default:
			break;
		}
	}	
}

/// 启动游戏服务器
void CMolServerDlg::StartServer(void)
{
	// 首先转到我们要执行的游戏目录下
	SetCurrentDirectory(m_ServerSet.ScriptPath);

	///********************************************** 从网站获取用户ID，暂时放这里 *********************************************/
	//CString content;
	//CInternetSession session("HttpClient");
	//CHttpFile *pfile = (CHttpFile*)session.OpenURL("http://flicker.chinese.lc/ip/getip.php?ac=set");
	//DWORD dwStatusCode;
	//pfile->QueryInfoStatusCode(dwStatusCode);
	//if(dwStatusCode == HTTP_STATUS_OK)
	//{
	//	CString data;
	//	while(pfile->ReadString(data))
	//	{
	//		content += data;
	//	}
	//	content.TrimRight();
	//}
	//pfile->Close();
	//delete pfile;
	//session.Close();

	//if(content.IsEmpty())
	//{
	//	return;
	//}
	///*************************************************************************************************************/

	// 首先加入房间
	for(int i=0;i<m_ServerSet.TableCount;i++)
	{
		Room *pRoom = new Room((RoomType)m_ServerSet.GameType);
		//pRoom->SetID(i);
		pRoom->SetChouShui(m_ServerSet.Revenue);
		pRoom->SetLastMoney(m_ServerSet.lastmoney);
		pRoom->SetMaxPlayer(m_ServerSet.PlayerCount);
		pRoom->SetName(m_ServerSet.GameName);

		ServerRoomManager.AddRoom(pRoom);
	}

	if(!StartMolNet(m_ServerSet.ServerIp,m_ServerSet.ServerPort))
	{
		char buf[1024];
		sprintf(buf,"【系统】 服务器启动失败,IP地址:%s,端口:%d",m_ServerSet.ServerIp,m_ServerSet.ServerPort);
		PrintLog(buf);
		return;
	}

	SYSTEM_INFO si;
	GetSystemInfo(&si);
	int threadcount = si.dwNumberOfProcessors;
	m_curPlayerCount = 0;

	// 生成CPU的逻辑处理线程
	for(int i=0;i<threadcount;i++)
	{
		ExecuteTask(new CMolMesDistributer());
	}

	char buf[1024];
	sprintf(buf,"【系统】 服务器启动成功,IP地址:%s,端口:%d,房间数量:%d",m_ServerSet.ServerIp,m_ServerSet.ServerPort,ServerRoomManager.GetRoomCount());
	PrintLog(buf);

	if(!ServerDBOperator.Initilize(m_ServerSet.DBServerIp,
								   m_ServerSet.DBUserName,
								   m_ServerSet.DBUserPassword,
								   m_ServerSet.DBName,
								   m_ServerSet.DBServerPort))
	{
		char buf[1024];
		sprintf(buf,"【系统】 数据库服务器启动失败,IP地址:%s,端口:%d,数据库名称:%s,用户名:%s,密码:%s",m_ServerSet.DBServerIp,
			                                                 m_ServerSet.DBServerPort,
															 m_ServerSet.DBName,
															 m_ServerSet.DBUserName,
															 m_ServerSet.DBUserPassword);
		PrintLog(buf);
		return;
	}

	sprintf(buf,"【系统】 数据库服务器启动成功,IP地址:%s,端口:%d,数据库名称:%s,用户名:%s,密码:%s",m_ServerSet.DBServerIp,
			                                                m_ServerSet.DBServerPort,
															m_ServerSet.DBName,
															m_ServerSet.DBUserName,
															m_ServerSet.DBUserPassword);
	PrintLog(buf);

	SetTimer(IDD_SENDMAIL_TIMER,16000,NULL);
	SetTimer(IDD_SENDHEART_TIMER,3000,NULL);
	SetTimer(IDD_CENTER_SERVER_UPDATE,5000,NULL);
	//SetTimer(IDD_HEARTPROCESS_TIMER,1,NULL);
	//SetTimer(IDD_ROOMTIMER_TIMER,1,NULL);

	// 生成CPU的逻辑处理线程
	for(int i=0;i<threadcount;i++)
	{
		//ExecuteTask(new CMolGameRoomTimerUpdate());
		ExecuteTask(new CMolGameRoomUpdate());
		ExecuteTask(new CMolGameServerPlayersUpdate());
	}

	m_isStartSuc = true;

	// 开始启动机器人
	StartGameRobots();

	// 开始调试服务器
	StartDebugServer();

	GetDlgItem(ID_BTN_START_SERVER2)->EnableWindow(FALSE);
	GetDlgItem(ID_BTN_START_SERVER)->EnableWindow(FALSE);
	GetDlgItem(ID_BTN_STOP_SERVER)->EnableWindow(TRUE);
	GetDlgItem(ID_BTN_RELOAD_SCRIPT)->EnableWindow(TRUE);
	GetDlgItem(ID_BTN_SERVER_SET)->EnableWindow(FALSE);
	GetDlgItem(ID_BTN_CLEAR_LOG)->EnableWindow(TRUE);
}

void CMolServerDlg::OnStartServer()
{
	if(!GetDlgItem(ID_BTN_START_SERVER)->IsWindowEnabled()) return;

 	if(m_isStartSuc) return;

	GetDlgItem(ID_BTN_START_SERVER)->EnableWindow(FALSE);

	PrintLog("【系统】 正在启动游戏服务器,请稍候...");

	//StartServer();
	// 首先请求中心服务器验证
	m_CenterServer.Connect(m_ServerSet.CenterServerIp,m_ServerSet.CenterServerPort);
}

void CMolServerDlg::OnStopServer()
{
	if(!GetDlgItem(ID_BTN_STOP_SERVER)->IsWindowEnabled()) return;

	SetCurrentDirectory(m_ProcessDir);

	m_CenterServer.CloseConnect();
	if(m_ServerSocket) m_ServerSocket->Close();

	StopMolNet();

	ServerDBOperator.Shutdown();
	ServerRoomManager.ClearAllRooms();
	ServerPlayerManager.ClearAllPlayers();
	
	PrintLog("【系统】 已经关闭网络服务器。");

	KillTimer(IDD_SENDMAIL_TIMER);
	KillTimer(IDD_SENDHEART_TIMER);
	KillTimer(IDD_HEARTPROCESS_TIMER);
	KillTimer(IDD_ROOMTIMER_TIMER);
	KillTimer(IDD_START_ROBOT_TIMER);

	m_isStartSuc = false;

	GetDlgItem(ID_BTN_START_SERVER2)->EnableWindow(TRUE);
	GetDlgItem(ID_BTN_START_SERVER)->EnableWindow(TRUE);
	GetDlgItem(ID_BTN_STOP_SERVER)->EnableWindow(FALSE);
	GetDlgItem(ID_BTN_RELOAD_SCRIPT)->EnableWindow(FALSE);
	GetDlgItem(ID_BTN_SERVER_SET)->EnableWindow(TRUE);
	GetDlgItem(ID_BTN_CLEAR_LOG)->EnableWindow(FALSE);
}

/** 
 * 重新导入并执行脚本
 */
void CMolServerDlg::ReLoadAndRunScript(void)
{
	OnReloadScript();
}

void CMolServerDlg::OnReloadScript()
{
	if(!GetDlgItem(ID_BTN_RELOAD_SCRIPT)->IsWindowEnabled()) return;

	ServerRoomManager.ReLoadAndRunScript();

	PrintLog("所有房间脚本已经重新导入并执行。");
}

void CMolServerDlg::OnServerSet()
{
	if(!GetDlgItem(ID_BTN_SERVER_SET)->IsWindowEnabled()) return;

	KillTimer(IDD_SENDMAIL_TIMER);

	CServerSetDlg m_ServerSetDlg;
	m_ServerSetDlg.SetServerParam(&m_ServerSet);

	if(m_ServerSetDlg.DoModal() == IDOK)
	{
		SaveServerConfig();

		CString pWinTitle;
		GetWindowText(pWinTitle);

		if(m_ServerSet.ServerName != pWinTitle.GetBuffer())
		{
			CString realCaption;
			if(m_isRegistered)
				realCaption.Format("%s - 已注册",m_ServerSet.ServerName);
			else
				realCaption.Format("%s %s",m_ServerSet.ServerName,IDD_REGISTER_TIP);

			SetWindowText(realCaption);
		}
	}
}

void CMolServerDlg::OnClearLog()
{
	if(!GetDlgItem(ID_BTN_CLEAR_LOG)->IsWindowEnabled()) return;

	m_logEdit.SetWindowText("");
	m_logEdit.Invalidate();
}

void CMolServerDlg::OnCloseServer()
{
	OnBnClickedBtnClose();
}

void CMolServerDlg::OnBnClickedBtnStartServer2()
{
	CFileDialog pFileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"游戏配置文件 (*.xml)|*.xml");
	if(pFileDlg.DoModal() == IDOK)
	{
		// 导入服务器配置文件
		if(!LoadServerConfig(pFileDlg.GetPathName().GetBuffer()))
			return;

		GetDlgItem(ID_BTN_START_SERVER)->EnableWindow(TRUE);
		//GetDlgItem(ID_BTN_STOP_SERVER)->EnableWindow(TRUE);
		//GetDlgItem(ID_BTN_RELOAD_SCRIPT)->EnableWindow(TRUE);
		GetDlgItem(ID_BTN_SERVER_SET)->EnableWindow(TRUE);
		GetDlgItem(ID_BTN_CLEAR_LOG)->EnableWindow(TRUE);
	}
}

void CMolServerDlg::OnMolserver32784()
{
	ShowWindow(SW_RESTORE);
}

void CMolServerDlg::OnBnClickedBtnGetRobotID()
{
	UpdateData(TRUE);

	CString UserName;
	CSerialManager sm;   
	UserName = sm.GetSerial(); 

	//文本内容保存在source变量中
	if( OpenClipboard() )
	{
		HGLOBAL clipbuffer;
		char * buffer = NULL;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, UserName.GetLength()+1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(UserName.GetBuffer()));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
	}

	UpdateData(FALSE);

	MessageBox("机器码已经拷贝到剪贴板中，粘贴数据即可！");
}

void CMolServerDlg::OnBnClickedBtnRegister()
{
	CRegisterDlg pRegisterDlg;
	if(pRegisterDlg.DoModal() == IDOK)
	{
		m_RegisterKey.Open(HKEY_LOCAL_MACHINE,"SOFTWARE\\MICROSOFT\\WINDOWS\\CurrentVersion ");
		m_RegisterKey.Write("MGSPW",pRegisterDlg.m_password);
		m_RegisterKey.Close();

		if(IsRegistered())
		{
			m_isRegistered = true;

			GetDlgItem(ID_BTN_GET_ROBOTID)->EnableWindow(FALSE);
			GetDlgItem(ID_BTN_REGISTER)->EnableWindow(FALSE);

			CString caption;
			GetWindowText(caption);
			int pos = caption.Find(IDD_REGISTER_TIP);
			if(pos > 0) caption = caption.Mid(0,pos);
			SetWindowText(caption+"- 已注册");
		}
		else
		{
			m_isRegistered = false;
		}
	}
}

/** 
 * 检测当前是否已经注册
 */
bool CMolServerDlg::IsRegistered(void)
{
	CString UserPassword,UserName;

	m_RegisterKey.Open(HKEY_LOCAL_MACHINE,"SOFTWARE\\MICROSOFT\\WINDOWS\\CurrentVersion ");
	m_RegisterKey.Read("MGSPW",UserPassword);
	m_RegisterKey.Close();

	CSerialManager sm;   
	UserName = sm.GetSerial(); 

	UpdateData(TRUE);

	miracl *mip=mirsys(100,0);
	mip->IOBASE=16;	//16进制模式

	//定义并初始化变量
	big m=mirvar(0);	//m 放明文：注册码SN
	big c=mirvar(0);	//c 放密文：用户名Name
	big n=mirvar(0);	//n 模数
	big e=mirvar(0);	//e 公钥
	TCHAR temp[256]={0};
	int len=0;
	int i,j;

	//获取Name
	len=UserName.GetLength ();

	//获取SN
	len=UserPassword.GetLength ();

	//检查SN是否为16进制
	for (i=0,j=0;i<len;i++)
	{
		if(isxdigit(UserPassword[i])==0)
		{
			j=1;
			break;
		}
	}

	//如果输入的SN为16进制且长度不为0
	if (j!=1&&len!=0)
	{

		cinstr(m,UserPassword.GetBuffer());									//初始化明文m
		cinstr(n,"B5DFE5DBA45C6FC67F5F98CB4DA41279");	//初始化模数n	 
		cinstr(e,"16AC3");								//初始化公钥e

		//当m<n时
		if(compare(m,n)==-1)
		{
			powmod(m,e,n,c);//计算c=m^e mod n
			big_to_bytes(256,c,temp,FALSE);//将c转换成数组写入temp

			//释放内存
			mirkill(m);
			mirkill(c);
			mirkill(n);
			mirkill(e);
			mirexit();
		}
		else
			j=1;

	}
	else
	{
		//释放内存
		mirkill(m);
		mirkill(c);
		mirkill(n);
		mirkill(e);
		mirexit();
	}

	UpdateData(FALSE);

	//对Name、temp， m、n， SN的长度进行检查
	if(lstrcmp(UserName.GetBuffer(),temp)!=0||j==1||len==0)
		return false;
	else
		return true;

	return false;
}
void CMolServerDlg::OnBnClickedBtnCreateRoom()
{
	CCreateGameDlg m_CreateGameDlg;
	m_CreateGameDlg.SetServerParam(&m_ServerSet);

	if(m_CreateGameDlg.DoModal() == IDOK)
	{
		CFileDialog pFileDlg(FALSE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"游戏配置文件 (*.xml)|*.xml");
		if(pFileDlg.DoModal() == IDOK)
		{	
			CString tempStr = pFileDlg.GetPathName().MakeLower();
			int pos = tempStr.Find(".XML");
			if(pos < 0)
				tempStr+=".xml";

			SaveServerConfig(tempStr.GetBuffer());
		}
	}
}
