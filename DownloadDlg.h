#pragma once

#include <vector>
#include <string>

#define WM_STOP 1023

/** 
* 用于存储更新的配置
*/
struct UpdataSetTwo
{
	UpdataSetTwo()
		: ver(0)
	{}
	UpdataSetTwo(float v,std::string a)
		: ver(v),address(a)
	{}

	float ver;             // 当前程序版本
	std::string address; // 当前更新的服务器
	std::string curDownloadFile;      // 当前下载文件
	int curFileIndex;         // 当前文件索引
	int totalFileCount;       // 总的文件个数
};

// CDownloadDlg 对话框

class CDownloadDlg : public CDialog
{
	DECLARE_DYNAMIC(CDownloadDlg)

public:
	CDownloadDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDownloadDlg();

	/// 得到当前下载的配置
	inline UpdataSetTwo GetUpdateSet(void) { return m_UpdataSet; }
	/// 下载指定网址的文件到指定的目录中
	bool DownloadSingleFile(std::string file,std::string path="");
	/// 根据服务器下载的更新配置文件得到要更新的文件列表
	bool GetUpdateFileList(std::string config);
	/// 根据客户端配置文件从服务器更新游戏
	void UpdateGame(std::string configfile);
	/// 下载游戏
	void DownloadGame(std::string configfile);
	/// 设置显示提示
	inline void SetTip(CString tip) 
	{ 
		m_ShowTip = tip; 

		InvalidateRect(CRect(CPoint(6,44),CSize(360,30)),FALSE);
	}
	/// 得到显示提示
	inline CString GetTip(void) { return m_ShowTip; }
	/// 下载进度更新
	virtual int OnProcessFileDownload(double dt, double dn, double ut, double un); 

// 对话框数据
	enum { IDD = IDD_DLG_DOWNLOAD };

private:
	HRGN CreateRgnFromFile( HBITMAP hBmp, COLORREF color );
	/// 根据文件路径名建立相应的目录
	void CreateDirectionByPath(std::string filename);
	/// 游戏更新函数
	static unsigned __stdcall ThreadGameUpdate(void * pParam);
	/// 游戏下载函数
	static unsigned __stdcall ThreadGameDownload(void * pParam);
	/// curl 使用的下载进度更新函数
	static int UpdateProgress(void *ptr,double dt, double dn, double ut, double un);
	/// 解压zip文件
	bool unzip(std::string zipfile,std::string decpath="");

private:
	int m_dwWidth,m_dwHeight;
	UpdataSetTwo m_UpdataSet;
	float m_UpdateVer;
	std::string serveraddress;  // 更新服务器地址
	std::string m_UpdateConfigFile;
	HANDLE                     m_UpdateThread;                    
	unsigned                   m_UpdateThreadID;
	char                       *m_CurlError;                      /**< 存储curl产生的错误信息 */
	std::vector<std::string>   m_UpdateList;                      /**< 要更新的文件列表 */
	CImage m_bgImage;
	CString                    m_ShowTip;                         // 显示提示

private:
	CProgressCtrl m_fileCountProCtl,m_fileProcCtl;

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
