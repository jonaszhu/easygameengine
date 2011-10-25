// UserLoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Mole2dGameClient.h"
#include "UserLoginDlg.h"

#include "Mole2dClientCommon.h"
#include "Mole2dGameClientDlg.h"
#include "MoleGameFrameDlg.h"

#include <string>
#include ".\userlogindlg.h"


// CUserLoginDlg 对话框

IMPLEMENT_DYNAMIC(CUserLoginDlg, CDialog)

CUserLoginDlg::CUserLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserLoginDlg::IDD, pParent),m_dwWidth(0),m_dwHeight(0)
{

}

CUserLoginDlg::~CUserLoginDlg()
{
}

void CUserLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_SERVER_LOGIN, m_btnlogin);
	DDX_Control(pDX, IDCANCEL, m_btnexit);
	DDX_Control(pDX, ID_BTN_REGISTER, m_btnRegister);
	DDX_Control(pDX, ID_BTN_FORGETPASS, m_btnForgetPass);
	DDX_Control(pDX, IDC_CHECK_PWD, m_btnCheck);
}


BEGIN_MESSAGE_MAP(CUserLoginDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CUserLoginDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_SERVER_LOGIN, &CUserLoginDlg::OnBnClickedServerLogin)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CHECK_PWD, &CUserLoginDlg::OnBnClickedCheckPwd)
	ON_BN_CLICKED(ID_BTN_REGISTER, &CUserLoginDlg::OnBnClickedBtnRegister)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_BTN_FORGETPASS, OnBnClickedBtnForgetpass)
END_MESSAGE_MAP()


// CUserLoginDlg 消息处理程序
BOOL CUserLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	::SetWindowPos(this->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	m_btnlogin.SetButtonImage(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "gameroomconfig\\ok.bmp" );
	m_btnexit.SetButtonImage(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() +  "gameroomconfig\\close.bmp" );
	m_btnRegister.SetButtonImage(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() +  "gameroomconfig\\no.bmp" );
	m_btnForgetPass.SetButtonImage(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() +  "gameroomconfig\\forgetpass.png" );
	m_btnCheck.SetButtonImage(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() +  "gameroomconfig\\gou.png" );
	m_bgImg.Load(CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "gameroomconfig\\logonbk.png");
    
	if(!m_bgImg.IsNull())
	{
		CString myimg = CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "gameroomconfig\\logonbk.png";
		std::wstring imgpath = CMole2dGameClientDlg::getSingleton().ConverToWideChar(myimg.GetBuffer());
		Bitmap *mybgImg = new Bitmap(imgpath.c_str());

		Color   cl(0,0,0);
		HBITMAP   hBitmap;
		mybgImg->GetHBITMAP(cl,   &hBitmap); 

		HRGN hRgn = CreateRgnFromFile( hBitmap, RGB(0,0,0) );

		SetWindowPos( NULL, 0, 0, m_bgImg.GetWidth(),m_bgImg.GetHeight(), SWP_NOZORDER | SWP_NOMOVE );
		SetWindowRgn( hRgn, FALSE );

		delete mybgImg;
		mybgImg = NULL;
	}

	TCHAR szProcessName[MAX_PATH]=TEXT("");
	GetModuleFileName(AfxGetInstanceHandle(),szProcessName,MAX_PATH);
	std::string tempStr = szProcessName;
	int pos = tempStr.find_last_of("\\");
	if(pos > 0) tempStr = tempStr.substr(0,pos+1);

	tempStr += "clientconfig.ini";

	char buf[1024];
	GetPrivateProfileString(TEXT("SystemSet"),TEXT("IsRegPWD"),"0",buf,1024,tempStr.c_str());

	CRadioButton *pBtn = (CRadioButton*)GetDlgItem(IDC_CHECK_PWD);
	pBtn->SetCheck(atoi(buf) > 0 ? true : false);

	if(pBtn->GetCheck() > 0)
	{
		GetDlgItem(IDC_EDIT_NAME)->SetWindowText(CMole2dGameClientDlg::getSingleton().GetRegisterUserName());
	}

	SetCtrlFocus();
	CenterWindow();

	return TRUE;
}

