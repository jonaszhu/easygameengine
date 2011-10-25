#ifndef _MOL_SOCKET_MGR_WIN32_H_INCLUDE
#define _MOL_SOCKET_MGR_WIN32_H_INCLUDE

/** 
* MolNet网络引擎
*
* 描述:用于管理当前系统中所有的客户端
* 作者:akinggw
* 日期:2010.2.12
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
	/// 构造函数
	SocketMgr();
	/// 析构函数
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

	/// 得到当前有多少个客户端
	uint32 GetClientCount(void)
	{
		return (uint32)_sockets.size();
	}

	void ShutdownThreads();
	/// 设置最大支持客户端,如果为0的话，不限制客户端个数
	inline void SetMaxSockets(int c)
	{
		m_maxsockets = c;
	}
	/// 得到最大支持客户端数量
	inline uint32 GetMaxSockets(void)
	{
		return m_maxsockets;
	}

	/// 添加一个消息到列表中
	inline void AddMessage(MessageStru mes)
	{
		mesLock.Acquire();
		if(mes.GetType() == MES_TYPE_ON_DISCONNECTED || mes.GetType() == MES_TYPE_ON_CONNECTED)
			_MesList.push_front(mes);
		else
			_MesList.push_back(mes);
		mesLock.Release();
	}
	/// 得到当前消息个数
	inline int GetMesCount(void)
	{
		return (int)_MesList.size();
	}
	/// 锁定消息列表
	inline void LockMesList(void)
	{
		mesLock.Acquire();
	}
	/// 解锁消息列表
	inline void UnlockMesList(void)
	{
		mesLock.Release();
	}
	/// 得到消息列表
	inline std::list<MessageStru>* GetMesList(void)
	{
		return &_MesList;
	}
	/// 清空消息列表
	void ClearMesList(void);

	/// 添加一个任务到系统中
	inline void AddTask(ThreadBase *task)
	{
		if(task == NULL) return;

		_ThreadBases.push_back(task);
	}
	/// 清除系统中所有的任务
	void ClearTasks(void);
	/// 压缩我们要传输的数据
	char* compress(CMolMessageOut &out,int *declength);
	/// 解压我们接收到的数据
	char* uncompress(unsigned char *data,int srclength,int *declength);
	/// 加密数据
	void Encrypto(unsigned char *data,unsigned long length);
	/// 解密数据
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
