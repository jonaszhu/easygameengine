// DownloadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Mole2dGameClient.h"
#include "Mole2dGameClientDlg.h"
#include "DownloadDlg.h"
#include "libzip/unzip.h"

#include <algorithm>
#include <curl/curl.h>
#include "tinyxml/tinyxml.h"

#include <string>

// CDownloadDlg 对话框

IMPLEMENT_DYNAMIC(CDownloadDlg, CDialog)

CDownloadDlg::CDownloadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDownloadDlg::IDD, pParent),m_dwWidth(0),m_dwHeight(0),m_UpdateVer(0)
{

}

CDownloadDlg::~CDownloadDlg()
{
}

void CDownloadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRO_TOTAL, m_fileCountProCtl);
	DDX_Control(pDX, IDC_PRO_CUR, m_fileProcCtl);
}


BEGIN_MESSAGE_MAP(CDownloadDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDownloadDlg 消息处理程序
BOOL CDownloadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_fileProcCtl.SetRange(0,100);

	CString myimg = CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + "gameroomconfig\\dlgbg.png";

	// TODO: 在此添加额外的初始化代码
	m_bgImage.Load(myimg.GetBuffer());
	if(!m_bgImage.IsNull())
	{
		std::wstring imgpath = CMole2dGameClientDlg::getSingleton().ConverToWideChar(myimg.GetBuffer());
		Bitmap *mybgImg = new Bitmap(imgpath.c_str());

		Color   cl(0,0,0);
		HBITMAP   hBitmap;
		mybgImg->GetHBITMAP(cl,   &hBitmap); 

		HRGN hRgn = CreateRgnFromFile( hBitmap, RGB(0,0,0) );

		SetWindowPos( NULL, 0, 0, m_bgImage.GetWidth(),m_bgImage.GetHeight(), SWP_NOZORDER | SWP_NOMOVE );
		SetWindowRgn( hRgn, FALSE );

		delete mybgImg;
		mybgImg = NULL;
	}

	CenterWindow();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDownloadDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rcClient;
	GetClientRect(&rcClient);

	//建立缓冲图
	CDC BufferDC;
	CBitmap BufferBmp;

	BufferDC.CreateCompatibleDC(NULL);
	BufferBmp.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
	CBitmap *pOldBit = BufferDC.SelectObject(&BufferBmp);

	if(!m_bgImage.IsNull())
		m_bgImage.Draw(BufferDC.GetSafeHdc(),0,0);

	if(m_ShowTip.GetLength() > 0)
	{
		BufferDC.SetBkMode(TRANSPARENT);
		BufferDC.SetTextColor(RGB(255,255,255));

		//创建字体
		CFont DrawFont;
		DrawFont.CreateFont(-14,0,0,0,400,0,0,0,134,3,2,1,2,TEXT("Arial"));
		CDC * pDC=CDC::FromHandle(BufferDC.GetSafeHdc());
		CFont * pOldFont=pDC->SelectObject(&DrawFont);

		DrawText(BufferDC.GetSafeHdc(),m_ShowTip,m_ShowTip.GetLength(),CRect(CPoint(10,135),CSize(360,30)),DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

		//清理资源
		pDC->SelectObject(pOldFont);
		DrawFont.DeleteObject();
	}

	dc.BitBlt(rcClient.left,rcClient.top,rcClient.right,rcClient.bottom,&BufferDC,0,0,SRCCOPY);

	BufferBmp.DeleteObject();
	BufferDC.DeleteDC();
}

HRGN CDownloadDlg::CreateRgnFromFile( HBITMAP hBmp, COLORREF color )
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
void CDownloadDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_SYSCOMMAND,0xF012,0);
	CDialog::OnLButtonDown(nFlags, point);
}

/** 
 * 根据客户端下载配置文件从服务器更新游戏
 *
 * @param configfile 要更新的配置文件
 */
void CDownloadDlg::UpdateGame(std::string configfile)
{
	if(configfile.empty())
		return;

	m_UpdateVer = 0.0f;
	serveraddress.clear();
	m_UpdateConfigFile = configfile;

	char buf[1024];
	GetPrivateProfileString(TEXT("UpdateSet"),TEXT("ver"),"",buf,1024,configfile.c_str());
	float ver = (float)atof(buf);
	GetPrivateProfileString(TEXT("UpdateSet"),TEXT("address"),"",buf,1024,configfile.c_str());
	std::string address = buf;

	m_UpdataSet = UpdataSetTwo(ver,address);

	CURLcode res;

	SetTip("正在加载资源,准备更新,请稍候...");

	// 初始化libcurl
	res = curl_global_init(CURL_GLOBAL_WIN32);
	if (CURLE_OK != res)
	{
		return;
	}

	// 建立更新线程
	m_UpdateThread = (HANDLE)::_beginthreadex(NULL,0,ThreadGameUpdate,(LPVOID)this,0,&m_UpdateThreadID);
	curl_global_cleanup();
}

