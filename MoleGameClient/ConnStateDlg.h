#pragma once


// CConnStateDlg �Ի���

class CConnStateDlg : public CDialog
{
	DECLARE_DYNAMIC(CConnStateDlg)

public:
	CConnStateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConnStateDlg();

	/// ��ʾָ������ʾ
	void ShowTip(CString tip);

// �Ի�������
	enum { IDD = IDD_DLG_STATE };

private:
	CImage m_bgImg;                        /**< ʹ�õı���ͼƬ */

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DWORD m_dwWidth;		// mask width
	DWORD m_dwHeight;		// mask height

private:
	HRGN CreateRgnFromFile( HBITMAP hBmp, COLORREF color );
};
