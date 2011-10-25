#include "stdafx.h"

#include "TrayIcon.h"

CTrayIcon::CTrayIcon(UINT uID)
{
	::memset(&m_NotifyData,0,sizeof(m_NotifyData));
	m_NotifyData.cbSize = sizeof(m_NotifyData);
	m_NotifyData.uID=uID;
}

CTrayIcon::~CTrayIcon()
{
	SetIcon(NULL,NULL);

	Shell_NotifyIcon( NIM_DELETE, &m_NotifyData );
}

void CTrayIcon::SetNotifyWnd(CWnd *pNotifyWnd,UINT uMessage)
{
	m_NotifyData.hWnd = pNotifyWnd->GetSafeHwnd();
	m_NotifyData.uCallbackMessage = uMessage;
}

BOOL CTrayIcon::SetIcon(HICON hIcon,LPCTSTR szTip,BOOL bForce)
{
	UINT uMessage=0;
	m_NotifyData.uFlags=0;

	if(hIcon)
	{
		if(bForce)
			uMessage=NIM_ADD;
		else
			uMessage=(m_NotifyData.hIcon!=NULL) ? NIM_MODIFY : NIM_ADD;
		m_NotifyData.hIcon=hIcon;
		m_NotifyData.uFlags|=NIF_ICON;
	}
	else
	{
		if(m_NotifyData.hIcon==NULL) return TRUE;
		uMessage=NIM_DELETE;
		m_NotifyData.hIcon=NULL;
	}

	if((szTip!=NULL)&&(lstrlen(szTip)<CountArray(m_NotifyData.szTip))) 
		::lstrcpy(m_NotifyData.szTip,szTip);
	if(m_NotifyData.szTip[0]!=0) m_NotifyData.uFlags|=NIF_TIP;
	if((m_NotifyData.uCallbackMessage!=0)&&
		(::IsWindow(m_NotifyData.hWnd))) m_NotifyData.uFlags|=NIF_MESSAGE;

	return Shell_NotifyIcon(uMessage,&m_NotifyData);
}

BOOL CTrayIcon::ShowBalloonTip(LPCTSTR szMessage,LPCTSTR szTitle,UINT uTimeout,DWORD dwInfoFlags)
{
	m_NotifyData.uFlags=NIF_INFO;
	m_NotifyData.uTimeout=uTimeout;
	m_NotifyData.dwInfoFlags=dwInfoFlags;
	::lstrcpy(m_NotifyData.szInfo,szMessage?szMessage:TEXT(""));
	::lstrcpy(m_NotifyData.szInfoTitle,szTitle?szTitle:TEXT(""));
	::Shell_NotifyIcon(NIM_MODIFY,&m_NotifyData);

	return TRUE;
}