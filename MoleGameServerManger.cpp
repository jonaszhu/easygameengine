#include "stdafx.h"
#include "MoleGameServerManger.h"
#include "Mole2dGameClientDlg.h"

#include "tinyxml/tinyxml.h"

BEGIN_MESSAGE_MAP(CRadioButton, CButton)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

//���캯��
CRadioButton::CRadioButton()
: m_isCheck(false)
{
}

//��������
CRadioButton::~CRadioButton()
{
}

//���󸽼ӵ����д���
void CRadioButton::PreSubclassWindow()
{
	__super::PreSubclassWindow();
	SetButtonStyle(GetButtonStyle()|BS_OWNERDRAW);
	return;
}

//������Ϣ
int CRadioButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;
	SetButtonStyle(GetButtonStyle()|BS_OWNERDRAW);
	return 0;
}

//����λͼ
bool CRadioButton::SetButtonImage(LPCTSTR pszFileName, bool bExpandImage)
{
	//Ч�����
	ASSERT(pszFileName);
	if (pszFileName==NULL) return false;

	//����λͼ
	m_ImageBack.Load(pszFileName);

	//����λ��
	FixButtonSize();
	if (GetSafeHwnd())
		Invalidate(FALSE);

	return true;
}

//����λ��
bool CRadioButton::FixButtonSize()
{
	if (!m_ImageBack.IsNull()&&GetSafeHwnd())
	{
		SetWindowPos(NULL,0,0,m_ImageBack.GetWidth()/2,m_ImageBack.GetHeight(),SWP_NOMOVE);
		return true;
	}
	return false;
}

//�����Ϣ
void CRadioButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(GetCheck()) SetCheck(false);
	else SetCheck(true);

	__super::OnLButtonDown(nFlags,point);
	Invalidate(FALSE);
}


//����ƶ���Ϣ
void CRadioButton::OnMouseMove(UINT nFlags, CPoint point)
{
	//ע����Ϣ
	Invalidate(FALSE);
	TRACKMOUSEEVENT TrackMouseEvent;
	TrackMouseEvent.cbSize=sizeof(TrackMouseEvent);
	TrackMouseEvent.dwFlags=TME_LEAVE;
	TrackMouseEvent.hwndTrack=GetSafeHwnd();
	TrackMouseEvent.dwHoverTime=HOVER_DEFAULT;
	_TrackMouseEvent(&TrackMouseEvent);

	__super::OnMouseMove(nFlags, point);
}

//����뿪��Ϣ
LRESULT CRadioButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	Invalidate(FALSE);
	return 0;
}

//��������
BOOL CRadioButton::OnEraseBkgnd(CDC * pDC)
{
	Invalidate(FALSE);
	UpdateWindow();
	return TRUE;
}

//����滭����
void CRadioButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//�������
	CRect ClientRect;
	GetClientRect(&ClientRect);

	if(!m_ImageBack.IsNull())
	{
		CDC * pDestDC=CDC::FromHandle(lpDrawItemStruct->hDC);
		if(!GetCheck())
			m_ImageBack.Draw(pDestDC->GetSafeHdc(),0,0,ClientRect.Width(),ClientRect.Height(),m_ImageBack.GetWidth()/2,0,m_ImageBack.GetWidth()/2,m_ImageBack.GetHeight());
		else
			m_ImageBack.Draw(pDestDC->GetSafeHdc(),0,0,ClientRect.Width(),ClientRect.Height(),0,0,m_ImageBack.GetWidth()/2,m_ImageBack.GetHeight());
	}

	return;
}

IMPLEMENT_DYNAMIC(CSkinButton, CButton)

BEGIN_MESSAGE_MAP(CSkinButton, CButton)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

//���캯��
CSkinButton::CSkinButton()
{
	m_crTextColor=RGB(0,0,0);
	m_ButtonState = BTN_STATE_NORMAL;
}

//��������
CSkinButton::~CSkinButton()
{
}

//���󸽼ӵ����д���
void CSkinButton::PreSubclassWindow()
{
	__super::PreSubclassWindow();
	SetButtonStyle(GetButtonStyle()|BS_OWNERDRAW);
	return;
}

//������Ϣ
int CSkinButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;
	SetButtonStyle(GetButtonStyle()|BS_OWNERDRAW);
	return 0;
}

