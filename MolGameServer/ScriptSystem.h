#ifndef _SCRIPT_SYSTEM_H_INCLUDE_
#define _SCRIPT_SYSTEM_H_INCLUDE_

#include "MolServerCom.h"

#include "Player.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#define IDD_GAME_ROOM_SCRIPT "gameroom.lua"

class Room;

class ScriptSystem
{
public:
	/// 初始化脚本脚本系统
	void InitScriptSystem(void);
	/// 卸载脚本系统
	void ShutdownScriptSystem(void);
	/// 导入并执行脚本
	void LoadAndRunScript(void);
	/// 回收内存
	void ReGetMemory(void);
	/// 处理用户准备消息
	void OnProcessPlayerReadyMes(Room *pRoom,int playerId);
	///// 处理用户游戏中消息
	//void OnProcessPlayerGamingMes(Room *pRoom,int playerId,CMolMessageIn *mes);
	/// 处理用户房间中消息
	void OnProcessPlayerRoomMes(Room *pRoom,int playerId,CMolMessageIn *mes);
	/// 处理用户进入房间消息
	void OnProcessEnterRoomMsg(Room *pRoom,int playerId);
	/// 处理用户离开房间消息
	void OnProcessLeaveRoomMsg(Room *pRoom,int playerId);
	/// 处理用户断开连接消息
	void OnProcessDisconnectNetMes(Room *pRoom,int playerId);
	/// 处理用户断线重连消息
	void OnProcessDisconnectBackNetMes(Room *pRoom,int playerId);
	/// 处理用户定时器消息
	void OnProcessTimerMsg(Room *pRoom,int timerId,int curTimer);

private:
	lua_State *m_luaState;
	//Mutex m_StateLock;
};

#endif
