// Mole2dGameClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Mole2dGameClient.h"
#include "Mole2dGameClientDlg.h"
#include "SwitchUserDlg.h"
#include "Mole2dClientCommon.h"
#include ".\mole2dgameclientdlg.h"

#include <curl/curl.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

initialiseSingleton(CMole2dGameClientDlg);

int StringReplace(std::string&   src_str,   const   std::string&   old_str,   const   std::string&   new_str) 
{ 
	int   count   =   0; 
	int   old_str_len   =   old_str.length(),   new_str_len   =   new_str.length(); 
	int   pos   =   0; 
	while(   (pos   =   src_str.find(   old_str,   pos   )   )   !=   std::string::npos   ) 
	{ 
		src_str.replace(   pos,   old_str_len,   new_str   ); 
		pos   +=   new_str_len; 
		++count; 
	} 
	return   count; 
} 

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


// CMole2dGameClientDlg 对话框



CMole2dGameClientDlg::CMole2dGameClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMole2dGameClientDlg::IDD, pParent),m_dwWidth(0),m_dwHeight(0),m_userLevel(0),m_userMoney(0),
	  m_UpdateState(UPDATESTATE_MAINFRAME),m_CurGameServerInfo(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMole2dGameClientDlg::~CMole2dGameClientDlg()
{
	SystemParametersInfo(SPI_SETCURSORS, 0, 0, SPIF_SENDWININICHANGE);

	UnregisterHotKey(m_hWnd,IDD_HOTKEY_DEBUGSERVER);
	//WSACleanup ();

	PostThreadMessage(m_UpdateThreadID,WM_STOP,0,0); 
	if(WaitForSingleObject(m_UpdateThread,INFINITE) == WAIT_OBJECT_0)
	{
		CloseHandle(m_UpdateThread);
		m_UpdateThread = NULL;
	}
	else   
	{
		TerminateThread(m_UpdateThread,   -1);
		CloseHandle(m_UpdateThread);
		m_UpdateThread = NULL;
	} 
}

void CMole2dGameClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDD_BTN_MIN, m_btnMin);
	DDX_Control(pDX, IDCANCEL, m_btnExit);
	DDX_Control(pDX, IDD_RETURN_ROOT, m_btnReturnRoot);
	DDX_Control(pDX, IDD_BTN_HOMEPAGE, m_btnHomePage);
	DDX_Control(pDX, IDD_BTN_ZHONGZHI, m_btnChongZhi);
	DDX_Control(pDX, IDD_BTN_BANK, m_btnBank);
	DDX_Control(pDX, IDD_BTN_KEHU, m_btnKeHu);
}

BEGIN_MESSAGE_MAP(CMole2dGameClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_WM_NCPAINT()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(IDD_CLOSE_GAME_FRAME,OnCloseGame)
	ON_MESSAGE(IDM_BTN_SERVER_LOGIN,OnUserLogin)
	ON_MESSAGE(IDM_GAMEFRAME_MESSAGE,OnGameFrameMes)
	ON_MESSAGE(IDD_EXIT_GAME,OnExitGame)
	ON_MESSAGE(IDD_REENTER_GAME,OnReEnterGame)
	ON_MESSAGE(IDD_SHOW_CONN_TIP,OnShowConnTip)
	ON_MESSAGE(WM_HOTKEY,   OnHotHey) 
	ON_MESSAGE(IDD_MAINFRAME_UPDATE,   OnMainFrameUpdate) 
	ON_MESSAGE(IDD_GAME_ROOM_LIST,OnShowGameServerList)
	ON_MESSAGE(IDD_GAME_UPDATE,OnGameUpdateFinish)
	ON_BN_CLICKED(IDOK2, OnBnClickedOk2)
	ON_BN_CLICKED(IDD_RETURN_ROOT, &CMole2dGameClientDlg::OnBnClickedReturnRoot)
	ON_BN_CLICKED(IDCANCEL, &CMole2dGameClientDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDD_BTN_MIN, &CMole2dGameClientDlg::OnBnClickedBtnMin)
	ON_BN_CLICKED(IDD_BTN_HOMEPAGE, &CMole2dGameClientDlg::OnBnClickedBtnHomepage)
	ON_BN_CLICKED(IDD_BTN_ZHONGZHI, &CMole2dGameClientDlg::OnBnClickedBtnChongZhi)
	ON_BN_CLICKED(IDD_BTN_BANK, &CMole2dGameClientDlg::OnBnClickedBtnBank)
	ON_BN_CLICKED(IDD_BTN_KEHU, &CMole2dGameClientDlg::OnBnClickedBtnKeHu)
END_MESSAGE_MAP()


// CMole2dGameClientDlg 消息处理程序

BOOL CMole2dGameClientDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	SetWindowText(IDD_CLIENT_CAPTION);

	WORD versionRequested = MAKEWORD (2, 2);
	WSADATA wsaData;

	if (WSAStartup (versionRequested, & wsaData))
		return TRUE;

	if (LOBYTE (wsaData.wVersion) != 2||
		HIBYTE (wsaData.wVersion) != 2)
	{
		WSACleanup ();
	}

	m_btnMin.SetButtonImage(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "gameroomconfig\\bt_min.bmp" );
	m_btnExit.SetButtonImage(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "gameroomconfig\\frame_close.png" );
	m_btnReturnRoot.SetButtonImage(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "gameroomconfig\\fhdt.png" );
	m_btnHomePage.SetButtonImage(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "gameroomconfig\\bt_home.png" );
	m_btnChongZhi.SetButtonImage(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "gameroomconfig\\bt_pay.png" );
	m_btnBank.SetButtonImage(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "gameroomconfig\\bt_bank.png" );
	m_btnKeHu.SetButtonImage(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "gameroomconfig\\bt_exit.png" );
	m_bgImg.Load(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "gameroomconfig\\framebg.png");

	if(!m_bgImg.IsNull())
	{
		Bitmap *mybgImg = Bitmap::FromHBITMAP(m_bgImg,NULL);

		Color   cl(0,0,0);
		HBITMAP   hBitmap;
		mybgImg->GetHBITMAP(cl,   &hBitmap); 

		HRGN hRgn = CreateRgnFromFile( hBitmap, RGB(0,0,0) );

		SetWindowPos( NULL, 0, 0, m_bgImg.GetWidth(),m_bgImg.GetHeight(), SWP_NOZORDER | SWP_NOMOVE );
		SetWindowRgn( hRgn, FALSE );
	}

	// TODO: 在此添加额外的初始化代码
	pGameFrameDlg.Initialize("测试程序",CMolDimension2d<int>(800,600));
	CMolGUIRoomList *pGameList = pGameFrameDlg.GetRoomList();
	if(pGameList != NULL) 
	{
		pGameList->SetDriver(pGameFrameDlg.GetDriver());
		pGameList->LoadRoomConfig("gameroomconfig\\gameroomconfig.xml");
	}
	pDebugServerDlg.Create(IDD_SER_DIALOG,this);
	pUserLoginDlg.Create(IDD_DLG_LOGIN,this);
	pConnStateDlg.Create(IDD_DLG_STATE,this);
	m_SwitchUserDlg.Create(IDD_DLG_SWITCHUSER,this);
	m_DownloadDlg.Create(IDD_DLG_DOWNLOAD,this);

	m_WebBrowser.Create(NULL,WS_CHILD,CRect(CPoint(20,143),CSize(710,490)),this,0);
	m_GameRoomManager.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(CPoint(20,143),CSize(710,490)),this,0);
	m_GameRoomManager.LoadRoomConfig("gameroomconfig\\maingameconfig.xml");

	RegisterHotKey(m_hWnd,IDD_HOTKEY_DEBUGSERVER,MOD_CONTROL,VK_F9);

	WIN32_FIND_DATA   FindData;

	// 更新游戏
	TCHAR szProcessName[MAX_PATH]=TEXT("");
	GetModuleFileName(AfxGetInstanceHandle(),szProcessName,MAX_PATH);
	std::string tempStr = szProcessName;
	int pos = tempStr.find_last_of("\\");
	if(pos > 0) tempStr = tempStr.substr(0,pos+1);

	std::string cmdPro = tempStr + "clientconfig.ini";

	// 检测当前是否为文件
	HANDLE   hFile   =   FindFirstFile(cmdPro.c_str(),   &FindData);
	if(INVALID_HANDLE_VALUE   !=   hFile)
	{
		m_UpdateState = UPDATESTATE_MAINFRAME;
		UpdateGame(cmdPro);
	}
	else
	{
		pUserLoginDlg.ShowWindow(SW_SHOW);
		pUserLoginDlg.SetCtrlFocus();
	}

	CenterWindow();
	SetSystemCursor(LoadCursorFromFile("gameroomconfig\\Arrow.cur"),32512);

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

