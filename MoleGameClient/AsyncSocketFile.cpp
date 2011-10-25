// AsyncSocketFile.cpp : implementation file
//

#include "stdafx.h"
#include  <algorithm> 
#include "AsyncSocketFile.h"

#include "DebugServerDlg.h"

#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CAsyncSocketFile* m_cAsyncSocketFile = NULL;

/////////////////////////////////////////////////////////////////////////////
// CAsyncSocketFile

CAsyncSocketFile::CAsyncSocketFile()
{
	//m_cAsyncSocketFile = NULL;
	m_isStartRev = false;
	m_isLoginOk = false;
	m_DebugServerDlg = NULL;
	m_curFileCount = 0;
	m_totalFileCount = 0;
	isConned = false;
}

CAsyncSocketFile::~CAsyncSocketFile()
{
	//if( m_cAsyncSocketFile != NULL )
	//{
	//	m_cAsyncSocketFile->Close();
	//	//m_cAsyncSocketFile->CloseFile();
	//	delete m_cAsyncSocketFile;
	//	m_cAsyncSocketFile = NULL;
	//}
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CAsyncSocketFile, CAsyncSocket)
	//{{AFX_MSG_MAP(CAsyncSocketFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CAsyncSocketFile member functions

void CAsyncSocketFile::OnReceive(int nErrorCode) 
{
	if(m_DebugServerDlg == NULL) return;

	m_MesLock.Acquire();
	if(!m_isStartRev)
	{
		mylogonpacket plogonpacket;
		int recv = Receive( &plogonpacket, sizeof(plogonpacket) );
		if(recv != sizeof(plogonpacket))
		{
			//m_cFile.Close();
			m_isStartRev = false;
			CAsyncSocket::OnReceive(nErrorCode);
			m_MesLock.Release();
			return;
		}

		switch(plogonpacket.type)
		{
		case 1:
			{
				m_isStartRev = true;

				m_totalFileCount = plogonpacket.totalCount;
				m_curFile.totalSize = plogonpacket.size;
				m_curFile.curSize = 0;

				CString lpszPath;
				lpszPath.Format("%s\\%s",m_filePath.GetBuffer(),plogonpacket.name);
				m_cFile.Open( lpszPath.GetBuffer(), CFile::modeCreate | CFile::modeWrite );

				CString tempStr;
				tempStr.Format("【系统】 从游戏服务器获取文件:%s。",plogonpacket.name);
				m_DebugServerDlg->PrintLog(tempStr.GetBuffer());				
			}
			break;
		case 2:
			{
				CAsyncSocket::OnReceive(nErrorCode);
				m_MesLock.Release();
				return;
			}
			break;
		case 3:
			{
				CString tempStr;
				tempStr.Format("【游戏】 %s。",plogonpacket.name);
				m_DebugServerDlg->PrintLog(tempStr.GetBuffer());

				CAsyncSocket::OnReceive(nErrorCode);
				m_MesLock.Release();
				return;
			}
			break;
		default:
			{
				//m_cFile.Close();
				m_isStartRev = false;

				if(m_DebugServerDlg->GetDlgItem(ID_BTN_CLOSE)->IsWindowEnabled() == false)
				{
					m_DebugServerDlg->GetDlgItem(ID_BTN_CLOSE)->EnableWindow(TRUE);
					m_DebugServerDlg->GetDlgItem(ID_BTN_UPDATE)->EnableWindow(TRUE);
					m_DebugServerDlg->GetDlgItem(ID_BTN_RESTART)->EnableWindow(TRUE);
					m_DebugServerDlg->GetDlgItem(ID_BTN_CLEAR)->EnableWindow(TRUE);

					m_DebugServerDlg->PrintLog("【系统】 文件获取失败，请稍候再试！");
				}

				CAsyncSocket::OnReceive(nErrorCode);
				m_MesLock.Release();
				return;
			}
			break;
		}
	}

	BYTE recvData[1024];
	int recv = 0;
	int realrecv = m_curFile.totalSize - m_curFile.curSize;

	if( realrecv > 1024)
		recv = Receive( recvData, sizeof(recvData) );
	else
		recv = Receive( recvData, realrecv );	

	if( recv>0)
	{
		m_cFile.Write( recvData, recv );
		m_curFile.curSize+=recv;

		if(m_curFile.curSize == m_curFile.totalSize)
		{
			m_cFile.Close();
			m_isStartRev = false;
			m_curFile.totalSize = m_curFile.curSize = 0;
			m_curFileCount+=1;

			if(m_curFileCount == m_totalFileCount)
			{
				isConned = true;

				CString tempStr;
				tempStr.Format("【系统】 文件接收完毕，共获取%d个文件。",m_curFileCount);
				m_DebugServerDlg->PrintLog(tempStr.GetBuffer());

				m_DebugServerDlg->GetDlgItem(ID_BTN_CLOSE)->EnableWindow(TRUE);
				m_DebugServerDlg->GetDlgItem(ID_BTN_UPDATE)->EnableWindow(TRUE);
				m_DebugServerDlg->GetDlgItem(ID_BTN_RESTART)->EnableWindow(TRUE);
				m_DebugServerDlg->GetDlgItem(ID_BTN_CLEAR)->EnableWindow(TRUE);
			}
		}
	}
	else
	{
		m_cFile.Close();
		m_isStartRev = false;
		m_DebugServerDlg->GetDlgItem(ID_BTN_CLOSE)->EnableWindow(TRUE);
		m_DebugServerDlg->GetDlgItem(ID_BTN_UPDATE)->EnableWindow(TRUE);
		m_DebugServerDlg->GetDlgItem(ID_BTN_RESTART)->EnableWindow(TRUE);
		m_DebugServerDlg->GetDlgItem(ID_BTN_CLEAR)->EnableWindow(TRUE);

		m_DebugServerDlg->PrintLog("【系统】 文件获取失败，请稍候再试！");
	}
	m_MesLock.Release();

	CAsyncSocket::OnReceive(nErrorCode);
}

