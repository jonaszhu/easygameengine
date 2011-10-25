// MolServerDlg.h : ͷ�ļ�
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

// CMolServerDlg �Ի���
class CMolServerDlg : public CDialog , public Singleton<CMolServerDlg>
{
// ����
public:
	CMolServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CMolServerDlg();

	/// �õ������������ļ�
	inline ServerSet* GetServerSet(void) { return &m_ServerSet; }
	/// ��������������ļ�
	bool LoadServerConfig(std::string filepath);
	/// ��������������ļ�
	void SaveServerConfig(std::string filepath="");
	/// ������Ϸ������
	void StartGameRobots(void);
	/// �������Է�����
	void StartDebugServer(void);
	/// ���µ��벢ִ�нű�
	void ReLoadAndRunScript(void);
	/// ��ӡ������������־
	void PrintLog(std::string log);
	/// ��⵱ǰ�Ƿ��Ѿ�ע��
	bool IsRegistered(void);
	/// �õ���ǰ�����������������
	inline int GetMaxOnlinePlayers(void) { return m_maxPlayerCount; }

	/// ������յ�������Ϣ
	void OnProcessNetMessage(ConnectState state,CMolMessageIn &msg);

private:
	/// ��ʼMolCrashRpt
	void InitMolCrashRpt(void);
	/// �õ�ϵͳʱ��
	DWORD GetTickCountEx(void);
	/// ��������������ļ�
	void LoadRobotConfig(void);
	/// ������Ϸ������
	void StartServer(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CTrayIcon	 m_TrayIcon;						//������ͼ��
	CEdit        m_logEdit;                         /**< ��ӡ��־ */

	ServerSet    m_ServerSet;                       /**< ���������� */
	CMolTcpSocketClient m_CenterServer;             /**< �����������ķ����� */
	int          m_curPlayerCount;                  /**< ��ǰ������� */
	bool         m_isStartSuc;                      /**< �Ƿ������ɹ� */
	std::string  m_curGameConfigFile;               /**< ��ǰ��������Ϸ�����ļ� */
	char         m_ProcessDir[256];                 /**< ��ǰ����·�� */

	CRegisterKey  m_RegisterKey;                    /**< ���ڲ������ݿ� */
	bool          m_isRegistered;                   /**< �Ƿ��Ѿ�ע�� */
	int           m_maxPlayerCount;                 /**< ����������� */

	CAsyncSocketFile *m_ServerSocket;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
