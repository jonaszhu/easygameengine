// MolServerDlg.h : 头文件
//

#pragma once

#include "TrayIcon.h"

#include "MolServerCom.h"
#include "MolMesDistributer.h"
#include "MolServerSetDlg.h"

#include "Mole2dLogger.h"

#include <string>
#include <map>

#define IDM_TRAY_NOTIFY_MSG (WM_USER +13)

#define IDD_SERVER_CONFIG_FILE "resources\\serverconfig.xml"

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
	void SaveServerConfig(void);
	/// 打印服务器工作日志
	void PrintLog(std::string log);

private:
	/// 初始MolCrashRpt
	void InitMolCrashRpt(void);
	/// 启动游戏服务器
	void StartServer(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	CTrayIcon	 m_TrayIcon;						//任务栏图标
	CEdit        m_logEdit;                         /**< 打印日志 */

	ServerSet    m_ServerSet;                       /**< 服务器设置 */
	std::string  m_curGameConfigFile;               /**< 当前操作的游戏配置文件 */
	char         m_ProcessDir[256];                 /**< 当前程序路径 */

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
	//afx_msg void OnReloadScript();
	afx_msg void OnServerSet();
	afx_msg void OnClearLog();
	afx_msg void OnCloseServer();
	afx_msg void OnBnClickedBtnStartServer2();
	afx_msg void OnMolserver32784();
};
