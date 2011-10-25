// Mole2dGameClientDlg.h : ͷ�ļ�
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

#define IDD_HOTKEY_DEBUGSERVER 1688               // ���ڲ������������Կ���̨

//#define MOLE2D_DOWNLOAD_TEMP_FILE "download.tmp"
#define WM_STOP 1023
#define IDD_MAINFRAME_UPDATE  WM_USER+2000                      // ����������Ϣ
#define IDD_GAME_UPDATE       WM_USER+2001                      // ��Ϸ���������Ϣ
#define IDD_GAMEFRAM_MESSAGEBOX WM_USER+2002                    // ��Ϸ�Ի���

int StringReplace(std::string&   src_str,   const   std::string&   old_str,   const   std::string&   new_str); 

/** 
* ���ڴ洢���µ�����
*/
struct UpdataSet
{
	UpdataSet()
		: ver(0)
	{}
	UpdataSet(float v,std::string a)
		: ver(v),address(a)
	{}

	float ver;             // ��ǰ����汾
	std::string address; // ��ǰ���µķ�����
	std::string curDownloadFile;      // ��ǰ�����ļ�
	int curFileIndex;         // ��ǰ�ļ�����
	int totalFileCount;       // �ܵ��ļ�����
};

/** 
 * ��ǰ����״̬
 */
enum UpdateState
{
	UPDATESTATE_MAINFRAME = 0,         // ���´���
	UPDATESTATE_GAME,                  // ������Ϸ
	UPDATESTATE_NULL
};

// CMole2dGameClientDlg �Ի���
class CMole2dGameClientDlg : public CDialog , public Singleton<CMole2dGameClientDlg>
{
// ����
public:
	CMole2dGameClientDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CMole2dGameClientDlg();

	/// ��ʾ������
	void ShowMainFrame(void);
	/// �õ���ǰ���ص�����
	inline UpdataSet GetUpdateSet(void) { return m_UpdataSet; }
	/// �õ���ǰ����״̬
	inline UpdateState GetCurUpdateState(void) { return m_UpdateState; }
	/// ��⵱ǰ�Ƿ�Ҫ�����û���
	bool IsRegisterPWD(void);
	/// �õ���ǰ��������·��
	CString GetCurrentProcessPath(void);
	/// ˢ���û���Ϣ
	void RefreshMyselfInfo(void);
	/// �����û��Լ�����Ϣ
	void SetMySelfInfo(Player* pPlayer);
	/// ת��˫�ֽڵ����ֽ�
	std::string ConverToMultiChar(const std::wstring& str);
	/// ת�����ֽڵ�˫�ֽ�
	std::wstring ConverToWideChar(const std::string& str);
	/// ���õ�ǰ����Ϸ��������
	inline void SetCurServerOnlinePlayers(int count) { if(m_CurGameServerInfo) m_CurGameServerInfo->OnlinePlayerCount = count; }
	/// �õ��û�ע����
	inline CString GetRegisterUserName(void) { return pGameFrameDlg.ReadRegisterKey("MOLEUSERNAME").c_str(); }
	/// ��ȡ��ǰ������Ϸ��������Ϣ
	inline GameServerInfo* GetCurrentGameServer(void) { return m_CurGameServerInfo; }

	/// ���һ�����������б���
	void AddGameServer(GameServerInfo gsf);

// �Ի�������
	enum { IDD = IDD_MOLE2DGAMECLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	/// ����ָ����ַ���ļ���ָ����Ŀ¼��
	bool DownloadSingleFile(std::string file,std::string path="");
	/// curl ʹ�õ����ؽ��ȸ��º���
	static int UpdateProgress(void *ptr,double dt, double dn, double ut, double un);
	/// �����ļ�·����������Ӧ��Ŀ¼
	void CreateDirectionByPath(std::string filename);
	/// ���ݿͻ��������ļ��ӷ�����������Ϸ
	void UpdateGame(std::string configfile);
	/// �ԱȰ汾��Ϣ������Ƿ����
	bool IsUpdateVersion(std::string configfile);
	/// ��Ϸ���º���
	static unsigned __stdcall ThreadGameUpdate(void * pParam);

	//��������
	void DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos);
	//��������
	void DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, LPRECT lpRect);

private:
	CDebugServerDlg pDebugServerDlg;            /**< ����������̨ */
	CUserLoginDlg pUserLoginDlg;                /**< �û���¼�Ի��� */
	CMole2dGameFrameDlg pGameFrameDlg;          /**< ��Ϸ�����Ի��� */
	CConnStateDlg pConnStateDlg;                /**< ������ʾ�Ի��� */
	CGameRoomManager m_GameRoomManager;         /**< ���ڹ������е���Ϸ�б� */
	CSwitchUserDlg m_SwitchUserDlg; 
	CWebBrowser2 m_WebBrowser;                  /**< ��Ϸ���õ�����ҳ����� */
	CDownloadDlg m_DownloadDlg;                 /**< ��Ϸ������ */

	HANDLE                     m_UpdateThread;                    
	unsigned                   m_UpdateThreadID;

	Player m_myselft;                          /**< ���ڱ��������Ϣ */

	UpdataSet m_UpdataSet;
	float m_UpdateVer;
	std::string m_UpdateConfigFile;
	UpdateState m_UpdateState;                                    /**< ��ǰ����״̬ */
	std::string serveraddress;  // ���·�������ַ
	GameServerInfo             *m_CurGameServerInfo;               /**< ��ǰҪ�������Ϸ */
	char                       *m_CurlError;                      /**< �洢curl�����Ĵ�����Ϣ */
	std::vector<std::string>   m_UpdateList;                      /**< Ҫ���µ��ļ��б� */
	std::map<int,std::vector<GameServerInfo> > m_GameServerInfos;                /**< ���ڴ洢��Ϸ��������Ϣ */

	CImage m_bgImg;                             /**< ����ͼƬ */
	CSkinButton m_btnMin,m_btnExit;             /**< ��С����ť */
	CSkinButton m_btnReturnRoot;                /**< ���ش��� */

	CSkinButton m_btnHomePage,m_btnChongZhi,m_btnBank,m_btnKeHu;                  

	CImage m_userLogoImg;                       /**< �û�ͷ��ͼƬ */
	CString m_userName;                         /**< �û��� */
	int m_userLevel;                            /**< �û��ȼ� */
	__int64 m_userMoney;                        /**< �û���� */

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	/// �ر���Ϸ
	LRESULT	OnCloseGame(WPARAM wparam, LPARAM lparam);
	/// �˳���Ϸ
	LRESULT OnExitGame(WPARAM wparam, LPARAM lparam);
	/// ���µ�¼��Ϸ
	LRESULT OnReEnterGame(WPARAM wparam, LPARAM lparam);
	/// �û���¼������
	LRESULT OnUserLogin(WPARAM wparam, LPARAM lparam);
	/// ��ʾ������ʾ
	LRESULT OnShowConnTip(WPARAM wparam, LPARAM lparam);
	/// ��Ϸ�ͻ��˷��ص���Ϣ
	LRESULT OnGameFrameMes(WPARAM wparam, LPARAM lparam);
	/// ����������Ϣ
	LRESULT OnMainFrameUpdate(WPARAM wparam, LPARAM lparam);
	/// ��Ϸ���������Ϣ
	LRESULT OnGameUpdateFinish(WPARAM wparam, LPARAM lparam);
	//��ʾ��Ϸ�������б�
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