BOOL CAsyncSocketFile::OpenFile(LPCTSTR lpszPath)
{
	m_filePath = lpszPath;
	
	return true;
}

BOOL CAsyncSocketFile::SendDirection(LPCTSTR lpszPath)
{
	m_dirPath = lpszPath;

	return true;
}

BOOL CAsyncSocketFile::SendFile(LPCTSTR lpszPath)
{
	BYTE sendData[1024];

	CFile f( lpszPath, CFile::modeRead );
	if(f.GetLength() <= 0) 
	{
		f.Close();
		return false;
	}

	std::string tempPath = lpszPath;
	int pos = tempPath.find_last_of("\\");
	if(pos > 0)
		tempPath = tempPath.substr(pos+1,tempPath.length());

	mylogonpacket plogonpacket;
	memset(&plogonpacket,0,sizeof(plogonpacket));
	plogonpacket.type = 1;
	if(tempPath.length() < 256)
		strcpy(plogonpacket.name,tempPath.c_str());
	plogonpacket.size=f.GetLength();
	Send(&plogonpacket,sizeof(plogonpacket));

	int read = 0;
	long totalSent = 0;
	do
	{
		f.Seek( totalSent, CFile::begin );
		read = f.Read( sendData, sizeof(sendData) );

		int sent = Send( sendData, read );
		if( sent>0 )
			totalSent += sent;

		if(totalSent >= f.GetLength())
			break;
	}while( read>0 );

	f.Close();

	return true;
}

/// 重新装载脚本
void CAsyncSocketFile::RestartGameServer(void)
{
	mylogonpacket plogonpacket;
	plogonpacket.type = 4;
	Send(&plogonpacket,sizeof(plogonpacket));
}

void CAsyncSocketFile::CloseFile()
{
	//m_cFile.Close();
}

