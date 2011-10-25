// AsyncSocketFile.cpp : implementation file
//

#include "stdafx.h"
#include  <algorithm> 
#include "AsyncSocketFile.h"

#include "MolServerDlg.h"

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
	m_curTime = 0;
	m_mainDlg = 0;
	m_totalFileCount = 0;
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
	m_MesLock.Acquire();
	if(!m_isStartRev)
	{
		mylogonpacket plogonpacket;
		int recv = Receive( &plogonpacket, sizeof(mylogonpacket) );
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

				m_curFile.totalSize = plogonpacket.size;
				m_curFile.curSize = 0;

				CString lpszPath;
				lpszPath.Format("%s\\%s",m_filePath.GetBuffer(),plogonpacket.name);
				m_cFile.Open( lpszPath.GetBuffer(), CFile::modeCreate | CFile::modeWrite );
			}
			break;
		case 2:
			{
				if(m_password == plogonpacket.name)
				{
					m_isLoginOk = true;
					if(m_mainDlg) 
						m_mainDlg->KillTimer(IDD_TIMER_DEBUG_SERVER);

					StartSendDireciton();
				}

				CAsyncSocket::OnReceive(nErrorCode);
				m_MesLock.Release();
				return;
			}
			break;
		case 4:
			{
				if(m_mainDlg) 
					m_mainDlg->ReLoadAndRunScript();

				CAsyncSocket::OnReceive(nErrorCode);
				m_MesLock.Release();
				return;
			}
			break;
		default:
			{
				//m_cFile.Close();
				m_isStartRev = false;
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
		}
	}
	else
	{
		m_cFile.Close();
		m_isStartRev = false;
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
	plogonpacket.totalCount = m_totalFileCount;
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

/// 发送错误信息
void CAsyncSocketFile::SendLogInfo(CString info)
{
	mylogonpacket plogonpacket;
	plogonpacket.type = 3;
	strcpy(plogonpacket.name,info.GetBuffer());
	Send(&plogonpacket,sizeof(plogonpacket));
}

void CAsyncSocketFile::CloseFile()
{
	//m_cFile.Close();
}

/// 获取工作目录下文件个数
int CAsyncSocketFile::GetWorkFileCount(void)
{
	WIN32_FIND_DATA   FindData;

	// 检测当前是否为文件
	CString lpszPath;
	lpszPath.Format("%s\\*.*",m_dirPath.GetBuffer());
	HANDLE hFile   =   FindFirstFile(lpszPath.GetBuffer(),   &FindData);
	BOOL   FindOK   =   (INVALID_HANDLE_VALUE   !=   hFile);

	int count = 0;
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
					count+=1;
				}
			}
		}

		FindOK   =   FindNextFile(hFile,   &FindData);
	}

	FindClose(hFile);

	m_totalFileCount = count;

	return m_totalFileCount;
}

/// 开始发送目录
void CAsyncSocketFile::StartSendDireciton(void)
{
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
					m_cAsyncSocketFile->SendFile(lpszPath.GetBuffer());					
				}
			}
		}

		FindOK   =   FindNextFile(hFile,   &FindData);
	}

	FindClose(hFile);	
}

void CAsyncSocketFile::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if( m_cAsyncSocketFile != NULL )
		return;

	m_cAsyncSocketFile = new CAsyncSocketFile();
	m_cAsyncSocketFile->SetMainDlg(m_mainDlg);
	m_cAsyncSocketFile->SetWorkFileCount(m_totalFileCount);
	m_cAsyncSocketFile->OpenFile(m_filePath);
	m_cAsyncSocketFile->SetPassword(m_password);
	m_cAsyncSocketFile->SendDirection(m_dirPath);
	m_cAsyncSocketFile->SetCurTime((DWORD)time(NULL));
	Accept( *m_cAsyncSocketFile);

	if(m_mainDlg) 
		m_mainDlg->SetTimer(IDD_TIMER_DEBUG_SERVER,10000,NULL);

	CAsyncSocket::OnAccept(nErrorCode);
}

void CAsyncSocketFile::OnSend( int nErrorCode)
{
	CAsyncSocket::OnSend(nErrorCode);
}

void CAsyncSocketFile::OnConnect(int nErrorCode)
{
	CAsyncSocket::OnConnect(nErrorCode);
}

/// 设置登录密码
void CAsyncSocketFile::SetPassword(CString pw)
{
	m_password = pw;
}

void CAsyncSocketFile::OnClose(int nErrorCode)
{
	if( m_cAsyncSocketFile != NULL )
	{
		if(m_mainDlg) 
			m_mainDlg->KillTimer(IDD_TIMER_DEBUG_SERVER);

		m_cAsyncSocketFile->Close();
		//m_cAsyncSocketFile->CloseFile();
		delete m_cAsyncSocketFile;
		m_cAsyncSocketFile = NULL;
	}

	CAsyncSocket::OnClose(nErrorCode);
}
