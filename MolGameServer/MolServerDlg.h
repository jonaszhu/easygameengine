// MolServerDlg.h : 头文件
//

#pragma once

#include "TrayIcon.h"

#include "MolServerCom.h"
#include "MolMesDistributer.h"
#include "Mole2dTcpSocketClient.h"
#include "MolServerSetDlg.h"

#include "Mole2dLogger.h"
#include "RegisterKey.h"

#include <string>

#define IDM_TRAY_NOTIFY_MSG (WM_USER +13)
#define IDD_SENDMAIL_TIMER 100
#define IDD_SENDHEART_TIMER 101
#define IDD_HEARTPROCESS_TIMER 102
#define IDD_ROOMTIMER_TIMER 103
#define IDD_CENTER_SERVER_UPDATE 104
#define IDD_START_ROBOT_TIMER 105

#define IDD_SERVER_CONFIG_FILE "resources\\serverconfig.xml"
#define IDD_ROBOT_CONFIG_FILE "resources\\robtoconfig.xml"

class CAsyncSocketFile;

// CMolServerDlg 对话框
class CMolServerDlg : public CDialog , public Singleton<CMolServerDlg>
{
// 构造
public:
	CMolServerDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CMolServerDlg();

	/// 得到服务器配置文件
	inline ServerSet* GetServerSet(void) { return &m_ServerSet; }
	/// 导入服务器配置文件
	bool LoadServerConfig(std::string filepath);
	/// 保存服务器配置文件
	void SaveServerConfig(std::string filepath="");
	/// 开启游戏机器人
	void StartGameRobots(void);
	/// 开启调试服务器
	void StartDebugServer(void);
	/// 重新导入并执行脚本
	void ReLoadAndRunScript(void);
	/// 打印服务器工作日志
	void PrintLog(std::string log);
	/// 检测当前是否已经注册
	bool IsRegistered(void);
	/// 得到当前服务器最大在线人数
	inline int GetMaxOnlinePlayers(void) { return m_maxPlayerCount; }

	/// 处理接收到网络消息
	void OnProcessNetMessage(ConnectState state,CMolMessageIn &msg);

private:
	/// 初始MolCrashRpt
	void InitMolCrashRpt(void);
	/// 得到系统时间
	DWORD GetTickCountEx(void);
	/// 导入机器人配置文件
	void LoadRobotConfig(void);
	/// 启动游戏服务器
	void StartServer(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	CTrayIcon	 m_TrayIcon;						//任务栏图标
	CEdit        m_logEdit;                         /**< 打印日志 */

	ServerSet    m_ServerSet;                       /**< 服务器设置 */
	CMolTcpSocketClient m_CenterServer;             /**< 用于连接中心服务器 */
	int          m_curPlayerCount;                  /**< 当前玩家人数 */
	bool         m_isStartSuc;                      /**< 是否启动成功 */
	std::string  m_curGameConfigFile;               /**< 当前操作的游戏配置文件 */
	char         m_ProcessDir[256];                 /**< 当前程序路径 */

	CRegisterKey  m_RegisterKey;                    /**< 用于操作数据库 */
	bool          m_isRegistered;                   /**< 是否已经注册 */
	int           m_maxPlayerCount;                 /**< 最大在线人数 */

	CAsyncSocketFile *m_ServerSocket;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	LRESULT OnTrayIconNotify(WPARAM wID, LPARAM lEvent);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnStartServer();
	afx_msg void OnStopServer();
	afx_msg void OnReloadScript();
	afx_msg void OnServerSet();
	afx_msg void OnClearLog();
	afx_msg void OnCloseServer();
	afx_msg void OnBnClickedBtnStartServer2();
	afx_msg void OnMolserver32784();
	afx_msg void OnBnClickedBtnGetRobotID();
	afx_msg void OnBnClickedBtnRegister();
	afx_msg void OnBnClickedBtnCreateRoom();
};
