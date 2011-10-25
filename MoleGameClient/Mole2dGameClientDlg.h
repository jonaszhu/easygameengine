// Mole2dGameClientDlg.h : 头文件
//

#pragma once

#include "DebugServerDlg.h"
#include "UserLoginDlg.h"
#include "ConnStateDlg.h"
#include "MoleGameFrameDlg.h"
#include "DownloadDlg.h"
#include "defines.h"
#include "MoleGameServerManger.h"
#include "SwitchUserDlg.h"
#include "MolSingleton.h"
#include "CWebBrowser2.h"

#define IDD_HOTKEY_DEBUGSERVER 1688               // 用于操作服务器调试控制台

//#define MOLE2D_DOWNLOAD_TEMP_FILE "download.tmp"
#define WM_STOP 1023
#define IDD_MAINFRAME_UPDATE  WM_USER+2000                      // 大厅更新消息
#define IDD_GAME_UPDATE       WM_USER+2001                      // 游戏更新完成消息
#define IDD_GAMEFRAM_MESSAGEBOX WM_USER+2002                    // 游戏对话框

int StringReplace(std::string&   src_str,   const   std::string&   old_str,   const   std::string&   new_str); 

/** 
* 用于存储更新的配置
*/
struct UpdataSet
{
	UpdataSet()
		: ver(0)
	{}
	UpdataSet(float v,std::string a)
		: ver(v),address(a)
	{}

	float ver;             // 当前程序版本
	std::string address; // 当前更新的服务器
	std::string curDownloadFile;      // 当前下载文件
	int curFileIndex;         // 当前文件索引
	int totalFileCount;       // 总的文件个数
};

/** 
 * 当前更新状态
 */
enum UpdateState
{
	UPDATESTATE_MAINFRAME = 0,         // 更新大厅
	UPDATESTATE_GAME,                  // 更新游戏
	UPDATESTATE_NULL
};

// CMole2dGameClientDlg 对话框
class CMole2dGameClientDlg : public CDialog , public Singleton<CMole2dGameClientDlg>
{
// 构造
public:
	CMole2dGameClientDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CMole2dGameClientDlg();

	/// 显示主窗口
	void ShowMainFrame(void);
	/// 得到当前下载的配置
	inline UpdataSet GetUpdateSet(void) { return m_UpdataSet; }
	/// 得到当前操作状态
	inline UpdateState GetCurUpdateState(void) { return m_UpdateState; }
	/// 检测当前是否要保存用户名
	bool IsRegisterPWD(void);
	/// 得到当前程序所在路径
	CString GetCurrentProcessPath(void);
	/// 刷新用户信息
	void RefreshMyselfInfo(void);
	/// 设置用户自己的信息
	void SetMySelfInfo(Player* pPlayer);
	/// 转换双字节到多字节
	std::string ConverToMultiChar(const std::wstring& str);
	/// 转换多字节到双字节
	std::wstring ConverToWideChar(const std::string& str);
	/// 设置当前打开游戏在线人数
	inline void SetCurServerOnlinePlayers(int count) { if(m_CurGameServerInfo) m_CurGameServerInfo->OnlinePlayerCount = count; }
	/// 得到用户注册名
	inline CString GetRegisterUserName(void) { return pGameFrameDlg.ReadRegisterKey("MOLEUSERNAME").c_str(); }
	/// 获取当前进入游戏服务器信息
	inline GameServerInfo* GetCurrentGameServer(void) { return m_CurGameServerInfo; }

	/// 添加一个服务器到列表中
	void AddGameServer(GameServerInfo gsf);

// 对话框数据
	enum { IDD = IDD_MOLE2DGAMECLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	/// 下载指定网址的文件到指定的目录中
	bool DownloadSingleFile(std::string file,std::string path="");
	/// curl 使用的下载进度更新函数
	static int UpdateProgress(void *ptr,double dt, double dn, double ut, double un);
	/// 根据文件路径名建立相应的目录
	void CreateDirectionByPath(std::string filename);
	/// 根据客户端配置文件从服务器更新游戏
	void UpdateGame(std::string configfile);
	/// 对比版本信息，检测是否更新
	bool IsUpdateVersion(std::string configfile);
	/// 游戏更新函数
	static unsigned __stdcall ThreadGameUpdate(void * pParam);

