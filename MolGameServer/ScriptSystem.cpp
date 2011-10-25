#include "stdafx.h"

#include "ScriptSystem.h"
#include "Room.h"

#include "MolServerDlg.h"

int  tolua_MolServer_open (lua_State* tolua_S);

/**
 * 卸载脚本系统
 */
void ScriptSystem::ShutdownScriptSystem(void)
{
	if(m_luaState) lua_close(m_luaState);
}

/**
 * 初始化脚本脚本系统
 */
void ScriptSystem::InitScriptSystem(void)
{
	m_luaState = lua_open();

	luaL_openlibs(m_luaState);
	tolua_MolServer_open(m_luaState);

	int state = luaL_dofile(m_luaState, IDD_GAME_ROOM_SCRIPT);
	if(state != 0)
	{
		char buf[128];
		sprintf(buf,"【游戏房间】 脚本文件:%s导入失败:%s!" ,IDD_GAME_ROOM_SCRIPT,lua_tostring(m_luaState, -1));    
		CMolServerDlg::getSingleton().PrintLog(buf);
	}
}

/**
 * 导入并执行脚本
 */
void ScriptSystem::LoadAndRunScript(void)
{
	int state = luaL_dofile(m_luaState, IDD_GAME_ROOM_SCRIPT);
	if(state != 0)
	{
		char buf[128];
		sprintf(buf,"【游戏房间】 脚本文件:%s导入失败:%s!" ,IDD_GAME_ROOM_SCRIPT,lua_tostring(m_luaState, -1));      
		CMolServerDlg::getSingleton().PrintLog(buf);
	}
}

/** 
 * 回收内存
 */
void ScriptSystem::ReGetMemory(void)
{
	//m_StateLock.Acquire();
	try
	{
		luaL_dostring(m_luaState,"collectgarbage('collect')");
	}
	catch(...)
	{

	}
	//m_StateLock.Release();
}

/**
 * 处理用户准备消息
 *
 * @param pRoom 要处理的游戏房间
 * @param playerId 要处理的房间玩家的ID
 */
void ScriptSystem::OnProcessPlayerReadyMes(Room *pRoom,int playerId)
{
	if(pRoom == NULL || playerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// 初始脚本加载函数
		lua_getglobal(m_luaState, "OnProcessPlayerReadyMes"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, playerId); 

		if( lua_pcall(m_luaState, 2, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"【游戏房间】 调用函数 OnProcessPlayerReadyMes 失败:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}

///**
// * 处理用户游戏中消息
// *
// * @param pRoom 要处理的游戏房间
// * @param playerId 要处理的房间玩家的ID
// * @param mes 要处理的玩家消息
// */
//void ScriptSystem::OnProcessPlayerGamingMes(Room *pRoom,int playerId,CMolMessageIn *mes)
//{
//	if(pRoom == NULL || mes == NULL || playerId == -1) return;
//
//	try
//	{
//		// 初始脚本加载函数
//		lua_getglobal(m_luaState, "OnProcessPlayerGamingMes"); 
//		lua_pushlightuserdata(m_luaState, pRoom); 
//		lua_pushinteger(m_luaState, playerId); 
//		lua_pushlightuserdata(m_luaState, mes); 
//
//		if( lua_pcall(m_luaState, 3, 0, 0) != 0 ) 
//		{         
//			char buf[128];
//			sprintf(buf,"【游戏房间】 调用函数 OnProcessPlayerGamingMes 失败:%s\n" ,lua_tostring(m_luaState, -1));    
//			CMolServerDlg::getSingleton().PrintLog(buf);
//		} 
//	}
//	catch(...)
//	{
//	
//	}
//}

/** 
 * 处理用户房间中消息
 *
 * @param pRoom 要处理的游戏房间
 * @param playerId 要处理的房间玩家的ID
 * @param mes 要处理的玩家消息
 */
void ScriptSystem::OnProcessPlayerRoomMes(Room *pRoom,int playerId,CMolMessageIn *mes)
{
	if(pRoom == NULL || mes == NULL || playerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// 初始脚本加载函数
		lua_getglobal(m_luaState, "OnProcessPlayerRoomMes"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, playerId); 
		lua_pushlightuserdata(m_luaState, mes); 

		if( lua_pcall(m_luaState, 3, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"【游戏房间】 调用函数 OnProcessPlayerRoomMes 失败:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}

/**
 * 处理用户进入房间消息
 *
 * @param pRoom 要处理的游戏房间
 * @param playerId 用户在房间中的ID
 */
void ScriptSystem::OnProcessEnterRoomMsg(Room *pRoom,int playerId)
{
	if(pRoom == NULL || playerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// 初始脚本加载函数
		lua_getglobal(m_luaState, "OnProcessEnterRoomMsg"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, playerId);

		if( lua_pcall(m_luaState, 2, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"【游戏房间】 调用函数 OnProcessEnterRoomMsg 失败:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}

/**
 * 处理用户离开房间消息
 *
 * @param pRoom 要处理的游戏房间
 * @param playerId 用户在房间中的ID
 */
void ScriptSystem::OnProcessLeaveRoomMsg(Room *pRoom,int playerId)
{
	if(pRoom == NULL || playerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// 初始脚本加载函数
		lua_getglobal(m_luaState, "OnProcessLeaveRoomMsg"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, playerId);

		if( lua_pcall(m_luaState, 2, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"【游戏房间】 调用函数 OnProcessLeaveRoomMsg 失败:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}

/**
 * 处理用户断开连接消息
 *
 * @param pRoom 要处理的游戏房间
 * @param playerId 用户在房间中的ID
 */
void ScriptSystem::OnProcessDisconnectNetMes(Room *pRoom,int playerId)
{
	if(pRoom == NULL || playerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// 初始脚本加载函数
		lua_getglobal(m_luaState, "OnProcessDisconnectNetMes"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, playerId);

		if( lua_pcall(m_luaState, 2, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"【游戏房间】 调用函数 OnProcessDisconnectNetMes 失败:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}

/**
 * 处理用户断线重连消息
 *
 * @param pRoom 要处理的游戏房间
 * @param playerId 用户在房间中的ID
 */
void ScriptSystem::OnProcessDisconnectBackNetMes(Room *pRoom,int playerId)
{
	if(pRoom == NULL || playerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// 初始脚本加载函数
		lua_getglobal(m_luaState, "OnProcessDisconnectBackNetMes"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, playerId);

		if( lua_pcall(m_luaState, 2, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"【游戏房间】 调用函数 OnProcessDisconnectBackNetMes 失败:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}

/**
 * 处理用户定时器消息
 *
 * @param pRoom 要处理的游戏房间
 * @param timerId 要处理的定时器ID
 * @param curTimer 当前时间
 */
void ScriptSystem::OnProcessTimerMsg(Room *pRoom,int timerId,int curTimer)
{
	if(pRoom == NULL || timerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// 初始脚本加载函数
		lua_getglobal(m_luaState, "OnProcessTimerMsg"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, timerId);
		lua_pushinteger(m_luaState, curTimer);

		if( lua_pcall(m_luaState, 3, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"【游戏房间】 调用函数 OnProcessTimerMsg 失败:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}
