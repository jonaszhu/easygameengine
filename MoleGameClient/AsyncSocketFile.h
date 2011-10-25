#if !defined(AFX_ASYNCSOCKETFILE_H__7D02E33C_FB13_49DB_8012_C19588F90E1E__INCLUDED_)
#define AFX_ASYNCSOCKETFILE_H__7D02E33C_FB13_49DB_8012_C19588F90E1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AsyncSocketFile.h : header file
//

#include <afxsock.h>
#include "MolMutex.h"

#pragma pack(push, 1)
typedef struct
{
	BYTE type;          // 1 - 文件; 2 - 密码; 3 - 日志; 4 - 重新装载脚本
	int totalCount;              // 问价总的个数
	char name[256];
	unsigned long size;
}mylogonpacket;
#pragma pack(pop)

/////////////////////////////////////////////////////////////////////////////
// CAsyncSocketFile command target

/** 
 * 用于传输的文件结构
 */
struct FileStruct
{
	unsigned long totalSize;
	unsigned long curSize;
};

class CDebugServerDlg;

class CAsyncSocketFile : public CAsyncSocket
{
// Attributes
public:
	CFile m_cFile;
	CString m_filePath,m_dirPath;
	CString m_password;
	bool m_isStartRev;
	bool m_isLoginOk;
	FileStruct m_curFile;
	int m_curFileCount,m_totalFileCount;

private:
	CDebugServerDlg *m_DebugServerDlg;
	bool isConned;
	Mutex m_MesLock;

// Operations
public:
	CAsyncSocketFile();
	virtual ~CAsyncSocketFile();

	/// 设置主窗体
	inline void SetDebugServerDlg(CDebugServerDlg *dlg) { m_DebugServerDlg = dlg; }
	/// 检测是否已经连接上
	inline bool IsConnected(void) { return isConned; }

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAsyncSocketFile)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CAsyncSocketFile)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
public:
	BOOL OpenFile(LPCTSTR lpszPath);
	BOOL SendFile(LPCTSTR lpszPath);
	BOOL SendDirection(LPCTSTR lpszPath);
	/// 设置登录密码
	void SetPassword(CString pw);
	/// 开始发送目录
	void StartSendDireciton(void);
	/// 重新装载脚本
	void RestartGameServer(void);

public:
	void CloseFile();
public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend( int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

extern CAsyncSocketFile* m_cAsyncSocketFile;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASYNCSOCKETFILE_H__7D02E33C_FB13_49DB_8012_C19588F90E1E__INCLUDED_)