	//艺术字体
	void DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos);
	//艺术字体
	void DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, LPRECT lpRect);

private:
	CDebugServerDlg pDebugServerDlg;            /**< 服务器控制台 */
	CUserLoginDlg pUserLoginDlg;                /**< 用户登录对话框 */
	CMole2dGameFrameDlg pGameFrameDlg;          /**< 游戏操作对话框 */
	CConnStateDlg pConnStateDlg;                /**< 连接提示对话框 */
	CGameRoomManager m_GameRoomManager;         /**< 用于管理所有的游戏列表 */
	CSwitchUserDlg m_SwitchUserDlg; 
	CWebBrowser2 m_WebBrowser;                  /**< 游戏中用到的网页浏览器 */
	CDownloadDlg m_DownloadDlg;                 /**< 游戏下载器 */

	HANDLE                     m_UpdateThread;                    
	unsigned                   m_UpdateThreadID;

	Player m_myselft;                          /**< 用于保存玩家信息 */

	UpdataSet m_UpdataSet;
	float m_UpdateVer;
	std::string m_UpdateConfigFile;
	UpdateState m_UpdateState;                                    /**< 当前更新状态 */
	std::string serveraddress;  // 更新服务器地址
	GameServerInfo             *m_CurGameServerInfo;               /**< 当前要进入的游戏 */
	char                       *m_CurlError;                      /**< 存储curl产生的错误信息 */
	std::vector<std::string>   m_UpdateList;                      /**< 要更新的文件列表 */
	std::map<int,std::vector<GameServerInfo> > m_GameServerInfos;                /**< 用于存储游戏服务器信息 */

	CImage m_bgImg;                             /**< 背景图片 */
	CSkinButton m_btnMin,m_btnExit;             /**< 最小化按钮 */
	CSkinButton m_btnReturnRoot;                /**< 返回大厅 */

	CSkinButton m_btnHomePage,m_btnChongZhi,m_btnBank,m_btnKeHu;                  

	CImage m_userLogoImg;                       /**< 用户头像图片 */
	CString m_userName;                         /**< 用户名 */
	int m_userLevel;                            /**< 用户等级 */
	__int64 m_userMoney;                        /**< 用户金币 */

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnHotHey(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNcPaint();
	/// 关闭游戏
	LRESULT	OnCloseGame(WPARAM wparam, LPARAM lparam);
	/// 退出游戏
	LRESULT OnExitGame(WPARAM wparam, LPARAM lparam);
	/// 重新登录游戏
	LRESULT OnReEnterGame(WPARAM wparam, LPARAM lparam);
	/// 用户登录服务器
	LRESULT OnUserLogin(WPARAM wparam, LPARAM lparam);
	/// 显示连接提示
	LRESULT OnShowConnTip(WPARAM wparam, LPARAM lparam);
	/// 游戏客户端返回的消息
	LRESULT OnGameFrameMes(WPARAM wparam, LPARAM lparam);
	/// 大厅更新消息
	LRESULT OnMainFrameUpdate(WPARAM wparam, LPARAM lparam);
	/// 游戏更新完成消息
	LRESULT OnGameUpdateFinish(WPARAM wparam, LPARAM lparam);
	//显示游戏服务器列表
	afx_msg LRESULT OnShowGameServerList(WPARAM wparam, LPARAM lparam);
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedReturnRoot();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnMin();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnHomepage();
	afx_msg void OnBnClickedBtnChongZhi();
	afx_msg void OnBnClickedBtnBank();
	afx_msg void OnBnClickedBtnKeHu();

	DWORD m_dwWidth;		// mask width
	DWORD m_dwHeight;		// mask height

private:
	HRGN CreateRgnFromFile( HBITMAP hBmp, COLORREF color );
};