/** 
 * 设置用户自己的信息
 */
void CMole2dGameClientDlg::SetMySelfInfo(Player* pPlayer)
{
	if(pPlayer == NULL) return;

	m_myselft.SetID(pPlayer->GetID());
	m_myselft.SetName(pPlayer->GetName());
	m_myselft.SetUserAvatar(pPlayer->GetUserAvatar());
	m_myselft.SetLevel(pPlayer->GetLevel());
	m_myselft.SetMoney(pPlayer->GetMoney());
	m_myselft.SetExperience(pPlayer->GetExperience());			
	m_myselft.SetTotalBureau(pPlayer->GetTotalBureau());
	m_myselft.SetSuccessBureau(pPlayer->GetSuccessBureau());
	m_myselft.SetFailBureau(pPlayer->GetFailBureau());
	m_myselft.SetSuccessRate(pPlayer->GetSuccessRate());
	m_myselft.SetRunawayrate(pPlayer->GetRunawayrate());
}

/** 
 * 刷新用户信息
 */
void CMole2dGameClientDlg::RefreshMyselfInfo(void)
{
	if(!m_userLogoImg.IsNull())
		m_userLogoImg.Destroy();

	CString logoPath;
	logoPath.Format("%sAvatars\\%s",CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath().GetBuffer(),m_myselft.GetUserAvatar().c_str());
	m_userLogoImg.Load(logoPath);

	m_userName = m_myselft.GetName().c_str();
	m_userLevel = m_myselft.GetLevel();
	m_userMoney = m_myselft.GetMoney();

	Invalidate(FALSE);
}