/// 下载游戏
void CDownloadDlg::DownloadGame(std::string configfile)
{
	if(configfile.empty())
		return;

	m_UpdataSet = UpdataSetTwo(0.0f,configfile);

	CURLcode res;

	SetTip("正在加载资源,准备更新,请稍候...");

	// 初始化libcurl
	res = curl_global_init(CURL_GLOBAL_WIN32);
	if (CURLE_OK != res)
	{
		return;
	}

	// 建立更新线程
	m_UpdateThread = (HANDLE)::_beginthreadex(NULL,0,ThreadGameDownload,(LPVOID)this,0,&m_UpdateThreadID);
	curl_global_cleanup();
}

/** 
 * 游戏更新函数
 *
 * @param pParam 传入的参数
 *
 * @return 
 */
unsigned __stdcall CDownloadDlg::ThreadGameUpdate(void * pParam)
{
	CDownloadDlg *pMolFrame = static_cast<CDownloadDlg*>(pParam);
	if(pMolFrame == NULL) return 0;

	// 首先从服务器上下载更新列表
	if(pMolFrame->DownloadSingleFile(pMolFrame->GetUpdateSet().address))
	{
		// 开始解析文件下载列表
		std::string filename = pMolFrame->GetUpdateSet().address;		
		filename = filename.substr(filename.find_last_of("//")+1,filename.length());		

		pMolFrame->GetUpdateFileList(filename);

		// 更新完成后，删除更新列表文件
		DeleteFile(filename.c_str());		
	}

	pMolFrame->PostMessage(WM_CLOSE,0,0);

	return 0;
}

/// 游戏下载函数
unsigned __stdcall CDownloadDlg::ThreadGameDownload(void * pParam)
{
	CDownloadDlg *pMolFrame = static_cast<CDownloadDlg*>(pParam);
	if(pMolFrame == NULL) return 0;

	// 首先从服务器上下载更新列表
	if(pMolFrame->DownloadSingleFile(pMolFrame->GetUpdateSet().address))
		pMolFrame->PostMessage(WM_CLOSE,1,0);
	else
		pMolFrame->PostMessage(WM_CLOSE,0,0);

	return 0;
}

/**
* 根据文件路径名建立相应的目录
*
* @param filename 要建立目录的文件名
*/
void CDownloadDlg::CreateDirectionByPath(std::string filename)
{
	if(filename.empty()) return;

	WIN32_FIND_DATA   FindData;
	std::string temp1,temp = filename;
	int oldindex,index = (int)temp.find("\\");
	std::string realdir;

	oldindex = 0;

	while(index >= 0) {
		std::string dir = temp.substr(oldindex,index);

		if(realdir.empty())
			realdir = /*m_curWorkingDir + "\\" + */dir;
		else
			realdir = realdir + "\\" + dir;

		// 检测当前目录是否存在，如果不存在，就建立目录
		HANDLE   hFile   =   FindFirstFile(realdir.c_str(),&FindData);
		if(INVALID_HANDLE_VALUE == hFile)
		{
			// 如果这个目录不存在就建立这个目录
			if(!CreateDirectory(realdir.c_str(),NULL)) {
				return;
			}
		}

		oldindex = oldindex+index+1;
		temp1 = temp.substr(oldindex,temp.length());
		index = (int)temp1.find("\\");
	}
}

/** 
 * 下载指定网址的文件到指定的目录中，我们的下载基于http协议，这个下载一次只能下载一个文件,而且文件必须是以pak打包过的压缩文件
 *
 * @param file 要下载的文件，要文件的完整路径
 * @param path 要保存的文件路径,如果为空的话保存到当前路径，如果路径不存在的话建立路径
 * 
 * @return 如果文件下载成功返回真，否则返回假
 */