//������ɫ
bool CSkinButton::SetTextColor(COLORREF crTextColor)
{
	m_crTextColor=crTextColor;
	if (GetSafeHwnd()) Invalidate(FALSE);
	return true;
}

void CSkinButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_ButtonState = BTN_STATE_DOWN;
	Invalidate(FALSE);

	CButton::OnLButtonDown(nFlags,point);
}

void CSkinButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_ButtonState = BTN_STATE_NORMAL;
	Invalidate(FALSE);

	CButton::OnLButtonUp(nFlags,point);
}


//����λͼ
bool CSkinButton::SetButtonImage(LPCTSTR pszFileName, bool bExpandImage)
{
	//Ч�����
	ASSERT(pszFileName);
	if (pszFileName==NULL) return false;

	//����λͼ
	m_ImageBack.Load(pszFileName);

	//����λ��
	FixButtonSize();
	if (GetSafeHwnd())
		Invalidate(FALSE);

	return true;
}

//Ĭ�ϰ�ť
void CSkinButton::SetDefaultButton(bool bResetIcon, bool bResetColor, bool bResetImage)
{
	//ˢ�½���
	if (GetSafeHwnd()) Invalidate(FALSE);

	return;
}

//����λ��
bool CSkinButton::FixButtonSize()
{
	if (!m_ImageBack.IsNull()&&GetSafeHwnd())
	{
		SetWindowPos(NULL,0,0,m_ImageBack.GetWidth()/4,m_ImageBack.GetHeight(),SWP_NOMOVE);
		return true;
	}
	return false;
}

//����ƶ���Ϣ
void CSkinButton::OnMouseMove(UINT nFlags, CPoint point)
{
	m_ButtonState = BTN_STATE_OVER;

	//ע����Ϣ
	Invalidate(FALSE);
	TRACKMOUSEEVENT TrackMouseEvent;
	TrackMouseEvent.cbSize=sizeof(TrackMouseEvent);
	TrackMouseEvent.dwFlags=TME_LEAVE;
	TrackMouseEvent.hwndTrack=GetSafeHwnd();
	TrackMouseEvent.dwHoverTime=HOVER_DEFAULT;
	_TrackMouseEvent(&TrackMouseEvent);

	__super::OnMouseMove(nFlags, point);
}

//����뿪��Ϣ
LRESULT CSkinButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_ButtonState = BTN_STATE_NORMAL;
	Invalidate(FALSE);
	return 0;
}

//��������
BOOL CSkinButton::OnEraseBkgnd(CDC * pDC)
{
	Invalidate(FALSE);
	UpdateWindow();
	return TRUE;
}

