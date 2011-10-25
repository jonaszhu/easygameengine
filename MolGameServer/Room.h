#ifndef _ROOM_H_INCLUDE_
#define _ROOM_H_INCLUDE_

#include "MolServerCom.h"
#include "Player.h"

#include <vector>
#include <string>
#include <map>

#include "ScriptSystem.h"

// 最大房间人数
#define ROOM_MAX_PLAYERS  500

/**
 * 房间类型
 */
enum RoomType
{
	ROOMTYPE_JINBIN = 0,             // 金币房间
	ROOMTYPE_JIFEN,                  // 积分房间
	ROOMTYPE_BISAI,                  // 比赛房间
	ROOMTYPE_LIANXI,                 // 练习房间
	ROOMTYPE_NULL
};

/**
 * 房间当前状态
 */
enum RoomState
{
	ROOMSTATE_WAITING = 0,             // 等待中
	ROOMSTATE_GAMING,                  // 游戏中
	ROOMSTATE_NULL
};

/** 
 * 房间中用到的定时器结构
 */
struct RoomTimer
{
	RoomTimer():TimerId(0),TimerSpace(0),curTime(0),m_isEnable(false) {}
	RoomTimer(long ti,int ts):TimerId(ti),TimerSpace(ts),curTime(ts),m_isEnable(true) {}

	long TimerId;                      // 时间ID
	int TimerSpace;                    // 时间间隔
	int curTime;                       // 当前时间
	bool m_isEnable;                   // 是否可用
};

class Room
{
public:
	Room(RoomType type=ROOMTYPE_NULL);
	virtual ~Room();

	/// 重新导入并执行脚本
	void ReLoadAndRunScript(void);
	/// 设置房间ID
	inline void SetID(int id) { m_Id = id; }
	/// 得到房间ID
	inline int GetID(void) { return m_Id; }
	/// 设置房间类型
	inline void SetRoomType(RoomType type) { m_RoomType = type; }
	/// 得到房间类型
	inline RoomType GetRoomType(void) { return m_RoomType; }
	/// 设置房间玩家人数
	inline void SetMaxPlayer(int max) 
	{ 
		if(max > ROOM_MAX_PLAYERS)
			m_MaxCount = ROOM_MAX_PLAYERS;
		else
			m_MaxCount = max; 
	}
	/// 得到房间玩家人数
	inline int GetMaxPlayer(void) { return m_MaxCount; }
	/// 设置房间状态
	inline void SetRoomState(RoomState state) { m_RoomState = state; }
	/// 得到房间状态
	inline RoomState GetRoomState(void) { return m_RoomState; }
	/// 设置房间名称
	inline void SetName(std::string name) { m_Name = name; }
	/// 得到房间名称
	inline std::string GetName(void) { return m_Name; }
	/// 设置游戏抽水值
	inline void SetChouShui(float cs) { m_RoomRevenue = cs; }
	/// 得到游戏抽水值
	inline float GetChouShui(void) { return m_RoomRevenue; }
	/// 设置游戏需要的最少金币
	inline void SetLastMoney(unsigned int money) { m_RoomLastMoney = money; }
	/// 得到游戏需要的最少金币
	inline unsigned int GetLastMoney(void) { return m_RoomLastMoney; }
	/// 当前房间是否为空
	bool IsEmpty(void);
	/// 得到指定索引的玩家
	Player* GetPlayer(int index);
	/// 得到当前房间人数
	int GetPlayerCount(void);
	/// 得到准备好状态下玩家的人数
	int GetReadyPlayerCount(void);
	/// 设置当前房间的房主
	void SetMaster(int playerId);
	/// 得到当前房间的房主，房主为当前第一准备开始游戏的玩家
	inline int GetMaster(void) { return m_masterId; }
	/// 得到房间中当前的玩家
	inline int GetCurrentPlayer(void) { return m_curPlayerId; }
	/// 根据用户连接ID得到用户在房间中的ID
	int GetPlayerRoomId(int connId);
	/// 得到当前房间指定状态的玩家个数
	int GetPlayerCount(PlayerState state);
	/// 设置当前房间所有玩家的状态
	void SetAllPlayerState(PlayerState state);
	/// 设置指定玩家的状态
	void SetPlayerState(int index,PlayerState state);
	/// 设置房间中当前玩家
	inline void SetCurrentPlayer(int playerId) { m_curPlayerId = playerId; }
	/// 得到当前房间中下一个玩家
	int GetCurNextPlayer(void);
	/// 得到当前房间中下一个出牌玩家
	int GetCurNextWorkPlayer(void);

