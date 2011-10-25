#ifndef _ROOM_MANAGER_H_INCLUDE_
#define _ROOM_MANAGER_H_INCLUDE_

#include "MolServerCom.h"

#include "Room.h"
#include "Player.h"

#include <list>

class RoomManager : public Singleton<RoomManager>
{
public:
	RoomManager();
	~RoomManager();

	/// 清除所有的房间
	void ClearAllRooms(void);
	/// 重新导入并执行脚本
	void ReLoadAndRunScript(void);

	/// 添加一个房间到房间管理器中
	void AddRoom(Room *pRoom);
	/// 添加一个玩家到房间中
	bool AddPlayer(Player *pPlayer,int roomIndex=-1,int chairIndex=-1);
	/// 添加一个旁观玩家到房间中
	bool AddLookOnPlayer(Player *pPlayer,int roomIndex,int chairIndex);
	/// 改变一个玩家的游戏房间
	bool ChangeGameRoom(Player *pPlayer);
	/// 从房间中清除指定的玩家
	void ClearPlayer(Player *pPlayer);
	/// 从当前房间中删除指定的玩家
	bool DeletePlayer(Player *pPlayer);
	/// 重置所有的游戏房间
	void ResetAllGameRooms(void);
	/// 根据房间ID号得到房间
	Room* GetRoomById(int id);
	/// 得到当前系统中的房间列表
	inline std::list<Room*>& GetRoomList(void) { return m_RoomList; }
	/// 得到当前系统中房间数量
	inline int GetRoomCount(void) { return (int)m_RoomList.size(); }
	/// 锁住当前房间
	inline void LockRoomList(void) { m_RoomLock.Acquire(); }
	/// 解锁当前房间
	inline void UnlockRoomList(void) { m_RoomLock.Release(); }

	/// 游戏所有房间更新
	void Update(DWORD time);
	/// 用于处理接收到的网络消息
	void OnProcessNetMes(int connId,CMolMessageIn *mes);
	/// 用于处理用于断开网络连接消息
	void OnProcessDisconnectNetMes(int connId);
	/// 用于处理玩家改变游戏房间
	void OnProcessChangeGameRoomMes(int connId);

private:
	std::list<Room*> m_RoomList;           /**< 房间列表 */    
	Mutex m_RoomLock;                      /**< 用于保护当前服务器上所有的房间 */
};

#define ServerRoomManager RoomManager::getSingleton()


#endif
