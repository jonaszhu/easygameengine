#ifndef _MOLE2D_COMMON_H_
#define _MOLE2D_COMMON_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2009.11.10
*/
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

#define MOLNET_HOST_TO_NET_16(value) (htons (value))
#define MOLNET_HOST_TO_NET_32(value) (htonl (value))

#define MOLNET_NET_TO_HOST_16(value) (ntohs (value))
#define MOLNET_NET_TO_HOST_32(value) (ntohl (value))

//#define MOL_REV_BUFFER_SIZE             10000
#define IDD_WM_SOCKET_MESSAGE           10003                       // 用于处理网络消息的ID
#define IDD_SOCKET_WND                  10002                       // 我们建立socket连接的窗口ID

#define IDD_REGISTER_TIP "- 未注册(购买正版授权请联系QQ:395314452)" // 注册提示

#pragma pack(push,1) //开始定义数据包, 采用字节对齐方式
/*----------------------包头---------------------*/
typedef struct tagPACKAGEHEAD
{
	BYTE Version;
	WORD Command;
	WORD nDataLen;//包体的长度
}PACKAGE_HEAD;
#pragma pack(pop) //结束定义数据包, 恢复原来对齐方式

#endif
