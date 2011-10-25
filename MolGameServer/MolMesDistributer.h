#ifndef _MOL_MES_DISTRIBUTER_H_INCLUDE
#define _MOL_MES_DISTRIBUTER_H_INCLUDE

#include "MolServerCom.h"

/**
 * 用于处理网络消息
 */
class CMolMesDistributer : public ThreadBase
{
public:
	/// 构造函数
	CMolMesDistributer();
	/// 析构函数
	~CMolMesDistributer();

	bool run();

private:
	NetMessage myMes;
	//Mutex m_MesLock;
};

/**
 * 用于维护当前服务器中所有的玩家
 */
class CMolGameServerPlayersUpdate : public ThreadBase
{
public:
	/// 构造函数
	CMolGameServerPlayersUpdate();
	/// 析构函数
	~CMolGameServerPlayersUpdate();

	bool run();

private:
	Mutex m_RoomPlayersLock;       
	DWORD m_curTimer;
};

/**
 * 用于游戏中房间更新
 */
class CMolGameRoomUpdate : public ThreadBase
{
public:
	/// 构造函数
	CMolGameRoomUpdate();
	/// 析构函数
	~CMolGameRoomUpdate();

	bool run();

private:
	Mutex m_RoomLock;                
};
#endif