//艺术字体
void CMole2dGameClientDlg::DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, LPRECT lpRect)
{
	//变量定义
	int nStringLength=lstrlen(pszString);
	int nXExcursion[8]={1,1,1,0,-1,-1,-1,0};
	int nYExcursion[8]={-1,0,1,1,1,0,-1,-1};

	//绘画边框
	pDC->SetTextColor(crFrame);
	CRect rcDraw;
	for (int i=0;i<CountArray(nXExcursion);i++)
	{
		rcDraw.CopyRect(lpRect);
		rcDraw.OffsetRect(nXExcursion[i],nYExcursion[i]);
		pDC->DrawText(pszString,nStringLength,&rcDraw,DT_VCENTER|DT_CENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
	}

	//绘画字体
	rcDraw.CopyRect(lpRect);
	pDC->SetTextColor(crText);
	pDC->DrawText(pszString,nStringLength,&rcDraw,DT_VCENTER|DT_CENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

	return;
}

//艺术字体
void CMole2dGameClientDlg::DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos)
{
	//变量定义
	int nStringLength=lstrlen(pszString);
	int nXExcursion[8]={1,1,1,0,-1,-1,-1,0};
	int nYExcursion[8]={-1,0,1,1,1,0,-1,-1};

	//绘画边框
	pDC->SetTextColor(crFrame);
	for (int i=0;i<CountArray(nXExcursion);i++)
	{
		pDC->TextOut(nXPos+nXExcursion[i],nYPos+nYExcursion[i],pszString,nStringLength);
	}

	//绘画字体
	pDC->SetTextColor(crText);
	pDC->TextOut(nXPos,nYPos,pszString,nStringLength);

	return;
}

/** 
 * 下载指定网址的文件到指定的目录中，我们的下载基于http协议，这个下载一次只能下载一个文件,而且文件必须是以pak打包过的压缩文件
 *
 * @param file 要下载的文件，要文件的完整路径
 * @param path 要保存的文件路径,如果为空的话保存到当前路径，如果路径不存在的话建立路径
 * 
 * @return 如果文件下载成功返回真，否则返回假
 */
bool CMole2dGameClientDlg::DownloadSingleFile(std::string file,std::string path)
{
	if(file.empty()) return false;

	// 得到我们要下载的文件
	std::string pFile = file;
	std::string pSerAddress = serveraddress + file;
	pFile = (path.empty() ? pFile : path + pFile);

	if(serveraddress.empty())
	{
		pFile = file.substr(file.find_last_of("//")+1,file.length());
		pFile = (path.empty() ? pFile : path + pFile);
	}

	// 首先建立我们文件保存需要的目录
	StringReplace(pFile,"/","\\");
	CreateDirectionByPath(pFile);

	int attempts = 0;
	CURL *curl;
	CURLcode res;

	while (attempts < 3)
	{
		FILE *outfile = NULL;

		try
		{
			curl = curl_easy_init();
			if (curl == NULL) return false;

			std::string newfile = MOLE2D_DOWNLOAD_TEMP_FILE;
			outfile = fopen(newfile.c_str(), "w+b");
			if(outfile == NULL) return false;

			curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);

			curl_easy_setopt(curl, CURLOPT_USERAGENT, "MOLGAMECLIENT");
			curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, m_CurlError);
			curl_easy_setopt(curl, CURLOPT_URL, pSerAddress.c_str());
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
			curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION,UpdateProgress);
			curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, (void*)this);
			curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
			curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 15);
			curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);

			if ((res = curl_easy_perform(curl)) != 0)
			{
				switch (res)
				{
				case CURLE_COULDNT_CONNECT:
				default:
					break;
				}

				fclose(outfile);
				attempts++;
				continue;
			}

			curl_easy_cleanup(curl);			

			fclose(outfile);
		}
		catch(...)
		{
			::OutputDebugString("error!");
			return false;
		}


		std::string pExName = pFile.substr(pFile.length()-3,pFile.length());

		std::transform(pExName.begin(), pExName.end(), pExName.begin(), toupper);

		//if(pExName == "ZIP")
		//{
		//	GetDlgItem(IDC_STATIC)->SetWindowText("正在生成文件,请稍候...");

		//	// 解压这个压缩文件到当前目录
		//	unzip(MOLE2D_DOWNLOAD_TEMP_FILE,path);
		//}	
		//else
		//{
			CopyFile(MOLE2D_DOWNLOAD_TEMP_FILE,pFile.c_str(),true);
		//}

		DeleteFile(MOLE2D_DOWNLOAD_TEMP_FILE);

		return true;
	}

	return false;
}

/** 
 * curl 使用的下载进度更新函数
 *
 * @param ptr 我们的传值
 * @param dt,dn,ut,un curl的传值，主要得到当前文件的更新进度
 *
 * @return 如果成功返回0，否则返回-1
 */
int CMole2dGameClientDlg::UpdateProgress(void *ptr,double dt, double dn, double ut, double un)
{
	return 0;
}

/** 
 * 得到当前程序所在路径
 */
CString CMole2dGameClientDlg::GetCurrentProcessPath(void)
{
	TCHAR szProcessName[MAX_PATH]=TEXT("");
	GetModuleFileName(AfxGetInstanceHandle(),szProcessName,MAX_PATH);
	std::string tempStr = szProcessName;
	int pos = tempStr.find_last_of("\\");
	if(pos > 0) tempStr = tempStr.substr(0,pos+1);

	return tempStr.c_str();
}

/** 
 * 根据客户端下载配置文件从服务器更新游戏
 *
 * @param configfile 要更新的配置文件
 */
void CMole2dGameClientDlg::UpdateGame(std::string configfile)
{
	if(configfile.empty())
		return;

	m_UpdateVer = 0.0f;
	serveraddress.clear();
	m_UpdateConfigFile = configfile;

	char buf[1024];
	GetPrivateProfileString(TEXT("UpdateSet"),TEXT("ver"),"",buf,1024,configfile.c_str());
	float ver = (float)atof(buf);
	GetPrivateProfileString(TEXT("UpdateSet"),TEXT("address"),"",buf,1024,configfile.c_str());
	std::string address = buf;

	m_UpdataSet = UpdataSet(ver,address);

	CURLcode res;

	// 初始化libcurl
	res = curl_global_init(CURL_GLOBAL_WIN32);
	if (CURLE_OK != res)
	{
		return;
	}

	// 建立更新线程
	m_UpdateThread = (HANDLE)::_beginthreadex(NULL,0,ThreadGameUpdate,(LPVOID)this,0,&m_UpdateThreadID);
	curl_global_cleanup();
}

/** 
 * 游戏更新函数
 *
 * @param pParam 传入的参数
 *
 * @return 
 */
unsigned __stdcall CMole2dGameClientDlg::ThreadGameUpdate(void * pParam)
{
	CMole2dGameClientDlg *pGameClientDlg = static_cast<CMole2dGameClientDlg*>(pParam);
	if(pGameClientDlg == NULL) return 0;

	// 首先从服务器上下载更新列表
	if(pGameClientDlg->DownloadSingleFile(pGameClientDlg->GetUpdateSet().address))
	{
		pGameClientDlg->PostMessage(IDD_MAINFRAME_UPDATE,1,0);		
		return 0;
	}

	pGameClientDlg->PostMessage(IDD_MAINFRAME_UPDATE,0,0);		

	return 0;
}