bool CDownloadDlg::DownloadSingleFile(std::string file,std::string path)
{
	if(file.empty()) return false;

	// 得到我们要下载的文件
	std::string pMyFile = file;
	std::string pSerAddress = serveraddress + file;
	pMyFile = (path.empty() ? pMyFile : path + pMyFile);

	if(serveraddress.empty())
	{
		int pos = file.find_last_of("//");
		int len = file.length();
		pMyFile = file.substr(pos+1,len);
		pMyFile = (path.empty() ? pMyFile : path + pMyFile);
	}

	// 首先建立我们文件保存需要的目录
	StringReplace(pMyFile,"/","\\");
	CreateDirectionByPath(pMyFile);

	int attempts = 0;
	CURL *curl;
	CURLcode res;

	while (attempts < 3)
	{
		FILE *outfile = NULL;

		try
		{
			curl = curl_easy_init();
			if (curl == NULL) return false;

			std::string newfile = MOLE2D_DOWNLOAD_TEMP_FILE;
			outfile = fopen(newfile.c_str(), "w+b");
			if(outfile == NULL) return false;

			curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);

			curl_easy_setopt(curl, CURLOPT_USERAGENT, "MOLEGAMEDOWN");
			curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, m_CurlError);
			curl_easy_setopt(curl, CURLOPT_URL, pSerAddress.c_str());
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
			curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION,UpdateProgress);
			curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, (void*)this);
			curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
			curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 15);
			curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);

			if ((res = curl_easy_perform(curl)) != 0)
			{
				switch (res)
				{
				case CURLE_COULDNT_CONNECT:
				default:
					break;
				}

				fclose(outfile);
				attempts++;
				continue;
			}

			curl_easy_cleanup(curl);			

			fclose(outfile);
		}
		catch(...)
		{
			return false;
		}

		std::string pExName = pMyFile.substr(pMyFile.length()-3,pMyFile.length());

		std::transform(pExName.begin(), pExName.end(), pExName.begin(), toupper);

		CopyFile(MOLE2D_DOWNLOAD_TEMP_FILE,pMyFile.c_str(),true);
		DeleteFile(MOLE2D_DOWNLOAD_TEMP_FILE);

		if(pExName == "ZIP")
		{
			SetTip("正在生成文件,请稍候...");

			// 解压这个压缩文件到当前目录
			unzip(pMyFile,path);

			DeleteFile(pMyFile.c_str());
		}	
		else if(pExName == "EXE")
		{
			ShowWindow(SW_HIDE);
			CString tempStr = CMole2dGameClientDlg::getSingleton().GetCurrentProcessPath() + pMyFile.c_str();
			ShellExecute(NULL,TEXT("open"),tempStr.GetBuffer(),NULL,NULL,SW_SHOW);
		}

		return true;
	}

	return false;
}

/** 
 * curl 使用的下载进度更新函数
 *
 * @param ptr 我们的传值
 * @param dt,dn,ut,un curl的传值，主要得到当前文件的更新进度
 *
 * @return 如果成功返回0，否则返回-1
 */
int CDownloadDlg::UpdateProgress(void *ptr,double dt, double dn, double ut, double un)
{
	CDownloadDlg *pMolBaseFrame = static_cast<CDownloadDlg*>(ptr);

	if(pMolBaseFrame)
	{
		return pMolBaseFrame->OnProcessFileDownload(dt,dn,ut,un);
	}

	return 0;
}

/** 
 * 根据服务器下载的更新配置文件得到要更新的文件列表
 *
 * @param config 要解析的配置文件
 * 
 * @return 如果文件解析成功返回真,否则返回假
 */
bool CDownloadDlg::GetUpdateFileList(std::string config)
{
	if(config.empty()) return false;

	TiXmlDocument doc;

	if(!doc.LoadFile(config.c_str()))
	{
		return false;
	}

	m_UpdateList.clear();

	TiXmlElement *UPDATEVERSION = doc.FirstChildElement("UPDATEVERSION");

	if(UPDATEVERSION)
	{
		// 得到更新版本
		m_UpdateVer = (float)atof(UPDATEVERSION->Attribute("ver"));
		serveraddress = UPDATEVERSION->Attribute("serveraddress");

		// 得到文件更新列表
		TiXmlElement *UPDATEFILE = UPDATEVERSION->FirstChildElement("UPDATEFILE");

		while(UPDATEFILE)
		{
			m_UpdateList.push_back(UPDATEFILE->Attribute("path"));

			UPDATEFILE = UPDATEFILE->NextSiblingElement();
		}
	}

	// 如果更新的文件个数为0，或者版本小于或等于服务器的版本，就不更新
	if(m_UpdateList.empty() || m_UpdateVer <= m_UpdataSet.ver)
	{
		SetTip("当前版本为最新版本。");

		return false;
	}

	m_UpdataSet.totalFileCount = (int)m_UpdateList.size();
	m_fileCountProCtl.SetRange(0,m_UpdataSet.totalFileCount);

	// 开始从服务器上下载文件，无论文件是否下载成功，要全部下载一次
	for(int i=0;i<(int)m_UpdateList.size();i++)
	{
		if(!m_UpdateList[i].empty())
		{
			m_UpdataSet.curDownloadFile = m_UpdateList[i];
			m_UpdataSet.curFileIndex = i+1;

			DownloadSingleFile(m_UpdateList[i]);
		}
	}

	// 文件更新完成后，改变当前客户端的版本号
	char buf[1024];
	sprintf(buf,"%.1f",m_UpdateVer);
	m_UpdataSet.ver = m_UpdateVer;

	if(!m_UpdateConfigFile.empty())
		WritePrivateProfileString(TEXT("UpdateSet"),TEXT("ver"),buf,m_UpdateConfigFile.c_str());

	SetTip("游戏已经更新完成。");

	return true;
}