//����滭����
void CSkinButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//�������
	CRect ClientRect;
	GetClientRect(&ClientRect);
	bool bDisable=((lpDrawItemStruct->itemState&ODS_DISABLED)!=0);
	//bool bButtonDown=((lpDrawItemStruct->itemState&ODS_SELECTED)!=0);

	if(bDisable)
		m_ButtonState = BTN_STATE_DISABLE;

	//���� DC
	HDC hDC=lpDrawItemStruct->hDC;

	//��ȡ����
	CString strText;
	GetWindowText(strText);

	//���ر���ͼ
	if (!m_ImageBack.IsNull())
	{
		//����λͼλ��
		int iPartWidth=m_ImageBack.GetWidth()/4,iDrawPos=0;
		if (m_ButtonState == BTN_STATE_DISABLE) 
			iDrawPos=iPartWidth*3;
		else if (m_ButtonState == BTN_STATE_NORMAL) 
			iDrawPos=iPartWidth*0;
		else if	(m_ButtonState == BTN_STATE_OVER) 
			iDrawPos=iPartWidth*1;
		else if	(m_ButtonState == BTN_STATE_DOWN) 
			iDrawPos=iPartWidth*1;

		//�滭����ͼ
		//CDC * pDestDC=CDC::FromHandle(lpDrawItemStruct->hDC);
		m_ImageBack.Draw(lpDrawItemStruct->hDC,0,0,iPartWidth,m_ImageBack.GetHeight(),iDrawPos,0,iPartWidth,m_ImageBack.GetHeight());
	}
	else
	{
		//�滭Ĭ�Ͻ���
		CDC * pDC=CDC::FromHandle(hDC);
		pDC->FillSolidRect(&ClientRect,GetSysColor(COLOR_BTNFACE));
		pDC->Draw3dRect(&ClientRect,GetSysColor(COLOR_WINDOWFRAME),GetSysColor(COLOR_3DHILIGHT));
	}

	//�滭����
	ClientRect.top+=1;
	::SetBkMode(hDC,TRANSPARENT);
	if (bDisable) 
		::SetTextColor(hDC,GetSysColor(COLOR_GRAYTEXT));
	else 
		::SetTextColor(hDC,m_crTextColor);

	//��������
	CFont DrawFont;
	DrawFont.CreateFont(-12,0,0,0,400,0,0,0,134,3,2,1,2,TEXT("Arial"));
	CDC * pDC=CDC::FromHandle(hDC);
	CFont * pOldFont=pDC->SelectObject(&DrawFont);

	DrawText(hDC,strText,strText.GetLength(),ClientRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

	//������Դ
	pDC->SelectObject(pOldFont);
	DrawFont.DeleteObject();

	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameRoomNode,CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

/** 
 * ���캯��
 */
CGameRoomNode::CGameRoomNode()
: m_NodeType(NODETYPE_GAME),m_GameId(0),m_isRegulate(false)
{

}

/**  
 * ��������
 */
CGameRoomNode::~CGameRoomNode()
{

}

/** 
 * ���ý��ͼƬ����
 *
 * @param bgImg ����ͼƬ
 * @param logoImg ��ϷlogoͼƬ
 * @param enterImg ���밴ťͼƬ
 * @param ruleImg ����ťͼƬ
 */
void CGameRoomNode::CreateNode(std::string bgImg,std::string logoImg,std::string enterImg,std::string ruleImg)
{
	if(bgImg.empty() || logoImg.empty() || enterImg.empty() || ruleImg.empty()) return;
	
	m_bgImg.Load(bgImg.c_str());

	if(m_NodeType == NODETYPE_GAME)
	{
		m_gameLogo.Load(logoImg.c_str());
	}

	if(!m_bgImg.IsNull())
	{
		std::wstring imgpath = CMole2dGameClientDlg::getSingleton().ConverToWideChar(bgImg);
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

	if(m_NodeType == NODETYPE_GAME)
	{
		m_enterBtn.Create("",WS_CHILD|WS_VISIBLE,CRect(CPoint(138,117),CSize(0,0)),this,0);
		m_enterBtn.SetButtonImage(enterImg.c_str());

		m_ruleBtn.Create("",WS_CHILD|WS_VISIBLE,CRect(CPoint(59,117),CSize(0,0)),this,0);
		m_ruleBtn.SetButtonImage(ruleImg.c_str());
	}
	else
	{
		m_enterBtn.Create("",WS_CHILD|WS_VISIBLE,CRect(CPoint(138,117),CSize(0,0)),this,0);
		m_enterBtn.SetButtonImage(enterImg.c_str());
	}
}

//��������
void CGameRoomNode::DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, LPRECT lpRect)
{
	//��������
	int nStringLength=lstrlen(pszString);
	int nXExcursion[8]={1,1,1,0,-1,-1,-1,0};
	int nYExcursion[8]={-1,0,1,1,1,0,-1,-1};

	//�滭�߿�
	pDC->SetTextColor(crFrame);
	CRect rcDraw;
	for (int i=0;i<CountArray(nXExcursion);i++)
	{
		rcDraw.CopyRect(lpRect);
		rcDraw.OffsetRect(nXExcursion[i],nYExcursion[i]);
		pDC->DrawText(pszString,nStringLength,&rcDraw,DT_VCENTER|DT_CENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
	}

	//�滭����
	rcDraw.CopyRect(lpRect);
	pDC->SetTextColor(crText);
	pDC->DrawText(pszString,nStringLength,&rcDraw,DT_VCENTER|DT_CENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

	return;
}


HRGN CGameRoomNode::CreateRgnFromFile( HBITMAP hBmp, COLORREF color )
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

//��Ϣ����
BOOL CGameRoomNode::PreTranslateMessage(MSG * pMsg)
{
	if(pMsg->message==WM_LBUTTONDOWN)  
	{
		if(pMsg->hwnd == m_enterBtn.GetSafeHwnd())
		{
			if(m_NodeType == CGameRoomNode::NODETYPE_GAME)
			{
				GetParent()->PostMessage(IDD_GAME_ROOM_LIST,IDD_SHOW_GAME_SERVER,m_GameId);
			}
			else
			{
				GetParent()->PostMessage(IDD_GAME_ROOM_LIST,IDD_ENTER_GAME_SERVER,(LPARAM)(&m_GameServerInfo));				
			}
		}
		else if(pMsg->hwnd == m_ruleBtn.GetSafeHwnd())
		{
			if(m_NodeType == CGameRoomNode::NODETYPE_GAME)
			{
				GetParent()->PostMessage(IDD_GAME_ROOM_LIST,IDD_GET_GAME_RULE,(LPARAM)m_ruleAddress.c_str());
			}
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}

void CGameRoomNode::OnPaint()
{
    CPaintDC dc(this); 

	CDC memDC;//�ڴ�DC
	CBitmap cbm;//�ڴ滭��
	CBitmap* oldBmp;//ԭ����
	CRect sourceRect;//Դ����
	CRect destRect;//Ŀ�����Ϊ�ͻ���
	  
 	GetClientRect(&destRect);//�ͻ�������
	memDC.CreateCompatibleDC(NULL);//�����ڴ�DC
	cbm.CreateCompatibleBitmap(&dc,destRect.Width(),destRect.Height());//�����ڴ滭��
	oldBmp=memDC.SelectObject(&cbm);//������ѡ��DC

	if(!m_bgImg.IsNull())
		m_bgImg.Draw(memDC,0,0);

	if(!m_gameLogo.IsNull())
		m_gameLogo.Draw(memDC,9,30);

	if(m_NodeType == CGameRoomNode::NODETYPE_SERVER)
	{
		//�滭����
		::SetBkMode(memDC,TRANSPARENT);

		//��������
		CFont DrawFont;
		DrawFont.CreateFont(-14,0,0,0,400,0,0,0,134,3,2,1,2,TEXT("Arial"));
		CDC * pDC=CDC::FromHandle(memDC);
		CFont * pOldFont=pDC->SelectObject(&DrawFont);

		DrawTextString(&memDC,m_GameServerInfo.ServerName.c_str(),RGB(255,255,255),RGB(0,0,0),CRect(CPoint(3,8),CSize(destRect.Width(),21)));

		CString onlinePlayerStr;

		onlinePlayerStr.Format("���ٽ��: %d",m_GameServerInfo.lastMoney);
		DrawText(memDC,onlinePlayerStr,onlinePlayerStr.GetLength(),CRect(CPoint(21,45),CSize(destRect.Width(),21)),DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

		onlinePlayerStr.Format("��������: %d",m_GameServerInfo.OnlinePlayerCount);
		DrawText(memDC,onlinePlayerStr,onlinePlayerStr.GetLength(),CRect(CPoint(21,75),CSize(destRect.Width(),21)),DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

		//������Դ
		pDC->SelectObject(pOldFont);
		DrawFont.DeleteObject();
	}

	dc.BitBlt(0,0,destRect.Width(),destRect.Height(),&memDC,0,0,SRCCOPY);//˫����

	memDC.SelectObject(oldBmp);//�ָ��ɵĻ���
	memDC.DeleteDC();//ɾ���ڴ�DC
}

////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameRoomManager,CWnd)
	ON_WM_PAINT()
	ON_MESSAGE(IDD_GAME_ROOM_LIST,OnShowGameServerList)
END_MESSAGE_MAP()

/**  
 * ���캯��
 */
CGameRoomManager::CGameRoomManager()
	: m_curSelGameId(-1)
{

}

/**  
 * ��������
 */
CGameRoomManager::~CGameRoomManager()
{
	Clear();
}

/** 
 * ������еķ���
 */
void CGameRoomManager::Clear(void)
{
	std::map<int,std::vector<CGameRoomNode*> >::iterator iter = m_GameRoomNodes.begin();
	for(;iter != m_GameRoomNodes.end();iter++)
	{
		for(int index=0;index<(int)(*iter).second.size();index++)
		{
			if((*iter).second[index]) delete (*iter).second[index];
			(*iter).second[index] = NULL;
		}
	}

	m_GameRoomNodes.clear();

	std::map<int,CGameRoomNode*>::iterator iterN = m_GameServerNodes.begin();
	for(;iterN != m_GameServerNodes.end();iterN++)
	{
		if((*iterN).second) delete (*iterN).second;
		(*iterN).second = NULL;
	}

	m_GameServerNodes.clear();
	m_curSelGameId = -1;
}

/** 
 * ����һ����Ϸ��㵽��������
 *
 * @param gameId Ҫ�������Ϸ��ID
 */
void CGameRoomManager::InsertGameNode(int gameId)
{
	// ���Ȳ����Ƿ��������Ϸ������оͲ������
	std::map<int,CGameRoomNode*>::iterator iter = m_GameServerNodes.find(gameId);
	if(iter != m_GameServerNodes.end()) return;

	CGameRoomNode *pGameRoomNode = new CGameRoomNode();
	pGameRoomNode->Create(NULL,NULL,WS_CHILD,CRect(0,0,100,100),this,0);

	std::string gamelogoimg,ruleaddress;
	std::map<int,GameParam>::iterator iterG = m_GameParams.find(gameId);
	if(iterG != m_GameParams.end())
	{
		gamelogoimg = (*iterG).second.gamelogo;
		ruleaddress = (*iterG).second.gamerule;
	}

	pGameRoomNode->SetNodeType(CGameRoomNode::NODETYPE_GAME);
	pGameRoomNode->SetRuleAddress(ruleaddress);
	pGameRoomNode->SetGameId(gameId);
	pGameRoomNode->CreateNode(m_gamebgimg,gamelogoimg,m_showbtnimg,m_rulebtnimg);

	m_GameServerNodes.insert(std::pair<int,CGameRoomNode*>(gameId,pGameRoomNode));
}

/** 
 * ����һ����������㵽��������
 *
 * @param gsf Ҫ����Ľ�����Ϣ
 */
void CGameRoomManager::InsertServerNode(GameServerInfo gsf)
{
	// ���Ȳ����Ƿ��������Ϸ�����û�оͲ������
	std::map<int,CGameRoomNode*>::iterator iter = m_GameServerNodes.find(gsf.GameId);
	if(iter == m_GameServerNodes.end()) return;	

	CGameRoomNode *pGameRoomNode = new CGameRoomNode();
	pGameRoomNode->Create(NULL,NULL,WS_CHILD,CRect(0,0,100,100),this,0);

	pGameRoomNode->SetNodeType(CGameRoomNode::NODETYPE_SERVER);
	pGameRoomNode->SetGameServerInfo(gsf);
	pGameRoomNode->CreateNode(m_gamebgimg,m_gamebgimg,m_enterbtnimg,m_rulebtnimg);

	std::map<int,std::vector<CGameRoomNode*> >::iterator iterGRN = m_GameRoomNodes.begin();
	if(iterGRN != m_GameRoomNodes.end())
	{
		(*iterGRN).second.push_back(pGameRoomNode);
	}
	else
	{
		std::vector<CGameRoomNode*> tempGRN;
		tempGRN.push_back(pGameRoomNode);

		m_GameRoomNodes.insert(std::pair<int,std::vector<CGameRoomNode*> >(gsf.GameId,tempGRN));
	}
}

/**  
 * �Ƿ���ʾ���е���Ϸ���
 *
 * @param show ��ʾ״̬
 */
void CGameRoomManager::ShowAllGameRoomNodes(int show)
{
	if(m_GameServerNodes.empty()) return;

	std::map<int,CGameRoomNode*>::iterator iter = m_GameServerNodes.begin();
	for(;iter != m_GameServerNodes.end();iter++)
	{
		if((*iter).second)
		{
			(*iter).second->ShowWindow(show);
		}
	}
}

/** 
 * �Ƿ���ʾָ����ϷID�ķ��������
 *
 * @param gameId Ҫ��ʾ����Ϸ��ID
 * @param show ��ʾ״̬
 */
void CGameRoomManager::ShowAllGameServerNodes(int gameId,int show)
{
	if(m_GameRoomNodes.empty()) return;

	std::map<int,std::vector<CGameRoomNode*> >::iterator iter = m_GameRoomNodes.find(gameId);
	if(iter == m_GameRoomNodes.end()) return;

	for(int index = 0;index < (int)(*iter).second.size();index++)
	{
		if((*iter).second[index] != NULL)
			(*iter).second[index]->ShowWindow(show);
	}
}

//��ʾ��Ϸ�������б�
LRESULT CGameRoomManager::OnShowGameServerList(WPARAM wparam, LPARAM lparam)
{
	int state = (int)wparam;

	switch(state)
	{
	case IDD_SHOW_GAME_SERVER:
		{
			m_curSelGameId = (int)lparam;

			ShowAllGameRoomNodes(SW_HIDE);
			RegulateGameServerNodes(m_curSelGameId);
			ShowAllGameServerNodes(m_curSelGameId,SW_SHOW);
		}
		break;
	case IDD_GET_GAME_RULE:
		{	
			GetParent()->PostMessage(IDD_GAME_ROOM_LIST,IDD_GET_GAME_RULE,lparam);
		}
		break;
	case IDD_ENTER_GAME_SERVER:
		{
			GetParent()->PostMessage(IDD_GAME_ROOM_LIST,IDD_ENTER_GAME_SERVER,lparam);		
		}
		break;
	default:
		break;
	}

	return 0;
}

/** 
 * ��ʾ����Ϸ�б����
 */
void CGameRoomManager::ShowMainGameNodes(void)
{
	ShowAllGameServerNodes(m_curSelGameId,SW_HIDE);
	ShowAllGameRoomNodes(SW_SHOW);
}

void CGameRoomManager::OnPaint()
{
    CPaintDC dc(this); 

	CDC memDC;//�ڴ�DC
	CBitmap cbm;//�ڴ滭��
	CBitmap* oldBmp;//ԭ����
	CRect sourceRect;//Դ����
	CRect destRect;//Ŀ�����Ϊ�ͻ���
	  
 	GetClientRect(&destRect);//�ͻ�������
	memDC.CreateCompatibleDC(NULL);//�����ڴ�DC
	cbm.CreateCompatibleBitmap(&dc,destRect.Width(),destRect.Height());//�����ڴ滭��
	oldBmp=memDC.SelectObject(&cbm);//������ѡ��DC

	memDC.FillSolidRect(destRect,RGB(227,233,239));

	if(!m_bgImage.IsNull())
		m_bgImage.Draw(memDC,0,0);

	dc.BitBlt(0,0,destRect.Width(),destRect.Height(),&memDC,0,0,SRCCOPY);//˫����

	memDC.SelectObject(oldBmp);//�ָ��ɵĻ���
	memDC.DeleteDC();//ɾ���ڴ�DC
}

/**
 * ���뷿������
 *
 * @param configfile Ҫ����ķ��������ļ�·��
 *
 * @return ����������õ���ɹ������棬���򷵻ؼ�
 */
bool CGameRoomManager::LoadRoomConfig(std::string configfile)
{
	if(configfile.empty()) return false;

	TiXmlDocument doc;

	if(!doc.LoadFile(configfile.c_str()))
	{
		return false;
	}

	m_GameParams.clear();

	TiXmlElement *gameroomconfig = doc.FirstChildElement("gameroomconfig");

	if(gameroomconfig)
	{
		m_rowlist.cx = atoi(gameroomconfig->Attribute("row"));
		m_rowlist.cy = atoi(gameroomconfig->Attribute("list"));
		m_rowlistspace.cx = atoi(gameroomconfig->Attribute("rowspace"));
		m_rowlistspace.cy = atoi(gameroomconfig->Attribute("listspace"));
		m_ShowPosition.x = atoi(gameroomconfig->Attribute("disX"));
		m_ShowPosition.y = atoi(gameroomconfig->Attribute("disY"));

		TiXmlElement *Propertys = gameroomconfig->FirstChildElement("Propertys");

		if(Propertys)
		{
			TiXmlElement *Property = Propertys->FirstChildElement("Property");

			while(Property)
			{
				std::string name = Property->Attribute("name");
				std::string value = Property->Attribute("value");

				if(name == "showbtn")
				{
					m_showbtnimg = value;
				}
				else if(name == "enterbtn")
				{
					m_enterbtnimg = value;
				}
				else if(name == "rulebtn")
				{
					m_rulebtnimg = value;
				}
				else if(name == "gameimage")
				{
					m_gamebgimg = value;
				}
				else if(name == "roomimage")
				{
					m_gameroomimg = value;
				}
				else if(name == "managerimage")
				{
					m_bgImage.Load(value.c_str());
				}

				Property = Property->NextSiblingElement();
			}
		}

		TiXmlElement *gameconfigs = gameroomconfig->FirstChildElement("gameconfigs");

		if(gameconfigs)
		{
			TiXmlElement *gameconfig = gameconfigs->FirstChildElement("gameconfig");

			while(gameconfig)
			{
				GameParam pGameParam;
				pGameParam.gameId = atol(gameconfig->Attribute("gameId"));
				pGameParam.gamelogo = gameconfig->Attribute("gamelogo");
				pGameParam.gamerule = gameconfig->Attribute("gamerule");

				m_GameParams.insert(std::pair<int,GameParam>(pGameParam.gameId,pGameParam));

				gameconfig = gameconfig->NextSiblingElement();
			}
		}
	}

	return true;
}

/** 
 * У����Ϸ���λ��
 */
void CGameRoomManager::RegulateGameNodes(void)
{
	if(m_GameServerNodes.empty()) return;

	int nodelistIndex,noderowIndex;
	nodelistIndex = noderowIndex = 0;	

	std::map<int,std::vector<CGameRoomNode*> >::iterator iterG = m_GameRoomNodes.find(m_curSelGameId);
	if(iterG != m_GameRoomNodes.end())
	{
		for(int index=0;index<(int)(*iterG).second.size();index++)
		{
			if((*iterG).second[index] != NULL)
				(*iterG).second[index]->ShowWindow(SW_SHOW);
		}
	}

	std::map<int,CGameRoomNode*>::iterator iter = m_GameServerNodes.begin();
	for(;iter != m_GameServerNodes.end();iter++)
	{
		CGameRoomNode *pGameRoomNode = static_cast<CGameRoomNode*>((*iter).second);
		if(pGameRoomNode == NULL) continue;

		if(m_curSelGameId != -1)
			pGameRoomNode->ShowWindow(SW_HIDE);
		else
			pGameRoomNode->ShowWindow(SW_SHOW);

		if(pGameRoomNode->IsRegulate()) continue;
		pGameRoomNode->SetRegulate(true);

		if(nodelistIndex >= m_rowlist.cx) 
		{
			nodelistIndex = 0;
			noderowIndex+=1;
		}

		CRect pRect;
		pGameRoomNode->GetClientRect(pRect);

		pGameRoomNode->MoveWindow(m_ShowPosition.x+nodelistIndex*pRect.Width()+nodelistIndex*m_rowlistspace.cx,m_ShowPosition.y+noderowIndex*pRect.Height()+noderowIndex*m_rowlistspace.cy,pRect.Width(),pRect.Height());

		nodelistIndex+=1;
	}
}

/** 
 * У��ָ����Ϸ�ķ�����λ��
 *
 * @param gameId ҪУ������ϷID
 */
void CGameRoomManager::RegulateGameServerNodes(int gameId)
{
	if(m_GameRoomNodes.empty()) return;

	std::map<int,std::vector<CGameRoomNode*> >::iterator iter = m_GameRoomNodes.find(gameId);
	if(iter == m_GameRoomNodes.end()) return;

	if((*iter).second.empty()) return;

	int nodelistIndex,noderowIndex;
	nodelistIndex = noderowIndex = 0;	

	std::vector<CGameRoomNode*>::iterator iterGRN = (*iter).second.begin();
	for(;iterGRN != (*iter).second.end();iterGRN++)
	{
		CGameRoomNode *pGameRoomNode = static_cast<CGameRoomNode*>((*iterGRN));
		if(pGameRoomNode == NULL) continue;

		if(pGameRoomNode->IsRegulate()) continue;
		pGameRoomNode->SetRegulate(true);

		if(nodelistIndex >= m_rowlist.cx) 
		{
			nodelistIndex = 0;
			noderowIndex+=1;
		}

		CRect pRect;
		pGameRoomNode->GetClientRect(pRect);

		pGameRoomNode->MoveWindow(m_ShowPosition.x+nodelistIndex*pRect.Width()+nodelistIndex*m_rowlistspace.cx,m_ShowPosition.y+noderowIndex*pRect.Height()+noderowIndex*m_rowlistspace.cy,pRect.Width(),pRect.Height());

		nodelistIndex+=1;
	}
}