/**
* 根据文件路径名建立相应的目录
*
* @param filename 要建立目录的文件名
*/
void CMole2dGameClientDlg::CreateDirectionByPath(std::string filename)
{
	if(filename.empty()) return;

	WIN32_FIND_DATA   FindData;
	std::string temp1,temp = filename;
	int oldindex,index = (int)temp.find("\\");
	std::string realdir;

	oldindex = 0;

	while(index >= 0) {
		std::string dir = temp.substr(oldindex,index);

		if(realdir.empty())
			realdir = /*m_curWorkingDir + "\\" + */dir;
		else
			realdir = realdir + "\\" + dir;

		// 检测当前目录是否存在，如果不存在，就建立目录
		HANDLE   hFile   =   FindFirstFile(realdir.c_str(),&FindData);
		if(INVALID_HANDLE_VALUE == hFile)
		{
			// 如果这个目录不存在就建立这个目录
			if(!CreateDirectory(realdir.c_str(),NULL)) {
				return;
			}
		}

		oldindex = oldindex+index+1;
		temp1 = temp.substr(oldindex,temp.length());
		index = (int)temp1.find("\\");
	}
}

//消息解释
BOOL CMole2dGameClientDlg::PreTranslateMessage(MSG * pMsg)
{
	//if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F9 && (GetKeyState(VK_CONTROL)&0x8000)) 
	//{
	//	if(!pDebugServerDlg.IsWindowVisible())
	//	{
	//		pDebugServerDlg.CenterWindow();
	//		pDebugServerDlg.ShowWindow(SW_SHOW);
	//	}
	//}

	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CMole2dGameClientDlg::OnHotHey(WPARAM wParam,LPARAM lParam)
{
	if(wParam == IDD_HOTKEY_DEBUGSERVER)
	{
		if(!pDebugServerDlg.IsWindowVisible())
			pDebugServerDlg.ShowWindow(SW_SHOW);
		else
			pDebugServerDlg.SetForegroundWindow();
	}

	return 0;
}

void CMole2dGameClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMole2dGameClientDlg::OnPaint() 
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
		CPaintDC dc(this); 

		CDC memDC;//内存DC
		CBitmap cbm;//内存画布
		CBitmap* oldBmp;//原画布
		CRect sourceRect;//源矩形
		CRect destRect;//目标矩形为客户区

		GetClientRect(&destRect);//客户区矩形
		memDC.CreateCompatibleDC(NULL);//兼容内存DC
		cbm.CreateCompatibleBitmap(&dc,destRect.Width(),destRect.Height());//兼容内存画布
		oldBmp=memDC.SelectObject(&cbm);//将画布选入DC

		if(!m_bgImg.IsNull())
			m_bgImg.Draw(memDC,0,0);

		memDC.SetBkMode(TRANSPARENT);

		//创建字体
		CFont DrawFont;
		DrawFont.CreateFont(-13,0,0,0,FW_NORMAL,0,0,0,134,3,2,1,2,TEXT("Arial"));
		CDC * pDC=CDC::FromHandle(memDC.GetSafeHdc());
		CFont * pOldFont=pDC->SelectObject(&DrawFont);

		DrawTextString(pDC,m_userName.GetBuffer(),RGB(255,255,255),RGB(0,0,0),926,112);

		CString tempStr;
		tempStr.Format("%d",m_userLevel);
		DrawTextString(pDC,tempStr.GetBuffer(),RGB(255,255,255),RGB(0,0,0),926,171);

		tempStr.Format("%I64d",m_userMoney);
		DrawTextString(pDC,tempStr.GetBuffer(),RGB(255,255,255),RGB(0,0,0),926,143);

		//清理资源
		pDC->SelectObject(pOldFont);
		DrawFont.DeleteObject();

		memDC.SetStretchBltMode(STRETCH_HALFTONE);
		// 显示用户头像
		if(!m_userLogoImg.IsNull())
			m_userLogoImg.StretchBlt(memDC.GetSafeHdc(),764,107,80,82,0,0,m_userLogoImg.GetWidth(),m_userLogoImg.GetHeight());

		dc.BitBlt(0,0,destRect.Width(),destRect.Height(),&memDC,0,0,SRCCOPY);//双缓冲

		memDC.SelectObject(oldBmp);//恢复旧的画布
		memDC.DeleteDC();//删除内存DC
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMole2dGameClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMole2dGameClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
}

void CMole2dGameClientDlg::OnNcPaint()
{
	static int i = 2;
	if(i > 0)
	{
		i --;
		ShowWindow(SW_HIDE);
	}
	else
		CDialog::OnNcPaint();
}

