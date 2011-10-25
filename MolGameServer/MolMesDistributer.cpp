#include "stdafx.h"

#include "MolMesDistributer.h"
#include "GameFrameManager.h"

#include "RoomManager.h"
#include "GameFrameManager.h"
#include "PlayerManager.h"

/**
 * 得到系统时间
 */
DWORD GetTickCountEx(void)
{
    SYSTEMTIME st;
    GetSystemTime(&st);

    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);
    // 100-nanoseconds since 1601
    ULONGLONG ull = ((ULONGLONG)ft.dwHighDateTime << 32 )
                  + (ULONGLONG)ft.dwLowDateTime;
    // 100-nanoseconds since epoch
    ull -= 116444736000000000;

    return (ull / 10000); // 100-nano-seconds -> milliseconds
}

/**
 * 构造函数
 */
CMolMesDistributer::CMolMesDistributer()
{

}

/**
 * 析构函数
 */
CMolMesDistributer::~CMolMesDistributer()
{

}

bool CMolMesDistributer::run()
{
	while(IsConnected())
	{
		//m_MesLock.Acquire();
		int count = GetNetMessage(myMes);
		for(int i=0;i<count;i++)
		{
			MessageStru *mes = myMes.GetMesById(i);
			if(mes==NULL) continue;

			switch(mes->GetType())
			{
			case MES_TYPE_ON_CONNECTED:
				{
					ServerGameFrameManager.OnProcessConnectedNetMes(mes->GetSocket());
				}
				break;
			case MES_TYPE_ON_DISCONNECTED:
				{
					ServerGameFrameManager.OnProcessDisconnectNetMes(mes->GetSocket());
				}
				break;
			case MES_TYPE_ON_READ:
				{
					ServerGameFrameManager.OnProcessNetMes(mes->GetSocket(),mes->GetMes());
				}
				break;
			default:
				break;
			}			
		}
		//if(count > 0) 
		//	myMes.Clear();	
		//m_MesLock.Release();

		Sleep(10);
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * 构造函数
 */
CMolGameServerPlayersUpdate::CMolGameServerPlayersUpdate():m_curTimer(0)
{

}

/**
 * 析构函数
 */
CMolGameServerPlayersUpdate::~CMolGameServerPlayersUpdate()
{

}

bool CMolGameServerPlayersUpdate::run()
{
	while(IsConnected())
	{
		DWORD time = GetTickCountEx();

		m_RoomPlayersLock.Acquire();

		//if(m_curTimer == 0)
		//	m_curTimer = time;

		//if(time > m_curTimer + 30000)
		//{
		//	m_curTimer = 0;

		//	// 向所有客户端发送心跳消息
		//	ServerPlayerManager.SendAllPlayersHeartJitter();
		//}

		/// 向客户端发送心跳消息
		ServerPlayerManager.OnProcessAllPlayersHeart();	

		m_RoomPlayersLock.Release();

		Sleep(10);
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * 构造函数
 */
CMolGameRoomUpdate::CMolGameRoomUpdate()
{

}

/**
 * 析构函数
 */
CMolGameRoomUpdate::~CMolGameRoomUpdate()
{

}

bool CMolGameRoomUpdate::run()
{
	while(IsConnected())
	{
		DWORD time = GetTickCountEx();

		m_RoomLock.Acquire();

		// 更新房间
		ServerRoomManager.Update(time);

		m_RoomLock.Release();

		Sleep(10);
	}

	return false;
}