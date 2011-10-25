#ifndef _MOLE2D_COMMON_H_
#define _MOLE2D_COMMON_H_

/** 
* Mole2d ͼ������
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
#define IDD_WM_SOCKET_MESSAGE           10003                       // ���ڴ���������Ϣ��ID
#define IDD_SOCKET_WND                  10002                       // ���ǽ���socket���ӵĴ���ID

#define IDD_REGISTER_TIP "- δע��(����������Ȩ����ϵQQ:395314452)" // ע����ʾ

#pragma pack(push,1) //��ʼ�������ݰ�, �����ֽڶ��뷽ʽ
/*----------------------��ͷ---------------------*/
typedef struct tagPACKAGEHEAD
{
	BYTE Version;
	WORD Command;
	WORD nDataLen;//����ĳ���
}PACKAGE_HEAD;
#pragma pack(pop) //�����������ݰ�, �ָ�ԭ�����뷽ʽ

#endif