/// 显示主窗口
void CMole2dGameClientDlg::ShowMainFrame(void)
{
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
	::SetWindowPos(this->m_hWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	m_GameRoomManager.RegulateGameNodes();

	EnableWindow(TRUE);
	ShowWindow(SW_RESTORE);
}

/// 关闭游戏
LRESULT	CMole2dGameClientDlg::OnCloseGame(WPARAM wparam, LPARAM lparam)
{
	return 0;
}

/// 退出游戏
LRESULT CMole2dGameClientDlg::OnExitGame(WPARAM wparam, LPARAM lparam)
{
	pGameFrameDlg.ShowWindow(SW_HIDE);
	pGameFrameDlg.CloseConnect();
	EndModalLoop(IDCANCEL);
	return 0;
}

/// 重新登录游戏
LRESULT CMole2dGameClientDlg::OnReEnterGame(WPARAM wparam, LPARAM lparam)
{
	pGameFrameDlg.ShowWindow(SW_HIDE);
	pGameFrameDlg.CloseConnect();
	pGameFrameDlg.Reset();

	pUserLoginDlg.ShowWindow(SW_SHOW);
	pUserLoginDlg.SetCtrlFocus();

	return 0;
}

HRGN CMole2dGameClientDlg::CreateRgnFromFile( HBITMAP hBmp, COLORREF color )
{
	// get image properties
	BITMAP bmp = { 0 };
	GetObject( hBmp, sizeof(BITMAP), &bmp );
	// allocate memory for extended image information
	LPBITMAPINFO bi = (LPBITMAPINFO) new BYTE[ sizeof(BITMAPINFO) + 8 ];
	memset( bi, 0, sizeof(BITMAPINFO) + 8 );
	bi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	// set window size
	m_dwWidth	= bmp.bmWidth;		// bitmap width
	m_dwHeight	= bmp.bmHeight;		// bitmap height
	// create temporary dc
	HDC dc = CreateIC( "DISPLAY",NULL,NULL,NULL );
	// get extended information about image (length, compression, length of color table if exist, ...)
	DWORD res = GetDIBits( dc, hBmp, 0, bmp.bmHeight, 0, bi, DIB_RGB_COLORS );
	// allocate memory for image data (colors)
	LPBYTE pBits = new BYTE[ bi->bmiHeader.biSizeImage + 4 ];
	// allocate memory for color table
	if ( bi->bmiHeader.biBitCount == 8 )
	{
		// actually color table should be appended to this header(BITMAPINFO),
		// so we have to reallocate and copy it
		LPBITMAPINFO old_bi = bi;
		// 255 - because there is one in BITMAPINFOHEADER
		bi = (LPBITMAPINFO)new char[ sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD) ];
		memcpy( bi, old_bi, sizeof(BITMAPINFO) );
		// release old header
		delete old_bi;
	}
	// get bitmap info header
	BITMAPINFOHEADER& bih = bi->bmiHeader;
	// get color table (for 256 color mode contains 256 entries of RGBQUAD(=DWORD))
	LPDWORD clr_tbl = (LPDWORD)&bi->bmiColors;
	// fill bits buffer
	res = GetDIBits( dc, hBmp, 0, bih.biHeight, pBits, bi, DIB_RGB_COLORS );
	DeleteDC( dc );

	BITMAP bm;
	GetObject( hBmp, sizeof(BITMAP), &bm );
	// shift bits and byte per pixel (for comparing colors)
	LPBYTE pClr = (LPBYTE)&color;
	// swap red and blue components
	BYTE tmp = pClr[0]; pClr[0] = pClr[2]; pClr[2] = tmp;
	// convert color if curent DC is 16-bit (5:6:5) or 15-bit (5:5:5)
	if ( bih.biBitCount == 16 )
	{
		// for 16 bit
		color = ((DWORD)(pClr[0] & 0xf8) >> 3) |
			((DWORD)(pClr[1] & 0xfc) << 3) |
			((DWORD)(pClr[2] & 0xf8) << 8);
		// for 15 bit
		//		color = ((DWORD)(pClr[0] & 0xf8) >> 3) |
		//				((DWORD)(pClr[1] & 0xf8) << 2) |
		//				((DWORD)(pClr[2] & 0xf8) << 7);
	}

	const DWORD RGNDATAHEADER_SIZE	= sizeof(RGNDATAHEADER);
	const DWORD ADD_RECTS_COUNT		= 40;			// number of rects to be appended
	// to region data buffer

	// BitPerPixel
	BYTE	Bpp = bih.biBitCount >> 3;				// bytes per pixel
	// bytes per line in pBits is DWORD aligned and bmp.bmWidthBytes is WORD aligned
	// so, both of them not
	DWORD m_dwAlignedWidthBytes = (bmp.bmWidthBytes & ~0x3) + (!!(bmp.bmWidthBytes & 0x3) << 2);
	// DIB image is flipped that's why we scan it from the last line
	LPBYTE	pColor = pBits + (bih.biHeight - 1) * m_dwAlignedWidthBytes;
	DWORD	dwLineBackLen = m_dwAlignedWidthBytes + bih.biWidth * Bpp;	// offset of previous scan line
	// (after processing of current)
	DWORD	dwRectsCount = bih.biHeight;			// number of rects in allocated buffer
	INT		i, j;									// current position in mask image
	INT		first = 0;								// left position of current scan line
	// where mask was found
	bool	wasfirst = false;						// set when mask has been found in current scan line
	bool	ismask;									// set when current color is mask color

	// allocate memory for region data
	// region data here is set of regions that are rectangles with height 1 pixel (scan line)
	// that's why first allocation is <bm.biHeight> RECTs - number of scan lines in image
	RGNDATAHEADER* pRgnData = 
		(RGNDATAHEADER*)new BYTE[ RGNDATAHEADER_SIZE + dwRectsCount * sizeof(RECT) ];
	// get pointer to RECT table
	LPRECT pRects = (LPRECT)((LPBYTE)pRgnData + RGNDATAHEADER_SIZE);
	// zero region data header memory (header  part only)
	memset( pRgnData, 0, RGNDATAHEADER_SIZE + dwRectsCount * sizeof(RECT) );
	// fill it by default
	pRgnData->dwSize	= RGNDATAHEADER_SIZE;
	pRgnData->iType		= RDH_RECTANGLES;

	for ( i = 0; i < bih.biHeight; i++ )
	{
		for ( j = 0; j < bih.biWidth; j++ )
		{
			// get color
			switch ( bih.biBitCount )
			{
			case 8:
				ismask = (clr_tbl[ *pColor ] != color);
				break;
			case 16:
				ismask = (*(LPWORD)pColor != (WORD)color);
				break;
			case 24:
				ismask = ((*(LPDWORD)pColor & 0x00ffffff) != color);
				break;
			case 32:
				ismask = (*(LPDWORD)pColor != color);
			}
			// shift pointer to next color
			pColor += Bpp;
			// place part of scan line as RECT region if transparent color found after mask color or
			// mask color found at the end of mask image
			if ( wasfirst )
			{
				if ( !ismask )
				{
					// save current RECT
					pRects[ pRgnData->nCount++ ] = CRect( first, i, j, i + 1 );
					// if buffer full reallocate it with more room
					if ( pRgnData->nCount >= dwRectsCount )
					{
						dwRectsCount += ADD_RECTS_COUNT;
						// allocate new buffer
						LPBYTE pRgnDataNew = new BYTE[ RGNDATAHEADER_SIZE + dwRectsCount * sizeof(RECT) ];
						// copy current region data to it
						memcpy( pRgnDataNew, pRgnData, RGNDATAHEADER_SIZE + pRgnData->nCount * sizeof(RECT) );
						// delte old region data buffer
						delete pRgnData;
						// set pointer to new regiondata buffer to current
						pRgnData = (RGNDATAHEADER*)pRgnDataNew;
						// correct pointer to RECT table
						pRects = (LPRECT)((LPBYTE)pRgnData + RGNDATAHEADER_SIZE);
					}
					wasfirst = false;
				}
			}
			else if ( ismask )		// set wasfirst when mask is found
			{
				first = j;
				wasfirst = true;
			}
		}

		if ( wasfirst && ismask )
		{
			// save current RECT
			pRects[ pRgnData->nCount++ ] = CRect( first, i, j, i + 1 );
			// if buffer full reallocate it with more room
			if ( pRgnData->nCount >= dwRectsCount )
			{
				dwRectsCount += ADD_RECTS_COUNT;
				// allocate new buffer
				LPBYTE pRgnDataNew = new BYTE[ RGNDATAHEADER_SIZE + dwRectsCount * sizeof(RECT) ];
				// copy current region data to it
				memcpy( pRgnDataNew, pRgnData, RGNDATAHEADER_SIZE + pRgnData->nCount * sizeof(RECT) );
				// delte old region data buffer
				delete pRgnData;
				// set pointer to new regiondata buffer to current
				pRgnData = (RGNDATAHEADER*)pRgnDataNew;
				// correct pointer to RECT table
				pRects = (LPRECT)((LPBYTE)pRgnData + RGNDATAHEADER_SIZE);
			}
			wasfirst = false;
		}

		pColor -= dwLineBackLen;
	}
	// release image data
	delete pBits;
	delete bi;

	// create region
	HRGN hRgn = ExtCreateRegion( NULL, RGNDATAHEADER_SIZE + pRgnData->nCount * sizeof(RECT), (LPRGNDATA)pRgnData );
	// release region data
	delete pRgnData;

	return hRgn;
}

