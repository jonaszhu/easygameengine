#ifndef _MOLE2D_TCP_SOCKET_CLIENT_H_
#define _MOLE2D_TCP_SOCKET_CLIENT_H_

/** 
* Mole2d 图像引擎
*
* 用于建立TCP连接，处理网络信息
*
* author: akinggw
* date: 2009.11.15
*/

#include "Mole2dCommon.h"
#include "Mole2dLogger.h"

#include "Mole2dMessageIn.h"
#include "Mole2dMessageOut.h"

#include <string>

//namespace mole2d
//{
//namespace graphics
//{  

#define REV_SIZE      30000                     // 接收数据的缓冲大小

class CMolBaseFrame;
class CMolCircularBuffer;

/** 
* 当前socket的连接状态
*/
enum ConnectState
{
	NOCONNECT = 0,     // 没有连接
	CONNECTTING,       // 连接中
	CONNECTED,         // 连接上
	MESPROCESS         // 网络消息处理
};

class MOLEXPORT CMolTcpSocketClient : public CWnd
{
public:
	/// 构造函数
	CMolTcpSocketClient(CWnd *pParent=NULL);
	/// 析构函数
	~CMolTcpSocketClient(void);

	/// 关闭连接
	void CloseConnect(void);
	/// 连接指定的服务器
	bool Connect(std::string ipaddress,int port);
	/// 发送数据
	int Send(CMolMessageOut &msg);
	/// 返回当前连接状态
	inline ConnectState GetConnectState(void) { return m_bConnectState; }
	/// 检测当前是否还在连接中
	inline bool IsConnected(void) 
	{ 
		if(m_bConnectState == CONNECTED || m_bConnectState == MESPROCESS)
			return true;

		return false;
	}

	/// 设置要处理消息的窗体
	inline void SetBaseFrame(CMolBaseFrame *pFrame)
	{
		m_BaseFrame = pFrame;
	}
	/// 得到要处理消息的窗体
	inline CMolBaseFrame* GetBaseFrame(void)
	{
		return m_BaseFrame;
	}
	
private:
	CWnd *m_Parent;                  /**< 当前控件的父控件 */
	SOCKET m_Socket;                 /**< 当前控件的socket句柄 */
	ConnectState m_bConnectState;    /**< 当前的连接状态 */
	CMolCircularBuffer *m_ReadBuffer;  /**< 接收数据缓冲区 */
	CMolBaseFrame *m_BaseFrame;      /**< 要处理网络消息的窗体 */
	unsigned int remaining;
	unsigned short opcode;

	char buffer[MOL_REV_BUFFER_SIZE];
	unsigned char *combuf,*uncombuf;

private:
	/// 建立socket对话框
	void CreateSocketHwnd(CWnd *pParnet);
	/// 处理socket网络消息
	LRESULT OnSocketNotifyMessage(WPARAM wParam,LPARAM lParam);
	/// 压缩我们要传输的数据
	char* compress(CMolMessageOut &out,int *declength);
	/// 解压我们接收到的数据
	char* uncompress(unsigned char *data,int srclength,int *declength);
	/// 加密数据
	void Encrypto(unsigned char *data,unsigned long length);
	/// 解密数据
	void Decrypto(unsigned char *data,unsigned long length);

	DECLARE_MESSAGE_MAP()
};

//}
//}

#endif
