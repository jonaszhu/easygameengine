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

#include "MolServerCom.h"
#include "Mole2dCommon.h"
#include "Mole2dLogger.h"

#include <string>

#define REV_SIZE      30000                     // �������ݵĻ����С

class CMolServerDlg;
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

class CMolTcpSocketClient : public CWnd
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
	inline bool IsConnected(void) { return m_bConnectState == CONNECTED ? true : false; }

	/// ����Ҫ������Ϣ�Ĵ���
	inline void SetBaseFrame(CMolServerDlg *pFrame)
	{
		m_BaseFrame = pFrame;
	}
	/// �õ�Ҫ������Ϣ�Ĵ���
	inline CMolServerDlg* GetBaseFrame(void)
	{
		return m_BaseFrame;
	}
	
private:
	CWnd *m_Parent;                  /**< ��ǰ�ؼ��ĸ��ؼ� */
	SOCKET m_Socket;                 /**< ��ǰ�ؼ���socket��� */
	ConnectState m_bConnectState;    /**< ��ǰ������״̬ */
	CMolCircularBuffer *m_ReadBuffer;  /**< �������ݻ����� */
	CMolServerDlg *m_BaseFrame;      /**< Ҫ����������Ϣ�Ĵ��� */
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

#endif
