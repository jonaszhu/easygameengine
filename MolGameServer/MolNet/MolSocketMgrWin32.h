#ifndef _MOL_SOCKET_MGR_WIN32_H_INCLUDE
#define _MOL_SOCKET_MGR_WIN32_H_INCLUDE

/** 
* MolNet��������
*
* ����:���ڹ���ǰϵͳ�����еĿͻ���
* ����:akinggw
* ����:2010.2.12
*/

#include "MolCommon.h"
#include "AtomicCounter.h"
#include "MolSingleton.h"
#include "MolThreadStarter.h"
#include "MolThreadPool.h"
#include "MolSocketDefines.h"
#include "MolSocket.h"

#include "MolNetMessage.h"

class SocketMgr : public Singleton<SocketMgr>
{
public:
	/// ���캯��
	SocketMgr();
	/// ��������
	~SocketMgr();

	inline HANDLE GetCompletionPort() { return m_completionPort; }
	void SpawnWorkerThreads();
	void CloseAll();
	void ShowStatus();
	void AddSocket(SOCKET fd,Socket * s)
	{
		socketLock.Acquire();
		_sockets.insert(std::pair<SOCKET,Socket*>(fd,s));
		++socket_count;
		socketLock.Release();
	}

	void RemoveSocket(Socket * s)
	{
		if(!s) return;

		socketLock.Acquire();
		std::map<SOCKET,Socket*>::iterator iter = _sockets.find(s->GetFd());
		if(iter != _sockets.end())
			_sockets.erase(iter);	
		--socket_count;
		socketLock.Release();
	}

	Socket* FindSocket(SOCKET fd)
	{
		if(_sockets.empty()) return NULL;

		socketLock.Acquire();
		std::map<SOCKET,Socket*>::iterator iter = _sockets.find(fd);
		socketLock.Release();

		if(iter != _sockets.end())
			return (*iter).second;

		return NULL;
	}

	/// �õ���ǰ�ж��ٸ��ͻ���
	uint32 GetClientCount(void)
	{
		return (uint32)_sockets.size();
	}

	void ShutdownThreads();
	/// �������֧�ֿͻ���,���Ϊ0�Ļ��������ƿͻ��˸���
	inline void SetMaxSockets(int c)
	{
		m_maxsockets = c;
	}
	/// �õ����֧�ֿͻ�������
	inline uint32 GetMaxSockets(void)
	{
		return m_maxsockets;
	}

	/// ���һ����Ϣ���б���
	inline void AddMessage(MessageStru mes)
	{
		mesLock.Acquire();
		if(mes.GetType() == MES_TYPE_ON_DISCONNECTED || mes.GetType() == MES_TYPE_ON_CONNECTED)
			_MesList.push_front(mes);
		else
			_MesList.push_back(mes);
		mesLock.Release();
	}
	/// �õ���ǰ��Ϣ����
	inline int GetMesCount(void)
	{
		return (int)_MesList.size();
	}
	/// ������Ϣ�б�
	inline void LockMesList(void)
	{
		mesLock.Acquire();
	}
	/// ������Ϣ�б�
	inline void UnlockMesList(void)
	{
		mesLock.Release();
	}
	/// �õ���Ϣ�б�
	inline std::list<MessageStru>* GetMesList(void)
	{
		return &_MesList;
	}
	/// �����Ϣ�б�
	void ClearMesList(void);

	/// ���һ������ϵͳ��
	inline void AddTask(ThreadBase *task)
	{
		if(task == NULL) return;

		_ThreadBases.push_back(task);
	}
	/// ���ϵͳ�����е�����
	void ClearTasks(void);
	/// ѹ������Ҫ���������
	char* compress(CMolMessageOut &out,int *declength);
	/// ��ѹ���ǽ��յ�������
	char* uncompress(unsigned char *data,int srclength,int *declength);
	/// ��������
	void Encrypto(unsigned char *data,unsigned long length);
	/// ��������
	void Decrypto(unsigned char *data,unsigned long length);

	long threadcount;

private:
	HANDLE m_completionPort;
	std::map<SOCKET,Socket*> _sockets;
	std::list<MessageStru> _MesList;
	Mutex mesLock;
	Mutex socketLock;
	uint32 m_maxsockets;
	unsigned char *combuf,*uncombuf;
	std::list<ThreadBase*> _ThreadBases;
	AtomicCounter socket_count;
};

#define sSocketMgr SocketMgr::getSingleton()

typedef void(*OperationHandler)(Socket * s,uint32 len);

class SocketWorkerThread : public ThreadBase
{
public:
	bool run();
};

void HandleReadComplete(Socket * s,uint32 len);
void HandleWriteComplete(Socket * s,uint32 len);
void HandleShutdown(Socket * s,uint32 len);

static OperationHandler ophandlers[NUM_SOCKET_IO_EVENTS] = {
	&HandleReadComplete,
	&HandleWriteComplete,
	&HandleShutdown };

#endif
