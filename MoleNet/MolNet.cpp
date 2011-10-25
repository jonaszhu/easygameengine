#include "MolNet.h"

#include "MolSocket.h"
#include "MolSocketMgrWin32.h"
#include "MolListenSocketWin32.h"

#include <stdio.h>

ListenSocket<NetClient> *m_ServerSocket = NULL;

namespace mole2d
{
namespace network
{

/** 
* ��ʼ���磬������Ӧ�Ĳ���
*
* @param MaxClients ���������֧�ֵĿͻ������������Ϊ0�Ļ���ʾû������
* @param TimeOut ���������õĳ�ʱ����ʼΪ60
* @param bufferSize ���������õ��ڲ���������С�����Ϊ0�Ļ���ʾʹ��Ĭ�ϴ�С
*
*/
void InitMolNet(uint32 MaxClients,uint32 TimeOut,uint32 bufferSize)
{
	ThreadPool.Startup();

	new SocketMgr;
	new SocketGarbageCollector;

	sSocketMgr.SpawnWorkerThreads();
	sSocketMgr.SetMaxSockets(MaxClients);

	m_ServerSocket = new ListenSocket<NetClient>();
	if(m_ServerSocket)
	{
		m_ServerSocket->SetTimeOut(TimeOut);
		m_ServerSocket->SetBufferSize(bufferSize);
	}

	// ���������������߳�
	m_NetworkUpdate = new MolNetworkUpdate();
}

/**
 * ֹͣ�������
 */
void StopMolNet(void)
{
	if(m_ServerSocket)
		m_ServerSocket->Close();
}

/** 
* ж������
*/
void CleanMolNet(void)
{
	StopMolNet();

	sSocketMgr.CloseAll();
	sSocketMgr.ShutdownThreads();

	ThreadPool.Shutdown();

	delete SocketMgr::getSingletonPtr();
	delete SocketGarbageCollector::getSingletonPtr();

	if(m_ServerSocket)
		delete m_ServerSocket;
	m_ServerSocket = NULL;

	if(m_NetworkUpdate)
		delete m_NetworkUpdate;
	m_NetworkUpdate = NULL;

	WSACleanup();
}

/** 
* ��ʼ�������
*
* @param ListenAddress �����������ַ
* @param Port �����ķ������˿�
*
* @return ���������������ɹ�������,���򷵻ؼ�
*/
bool StartMolNet(const char * ListenAddress, uint32 Port)
{
	if(!m_ServerSocket) return false;

	if(!m_ServerSocket->Start(ListenAddress,Port))
		return false;

	if(m_ServerSocket->IsOpen())
	{
		ThreadPool.ExecuteTask(m_ServerSocket);
		ThreadPool.ExecuteTask(m_NetworkUpdate);

		return true;
	}

	return false;
}

/** 
* �������Ƿ񻹴�������״̬
*
* @return �����������������״̬�����棬���򷵻ؼ�
*/
bool IsConnected(void)
{
	if(m_ServerSocket == NULL) return false;

	return m_ServerSocket->IsOpen();
}

/** 
* ָֹͣ���Ŀͻ���
*
* @param index Ҫֹͣ�Ŀͻ��˵�����
*/
void Disconnect(uint32 index)
{
	Socket *pSocket = sSocketMgr.FindSocket(index);
	if(pSocket && 
		pSocket->IsConnected()) 
	{
		pSocket->Disconnect();
	}
}

/**
 * ���ָ���ͻ����Ƿ��Ѿ�����
 *
 * @param index Ҫ������ӵĿͻ�������
 *
 * @return ������Ҫ���Ŀͻ����Ѿ����ӷ����棬���򷵻ؼ�
 */
bool IsConnected(uint32 index)
{
	Socket *pSocket = sSocketMgr.FindSocket(index);
	if(pSocket)
		return pSocket->IsConnected();
	
	return false;
}

/** 
* ����ָ�������ݵ�ָ���Ŀͻ���
*
* @param index Ҫ�������ݵĿͻ�������
* @param out Ҫ���͵�����
*
* @return ������ݷ��ͳɹ�������,���򷵻ؼ�
*/
bool Send(uint32 index,CMolMessageOut &out)
{
	Socket *pSocket = sSocketMgr.FindSocket(index);
	if(!pSocket) return false;
	
	return pSocket->Send(out);
}

/**  
* �õ�ָ���ͻ��˵�IP��ַ
*
* @param index Ҫ�õ�IP��ַ�Ŀͻ��˵�����
*
* @return �������ͻ�����IP��ַ����IP��ַ,���򷵻�NULL
*/
std::string GetIpAddress(uint32 index)
{
	Socket *pSocket = sSocketMgr.FindSocket(index);
	if(!pSocket) return NULL;

	return pSocket->GetRemoteIP();
}

/** 
* �õ���Ϣ�б�
*
* @param mes ���ڴ洢�õ�����Ϣ
*
* @return ���صõ�����Ϣ�ĸ���
*/
int GetNetMessage(NetMessage & mes)
{
	mes.Clear();

	if(sSocketMgr.GetMesCount() <= 0 ||
		mes.GetMaxCount() <= 0)
		return 0;

	int count = 0;

	// �����ǰϵͳ�е���Ϣ����С������Ҫ��ȡ�ĸ���ʱ����ȡȫ������Ϣ��
	// �����ȡ�������õ���Ϣ��������Ϣ
	if(sSocketMgr.GetMesCount() < mes.GetMaxCount())
	{
		count = sSocketMgr.GetMesCount();

		sSocketMgr.LockMesList();
		std::list<MessageStru> *meslist = sSocketMgr.GetMesList();
		if(meslist == NULL || meslist->empty()) 
		{
			sSocketMgr.UnlockMesList();
			return 0;
		}

		std::list<MessageStru>::iterator iter = meslist->begin();
		for(;iter != meslist->end();)
		{
			mes.AddMessage((*iter));
			iter = meslist->erase(iter);
		}
		sSocketMgr.UnlockMesList();
	}
	else
	{
		sSocketMgr.LockMesList();
		std::list<MessageStru> *meslist = sSocketMgr.GetMesList();
		if(meslist == NULL || meslist->empty()) 
		{
			sSocketMgr.UnlockMesList();
			return 0;
		}

		std::list<MessageStru>::iterator iter = meslist->begin();
		for(int i=0;iter != meslist->end(),i<mes.GetMaxCount();i++)
		{
			if(iter == meslist->end()) break;

			mes.AddMessage((*iter));
			iter = meslist->erase(iter);
		}
		sSocketMgr.UnlockMesList();

		count = mes.GetMaxCount();
	}

	return count;
}

/** 
* ִ��һ��ָ��������
*
* @param task ����Ҫִ�е�����
*/
void ExecuteTask(ThreadBase * ExecutionTarget)
{
	sSocketMgr.AddTask(ExecutionTarget);

	ThreadPool.ExecuteTask(ExecutionTarget);
}

}
}