/// 开始发送目录
void CAsyncSocketFile::StartSendDireciton(void)
{
	if(m_DebugServerDlg == NULL) return;

	m_DebugServerDlg->PrintLog("【系统】 正在更新游戏服务器中的脚本文件，请稍后...");
	m_DebugServerDlg->GetDlgItem(ID_BTN_UPDATE)->EnableWindow(FALSE);

	WIN32_FIND_DATA   FindData;

	// 检测当前是否为文件
	CString lpszPath;
	lpszPath.Format("%s\\*.*",m_dirPath.GetBuffer());
	HANDLE hFile   =   FindFirstFile(lpszPath.GetBuffer(),   &FindData);
	BOOL   FindOK   =   (INVALID_HANDLE_VALUE   !=   hFile);

	while(FindOK)
	{
		if(FindOK) {
			// 搜索文件夹
			if(!(FindData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) &&
				std::string(".") != std::string(FindData.cFileName) &&
				std::string("..") != std::string(FindData.cFileName))
			{
				std::string myFilename = std::string(FindData.cFileName);
				std::transform(myFilename.begin(),myFilename.end(),myFilename.begin(),tolower); 
				int pos = myFilename.find(".scc");
				if(pos < 0) 
				{
					lpszPath.Format("%s\\%s",m_dirPath.GetBuffer(),FindData.cFileName);
					SendFile(lpszPath.GetBuffer());					
				}
			}
		}

		FindOK   =   FindNextFile(hFile,   &FindData);
	}

	FindClose(hFile);	

	m_DebugServerDlg->PrintLog("【系统】 所有文件已经全部更新完成。");
	m_DebugServerDlg->GetDlgItem(ID_BTN_UPDATE)->EnableWindow(TRUE);
}

void CAsyncSocketFile::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if( m_cAsyncSocketFile != NULL )
		return;

	m_cAsyncSocketFile = new CAsyncSocketFile();
	m_cAsyncSocketFile->OpenFile(m_filePath);
	m_cAsyncSocketFile->SetPassword(m_password);
	Accept( *m_cAsyncSocketFile);

	CAsyncSocket::OnAccept(nErrorCode);
}

void CAsyncSocketFile::OnSend( int nErrorCode)
{
	CAsyncSocket::OnSend(nErrorCode);
}

void CAsyncSocketFile::OnConnect(int nErrorCode)
{
	if(m_DebugServerDlg == NULL) return;

	if(nErrorCode != 0)
	{
		m_DebugServerDlg->PrintLog("【系统】 游戏服务器连接失败，请检查你的网络。");
		m_DebugServerDlg->GetDlgItem(ID_BTN_CONNECT)->EnableWindow(TRUE);
	}
	else
	{
		if(m_password.IsEmpty()) return;

		m_curFileCount = 0;
		m_totalFileCount = 0;
		m_DebugServerDlg->PrintLog("【系统】 游戏服务器连接成功，正在验证用户密码，请稍后...");

		mylogonpacket plogonpass;
		plogonpass.type = 2;
		strcpy(plogonpass.name,m_password.GetBuffer());
		Send(&plogonpass,sizeof(plogonpass));
	}

	CAsyncSocket::OnConnect(nErrorCode);
}

/// 设置登录密码
void CAsyncSocketFile::SetPassword(CString pw)
{
	m_password = pw;
}

void CAsyncSocketFile::OnClose(int nErrorCode)
{
	if(m_DebugServerDlg == NULL) return;

	m_DebugServerDlg->PrintLog("【系统】 已经断开和游戏服务器之间的连接。");

	if( m_cAsyncSocketFile != NULL )
	{
		m_cAsyncSocketFile->Close();
		//m_cAsyncSocketFile->CloseFile();
		delete m_cAsyncSocketFile;
		m_cAsyncSocketFile = NULL;
	}

	isConned = false;
	CAsyncSocket::OnClose(nErrorCode);

	Close();

	m_DebugServerDlg->GetDlgItem(ID_BTN_CLOSE)->EnableWindow(FALSE);
	m_DebugServerDlg->GetDlgItem(ID_BTN_UPDATE)->EnableWindow(FALSE);
	m_DebugServerDlg->GetDlgItem(ID_BTN_RESTART)->EnableWindow(FALSE);
	m_DebugServerDlg->GetDlgItem(ID_BTN_CLEAR)->EnableWindow(FALSE);
	m_DebugServerDlg->GetDlgItem(ID_BTN_CONNECT)->EnableWindow(TRUE);
}
