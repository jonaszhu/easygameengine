#ifndef _MOLE2D_COMMON_H_
#define _MOLE2D_COMMON_H_

/** 
* Mole2d 图像引擎
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
* 我们系统当前使用的顶点结构
*/
struct MOLVertex
{
	float			x, y;		// 屏幕坐标
	float			z;			// z 缓冲
	DWORD			col;		// 顶点颜色
	float			tx, ty;		// 纹理坐标
};

/**
* 我们系统使用的纹理结构
*/
struct MOLTexture
{
	HTEXTURE tex;               // 纹理ID
	int Width,Height;           // 纹理高宽
	std::string Name;           // 纹理名称
};

/**
* 下载状态
*/
enum DownloadStatus
{
	UPDATE_ERROR = 0,                       // 出错
	UPDATE_LIST,                            // 得到下载的资源列表
	UPDATE_COMPLETE,                        // 下载完成
	UPDATE_RESOURCES,                       // 从资源文件中下载这些文件
	UPDATE_UNZIP,                           // 从压缩文件中解压这些文件
	UPDATE_NULL               
};

/** 
 * 对齐方式
 */
enum SnapStyle
{
	SNAPSTYLE_LEFT = 0,                // 居左
	SANPSTYLE_CENTER,                  // 居中
	SNAPSTYLE_RIGHT,                   // 居右
	SNAPSTYLE_NULL
};

/** 
 * 方向
 */
enum DirectionType
{
	DIR_HORIZONTAL = 0,                // 横向
	DIR_VERTICAL                       // 垂直
};

#define IDD_TIMER_MOL_RENDER            10000                       // 主窗口刷新定时器
#define IDD_TIMER_MOL_GETLOG            10001                       // 用于发送日志到共享内存中
#define IDD_SOCKET_WND                  10002                       // 我们建立socket连接的窗口ID
#define IDD_WM_SOCKET_MESSAGE           10003                       // 用于处理网络消息的ID
#define IDD_WM_GAME_UPDATE              10004                       // 游戏更新消息
#define IDD_MESSAGE_HEART_JITTER        600                         // 游戏服务器心跳信息

#define MOLE2D_LOGGER_FILE              "mole2d.log"                // 系统使用的日志文件
#define MOLE2D_DOWNLOAD_TEMP_FILE       "download.temp"             // 用于下载的临时文件
#define MOLE2D_SYSTEM_DEFAULT_FONT      "DefaultFont"               // 系统初始字体名称
#define MOLE2D_SYSTEM_DEFAULT_DIRECTION "resources"                 // 系统初始的目录
#define MOLE2D_SYSTEM_INI_CONFIG        "systemini.ini"             // 系统初始配置文件
#define MOLE2D_SYSTEM_DEFAULT_SCRIPT    "游戏脚本\\gamelogic.lua"    // 系统初始加载脚本
#define MOLE2D_SYSTEM_DEFAULT_FONT_SIZE 14                          // 系統初始字體大小
#define MOLE2D_SYSTEM_SCREEN_WIDTH      800                         // 系统初始屏幕宽度
#define MOLE2D_SYSTEM_SCREEN_HEIGHT     600                         // 系统初始屏幕高度
#define MOLE2D_UNIQE_NAME               "{22E932F2-F618-4d74-93C0-1A315B52CDEF}"       // 用于控制程序单开


#define MOLE2D_GUI_CONTINUE_CONTAINER   10004                       // 继续运行包容器
#define MOLE2D_GUI_CLOSE_CONTAINER      10005                       // 关闭包容器
#define MOLE2D_GUI_MIN_FRAME            10006                       // 窗体最小化
#define MOLE2D_GUI_MAX_FRAME            10007                       // 窗体最大化
#define MOLE2D_GUI_RESERVE_FRAME        10008                       // 窗体重设
#define MOLE2D_GUI_CLOSE_FRAME          10009                       // 关闭游戏窗口
#define MOLE2D_GUI_ROOM_LIST            10010                       // 游戏房间列表

#define MOL_REV_BUFFER_SIZE             20480
#define MOL_SHARE_MEORY_COUNT           500                         // 一次读取日志个数
#define MOL_SHARE_MEMORY_SIZE           5000                        // 共享内存大小

//}
//}

#endif
