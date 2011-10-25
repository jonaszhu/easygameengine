#ifndef _MOLE2D_TCP_SOCKET_CLIENT_H_
#define _MOLE2D_TCP_SOCKET_CLIENT_H_

/** 
* Mole2d ͼ������
*
* ���ڽ���TCP���ӣ�����������Ϣ
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

#define REV_SIZE      30000                     // �������ݵĻ����С

class CMolBaseFrame;
class CMolCircularBuffer;

/** 
* ��ǰsocket������״̬
*/
enum ConnectState
{
	NOCONNECT = 0,     // û������
	CONNECTTING,       // ������
	CONNECTED,         // ������
	MESPROCESS         // ������Ϣ����
};

class MOLEXPORT CMolTcpSocketClient : public CWnd
{
public:
	/// ���캯��
	CMolTcpSocketClient(CWnd *pParent=NULL);
	/// ��������
	~CMolTcpSocketClient(void);

	/// �ر�����
	void CloseConnect(void);
	/// ����ָ���ķ�����
	bool Connect(std::string ipaddress,int port);
	/// ��������
	int Send(CMolMessageOut &msg);
	/// ���ص�ǰ����״̬
	inline ConnectState GetConnectState(void) { return m_bConnectState; }
	/// ��⵱ǰ�Ƿ���������
	inline bool IsConnected(void) 
	{ 
		if(m_bConnectState == CONNECTED || m_bConnectState == MESPROCESS)
			return true;

		return false;
	}

	/// ����Ҫ������Ϣ�Ĵ���
	inline void SetBaseFrame(CMolBaseFrame *pFrame)
	{
		m_BaseFrame = pFrame;
	}
	/// �õ�Ҫ������Ϣ�Ĵ���
	inline CMolBaseFrame* GetBaseFrame(void)
	{
		return m_BaseFrame;
	}
	
private:
	CWnd *m_Parent;                  /**< ��ǰ�ؼ��ĸ��ؼ� */
	SOCKET m_Socket;                 /**< ��ǰ�ؼ���socket��� */
	ConnectState m_bConnectState;    /**< ��ǰ������״̬ */
	CMolCircularBuffer *m_ReadBuffer;  /**< �������ݻ����� */
	CMolBaseFrame *m_BaseFrame;      /**< Ҫ����������Ϣ�Ĵ��� */
	unsigned int remaining;
	unsigned short opcode;

	char buffer[MOL_REV_BUFFER_SIZE];
	unsigned char *combuf,*uncombuf;

private:
	/// ����socket�Ի���
	void CreateSocketHwnd(CWnd *pParnet);
	/// ����socket������Ϣ
	LRESULT OnSocketNotifyMessage(WPARAM wParam,LPARAM lParam);
	/// ѹ������Ҫ���������
	char* compress(CMolMessageOut &out,int *declength);
	/// ��ѹ���ǽ��յ�������
	char* uncompress(unsigned char *data,int srclength,int *declength);
	/// ��������
	void Encrypto(unsigned char *data,unsigned long length);
	/// ��������
	void Decrypto(unsigned char *data,unsigned long length);

	DECLARE_MESSAGE_MAP()
};

//}
//}

#endif