/** 
 * 转换多字节到双字节
 *
 * @param str 要转换的字符串
 *
 * @return 返回转换好的字符串
 */
std::wstring CMole2dGameClientDlg::ConverToWideChar(const std::string& str)
{
	int  len = 0;

	len = str.length();

	int  unicodeLen = ::MultiByteToWideChar(CP_ACP,0,str.c_str(),-1,NULL,0); 

	wchar_t *  pUnicode; 
	pUnicode = new  wchar_t[unicodeLen+1]; 

	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t)); 

	::MultiByteToWideChar(CP_ACP,0,str.c_str(),-1,(LPWSTR)pUnicode,unicodeLen); 

	std::wstring  rt; 
	rt = ( wchar_t* )pUnicode;
	delete  pUnicode;

	return  rt;  
}

/** 
 * 转换双字节到多字节
 *
 * @param str 要转换的字符串
 *
 * @return 返回转换后的字符串
 */
std::string CMole2dGameClientDlg::ConverToMultiChar(const std::wstring& str)
{
	char* pElementText;

	int  iTextLen;

	// wide char to multi char
	iTextLen = WideCharToMultiByte( CP_ACP,
		0,
		str.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL );

	pElementText = new char[iTextLen + 1];

	memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );

	::WideCharToMultiByte( CP_ACP,
		0,
		str.c_str(),
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL );

	std::string strText;

	strText = pElementText;

	delete[] pElementText;

	return strText;
}

/// 显示连接提示
LRESULT CMole2dGameClientDlg::OnShowConnTip(WPARAM wparam, LPARAM lparam)
{
	int state = (int)wparam;

	if(state == 1)
		pConnStateDlg.ShowTip("正在获取在线玩家列表,请稍候...");
	else if(state == 2)
		pConnStateDlg.ShowTip("正在获取在线房间列表,请稍候...");
	else if(state == 3)
		pConnStateDlg.ShowTip("正在检测游戏平台更新,请稍候...");
	else if(state == 4)
		pConnStateDlg.ShowTip("正在获取所有游戏信息,请稍候...");
	else if(state == 5)
		pConnStateDlg.ShowTip("正在连接登录服务器,请稍候...");
	else if(state == 6)
		pConnStateDlg.ShowTip("正在连接游戏服务器,请稍候...");
	else
		pConnStateDlg.ShowWindow(SW_HIDE);

	if(pConnStateDlg.IsWindowVisible())
		EnableWindow(TRUE);
	else
		EnableWindow(FALSE);

	return 0;
}

/// 用户登录服务器
LRESULT CMole2dGameClientDlg::OnUserLogin(WPARAM wparam, LPARAM lparam)
{
	CString pUserName = (LPSTR)wparam;
	CString pPassword = (LPSTR)lparam;

	pUserLoginDlg.ShowWindow(SW_HIDE);
	m_UpdateState = UPDATESTATE_MAINFRAME;
	m_GameRoomManager.Clear();
	m_GameServerInfos.clear();
	
	// 开始连接服务器
	pGameFrameDlg.ConnectLoginServer(pUserName.GetBuffer(),pPassword.GetBuffer());

	return 0;
}

