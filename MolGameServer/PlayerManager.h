#ifndef _PLAYER_MANAGER_H_INCLUDE_
#define _PLAYER_MANAGER_H_INCLUDE_

#include "MolServerCom.h"

#include "Player.h"

#include <map>

class PlayerManager : public Singleton<PlayerManager>
{
public:
	PlayerManager();
	~PlayerManager();

	/// 清除所有的玩家
	void ClearAllPlayers(void);
	/// 添加一个玩家到系统中
	void AddPlayer(Player *pPlayer);
	/// 添加一个机器人到系统中
	void AddRobot(Player *pPlayer);
	/// 根据玩家的连接ID设置玩家
	void Reset(int oldConn,Player *pPlayer);
	/// 得到空闲的机器人
	Player* GetFreeRobot(void);
	/// 从系统中删除指定的玩家
	void ClearPlayer(Player *pPlayer);
	/// 从系统中删除指定网络ID的玩家
	void ClearPlayerByconnId(int connId);
	/// 通过客户端连接ID得到客户端
	Player* GetPlayer(int connId);
	/// 通过客户端连接ID得到刚登陆的客户端
	Player* GetNewPlayer(int connId);
	/// 通过玩家ID得到客户端
	Player* GetPlayerById(int id);
	/// 得到当前系统玩家个数
	inline int GetPlayerCount(void) { return (int)m_PlayerList.size(); } 
	/// 得到当前系统机器人个数
	inline int GetRobotCount(void) { return (int)m_RobotList.size(); }
	/// 得到当前系统总的玩家人数
	inline int GetTotalCount(void) { return GetPlayerCount() + GetRobotCount(); }
	/// 锁定当前玩家
	inline void LockPlayerList(void) { m_PlayersLock.Acquire(); }
	/// 解锁当前玩家
	inline void UnlockPlayerList(void) { m_PlayersLock.Release(); }
	/// 得到在线玩家列表
	inline std::map<int,Player*>& GetPlayerList(void) { return m_PlayerList; }
	/// 得到在线机器人列表
	inline std::map<int,Player*>& GetRobotList(void) { return m_RobotList; }

	/// 发送消息给当前在线的所有玩家
	void SendMsgToEveryone(CMolMessageOut &msg);
	/// 发送消息给除了指定玩家的所有在线玩家
	void SendMsgToOtherPlayer(int connId,CMolMessageOut &msg);
	/// 发送给所有玩家心跳包
	void SendAllPlayersHeartJitter(void);
	/// 用于维护当前所有的玩家
	void OnProcessAllPlayersHeart(void);

private:
	std::map<int,Player*> m_PlayerList;                 /**< 玩家列表 */
	std::map<int,Player*> m_RobotList;                  /**< 机器人列表 */
	Mutex m_PlayersLock;                                /**< 保护当前在线玩家 */
};

#define ServerPlayerManager PlayerManager::getSingleton()

#endif