/// 设置控件焦点
void CUserLoginDlg::SetCtrlFocus(void)
{
	CString tempStr;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(tempStr);

	if(tempStr.IsEmpty())
	{
		GetDlgItem(IDC_EDIT_NAME)->SetFocus();
	}
	else
	{
		GetDlgItem(IDC_EDIT_PW)->SetFocus();
	}
}

void CUserLoginDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxGetMainWnd()->SendMessage(IDD_EXIT_GAME,0,0);

	OnCancel();
}

HBRUSH CUserLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,0)); 
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	} 
	else if(nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkColor(RGB(255,255,255));
		pDC->SetTextColor(RGB(0,0,0)); 
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	return hbr;
}

void CUserLoginDlg::OnBnClickedServerLogin()
{
	CString pName,pPassword;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(pName);
	if(pName.IsEmpty())
	{
		MMessageBox("用户名不能为空！","登录失败",MB_OK);
		GetDlgItem(IDC_EDIT_NAME)->SetFocus();
		return;
	}

	GetDlgItem(IDC_EDIT_PW)->GetWindowText(pPassword);
	if(pPassword.IsEmpty())
	{
		MMessageBox("用户密码不能为空！","登录失败",MB_OK);
		GetDlgItem(IDC_EDIT_PW)->SetFocus();
		return;
	}

	AfxGetMainWnd()->SendMessage(IDM_BTN_SERVER_LOGIN,(WPARAM)pName.GetBuffer(),(LPARAM)pPassword.GetBuffer());	
}

void CUserLoginDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_SYSCOMMAND,0xF012,0);

	CDialog::OnLButtonDown(nFlags, point);
}

void CUserLoginDlg::OnBnClickedCheckPwd()
{
	TCHAR szProcessName[MAX_PATH]=TEXT("");
	GetModuleFileName(AfxGetInstanceHandle(),szProcessName,MAX_PATH);
	std::string tempStr = szProcessName;
	int pos = tempStr.find_last_of("\\");
	if(pos > 0) tempStr = tempStr.substr(0,pos+1);

	tempStr += "clientconfig.ini";

	CRadioButton *pBtn = (CRadioButton*)GetDlgItem(IDC_CHECK_PWD);

	char buf[1024];
	sprintf(buf,"%d",(int)pBtn->GetCheck());
	WritePrivateProfileString(TEXT("SystemSet"),TEXT("IsRegPWD"),buf,tempStr.c_str());
}

