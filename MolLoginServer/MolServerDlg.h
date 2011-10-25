// MolServerDlg.h : ͷ�ļ�
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
	void SaveServerConfig(void);
	/// ��ӡ������������־
	void PrintLog(std::string log);

private:
	/// ��ʼMolCrashRpt
	void InitMolCrashRpt(void);
	/// ������Ϸ������
	void StartServer(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CTrayIcon	 m_TrayIcon;						//������ͼ��
	CEdit        m_logEdit;                         /**< ��ӡ��־ */

	ServerSet    m_ServerSet;                       /**< ���������� */
	std::string  m_curGameConfigFile;               /**< ��ǰ��������Ϸ�����ļ� */
	char         m_ProcessDir[256];                 /**< ��ǰ����·�� */

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
	//afx_msg void OnReloadScript();
	afx_msg void OnServerSet();
	afx_msg void OnClearLog();
	afx_msg void OnCloseServer();
	afx_msg void OnBnClickedBtnStartServer2();
	afx_msg void OnMolserver32784();
};