	/// 清除房间中所有的玩家
	void ClearAllPlayers(void);
	/// 添加一个玩家到当前房间中
	int AddPlayer(Player *pPlayer,int index=-1);
	/// 添加一个旁观玩家到当前房间中
	int AddLookOnPlayer(Player *pPlayer,int index);
	/// 从当前房间中清除指定的玩家
	void ClearPlayer(Player *pPlayer);
	/// 从当前房间中删除指定的玩家
	void DeletePlayer(Player *pPlayer);
	/// 从当前房间中清除指定房间ID的玩家
	void ClearPlayerById(int Id);
	/// 检测指定玩家是否存在当前房间
	bool IsExist(Player *pPlayer);
	/// 检测指定的旁观玩家是否存在当前房间中
	bool IsExistLookOn(Player *pPlayer);
	/// 检测房间是否已经满员
	bool IsFull(void);
	/// 检测房间是否全部准备完毕
	bool IsReadyed(void);
	/// 根据玩家连接id得到玩家在当前房间中的索引
	int GetPlayerIndex(int connId);
	/// 得到当前房间中掉线玩家人数
	inline int GetLostPlayerCount(void) { return (int)m_lostPlayerList.size(); }
	/// 清除掉线玩家列表中玩家
	void ClearLostPlayerById(int id);
	/// 清空当前房间数据
	void Clear(void);
	/// 更新指定玩家的数据
	void UpdateUserScore(int ChairID);
	/// 游戏结束时调用
	void GameEnd(void);
	/// 游戏开始是调用
	void GameStart(void);

	/// 向当前房间所有玩家发送用户离开服务器消息
	void AllPlayerLeveaServer(void);
	
	/// 向指定的玩家发送数据
	void SendTableMsg(int index,CMolMessageOut &msg);
	/// 向指定的玩家发送旁观数据
	void SendLookOnMes(int index,CMolMessageOut &msg);
	/// 向所有玩家发送数据
	void SendAllPlayerMsg(CMolMessageOut &msg);
	///// 向除了指定玩家的其它玩家发送数据
	//void SendOtherPlayerMsg(int index,CMolMessageOut &msg);

	/// 打印调试信息
	void PrintDebugInfo(const char* info);
	/// 开始一个定时器
	bool StartTimer(int timerId,int space);
	/// 关闭一个定时器
	void StopTimer(int id);
	/// 关闭所有的定时器
	void StopAllTimer(void);

	/// 游戏房间更新
	virtual void Update(DWORD time);
	/// 用于处理接收到的网络消息
	virtual void OnProcessNetMes(int connId,CMolMessageIn *mes);
	/// 更新房间中所有的当前用户--这个函数用于防止用户突然离开房间
	void UpdateOnlinePlayers(void);
	///// 更新房间中所有的用户--这个函数用于防止一些用户已经掉线，但没有离开房间
	//void UpdateAllPlayers(void);

	/// 用于处理用户准备后的消息
	void OnProcessPlayerReadyMes(int playerId);
	///// 用于处理用户开始游戏后的消息
	//void OnProcessPlayerGamingMes(int playerId,CMolMessageIn *mes);
	/// 用于处理用户进入游戏房间后的消息
	void OnProcessPlayerRoomMes(int playerId,CMolMessageIn *mes);
	/// 处理用户进入房间消息
	void OnProcessEnterRoomMsg(int playerId);
	/// 处理用户离开房间消息
	void OnProcessLeaveRoomMsg(int playerId);
	/// 处理用户断开连接消息
	void OnProcessDisconnectNetMes(int playerId);
	/// 处理用户断线重连消息
	void OnProcessDisconnectBackNetMes(int playerId);
	/// 处理用户定时器消息
	void OnProcessTimerMsg();

private:
	/// 向所有旁观玩家发送数据
	void SendAllLookOnPlayerMsg(CMolMessageOut &msg);
	/// 检测指定的索引是否在掉线玩家列表中
	bool IsExistLostPlayer(int index);
	static void CALLBACK MyTimeProc(void*, BOOLEAN);  

private:
	int m_Id;                   /**< 房间ID */
	std::string m_Name;         /**< 房间名称 */
	int m_MaxCount;             /**< 房间中最大玩家个数 */
	RoomType m_RoomType;        /**< 房间类型 */
	RoomState m_RoomState;      /**< 房间当前状态 */
	float m_RoomRevenue;        /**< 房间税收 */
	int m_RoomLastMoney;        /**< 房间最小金币 */

	int m_masterId;             /**< 当前房主ID */
	int m_curPlayerId;          /**< 当前玩家ID */

	Player *m_PlayerList[ROOM_MAX_PLAYERS];       /**< 房间中游戏玩家列表 */
	std::map<int,std::vector<Player*> > m_LookonPlayerList;       /**< 房间中旁观玩家列表 */
	std::vector<int> m_lostPlayerList;            /**< 房间中掉线玩家列表 */
	std::map<long,RoomTimer> m_timerList;                /**< 房间中用到的定时器 */
	HANDLE hRoomTimer;

	ScriptSystem m_ScriptSystem;                  /**< 脚本系统 */
	Mutex m_playersLock;                          /**< 用于玩家操作 */
	Mutex m_timerLock;                            /**< 用于保护房间中的定时器 */
	//Mutex m_scriptLock;                           /**< 用于保护脚本操作 */
};

#endif
