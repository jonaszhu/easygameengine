#pragma once

#include <vector>
#include <string>

#define WM_STOP 1023

/** 
* ���ڴ洢���µ�����
*/
struct UpdataSetTwo
{
	UpdataSetTwo()
		: ver(0)
	{}
	UpdataSetTwo(float v,std::string a)
		: ver(v),address(a)
	{}

	float ver;             // ��ǰ����汾
	std::string address; // ��ǰ���µķ�����
	std::string curDownloadFile;      // ��ǰ�����ļ�
	int curFileIndex;         // ��ǰ�ļ�����
	int totalFileCount;       // �ܵ��ļ�����
};

// CDownloadDlg �Ի���

class CDownloadDlg : public CDialog
{
	DECLARE_DYNAMIC(CDownloadDlg)

public:
	CDownloadDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDownloadDlg();

	/// �õ���ǰ���ص�����
	inline UpdataSetTwo GetUpdateSet(void) { return m_UpdataSet; }
	/// ����ָ����ַ���ļ���ָ����Ŀ¼��
	bool DownloadSingleFile(std::string file,std::string path="");
	/// ���ݷ��������صĸ��������ļ��õ�Ҫ���µ��ļ��б�
	bool GetUpdateFileList(std::string config);
	/// ���ݿͻ��������ļ��ӷ�����������Ϸ
	void UpdateGame(std::string configfile);
	/// ������Ϸ
	void DownloadGame(std::string configfile);
	/// ������ʾ��ʾ
	inline void SetTip(CString tip) 
	{ 
		m_ShowTip = tip; 

		InvalidateRect(CRect(CPoint(6,44),CSize(360,30)),FALSE);
	}
	/// �õ���ʾ��ʾ
	inline CString GetTip(void) { return m_ShowTip; }
	/// ���ؽ��ȸ���
	virtual int OnProcessFileDownload(double dt, double dn, double ut, double un); 

// �Ի�������
	enum { IDD = IDD_DLG_DOWNLOAD };

private:
	HRGN CreateRgnFromFile( HBITMAP hBmp, COLORREF color );
	/// �����ļ�·����������Ӧ��Ŀ¼
	void CreateDirectionByPath(std::string filename);
	/// ��Ϸ���º���
	static unsigned __stdcall ThreadGameUpdate(void * pParam);
	/// ��Ϸ���غ���
	static unsigned __stdcall ThreadGameDownload(void * pParam);
	/// curl ʹ�õ����ؽ��ȸ��º���
	static int UpdateProgress(void *ptr,double dt, double dn, double ut, double un);
	/// ��ѹzip�ļ�
	bool unzip(std::string zipfile,std::string decpath="");

private:
	int m_dwWidth,m_dwHeight;
	UpdataSetTwo m_UpdataSet;
	float m_UpdateVer;
	std::string serveraddress;  // ���·�������ַ
	std::string m_UpdateConfigFile;
	HANDLE                     m_UpdateThread;                    
	unsigned                   m_UpdateThreadID;
	char                       *m_CurlError;                      /**< �洢curl�����Ĵ�����Ϣ */
	std::vector<std::string>   m_UpdateList;                      /**< Ҫ���µ��ļ��б� */
	CImage m_bgImage;
	CString                    m_ShowTip;                         // ��ʾ��ʾ

private:
	CProgressCtrl m_fileCountProCtl,m_fileProcCtl;

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