HRGN CUserLoginDlg::CreateRgnFromFile( HBITMAP hBmp, COLORREF color )
{
	// get image properties
	BITMAP bmp = { 0 };
	GetObject( hBmp, sizeof(BITMAP), &bmp );
	// allocate memory for extended image information
	LPBITMAPINFO bi = (LPBITMAPINFO) new BYTE[ sizeof(BITMAPINFO) + 8 ];
	memset( bi, 0, sizeof(BITMAPINFO) + 8 );
	bi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	// set window size
	m_dwWidth	= bmp.bmWidth;		// bitmap width
	m_dwHeight	= bmp.bmHeight;		// bitmap height
	// create temporary dc
	HDC dc = CreateIC( "DISPLAY",NULL,NULL,NULL );
	// get extended information about image (length, compression, length of color table if exist, ...)
	DWORD res = GetDIBits( dc, hBmp, 0, bmp.bmHeight, 0, bi, DIB_RGB_COLORS );
	// allocate memory for image data (colors)
	LPBYTE pBits = new BYTE[ bi->bmiHeader.biSizeImage + 4 ];
	// allocate memory for color table
	if ( bi->bmiHeader.biBitCount == 8 )
	{
		// actually color table should be appended to this header(BITMAPINFO),
		// so we have to reallocate and copy it
		LPBITMAPINFO old_bi = bi;
		// 255 - because there is one in BITMAPINFOHEADER
		bi = (LPBITMAPINFO)new char[ sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD) ];
		memcpy( bi, old_bi, sizeof(BITMAPINFO) );
		// release old header
		delete old_bi;
	}
	// get bitmap info header
	BITMAPINFOHEADER& bih = bi->bmiHeader;
	// get color table (for 256 color mode contains 256 entries of RGBQUAD(=DWORD))
	LPDWORD clr_tbl = (LPDWORD)&bi->bmiColors;
	// fill bits buffer
	res = GetDIBits( dc, hBmp, 0, bih.biHeight, pBits, bi, DIB_RGB_COLORS );
	DeleteDC( dc );

	BITMAP bm;
	GetObject( hBmp, sizeof(BITMAP), &bm );
	// shift bits and byte per pixel (for comparing colors)
	LPBYTE pClr = (LPBYTE)&color;
	// swap red and blue components
	BYTE tmp = pClr[0]; pClr[0] = pClr[2]; pClr[2] = tmp;
	// convert color if curent DC is 16-bit (5:6:5) or 15-bit (5:5:5)
	if ( bih.biBitCount == 16 )
	{
		// for 16 bit
		color = ((DWORD)(pClr[0] & 0xf8) >> 3) |
			((DWORD)(pClr[1] & 0xfc) << 3) |
			((DWORD)(pClr[2] & 0xf8) << 8);
		// for 15 bit
		//		color = ((DWORD)(pClr[0] & 0xf8) >> 3) |
		//				((DWORD)(pClr[1] & 0xf8) << 2) |
		//				((DWORD)(pClr[2] & 0xf8) << 7);
	}

	const DWORD RGNDATAHEADER_SIZE	= sizeof(RGNDATAHEADER);
	const DWORD ADD_RECTS_COUNT		= 40;			// number of rects to be appended
	// to region data buffer

	// BitPerPixel
	BYTE	Bpp = bih.biBitCount >> 3;				// bytes per pixel
	// bytes per line in pBits is DWORD aligned and bmp.bmWidthBytes is WORD aligned
	// so, both of them not
	DWORD m_dwAlignedWidthBytes = (bmp.bmWidthBytes & ~0x3) + (!!(bmp.bmWidthBytes & 0x3) << 2);
	// DIB image is flipped that's why we scan it from the last line
	LPBYTE	pColor = pBits + (bih.biHeight - 1) * m_dwAlignedWidthBytes;
	DWORD	dwLineBackLen = m_dwAlignedWidthBytes + bih.biWidth * Bpp;	// offset of previous scan line
	// (after processing of current)
	DWORD	dwRectsCount = bih.biHeight;			// number of rects in allocated buffer
	INT		i, j;									// current position in mask image
	INT		first = 0;								// left position of current scan line
	// where mask was found
	bool	wasfirst = false;						// set when mask has been found in current scan line
	bool	ismask;									// set when current color is mask color

	// allocate memory for region data
	// region data here is set of regions that are rectangles with height 1 pixel (scan line)
	// that's why first allocation is <bm.biHeight> RECTs - number of scan lines in image
	RGNDATAHEADER* pRgnData = 
		(RGNDATAHEADER*)new BYTE[ RGNDATAHEADER_SIZE + dwRectsCount * sizeof(RECT) ];
	// get pointer to RECT table
	LPRECT pRects = (LPRECT)((LPBYTE)pRgnData + RGNDATAHEADER_SIZE);
	// zero region data header memory (header  part only)
	memset( pRgnData, 0, RGNDATAHEADER_SIZE + dwRectsCount * sizeof(RECT) );
	// fill it by default
	pRgnData->dwSize	= RGNDATAHEADER_SIZE;
	pRgnData->iType		= RDH_RECTANGLES;

	for ( i = 0; i < bih.biHeight; i++ )
	{
		for ( j = 0; j < bih.biWidth; j++ )
		{
			// get color
			switch ( bih.biBitCount )
			{
			case 8:
				ismask = (clr_tbl[ *pColor ] != color);
				break;
			case 16:
				ismask = (*(LPWORD)pColor != (WORD)color);
				break;
			case 24:
				ismask = ((*(LPDWORD)pColor & 0x00ffffff) != color);
				break;
			case 32:
				ismask = (*(LPDWORD)pColor != color);
			}
			// shift pointer to next color
			pColor += Bpp;
			// place part of scan line as RECT region if transparent color found after mask color or
			// mask color found at the end of mask image
			if ( wasfirst )
			{
				if ( !ismask )
				{
					// save current RECT
					pRects[ pRgnData->nCount++ ] = CRect( first, i, j, i + 1 );
					// if buffer full reallocate it with more room
					if ( pRgnData->nCount >= dwRectsCount )
					{
						dwRectsCount += ADD_RECTS_COUNT;
						// allocate new buffer
						LPBYTE pRgnDataNew = new BYTE[ RGNDATAHEADER_SIZE + dwRectsCount * sizeof(RECT) ];
						// copy current region data to it
						memcpy( pRgnDataNew, pRgnData, RGNDATAHEADER_SIZE + pRgnData->nCount * sizeof(RECT) );
						// delte old region data buffer
						delete pRgnData;
						// set pointer to new regiondata buffer to current
						pRgnData = (RGNDATAHEADER*)pRgnDataNew;
						// correct pointer to RECT table
						pRects = (LPRECT)((LPBYTE)pRgnData + RGNDATAHEADER_SIZE);
					}
					wasfirst = false;
				}
			}
			else if ( ismask )		// set wasfirst when mask is found
			{
				first = j;
				wasfirst = true;
			}
		}

		if ( wasfirst && ismask )
		{
			// save current RECT
			pRects[ pRgnData->nCount++ ] = CRect( first, i, j, i + 1 );
			// if buffer full reallocate it with more room
			if ( pRgnData->nCount >= dwRectsCount )
			{
				dwRectsCount += ADD_RECTS_COUNT;
				// allocate new buffer
				LPBYTE pRgnDataNew = new BYTE[ RGNDATAHEADER_SIZE + dwRectsCount * sizeof(RECT) ];
				// copy current region data to it
				memcpy( pRgnDataNew, pRgnData, RGNDATAHEADER_SIZE + pRgnData->nCount * sizeof(RECT) );
				// delte old region data buffer
				delete pRgnData;
				// set pointer to new regiondata buffer to current
				pRgnData = (RGNDATAHEADER*)pRgnDataNew;
				// correct pointer to RECT table
				pRects = (LPRECT)((LPBYTE)pRgnData + RGNDATAHEADER_SIZE);
			}
			wasfirst = false;
		}

		pColor -= dwLineBackLen;
	}
	// release image data
	delete pBits;
	delete bi;

	// create region
	HRGN hRgn = ExtCreateRegion( NULL, RGNDATAHEADER_SIZE + pRgnData->nCount * sizeof(RECT), (LPRGNDATA)pRgnData );
	// release region data
	delete pRgnData;

	return hRgn;
}
void CUserLoginDlg::OnBnClickedBtnRegister()
{
	CString tempStr = CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "clientconfig.ini";

	char buf[1024];
	GetPrivateProfileString(TEXT("SystemSet"),TEXT("registerpage"),"0",buf,1024,tempStr.GetBuffer());

	ShellExecute(NULL,TEXT("open"),buf,NULL,NULL,SW_SHOW);
}