/** 
 * 下载进度更新
 *
 * @param dt,dn,ut,un curl的传值，主要得到当前文件的更新进度
 *
 * @return 如果成功返回0，否则返回-1
 */
int CDownloadDlg::OnProcessFileDownload(double dt, double dn, double ut, double un)
{
	float progress = dn / dt;

	if (progress < 0) progress = 0.0f;
	if (progress > 1) progress = 1.0f;

	int m_DownloadProcess = (int)(progress * 100.0f);

	m_fileCountProCtl.SetPos(m_UpdataSet.curFileIndex);
	m_fileProcCtl.SetPos(m_DownloadProcess);

	std::string filename = m_UpdataSet.curDownloadFile;
	filename = filename.substr(filename.find_last_of("//")+1,filename.length());

	CString tempStr;
	tempStr.Format("当前下载文件:%s,还有%d个文件需要下载。",filename.c_str(),m_UpdataSet.totalFileCount-m_UpdataSet.curFileIndex);
	SetTip(tempStr);

	return 0;
}
void CDownloadDlg::OnClose()
{
	PostThreadMessage(m_UpdateThreadID,WM_STOP,0,0); 
	if(WaitForSingleObject(m_UpdateThread,INFINITE) == WAIT_OBJECT_0)
	{
		CloseHandle(m_UpdateThread);
		m_UpdateThread = NULL;
	}
	else   
	{
		TerminateThread(m_UpdateThread,   -1);
		CloseHandle(m_UpdateThread);
		m_UpdateThread = NULL;
	} 

	CDialog::OnClose();

	// 发送游戏更新完成消息
	AfxGetMainWnd()->SendMessage(IDD_GAME_UPDATE,0,0);
}

bool CDownloadDlg::unzip(std::string zipfile,std::string decpath)
{
	if(zipfile.empty())
		return false;

	char chOldFolder[1024];
	GetCurrentDirectory(1024, chOldFolder);
	std::string realpath = chOldFolder;

	char szName[_MAX_PATH];
	char szZipName[_MAX_PATH];
	unzFile zip;
	unz_file_info file_info;
	int done, i;
	void *ptr;

	strcpy(szName,zipfile.c_str());
	//strupr(szName);
	for(i=0; szName[i]; i++) { if(szName[i]=='/') szName[i]='\\'; }

	zip=unzOpen(zipfile.c_str());
	if(zip == NULL) return false;

	if(!decpath.empty()) 
	{
		SetCurrentDirectory(decpath.c_str());
		realpath = decpath;	
	}

	done=unzGoToFirstFile(zip);
	while(done==UNZ_OK)
	{
		unzGetCurrentFileInfo(zip, &file_info, szZipName, sizeof(szZipName), NULL, 0, NULL, 0);

		if(file_info.uncompressed_size <= 0)
		{
			done=unzGoToNextFile(zip);
			continue;
		}

		ptr = NULL;
		//strupr(szZipName);
		for(i=0; szZipName[i]; i++)	{ if(szZipName[i]=='/') szZipName[i]='\\'; }

		CreateDirectionByPath(szZipName);

		if(unzOpenCurrentFilePassword(zip, 0) != UNZ_OK)
		{
			unzClose(zip);
			return false;
		}

		ptr = malloc(file_info.uncompressed_size);
		if(!ptr)
		{
			unzCloseCurrentFile(zip);
			unzClose(zip);
			return false;
		}

		if(unzReadCurrentFile(zip, ptr, file_info.uncompressed_size) < 0)
		{
			unzCloseCurrentFile(zip);
			unzClose(zip);
			free(ptr);
			return false;
		}
		unzCloseCurrentFile(zip);

		if(file_info.uncompressed_size > 0 && ptr != NULL)
		{
			std::string temp = realpath + "\\" + std::string(szZipName);
			FILE *outputfile = fopen(temp.c_str(),"wb");
			if(outputfile == NULL)
			{
				free(ptr);
				unzClose(zip);
				return false;
			}

			if(fwrite(ptr,1,file_info.uncompressed_size,outputfile) != file_info.uncompressed_size)
			{
				free(ptr);
				fclose(outputfile);
				unzClose(zip);
				return false;
			}

			free(ptr);
			fclose(outputfile);
		}

		done=unzGoToNextFile(zip);
	}

	unzClose(zip);

	SetCurrentDirectory(chOldFolder);

	return true;
}

HBRUSH CDownloadDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor==CTLCOLOR_STATIC)
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(RGB(227,223,239));
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	} 

	return hbr;
}
