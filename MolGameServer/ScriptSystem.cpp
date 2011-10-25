#include "stdafx.h"

#include "ScriptSystem.h"
#include "Room.h"

#include "MolServerDlg.h"

int  tolua_MolServer_open (lua_State* tolua_S);

/**
 * ж�ؽű�ϵͳ
 */
void ScriptSystem::ShutdownScriptSystem(void)
{
	if(m_luaState) lua_close(m_luaState);
}

/**
 * ��ʼ���ű��ű�ϵͳ
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
		sprintf(buf,"����Ϸ���䡿 �ű��ļ�:%s����ʧ��:%s!" ,IDD_GAME_ROOM_SCRIPT,lua_tostring(m_luaState, -1));    
		CMolServerDlg::getSingleton().PrintLog(buf);
	}
}

/**
 * ���벢ִ�нű�
 */
void ScriptSystem::LoadAndRunScript(void)
{
	int state = luaL_dofile(m_luaState, IDD_GAME_ROOM_SCRIPT);
	if(state != 0)
	{
		char buf[128];
		sprintf(buf,"����Ϸ���䡿 �ű��ļ�:%s����ʧ��:%s!" ,IDD_GAME_ROOM_SCRIPT,lua_tostring(m_luaState, -1));      
		CMolServerDlg::getSingleton().PrintLog(buf);
	}
}

/** 
 * �����ڴ�
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
 * �����û�׼����Ϣ
 *
 * @param pRoom Ҫ�������Ϸ����
 * @param playerId Ҫ����ķ�����ҵ�ID
 */
void ScriptSystem::OnProcessPlayerReadyMes(Room *pRoom,int playerId)
{
	if(pRoom == NULL || playerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// ��ʼ�ű����غ���
		lua_getglobal(m_luaState, "OnProcessPlayerReadyMes"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, playerId); 

		if( lua_pcall(m_luaState, 2, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"����Ϸ���䡿 ���ú��� OnProcessPlayerReadyMes ʧ��:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}

///**
// * �����û���Ϸ����Ϣ
// *
// * @param pRoom Ҫ�������Ϸ����
// * @param playerId Ҫ����ķ�����ҵ�ID
// * @param mes Ҫ����������Ϣ
// */
//void ScriptSystem::OnProcessPlayerGamingMes(Room *pRoom,int playerId,CMolMessageIn *mes)
//{
//	if(pRoom == NULL || mes == NULL || playerId == -1) return;
//
//	try
//	{
//		// ��ʼ�ű����غ���
//		lua_getglobal(m_luaState, "OnProcessPlayerGamingMes"); 
//		lua_pushlightuserdata(m_luaState, pRoom); 
//		lua_pushinteger(m_luaState, playerId); 
//		lua_pushlightuserdata(m_luaState, mes); 
//
//		if( lua_pcall(m_luaState, 3, 0, 0) != 0 ) 
//		{         
//			char buf[128];
//			sprintf(buf,"����Ϸ���䡿 ���ú��� OnProcessPlayerGamingMes ʧ��:%s\n" ,lua_tostring(m_luaState, -1));    
//			CMolServerDlg::getSingleton().PrintLog(buf);
//		} 
//	}
//	catch(...)
//	{
//	
//	}
//}

/** 
 * �����û���������Ϣ
 *
 * @param pRoom Ҫ�������Ϸ����
 * @param playerId Ҫ����ķ�����ҵ�ID
 * @param mes Ҫ����������Ϣ
 */
void ScriptSystem::OnProcessPlayerRoomMes(Room *pRoom,int playerId,CMolMessageIn *mes)
{
	if(pRoom == NULL || mes == NULL || playerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// ��ʼ�ű����غ���
		lua_getglobal(m_luaState, "OnProcessPlayerRoomMes"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, playerId); 
		lua_pushlightuserdata(m_luaState, mes); 

		if( lua_pcall(m_luaState, 3, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"����Ϸ���䡿 ���ú��� OnProcessPlayerRoomMes ʧ��:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}

/**
 * �����û����뷿����Ϣ
 *
 * @param pRoom Ҫ�������Ϸ����
 * @param playerId �û��ڷ����е�ID
 */
void ScriptSystem::OnProcessEnterRoomMsg(Room *pRoom,int playerId)
{
	if(pRoom == NULL || playerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// ��ʼ�ű����غ���
		lua_getglobal(m_luaState, "OnProcessEnterRoomMsg"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, playerId);

		if( lua_pcall(m_luaState, 2, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"����Ϸ���䡿 ���ú��� OnProcessEnterRoomMsg ʧ��:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}

/**
 * �����û��뿪������Ϣ
 *
 * @param pRoom Ҫ�������Ϸ����
 * @param playerId �û��ڷ����е�ID
 */
void ScriptSystem::OnProcessLeaveRoomMsg(Room *pRoom,int playerId)
{
	if(pRoom == NULL || playerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// ��ʼ�ű����غ���
		lua_getglobal(m_luaState, "OnProcessLeaveRoomMsg"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, playerId);

		if( lua_pcall(m_luaState, 2, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"����Ϸ���䡿 ���ú��� OnProcessLeaveRoomMsg ʧ��:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}

/**
 * �����û��Ͽ�������Ϣ
 *
 * @param pRoom Ҫ�������Ϸ����
 * @param playerId �û��ڷ����е�ID
 */
void ScriptSystem::OnProcessDisconnectNetMes(Room *pRoom,int playerId)
{
	if(pRoom == NULL || playerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// ��ʼ�ű����غ���
		lua_getglobal(m_luaState, "OnProcessDisconnectNetMes"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, playerId);

		if( lua_pcall(m_luaState, 2, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"����Ϸ���䡿 ���ú��� OnProcessDisconnectNetMes ʧ��:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}

/**
 * �����û�����������Ϣ
 *
 * @param pRoom Ҫ�������Ϸ����
 * @param playerId �û��ڷ����е�ID
 */
void ScriptSystem::OnProcessDisconnectBackNetMes(Room *pRoom,int playerId)
{
	if(pRoom == NULL || playerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// ��ʼ�ű����غ���
		lua_getglobal(m_luaState, "OnProcessDisconnectBackNetMes"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, playerId);

		if( lua_pcall(m_luaState, 2, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"����Ϸ���䡿 ���ú��� OnProcessDisconnectBackNetMes ʧ��:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}

/**
 * �����û���ʱ����Ϣ
 *
 * @param pRoom Ҫ�������Ϸ����
 * @param timerId Ҫ����Ķ�ʱ��ID
 * @param curTimer ��ǰʱ��
 */
void ScriptSystem::OnProcessTimerMsg(Room *pRoom,int timerId,int curTimer)
{
	if(pRoom == NULL || timerId == -1) return;

	//m_StateLock.Acquire();
	try
	{
		// ��ʼ�ű����غ���
		lua_getglobal(m_luaState, "OnProcessTimerMsg"); 
		lua_pushlightuserdata(m_luaState, pRoom); 
		lua_pushinteger(m_luaState, timerId);
		lua_pushinteger(m_luaState, curTimer);

		if( lua_pcall(m_luaState, 3, 0, 0) != 0 ) 
		{         
			char buf[128];
			sprintf(buf,"����Ϸ���䡿 ���ú��� OnProcessTimerMsg ʧ��:%s\n" ,lua_tostring(m_luaState, -1));    
			CMolServerDlg::getSingleton().PrintLog(buf);
		} 
	}
	catch(...)
	{
	
	}
	//m_StateLock.Release();
}
