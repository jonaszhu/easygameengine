#pragma once

#include "Resource.h"
#include "MoleGameServerManger.h"

#define IDD_TIMER_CLOSE      WM_USER+1500                  // 10秒后自动关闭 

int MMessageBox(CString lpText,CString lpCaption,UINT uType,CWnd* pParent=NULL);

// CMMessageBoxDlg 对话框

class CMMessageBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(CMMessageBoxDlg)

public:
	CMMessageBoxDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMMessageBoxDlg();

	/// 设置按钮风格
	inline void SetStyle(UINT style) { m_btnStyle = style; }
	/// 得到按钮风格
	inline UINT GetStyle(void) { return m_btnStyle; }
	/// 设置标题和内容
	inline void SetCaptionAndContent(CString c,CString con)
	{
		m_caption = c;
		m_content = con;
	}

// 对话框数据
	enum { IDD = IDD_DLG_MESBOX };

private:
	CImage m_bgImg;                      /**< 背景图片 */
	CSkinButton m_btnOk,m_btnCancel;     /**< 确定和取消按钮 */
	CSkinButton m_btnClose;              // 关闭按钮

protected:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()

	DWORD m_dwWidth;		// mask width
	DWORD m_dwHeight;		// mask height
	UINT m_btnStyle;                             // 按钮风格
	int  m_closeCount;                           // 关闭计数
	CString m_caption,m_content;                 // 要显示的标题和文本

private:
	HRGN CreateRgnFromFile( HBITMAP hBmp, COLORREF color );
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel2();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
