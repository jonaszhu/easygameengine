#pragma once

#include "MoleGameServerManger.h"

// CUserLoginDlg 对话框

class CUserLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserLoginDlg)

public:
	CUserLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserLoginDlg();

	/// 设置控件焦点
	void SetCtrlFocus(void);

// 对话框数据
	enum { IDD = IDD_DLG_LOGIN };

private:
	CImage m_bgImg;                      /**< 登陆框背景图片 */
	CSkinButton m_btnlogin,m_btnexit;    /**< 登录和退出按钮 */
	CSkinButton m_btnRegister;           /**< 注册账号按钮 */
	CSkinButton m_btnForgetPass;         /**< 忘记密码按钮 */
	CRadioButton m_btnCheck;             /**< 记住密码按钮 */

protected:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