/// 游戏客户端返回的消息
LRESULT CMole2dGameClientDlg::OnGameFrameMes(WPARAM wparam, LPARAM lparam)
{
	switch(wparam)
	{
	case IDD_MESSAGE_GAME_LOGIN_FAIL:
	case IDD_MESSAGE_GAME_LOGIN_EXIST:
	case IDD_MESSAGE_GAME_LOGIN_FULL:
		{
			//pUserLoginDlg.ShowWindow(SW_SHOW);
			//pUserLoginDlg.SetCtrlFocus();
		}
		break;
	case IDD_MESSAGE_GAME_CENTER_LOGIN_FAIL:
		{
			pUserLoginDlg.ShowWindow(SW_SHOW);
			pUserLoginDlg.SetCtrlFocus();
		}
		break;
	default:
		break;
	}

	return 0;
}
void CMole2dGameClientDlg::OnBnClickedOk2()
{

}

/// 对比版本信息，检测是否更新
bool CMole2dGameClientDlg::IsUpdateVersion(std::string configfile)
{
	if(configfile.empty()) return false;

	TiXmlDocument doc;

	if(!doc.LoadFile(configfile.c_str()))
	{
		return false;
	}

	m_UpdateList.clear();

	TiXmlElement *UPDATEVERSION = doc.FirstChildElement("UPDATEVERSION");

	if(UPDATEVERSION)
	{
		// 得到更新版本
		m_UpdateVer = (float)atof(UPDATEVERSION->Attribute("ver"));
		serveraddress = UPDATEVERSION->Attribute("serveraddress");

		// 得到文件更新列表
		TiXmlElement *UPDATEFILE = UPDATEVERSION->FirstChildElement("UPDATEFILE");

		while(UPDATEFILE)
		{
			m_UpdateList.push_back(UPDATEFILE->Attribute("path"));

			UPDATEFILE = UPDATEFILE->NextSiblingElement();
		}
	}

	// 如果更新的文件个数为0，或者版本小于或等于服务器的版本，就不更新
	if(m_UpdateList.empty() || m_UpdateVer <= m_UpdataSet.ver)
	{
		return false;
	}

	return true;
}

/// 大厅更新消息
LRESULT CMole2dGameClientDlg::OnMainFrameUpdate(WPARAM wparam, LPARAM lparam)
{
	int state = (int)wparam;

	// 开始解析文件下载列表
	std::string filename = GetUpdateSet().address;		
	filename = filename.substr(filename.find_last_of("//")+1,filename.length());	

	if(state == 1)
	{
		if(IsUpdateVersion(filename))
		{
			if(m_UpdateState == UPDATESTATE_MAINFRAME)
			{
				// 启动下载模块，开始更新游戏
				m_DownloadDlg.ShowWindow(SW_SHOW);
				CString downaddress = GetCurrentProcessPath() + "clientconfig.ini";
				m_DownloadDlg.UpdateGame(downaddress.GetBuffer());

				DeleteFile(filename.c_str());
				AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,0,0);
				return 0;
			}
			else if(m_UpdateState == UPDATESTATE_GAME)
			{
				if(m_CurGameServerInfo != NULL)
				{
					// 如果存在就检测是否要更新
					// 启动下载模块，开始更新游戏
					m_DownloadDlg.ShowWindow(SW_SHOW);
					CString downaddress;
					downaddress.Format("%s%d\\gameconfig.ini",GetCurrentProcessPath(),m_CurGameServerInfo->GameId);
					m_DownloadDlg.UpdateGame(downaddress.GetBuffer());
				}
			}
		}
	}

	DeleteFile(filename.c_str());
	AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,0,0);
	EnableWindow(TRUE);

	if(m_UpdateState == UPDATESTATE_MAINFRAME)
	{
		pUserLoginDlg.ShowWindow(SW_SHOW);
		pUserLoginDlg.SetCtrlFocus();
	}
	else if(m_UpdateState == UPDATESTATE_GAME)
	{
		AfxGetMainWnd()->PostMessage(IDD_GAME_UPDATE,state,0);
	}

	return 0;
}

/**
 * 检测当前是否要保存用户名
 */
bool CMole2dGameClientDlg::IsRegisterPWD(void)
{
	TCHAR szProcessName[MAX_PATH]=TEXT("");
	GetModuleFileName(AfxGetInstanceHandle(),szProcessName,MAX_PATH);
	std::string tempStr = szProcessName;
	int pos = tempStr.find_last_of("\\");
	if(pos > 0) tempStr = tempStr.substr(0,pos+1);

	tempStr += "clientconfig.ini";

	char buf[1024];
	GetPrivateProfileString(TEXT("SystemSet"),TEXT("IsRegPWD"),"0",buf,1024,tempStr.c_str());
	
	return atoi(buf) > 0 ? true : false;
}

/**
 * 添加一个服务器到列表中
 */
void CMole2dGameClientDlg::AddGameServer(GameServerInfo gsf)
{
	std::map<int,std::vector<GameServerInfo> >::iterator iter = m_GameServerInfos.find(gsf.GameId);
	if(iter != m_GameServerInfos.end())
	{
		(*iter).second.push_back(gsf);
		m_GameRoomManager.InsertServerNode(gsf);
	}
	else
	{
		std::vector<GameServerInfo> tempInfos;
		tempInfos.push_back(gsf);

		m_GameServerInfos.insert(std::pair<int,std::vector<GameServerInfo> >(gsf.GameId,tempInfos));	

		m_GameRoomManager.InsertGameNode(gsf.GameId);
		m_GameRoomManager.InsertServerNode(gsf);
	}
}

