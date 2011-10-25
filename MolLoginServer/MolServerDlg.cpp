// MolServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MolServer.h"
#include "MolServerDlg.h"
#include ".\molserverdlg.h"
#include "MolMesDistributer.h"

#include "tinyxml/tinyxml.h"
#include "libcrashrpt/MolCrashRpt.h"

#include "GameFrameManager.h"
#include "GameServerManager.h"
#include "DBOperator.h"
#include "defines.h"

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
	: CDialog(IDD_MOLSERVER_DIALOG, pParent),m_TrayIcon(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMolServerDlg::~CMolServerDlg()
{
	CleanMolNet();

	delete DBOperator::getSingletonPtr();
	delete GameFrameManager::getSingletonPtr();
	delete GameServerManager::getSingletonPtr();
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
	//ON_BN_CLICKED(ID_BTN_RELOAD_SCRIPT, OnReloadScript)
	//ON_COMMAND(ID_RELOAD_SCRIPT, OnReloadScript)
	ON_BN_CLICKED(ID_BTN_SERVER_SET, OnServerSet)
	ON_COMMAND(ID_SERVER_SET, OnServerSet)
	ON_BN_CLICKED(ID_BTN_CLEAR_LOG, OnClearLog)
	ON_COMMAND(ID_CLEAR_LOG, OnClearLog)
	ON_COMMAND(ID_CLOSE_SERVER, OnCloseServer)
	ON_BN_CLICKED(ID_BTN_START_SERVER2, OnBnClickedBtnStartServer2)
	ON_COMMAND(ID_MOLSERVER_32784, OnMolserver32784)
END_MESSAGE_MAP()

/**
 * 保存服务器配置文件
 */
void CMolServerDlg::SaveServerConfig(void)
{
	if(m_curGameConfigFile.empty()) return;

	// 输出XML文件
	TiXmlDocument doc(m_curGameConfigFile.c_str());
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

	ServerConfig.InsertEndChild(GameServerConfig);

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

				/*if(name == "ServerName")
				{
					std::string temp = value.substr(0,value.length()-3);
					strcpy(m_ServerSet.ServerName , temp.c_str());
				}
				else */if(name == "ServerIp")
				{
					strcpy(m_ServerSet.ServerIp , value.c_str());
				}
				else if(name == "ServerPort")
				{
					m_ServerSet.ServerPort = atoi(value.c_str());
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

	// 开始启动服务器
	InitMolNet();

	//建立任务栏图标
	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_TrayIcon.SetNotifyWnd(this,IDM_TRAY_NOTIFY_MSG);//将主对话框和开始状态栏上的icon联系上
	m_TrayIcon.SetIcon(hIcon,"MolLoginServer");
	m_TrayIcon.ShowBalloonTip("正在启动登陆服务器，请稍后...   ","MolLoginServer");
	SetIcon(hIcon,FALSE);
	DestroyIcon(hIcon);

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetCurrentDirectory(256,m_ProcessDir);

	// 设置我们游戏使用的日志文件
	CMolLogger::setLogFile("molloginserver.txt");

	new GameFrameManager();
	new GameServerManager();
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
	MolCrash_SetProjectName("MolLoginServer");
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
	CDialog::OnTimer(nIDEvent);
}

void CMolServerDlg::OnBnClickedBtnClose()
{
	int state = MessageBox("你确定要退出登陆服务器吗?","退出服务器",MB_ICONWARNING|MB_OKCANCEL);
	if(state != 1)
		return;

	OnCancel();
}

/// 启动游戏服务器
void CMolServerDlg::StartServer(void)
{
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

	// 生成CPU的逻辑处理线程
	for(int i=0;i<threadcount;i++)
	{
		ExecuteTask(new CMolMesDistributer());
	}

	char buf[1024];
	sprintf(buf,"【系统】 服务器启动成功,IP地址:%s,端口:%d",m_ServerSet.ServerIp,m_ServerSet.ServerPort);
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

	GetDlgItem(ID_BTN_START_SERVER2)->EnableWindow(FALSE);
	GetDlgItem(ID_BTN_START_SERVER)->EnableWindow(FALSE);
	GetDlgItem(ID_BTN_STOP_SERVER)->EnableWindow(TRUE);
	//GetDlgItem(ID_BTN_RELOAD_SCRIPT)->EnableWindow(TRUE);
	GetDlgItem(ID_BTN_SERVER_SET)->EnableWindow(FALSE);
	GetDlgItem(ID_BTN_CLEAR_LOG)->EnableWindow(TRUE);
}

void CMolServerDlg::OnStartServer()
{
	if(!GetDlgItem(ID_BTN_START_SERVER)->IsWindowEnabled()) return;

	GetDlgItem(ID_BTN_START_SERVER)->EnableWindow(FALSE);

	PrintLog("【系统】 正在启动登陆服务器,请稍候...");

	StartServer();
}

void CMolServerDlg::OnStopServer()
{
	if(!GetDlgItem(ID_BTN_STOP_SERVER)->IsWindowEnabled()) return;

	StopMolNet();

	ServerDBOperator.Shutdown();
	
	PrintLog("【系统】 已经关闭网络服务器。");

	GetDlgItem(ID_BTN_START_SERVER2)->EnableWindow(TRUE);
	GetDlgItem(ID_BTN_START_SERVER)->EnableWindow(TRUE);
	GetDlgItem(ID_BTN_STOP_SERVER)->EnableWindow(FALSE);
	//GetDlgItem(ID_BTN_RELOAD_SCRIPT)->EnableWindow(FALSE);
	GetDlgItem(ID_BTN_SERVER_SET)->EnableWindow(TRUE);
	GetDlgItem(ID_BTN_CLEAR_LOG)->EnableWindow(FALSE);
}

void CMolServerDlg::OnServerSet()
{
	if(!GetDlgItem(ID_BTN_SERVER_SET)->IsWindowEnabled()) return;

	CServerSetDlg m_ServerSetDlg;
	m_ServerSetDlg.SetServerParam(&m_ServerSet);

	if(m_ServerSetDlg.DoModal() == IDOK)
	{
		SaveServerConfig();
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

