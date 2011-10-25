// DebugServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Mole2dGameClient.h"
#include "DebugServerDlg.h"

#include "SerParamSetDlg.h"

// CDebugServerDlg 对话框

IMPLEMENT_DYNAMIC(CDebugServerDlg, CDialog)
CDebugServerDlg::CDebugServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDebugServerDlg::IDD, pParent),m_fileClient(NULL)
{
	strcpy(pSerParam.IPAddress,"127.0.0.1");
	pSerParam.Port = 5679;
	strcpy(pSerParam.Password,"12345");
}

CDebugServerDlg::~CDebugServerDlg()
{
	if(m_fileClient)
	{
		//m_fileClient->Close();
		delete m_fileClient;
		m_fileClient = NULL;
	}
}

void CDebugServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOG,m_logEdit);	
}


BEGIN_MESSAGE_MAP(CDebugServerDlg, CDialog)
	ON_BN_CLICKED(ID_BTN_SET, &CDebugServerDlg::OnBnClickedBtnSet)
	ON_BN_CLICKED(ID_BTN_CONNECT, &CDebugServerDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(ID_BTN_CLOSE, &CDebugServerDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(ID_BTN_UPDATE, &CDebugServerDlg::OnBnClickedBtnUpdate)
	ON_BN_CLICKED(ID_BTN_RESTART, &CDebugServerDlg::OnBnClickedBtnRestart)
	ON_BN_CLICKED(ID_BTN_CLEAR, &CDebugServerDlg::OnBnClickedBtnClear)
END_MESSAGE_MAP()


// CDebugServerDlg 消息处理程序
BOOL CDebugServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDebugServerDlg::OnBnClickedBtnSet()
{
	CSerParamSetDlg pSerParamSetDlg;
	pSerParamSetDlg.SetServParam(&pSerParam);
	pSerParamSetDlg.DoModal();
}

/**
 * 打印服务器工作日志
 *
 * @param log 要打印的服务器日志
 */
void CDebugServerDlg::PrintLog(std::string log)
{
	if(log.empty() || !m_logEdit.GetSafeHwnd()) return;

	log += "\r\n";

	if(m_logEdit.GetLineCount() > 250)
		m_logEdit.SetWindowText("");

	int len = m_logEdit.GetWindowTextLength();
	m_logEdit.SetSel(len,len);
	m_logEdit.ReplaceSel(log.c_str());
	m_logEdit.ScrollWindow(0,0);
}

void CDebugServerDlg::OnBnClickedBtnConnect()
{
	if(m_fileClient == NULL)
	{
		m_fileClient = new CAsyncSocketFile();
		m_fileClient->SetDebugServerDlg(this);		
	}

	m_fileClient->Create();
	m_fileClient->Connect(pSerParam.IPAddress,pSerParam.Port);
	m_fileClient->SetPassword(pSerParam.Password);

	char curDir[1024];
	GetCurrentDirectory(1024,curDir);
	CString realDir;
	realDir.Format("%s\\Debug-Server",curDir);

	// 检测目录是否存在，如果不存在就创建它
	if(GetFileAttributes(realDir) == 0xFFFFFFFF)   
		CreateDirectory(realDir,NULL);   

	m_fileClient->OpenFile(realDir.GetBuffer());
	m_fileClient->SendDirection(realDir.GetBuffer());

	GetDlgItem(ID_BTN_CONNECT)->EnableWindow(FALSE);
	PrintLog("【系统】 正在连接游戏服务器，请稍后...");
}

void CDebugServerDlg::OnBnClickedBtnClose()
{
	if(m_fileClient == NULL) return;

	m_fileClient->Close();

	PrintLog("【系统】 已经断开和游戏服务器之间的连接。");
	GetDlgItem(ID_BTN_CLOSE)->EnableWindow(FALSE);
	GetDlgItem(ID_BTN_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(ID_BTN_RESTART)->EnableWindow(FALSE);
	GetDlgItem(ID_BTN_CLEAR)->EnableWindow(FALSE);
	GetDlgItem(ID_BTN_CONNECT)->EnableWindow(TRUE);
}

void CDebugServerDlg::OnBnClickedBtnUpdate()
{
	if(m_fileClient == NULL) return;

	if(m_fileClient->IsConnected())
		m_fileClient->StartSendDireciton();
}

void CDebugServerDlg::OnBnClickedBtnRestart()
{
	if(m_fileClient == NULL) return;

	if(m_fileClient->IsConnected())
		m_fileClient->RestartGameServer();
}

void CDebugServerDlg::OnBnClickedBtnClear()
{
	m_logEdit.SetWindowText("");
	m_logEdit.Invalidate();
}