//显示游戏服务器列表
LRESULT CMole2dGameClientDlg::OnShowGameServerList(WPARAM wparam, LPARAM lparam)
{
	int state = (int)wparam;

	switch(state)
	{
	case IDD_GET_GAME_RULE:
		{
			std::string ruleaddress = (char*)lparam;

			m_GameRoomManager.ShowWindow(SW_HIDE);

			if(!m_WebBrowser.GetSafeHwnd())
			{
				m_WebBrowser.Create(NULL,WS_CHILD,CRect(CPoint(16,183),CSize(710,435)),this,0);
			}

			m_WebBrowser.ShowWindow(SW_SHOW);
			m_WebBrowser.Navigate(ruleaddress.c_str(),NULL,NULL,NULL,NULL);			
		}
		break;
	case IDD_ENTER_GAME_SERVER:
		{
			m_CurGameServerInfo = (GameServerInfo*)lparam;
			if(m_CurGameServerInfo == NULL) return 0;

			CString gamePath;
			gamePath.Format("%s%d",GetCurrentProcessPath(),m_CurGameServerInfo->GameId);

			//首先检测这个文件是否存在
			WIN32_FIND_DATA   FindData;
			HANDLE   hFile   =   FindFirstFile(gamePath,&FindData);
			if(INVALID_HANDLE_VALUE == hFile)
			{
				int state = MMessageBox("当前游戏不存在，你确定要下载游戏吗？","游戏下载",MB_OKCANCEL);
				if(state == 1)
				{
					m_UpdateState = UPDATESTATE_GAME;

					EnableWindow(FALSE);

					// 启动下载模块，开始更新游戏
					m_DownloadDlg.ShowWindow(SW_SHOW);
					CString tempStr = CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "clientconfig.ini";
					char buf[1024];
					GetPrivateProfileString(TEXT("SystemSet"),TEXT("gamedownpage"),"0",buf,1024,tempStr.GetBuffer());
					CString downaddress;
					downaddress.Format("%s/%d/%d.zip",buf,m_CurGameServerInfo->GameId,m_CurGameServerInfo->GameId);					

					m_DownloadDlg.DownloadGame(downaddress.GetBuffer());
				}
			}
			else
			{
				m_UpdateState = UPDATESTATE_GAME;

				// 如果存在就检测是否要更新
				CString downaddress;
				downaddress.Format("%s%d\\gameconfig.ini",GetCurrentProcessPath(),m_CurGameServerInfo->GameId);
				UpdateGame(downaddress.GetBuffer());
			}
		}
		break;
	default:
		break;
	}

	return 0;
}

/// 游戏更新完成消息
LRESULT CMole2dGameClientDlg::OnGameUpdateFinish(WPARAM wparam, LPARAM lparam)
{
	if(m_UpdateState == UPDATESTATE_MAINFRAME)
	{
		AfxGetMainWnd()->SendMessage(IDD_EXIT_GAME,0,0);
	}
	else if(m_UpdateState == UPDATESTATE_GAME)
	{
		int state = (int)wparam;

		EnableWindow(TRUE);

		if(m_CurGameServerInfo && state == 1)
		{
			// 开始连接游戏服务器
			pGameFrameDlg.ConnectGameServer(m_CurGameServerInfo->ServerIP,m_CurGameServerInfo->ServerPort);
		}
		else
		{
			MMessageBox("游戏更新失败，请检查相关配置或联系工作人员！","游戏更新错误",MB_OK);
		}
	}

	return 0;
}

void CMole2dGameClientDlg::OnBnClickedReturnRoot()
{
	if(m_WebBrowser.GetSafeHwnd() && m_WebBrowser.IsWindowVisible())
		m_WebBrowser.ShowWindow(SW_HIDE);

	m_GameRoomManager.ShowMainGameNodes();
	m_GameRoomManager.ShowWindow(SW_SHOW);

	m_GameRoomManager.ClearCurSel();
}

void CMole2dGameClientDlg::OnBnClickedCancel()
{
	if(m_SwitchUserDlg.GetSafeHwnd())
		m_SwitchUserDlg.ShowWindow(SW_SHOW);

	EnableWindow(FALSE);
}

void CMole2dGameClientDlg::OnBnClickedBtnMin()
{
	ShowWindow(SW_SHOWMINIMIZED); 
}

void CMole2dGameClientDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect pRect,pDecRect;
	GetClientRect(pRect);
	pDecRect = CRect(0,0,pRect.Width(),36);

	if(pDecRect.PtInRect(point))
		SendMessage(WM_SYSCOMMAND,0xF012,0);

	CDialog::OnLButtonDown(nFlags, point);
}

void CMole2dGameClientDlg::OnBnClickedBtnHomepage()
{
	CString tempStr = CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "clientconfig.ini";

	char buf[1024];
	GetPrivateProfileString(TEXT("SystemSet"),TEXT("homepage"),"0",buf,1024,tempStr.GetBuffer());

	ShellExecute(NULL,TEXT("open"),buf,NULL,NULL,SW_SHOW);
}

void CMole2dGameClientDlg::OnBnClickedBtnChongZhi()
{
	CString tempStr = CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "clientconfig.ini";

	char buf[1024];
	GetPrivateProfileString(TEXT("SystemSet"),TEXT("chongzhipage"),"0",buf,1024,tempStr.GetBuffer());

	ShellExecute(NULL,TEXT("open"),buf,NULL,NULL,SW_SHOW);
}

void CMole2dGameClientDlg::OnBnClickedBtnBank()
{
	CString tempStr = CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "clientconfig.ini";

	char buf[1024];
	GetPrivateProfileString(TEXT("SystemSet"),TEXT("bankpage"),"0",buf,1024,tempStr.GetBuffer());

	m_GameRoomManager.ShowWindow(SW_HIDE);

	if(!m_WebBrowser.GetSafeHwnd())
	{
		m_WebBrowser.Create(NULL,WS_CHILD,CRect(CPoint(16,183),CSize(710,435)),this,0);
	}

	m_WebBrowser.ShowWindow(SW_SHOW);
	m_WebBrowser.Navigate(buf,NULL,NULL,NULL,NULL);
}

void CMole2dGameClientDlg::OnBnClickedBtnKeHu()
{
	CString tempStr = CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "clientconfig.ini";

	char buf[1024];
	GetPrivateProfileString(TEXT("SystemSet"),TEXT("servicepage"),"0",buf,1024,tempStr.GetBuffer());

	ShellExecute(NULL,TEXT("open"),buf,NULL,NULL,SW_SHOW);
}

