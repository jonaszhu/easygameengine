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
	/// ��ʼ���ű��ű�ϵͳ
	void InitScriptSystem(void);
	/// ж�ؽű�ϵͳ
	void ShutdownScriptSystem(void);
	/// ���벢ִ�нű�
	void LoadAndRunScript(void);
	/// �����ڴ�
	void ReGetMemory(void);
	/// �����û�׼����Ϣ
	void OnProcessPlayerReadyMes(Room *pRoom,int playerId);
	///// �����û���Ϸ����Ϣ
	//void OnProcessPlayerGamingMes(Room *pRoom,int playerId,CMolMessageIn *mes);
	/// �����û���������Ϣ
	void OnProcessPlayerRoomMes(Room *pRoom,int playerId,CMolMessageIn *mes);
	/// �����û����뷿����Ϣ
	void OnProcessEnterRoomMsg(Room *pRoom,int playerId);
	/// �����û��뿪������Ϣ
	void OnProcessLeaveRoomMsg(Room *pRoom,int playerId);
	/// �����û��Ͽ�������Ϣ
	void OnProcessDisconnectNetMes(Room *pRoom,int playerId);
	/// �����û�����������Ϣ
	void OnProcessDisconnectBackNetMes(Room *pRoom,int playerId);
	/// �����û���ʱ����Ϣ
	void OnProcessTimerMsg(Room *pRoom,int timerId,int curTimer);

private:
	lua_State *m_luaState;
	//Mutex m_StateLock;
};

#endif
