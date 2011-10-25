#pragma once

#include "Resource.h"

// CSwitchUserDlg 对话框

class CSwitchUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CSwitchUserDlg)

public:
	CSwitchUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSwitchUserDlg();

// 对话框数据
	enum { IDD = IDD_DLG_SWITCHUSER };

private:
	CImage m_bgImg;                      /**< 背景图片 */
	CSkinButton m_btnSwitch,m_btnExit,m_btnCancel;       /**< 切换，退出和取消按钮 */

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DWORD m_dwWidth;		// mask width
	DWORD m_dwHeight;		// mask height

private:
	HRGN CreateRgnFromFile( HBITMAP hBmp, COLORREF color );
	afx_msg void OnPaint();
};
