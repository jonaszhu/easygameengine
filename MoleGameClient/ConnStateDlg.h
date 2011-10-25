#pragma once


// CConnStateDlg 对话框

class CConnStateDlg : public CDialog
{
	DECLARE_DYNAMIC(CConnStateDlg)

public:
	CConnStateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConnStateDlg();

	/// 显示指定的提示
	void ShowTip(CString tip);

// 对话框数据
	enum { IDD = IDD_DLG_STATE };

private:
	CImage m_bgImg;                        /**< 使用的背景图片 */

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DWORD m_dwWidth;		// mask width
	DWORD m_dwHeight;		// mask height

private:
	HRGN CreateRgnFromFile( HBITMAP hBmp, COLORREF color );
};
