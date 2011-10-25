#pragma once

#include "Resource.h"
#include "MoleGameServerManger.h"

#define IDD_TIMER_CLOSE      WM_USER+1500                  // 10����Զ��ر� 

int MMessageBox(CString lpText,CString lpCaption,UINT uType,CWnd* pParent=NULL);

// CMMessageBoxDlg �Ի���

class CMMessageBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(CMMessageBoxDlg)

public:
	CMMessageBoxDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMMessageBoxDlg();

	/// ���ð�ť���
	inline void SetStyle(UINT style) { m_btnStyle = style; }
	/// �õ���ť���
	inline UINT GetStyle(void) { return m_btnStyle; }
	/// ���ñ��������
	inline void SetCaptionAndContent(CString c,CString con)
	{
		m_caption = c;
		m_content = con;
	}

// �Ի�������
	enum { IDD = IDD_DLG_MESBOX };

private:
	CImage m_bgImg;                      /**< ����ͼƬ */
	CSkinButton m_btnOk,m_btnCancel;     /**< ȷ����ȡ����ť */
	CSkinButton m_btnClose;              // �رհ�ť

protected:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()

	DWORD m_dwWidth;		// mask width
	DWORD m_dwHeight;		// mask height
	UINT m_btnStyle;                             // ��ť���
	int  m_closeCount;                           // �رռ���
	CString m_caption,m_content;                 // Ҫ��ʾ�ı�����ı�

private:
	HRGN CreateRgnFromFile( HBITMAP hBmp, COLORREF color );
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel2();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
