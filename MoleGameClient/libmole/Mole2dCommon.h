#ifndef _MOLE2D_COMMON_H_
#define _MOLE2D_COMMON_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2009.11.10
*/

#include "dx9sdk/include/d3d9.h"
#include "dx9sdk/include/d3dx9.h"

#include <afxpriv.h>

#include <WinSock2.h>

#include <list>

#pragma warning(disable:4311)
#pragma warning(disable:4312)
//#pragma warning(disable:4251)
//#pragma warning(disable:4275)

typedef unsigned char     u8;
typedef signed char       s8;

typedef char              c8;

typedef unsigned short    u16;
typedef signed short      s16;

typedef unsigned int      u32;
typedef int               s32;

typedef float             f32;
typedef double            f64;

typedef DWORD HTEXTURE;

#define	BLEND_COLORADD		1
#define	BLEND_COLORMUL		0
#define	BLEND_ALPHABLEND	2
#define	BLEND_ALPHAADD		0
#define	BLEND_ZWRITE		4
#define	BLEND_NOZWRITE		0

#define BLEND_DEFAULT		(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE)
#define BLEND_DEFAULT_Z		(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_ZWRITE)

#define MOLPRIM_POINTS      1
#define MOLPRIM_LINES		2
#define MOLPRIM_TRIPLES		3
#define MOLPRIM_QUADS		4

#define D3DFVF_MOLVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define VERTEX_BUFFER_SIZE 5000

#define MOLNET_HOST_TO_NET_16(value) (htons (value))
#define MOLNET_HOST_TO_NET_32(value) (htonl (value))

#define MOLNET_NET_TO_HOST_16(value) (ntohs (value))
#define MOLNET_NET_TO_HOST_32(value) (ntohl (value))

#define WM_STOP 1023

#ifdef MOLE2D_GRAPHICS_DLL
#define MOLEXPORT  __declspec(dllexport)
#else
#define MOLEXPORT
#endif

//namespace mole2d
//{
//namespace graphics
//{

/**
* ����ϵͳ��ǰʹ�õĶ���ṹ
*/
struct MOLVertex
{
	float			x, y;		// ��Ļ����
	float			z;			// z ����
	DWORD			col;		// ������ɫ
	float			tx, ty;		// ��������
};

/**
* ����ϵͳʹ�õ�����ṹ
*/
struct MOLTexture
{
	HTEXTURE tex;               // ����ID
	int Width,Height;           // ����߿�
	std::string Name;           // ��������
};

/**
* ����״̬
*/
enum DownloadStatus
{
	UPDATE_ERROR = 0,                       // ����
	UPDATE_LIST,                            // �õ����ص���Դ�б�
	UPDATE_COMPLETE,                        // �������
	UPDATE_RESOURCES,                       // ����Դ�ļ���������Щ�ļ�
	UPDATE_UNZIP,                           // ��ѹ���ļ��н�ѹ��Щ�ļ�
	UPDATE_NULL               
};

/** 
 * ���뷽ʽ
 */
enum SnapStyle
{
	SNAPSTYLE_LEFT = 0,                // ����
	SANPSTYLE_CENTER,                  // ����
	SNAPSTYLE_RIGHT,                   // ����
	SNAPSTYLE_NULL
};

/** 
 * ����
 */
enum DirectionType
{
	DIR_HORIZONTAL = 0,                // ����
	DIR_VERTICAL                       // ��ֱ
};

#define IDD_TIMER_MOL_RENDER            10000                       // ������ˢ�¶�ʱ��
#define IDD_TIMER_MOL_GETLOG            10001                       // ���ڷ�����־�������ڴ���
#define IDD_SOCKET_WND                  10002                       // ���ǽ���socket���ӵĴ���ID
#define IDD_WM_SOCKET_MESSAGE           10003                       // ���ڴ���������Ϣ��ID
#define IDD_WM_GAME_UPDATE              10004                       // ��Ϸ������Ϣ
#define IDD_MESSAGE_HEART_JITTER        600                         // ��Ϸ������������Ϣ

#define MOLE2D_LOGGER_FILE              "mole2d.log"                // ϵͳʹ�õ���־�ļ�
#define MOLE2D_DOWNLOAD_TEMP_FILE       "download.temp"             // �������ص���ʱ�ļ�
#define MOLE2D_SYSTEM_DEFAULT_FONT      "DefaultFont"               // ϵͳ��ʼ��������
#define MOLE2D_SYSTEM_DEFAULT_DIRECTION "resources"                 // ϵͳ��ʼ��Ŀ¼
#define MOLE2D_SYSTEM_INI_CONFIG        "systemini.ini"             // ϵͳ��ʼ�����ļ�
#define MOLE2D_SYSTEM_DEFAULT_SCRIPT    "��Ϸ�ű�\\gamelogic.lua"    // ϵͳ��ʼ���ؽű�
#define MOLE2D_SYSTEM_DEFAULT_FONT_SIZE 14                          // ϵ�y��ʼ���w��С
#define MOLE2D_SYSTEM_SCREEN_WIDTH      800                         // ϵͳ��ʼ��Ļ���
#define MOLE2D_SYSTEM_SCREEN_HEIGHT     600                         // ϵͳ��ʼ��Ļ�߶�
#define MOLE2D_UNIQE_NAME               "{22E932F2-F618-4d74-93C0-1A315B52CDEF}"       // ���ڿ��Ƴ��򵥿�


#define MOLE2D_GUI_CONTINUE_CONTAINER   10004                       // �������а�����
#define MOLE2D_GUI_CLOSE_CONTAINER      10005                       // �رհ�����
#define MOLE2D_GUI_MIN_FRAME            10006                       // ������С��
#define MOLE2D_GUI_MAX_FRAME            10007                       // �������
#define MOLE2D_GUI_RESERVE_FRAME        10008                       // ��������
#define MOLE2D_GUI_CLOSE_FRAME          10009                       // �ر���Ϸ����
#define MOLE2D_GUI_ROOM_LIST            10010                       // ��Ϸ�����б�

#define MOL_REV_BUFFER_SIZE             20480
#define MOL_SHARE_MEORY_COUNT           500                         // һ�ζ�ȡ��־����
#define MOL_SHARE_MEMORY_SIZE           5000                        // �����ڴ��С

//}
//}

#endif