void CUserLoginDlg::OnPaint()
{
	CPaintDC dc(this); 

	CDC memDC;//内存DC
	CBitmap cbm;//内存画布
	CBitmap* oldBmp;//原画布
	CRect sourceRect;//源矩形
	CRect destRect;//目标矩形为客户区

	GetClientRect(&destRect);//客户区矩形
	memDC.CreateCompatibleDC(NULL);//兼容内存DC
	cbm.CreateCompatibleBitmap(&dc,destRect.Width(),destRect.Height());//兼容内存画布
	oldBmp=memDC.SelectObject(&cbm);//将画布选入DC

	if(!m_bgImg.IsNull())
		m_bgImg.Draw(memDC,0,0);

	dc.BitBlt(0,0,destRect.Width(),destRect.Height(),&memDC,0,0,SRCCOPY);//双缓冲

	memDC.SelectObject(oldBmp);//恢复旧的画布
	memDC.DeleteDC();//删除内存DC
}

BOOL CUserLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{    
		case VK_RETURN:
			{
				OnBnClickedServerLogin();
				return true;
			}
			break;
		default:
			break;
		} 
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CUserLoginDlg::OnBnClickedBtnForgetpass()
{
	CString tempStr = CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "clientconfig.ini";

	char buf[1024];
	GetPrivateProfileString(TEXT("SystemSet"),TEXT("forgetpasspage"),"0",buf,1024,tempStr.GetBuffer());

	ShellExecute(NULL,TEXT("open"),buf,NULL,NULL,SW_SHOW);
}
