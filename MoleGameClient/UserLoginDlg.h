#pragma once

#include "MoleGameServerManger.h"

// CUserLoginDlg �Ի���

class CUserLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserLoginDlg)

public:
	CUserLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserLoginDlg();

	/// ���ÿؼ�����
	void SetCtrlFocus(void);

// �Ի�������
	enum { IDD = IDD_DLG_LOGIN };

private:
	CImage m_bgImg;                      /**< ��½�򱳾�ͼƬ */
	CSkinButton m_btnlogin,m_btnexit;    /**< ��¼���˳���ť */
	CSkinButton m_btnRegister;           /**< ע���˺Ű�ť */
	CSkinButton m_btnForgetPass;         /**< �������밴ť */
	CRadioButton m_btnCheck;             /**< ��ס���밴ť */

protected:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedServerLogin();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedCheckPwd();

	DWORD m_dwWidth;		// mask width
	DWORD m_dwHeight;		// mask height

private:
	HRGN CreateRgnFromFile( HBITMAP hBmp, COLORREF color );
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnRegister();
	afx_msg void OnPaint();
public:
	afx_msg void OnBnClickedBtnForgetpass();
};
