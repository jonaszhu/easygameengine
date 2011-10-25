#pragma once

#include "Resource.h"

// CSwitchUserDlg �Ի���

class CSwitchUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CSwitchUserDlg)

public:
	CSwitchUserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSwitchUserDlg();

// �Ի�������
	enum { IDD = IDD_DLG_SWITCHUSER };

private:
	CImage m_bgImg;                      /**< ����ͼƬ */
	CSkinButton m_btnSwitch,m_btnExit,m_btnCancel;       /**< �л����˳���ȡ����ť */

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
