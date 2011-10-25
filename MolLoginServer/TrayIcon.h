#ifndef _TRAY_ICON_H_INCLUDE
#define _TRAY_ICON_H_INCLUDE

const UINT WM_CREATETRAYBAR = RegisterWindowMessage(_T("TaskbarCreated"));

//计算数组维数
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))

class CTrayIcon
{
protected:
	NOTIFYICONDATA      m_NotifyData;               

public:
	explicit CTrayIcon(UINT uID);
	~CTrayIcon();

	void SetNotifyWnd(CWnd *pNotifyWnd,UINT uMessage);

public:
	BOOL SetIcon(HICON hIcon,LPCTSTR szTip,BOOL bForce=FALSE);
	BOOL ShowBalloonTip(LPCTSTR szMessage,LPCTSTR szTitle,UINT uTimeout=5,DWORD dwInfoFlags=NIIF_INFO);
};

#endif
