#include "stdafx.h"

#include "MolServerCom.h"

#include "defines.h"
#include "Room.h"
#include "PlayerManager.h"

#include "MolServerDlg.h"
#include "DBOperator.h"

#include "mmsystem.h"

Room::Room(RoomType type)
	: m_Id(0),m_MaxCount(0),m_RoomType(type),m_RoomState(ROOMSTATE_WAITING),
	  m_masterId(-1),m_curPlayerId(-1),m_RoomRevenue(0),m_RoomLastMoney(0)
{
	m_ScriptSystem.InitScriptSystem();

	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		m_PlayerList[i] = NULL;
	}

	if (!CreateTimerQueueTimer(
		&hRoomTimer, NULL, MyTimeProc, this , 2000, 1000, /*WT_EXECUTEINTIMERTHREAD*/WT_EXECUTEDEFAULT))   
		CMolServerDlg::getSingleton().PrintLog("房间定时器建立不成功。");
}

Room::~Room()
{
	StopAllTimer();
	m_timerList.clear();
	ClearAllPlayers();
	if(hRoomTimer) DeleteTimerQueueTimer(NULL,hRoomTimer,NULL);
	hRoomTimer = NULL;
	m_ScriptSystem.ShutdownScriptSystem();
}

/** 
 * 重新导入并执行脚本
 */
void Room::ReLoadAndRunScript(void)
{
	m_ScriptSystem.LoadAndRunScript();
}

/**
 * 当前房间是否为空
 *
 * @return 如果当前房间为空的话返回真，否则返回假
 */
bool Room::IsEmpty(void)
{
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i])
			return false;
	}

	return true;
}

/**
 * 清除房间中所有的玩家
 */
void Room::ClearAllPlayers(void)
{
	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i] != NULL) 
		{
			m_PlayerList[i]->SetRoomId(-1);
			m_PlayerList[i]->SetRoomIndex(-1);
			m_PlayerList[i]->SetState(PLAYERSTATE_NORAML);
			m_PlayerList[i]->SetLookOn(false);
		}
		m_PlayerList[i] = NULL;
	}
	std::map<int,std::vector<Player*> >::iterator iter = m_LookonPlayerList.begin();
	for(;iter != m_LookonPlayerList.end();iter++)
	{
		for(int index = 0;index < (int)(*iter).second.size();index++)
		{
			if((*iter).second[index] != NULL)
			{
				(*iter).second[index]->SetRoomId(-1);
				(*iter).second[index]->SetRoomIndex(-1);
				(*iter).second[index]->SetState(PLAYERSTATE_NORAML);
				(*iter).second[index]->SetLookOn(false);
			}
			(*iter).second[index] = NULL;
		}
		(*iter).second.clear();
	}
	m_playersLock.Release();

	m_lostPlayerList.clear();

	//char buf[128];
	//sprintf(buf,"从房间:%d中清除所有的玩家。\n",GetID());
	//CMolServerDlg::getSingleton().PrintLog(buf);
}

/** 
 * 向当前房间所有玩家发送用户离开服务器消息
 */
void Room::AllPlayerLeveaServer(void)
{
	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		//m_LookonPlayerList[i] = NULL;

		if(m_PlayerList[i] == NULL) continue;

		// 向房间所有玩家广播玩家离开服务器消息
		CMolMessageOut out(IDD_MESSAGE_FRAME);
		out.writeShort(IDD_MESSAGE_LEAVE_SERVER);
		out.writeLong(m_PlayerList[i]->GetID());		
		ServerPlayerManager.SendMsgToEveryone(out);

		m_PlayerList[i]->SetRoomId(-1);
		m_PlayerList[i]->SetRoomIndex(-1);
		m_PlayerList[i]->SetState(PLAYERSTATE_NORAML);

		Disconnect(m_PlayerList[i]->GetConnectID());
		ServerPlayerManager.ClearPlayer(m_PlayerList[i]);

		m_PlayerList[i] = NULL;
	}
	m_playersLock.Release();
}

/**
 * 得到当前房间指定状态的玩家个数
 *
 * @param state 要得到的玩家的状态
 *
 * @return 返回指定玩家玩家状态的玩家个数
 */
int Room::GetPlayerCount(PlayerState state)
{
	int count = 0;

	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i] &&
			m_PlayerList[i]->GetState() == state)
			count+=1;
	}
	m_playersLock.Release();

	return count;
}

/**
 * 设置当前房间所有玩家的状态
 *
 * @param state 要设置的玩家的状态
 */
void Room::SetAllPlayerState(PlayerState state)
{
	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i])
			m_PlayerList[i]->SetState(state);
	}
	m_playersLock.Release();
}

/**
 * 设置指定玩家的状态
 *
 * @param index 要设置的玩家的房间ID
 * @param state 要设置的玩家状态
 */
void Room::SetPlayerState(int index,PlayerState state)
{
	if(index < 0 || index >= ROOM_MAX_PLAYERS) return;

	m_playersLock.Acquire();
	if(m_PlayerList[index])
		m_PlayerList[index]->SetState(state);
	m_playersLock.Release();
}

/**
 * 添加一个玩家到当前房间中
 *
 * @param pPlayer 要添加的玩家
 * @param index 要把玩家添加到指定的位置上，如果设置成-1,那么表示随机添加到房间中
 *
 * @return 返回玩家在房间中的索引
 */
int Room::AddPlayer(Player *pPlayer,int index)
{
	int playerIndex = -1;
	
	if(pPlayer == NULL ||
		GetPlayerCount() > m_MaxCount) 
		return playerIndex;

	// 如果用户已经在房间中，就不加入了
	if(IsExist(pPlayer)) return playerIndex;

	// 检测玩家的金币数量是否满足当前房间要求
	if(pPlayer->GetMoney() < m_RoomLastMoney) return playerIndex;

	m_playersLock.Acquire();
	if(index == playerIndex)
	{
		for(int i=0;i<ROOM_MAX_PLAYERS;i++)
		{
			if(m_PlayerList[i] == NULL/* ||
				(m_PlayerList[i]->GetRoomId() == -1 && m_PlayerList[i]->GetRoomIndex() == -1)*/)
			{
				m_PlayerList[i] = pPlayer;
				playerIndex = i;
				break;
			}
		}
	}
	else
	{
		if(index >= 0 && index < ROOM_MAX_PLAYERS)
		{
			if(m_PlayerList[index] == NULL/* ||
				(m_PlayerList[index]->GetRoomId() == -1 && m_PlayerList[index]->GetRoomIndex() == -1)*/)
			{
				m_PlayerList[index] = pPlayer;
				playerIndex = index;
			}
		}
	}
	m_playersLock.Release();
	
	return playerIndex;
}

/** 
 * 添加一个旁观玩家到当前房间中
 *
 * @param pPlayer 要添加的玩家
 * @param index 要把玩家添加到指定的位置上
 *
 * @return 返回玩家在房间中的索引
 */
int Room::AddLookOnPlayer(Player *pPlayer,int index)
{
	int playerIndex = -1;
	
	if(pPlayer == NULL || 
		(index < 0 || index > m_MaxCount)) 
		return playerIndex;

	// 如果用户已经在房间中，就不加入了
	if(IsExistLookOn(pPlayer)) return playerIndex;

	m_playersLock.Acquire();
	if(index >= 0 && index < ROOM_MAX_PLAYERS)
	{
		std::map<int,std::vector<Player*> >::iterator iter = m_LookonPlayerList.find(index);
		if(iter != m_LookonPlayerList.end())
		{
			// 检测是否有这个用户，没有才添加进去
			bool isExistPlayer = true;
			for(int indexP = 0;indexP < (int)(*iter).second.size();indexP++)
			{
				if((*iter).second[indexP] == pPlayer)
				{
					isExistPlayer = false;
					break;
				}
			}
			
			if(isExistPlayer)
			{
				(*iter).second.push_back(pPlayer);
				playerIndex = index;
			}
		}
		else
		{
			std::vector<Player*> tempPlayers;
			tempPlayers.push_back(pPlayer);
			
			m_LookonPlayerList.insert(std::pair<int,std::vector<Player*> >(index,tempPlayers));
			playerIndex = index;
		}
	}
	m_playersLock.Release();
	
	return playerIndex;
}

/**
 * 设置当前房间的房主
 *
 * @param playerId 要设置成房主的玩家ID
 */
void Room::SetMaster(int playerId)
{
	// 如果当前房间已经设置了房主，就不用设置了
	//if(m_masterId != -1) return;

	m_masterId = playerId;
	m_curPlayerId = m_masterId;
}

/**
 * 得到当前房间中下一个玩家
 */
int Room::GetCurNextPlayer(void)
{
	m_curPlayerId += 1;

	if(m_curPlayerId >= GetPlayerCount())
		m_curPlayerId = 0;

	return m_curPlayerId;
}

/**
 * 得到当前房间中下一个出牌玩家
 */
int Room::GetCurNextWorkPlayer(void)
{
	int count = 0;

	while(true)
	{
		if(count >= GetPlayerCount()) break;

		int index = GetCurNextPlayer();
		Player *pPlayer = GetPlayer(index);
		if(pPlayer && pPlayer->GetState() == PLAYERSTATE_GAMING)
			return index;

		count+=1;
	}

	return -1;
}

void CALLBACK Room::MyTimeProc(void* param, BOOLEAN timerCalled)
{
	Room *pRoom = static_cast<Room*>(param);
	if(pRoom == NULL) return;

	pRoom->OnProcessTimerMsg();
}

/**
 * 开始一个定时器
 *
 * @param timerId 要开启的定时器ID
 * @param space 定时间隔
 *
 * @return 如果开启成功返回真，否则返回假
 */
bool Room::StartTimer(int timerId,int space)
{
	bool success = true;
	m_timerLock.Acquire();
	std::map<long,RoomTimer>::iterator iter = m_timerList.find(timerId);
	if(iter != m_timerList.end())
	{
		(*iter).second = RoomTimer(timerId,space);
	}
	else
	{
		m_timerList.insert(std::pair<long,RoomTimer>(timerId,RoomTimer(timerId,space)));		
	}
	m_timerLock.Release();

	return success;
}

/**
 * 关闭一个定时器
 *
 * @param id 要关闭的定时器ID
 */
void Room::StopTimer(int id)
{
	if(m_timerList.empty()) return;

	m_timerLock.Acquire();
	std::map<long,RoomTimer>::iterator iter = m_timerList.find(id);
	if(iter != m_timerList.end())
	{
		(*iter).second.m_isEnable = false;
	}
	m_timerLock.Release();
}

/**
 * 关闭所有的定时器
 */
void Room::StopAllTimer(void)
{
	if(m_timerList.empty()) return;

	m_timerLock.Acquire();
	std::map<long,RoomTimer>::iterator iter = m_timerList.begin();
	for(;iter != m_timerList.end();iter++)
	{
		(*iter).second.m_isEnable = false;
	}
	m_timerLock.Release();
}

/**
 * 从当前房间中清除指定的玩家
 *
 * @param pPlayer 要清除的玩家
 */
void Room::ClearPlayer(Player *pPlayer)
{
	if(pPlayer == NULL) 
		return;

	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i] &&
			m_PlayerList[i]->GetID() == pPlayer->GetID()) 
		{
			pPlayer->SetState(PLAYERSTATE_NORAML);
			pPlayer->SetRoomId(-1);
			pPlayer->SetRoomIndex(-1);
			pPlayer->SetLookOn(false);

			ClearLostPlayerById(i);

			m_PlayerList[i] = NULL;

			//char buf[256];
			//sprintf(buf,"从房间%d中清除玩家%d:%d\n",GetID(),(*iter)->GetID(),(*iter)->GetConnectID());
			//CMolServerDlg::getSingleton().PrintLog(buf);

			break;
		}
	}
	std::map<int,std::vector<Player*> >::iterator iter = m_LookonPlayerList.find(pPlayer->GetRoomIndex());
	if(iter != m_LookonPlayerList.end())	
	{
		std::vector<Player*>::iterator iter2 = (*iter).second.begin();
		for(;iter2 != (*iter).second.end();iter2++)
		{
			if((*iter2) == pPlayer)
			{
				pPlayer->SetState(PLAYERSTATE_NORAML);
				pPlayer->SetRoomId(-1);
				pPlayer->SetRoomIndex(-1);
				pPlayer->SetLookOn(false);

				(*iter2) = NULL;
				(*iter).second.erase(iter2);
				break;
			}
		}
	}
	m_playersLock.Release();
}

/**
 * 从当前房间中删除指定的玩家
 *
 * @param pPlayer 要删除的玩家
 */
void Room::DeletePlayer(Player *pPlayer)
{
	if(pPlayer == NULL) 
		return;

	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i] == pPlayer) 
		{
			if(!IsExistLostPlayer(i))
				m_lostPlayerList.push_back(i);

			delete m_PlayerList[i];
			m_PlayerList[i] = NULL;
			break;
		}

		/*if(m_LookonPlayerList[i] == pPlayer) 
		{
			delete m_LookonPlayerList[i];
			m_LookonPlayerList[i] = NULL;
			break;
		}*/
	}
	m_playersLock.Release();
}

/**
 * 根据用户连接ID得到用户在房间中的ID
 *
 * @param connId 要得到的用户的连接ID
 *
 * @return 如果这个用户存在于这个房间，返回这个用户在这个房间中的ID，否则返回-1
 */
int Room::GetPlayerRoomId(int connId)
{
	int state = -1;

	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i] == NULL) continue;

		if(m_PlayerList[i]->GetConnectID() == connId) 
		{
			state = i;
			break;
		}
	}
	m_playersLock.Release();

	return state;
}

/**
 * 检测指定的索引是否在掉线玩家列表中
 *
 * @param index 要检测的玩家在房间中的索引
 *
 * @return 如果玩家在掉线玩家列表中返回真，否则返回假
 */
bool Room::IsExistLostPlayer(int index)
{
	if(m_lostPlayerList.empty()) return false;

	for(int i=0;i<(int)m_lostPlayerList.size();i++)
	{
		if(m_lostPlayerList[i] == index)
			return true;
	}

	return false;
}

/**
 * 清除掉线玩家列表中玩家
 *
 * @param id 要清除的玩家的ID
 */
void Room::ClearLostPlayerById(int id)
{
	if(m_lostPlayerList.empty()) return;

	m_playersLock.Acquire();
	std::vector<int>::iterator iter = m_lostPlayerList.begin();
	for(int i=0;iter != m_lostPlayerList.end();i++)
	{
		if(i == id) 
		{
			iter = m_lostPlayerList.erase(iter);
			break;
		}
		else
		{
			iter++;
		}
	}
	m_playersLock.Release();
}

/**
 * 从当前房间中清除指定房间ID的玩家
 *
 * @param Id 要清除的玩家在房间中的ID
 */
void Room::ClearPlayerById(int Id)
{
	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i] && m_PlayerList[i]->GetRoomIndex() == Id) 
		{
			m_PlayerList[i]->SetRoomId(-1);
			m_PlayerList[i]->SetRoomIndex(-1);
			m_PlayerList[i]->SetLookOn(false);

			ClearLostPlayerById(Id);

			m_PlayerList[i] = NULL;

			break;
		}
	}
	std::map<int,std::vector<Player*> >::iterator iter = m_LookonPlayerList.find(Id);
	if(iter != m_LookonPlayerList.end())
	{
		for(int index = 0;index < (int)(*iter).second.size();index++)
		{
			if((*iter).second[index] != NULL)
			{
				(*iter).second[index]->SetRoomId(-1);
				(*iter).second[index]->SetRoomIndex(-1);
				(*iter).second[index]->SetState(PLAYERSTATE_NORAML);
				(*iter).second[index]->SetLookOn(false);
			}
			(*iter).second[index] = NULL;
		}
		(*iter).second.clear();
	}	
	m_playersLock.Release();
}

/**
 * 得到当前房间人数
 */
int Room::GetPlayerCount(void)
{
	int count = 0;

	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i] == NULL) continue;

		if(m_PlayerList[i]->GetRoomId() != -1 &&
			m_PlayerList[i]->GetRoomIndex() != -1)
			count+=1;
	}
	m_playersLock.Release();

	return count;
}

/**
 * 得到准备好状态下玩家的人数
 *
 * @return 返回当前房间中准备好的玩家的个数
 */
int Room::GetReadyPlayerCount(void)
{
	int count = 0;

	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i] == NULL) continue;

		if(m_PlayerList[i]->GetState() == PLAYERSTATE_READY) 
		{
			count += 1;
		}
	}
	m_playersLock.Release();

	return count;
}

/**
 * 清空当前房间数据
 */
void Room::Clear(void)
{
	m_lostPlayerList.clear();
	m_RoomState = ROOMSTATE_WAITING;
	m_masterId = -1;
	m_curPlayerId = -1;

	StopAllTimer();
}

/**
 * 检测指定玩家是否存在当前房间
 *
 * @param pPlayer 要检测的玩家
 *
 * @return 如果要检测的玩家存在返回真，否则返回假
 */
bool Room::IsExist(Player *pPlayer)
{
	if(pPlayer == NULL) return false;

	bool state = false;

	if(pPlayer == NULL) 
		return state;

	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i] &&
			m_PlayerList[i]->GetID() == pPlayer->GetID())
		{
			state = true;
			break;
		}
	}
	std::map<int,std::vector<Player*> >::iterator iter = m_LookonPlayerList.find(pPlayer->GetRoomIndex());
	if(iter != m_LookonPlayerList.end())
	{
		for(int index = 0;index < (int)(*iter).second.size();index++)
		{
			if((*iter).second[index] == pPlayer)
			{
				state = true;
				break;
			}
		}
	}	
	m_playersLock.Release();

	return state;
}

/** 
 * 检测指定的旁观玩家是否存在当前房间中
 *
 * @param pPlayer 要检测的玩家
 *
 * @return 如果要检测的玩家存在返回真，否则返回假
 */
bool Room::IsExistLookOn(Player *pPlayer)
{
	if(pPlayer == NULL) return false;

	bool state = false;

	if(pPlayer == NULL) 
		return state;

	m_playersLock.Acquire();
	std::map<int,std::vector<Player*> >::iterator iter = m_LookonPlayerList.find(pPlayer->GetRoomIndex());
	if(iter != m_LookonPlayerList.end())
	{
		for(int index = 0;index < (int)(*iter).second.size();index++)
		{
			if((*iter).second[index] == pPlayer)
			{
				state = true;
				break;
			}
		}
	}
	m_playersLock.Release();

	return state;
}

/**
 * 检测房间是否已经满员
 *
 * @return 如果房间已经满员返回真，否则返回假
 */
bool Room::IsFull(void)
{
	return GetPlayerCount() == m_MaxCount ? true : false;
}

/**
 * 检测房间是否全部准备完毕
 *
 * @param 如果当前房间满员并且全部处于准备状态下返回真，否则返回假
 */
bool Room::IsReadyed(void)
{
	if(m_RoomState == ROOMSTATE_WAITING &&
		IsFull())
	{
		bool isReady = true;

		m_playersLock.Acquire();
		for(int i=0;i<ROOM_MAX_PLAYERS;i++)
		{
			if(m_PlayerList[i] == NULL) continue;

			if(m_PlayerList[i]->GetState() != PLAYERSTATE_READY)
			{
				isReady = false;
				break;
			}
		}
		m_playersLock.Release();

		return isReady;
	}

	return false;
}

/**
 * 向指定的玩家发送数据
 *
 * @param index 要发送的玩家的索引,如果为-1的话，表示发送给所有人，否则发送给指定的人
 * @param msg 要发送的数据
 */
void Room::SendTableMsg(int index,CMolMessageOut &msg)
{
	if(index >= 0 && index < ROOM_MAX_PLAYERS)
	{
		m_playersLock.Acquire();
		Player *pPlayer = dynamic_cast<Player*>(m_PlayerList[index]);
		if(pPlayer != NULL) 
		{
			Send(m_PlayerList[index]->GetConnectID(),msg);
		}
		m_playersLock.Release();
	}
	else if(index == -1)                    // 发送给所有人
	{
		SendAllPlayerMsg(msg);
	}
}

/** 
 * 向指定的玩家发送旁观数据
 *
 * @param index 要发送的玩家的索引,如果为-1的话，表示发送给所有人，否则发送给指定的人
 * @param msg 要发送的数据
 */
void Room::SendLookOnMes(int index,CMolMessageOut &msg)
{
	if(index >= 0 && index < ROOM_MAX_PLAYERS)
	{
		m_playersLock.Acquire();
		std::map<int,std::vector<Player*> >::iterator iter = m_LookonPlayerList.find(index);
		if(iter != m_LookonPlayerList.end())
		{
			for(int index = 0;index < (int)(*iter).second.size();index++)
			{
				if((*iter).second[index] != NULL)
				{
					Send((*iter).second[index]->GetConnectID(),msg);
				}
			}
		}		
		m_playersLock.Release();
	}
	else if(index == -1)                    // 发送给所有人
	{
		SendAllLookOnPlayerMsg(msg);
	}
}

///**
// * 向除了指定玩家的其它玩家发送数据
// *
// * @param index 要除开的玩家的索引
// * @param msg 要发送的数据
// */
//void Room::SendOtherPlayerMsg(int index,CMolMessageOut &msg)
//{
//	m_playersLock.Acquire();
//	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
//	{
//		if(m_PlayerList[i] && 
//			m_PlayerList[i]->GetRoomIndex() != index) 
//		{
//			Send(m_PlayerList[i]->GetConnectID(),msg);
//		}
//	}
//	m_playersLock.Release();
//}

/**
 * 向所有玩家发送数据
 *
 * @param msg 要发送的数据
 */
void Room::SendAllPlayerMsg(CMolMessageOut &msg)
{
	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i] == NULL) continue;

		Send(m_PlayerList[i]->GetConnectID(),msg);
	}
	m_playersLock.Release();
}

/** 
 * 向所有旁观玩家发送数据
 *
 * @param msg 要发送的数据
 */
void Room::SendAllLookOnPlayerMsg(CMolMessageOut &msg)
{
	m_playersLock.Acquire();
	std::map<int,std::vector<Player*> >::iterator iter = m_LookonPlayerList.begin();
	for(;iter != m_LookonPlayerList.end();iter++)
	{
		for(int index = 0;index < (int)(*iter).second.size();index++)
		{
			if((*iter).second[index] != NULL)
			{
				Send((*iter).second[index]->GetConnectID(),msg);
			}
		}
	}	
	m_playersLock.Release();
}

/**
 * 打印调试信息
 *
 * @param info 要打印的调试信息
 */
void Room::PrintDebugInfo(const char* info)
{
	if(info == NULL) return;

	CString tempStr;
	tempStr.Format("【游戏房间】 %s",info);
	CMolServerDlg::getSingleton().PrintLog(tempStr.GetBuffer());
}

/**
 * 得到指定索引的玩家
 *
 * @param index 要得到的玩家的索引
 *
 * @return 如果这个指定索引的玩家存在返回这个玩家，否则返回NULL
 */
Player* Room::GetPlayer(int index)
{
	if(index < 0 || index >= ROOM_MAX_PLAYERS)
		return NULL;

	//for(int i=0;i<(int)m_PlayerList.size();i++)
	//{
	//	if(m_PlayerList[i] &&
	//		m_PlayerList[i]->GetRoomIndex() == index)
	//		return m_PlayerList[i];
	//}

	return dynamic_cast<Player*>(m_PlayerList[index]);
}

/**
 * 更新房间中所有的当前用户--这个函数用于防止用户突然离开房间
 */
void Room::UpdateOnlinePlayers(void)
{
	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i] == NULL) continue;

		if(	m_PlayerList[i]->GetRoomIndex() != i)
			m_PlayerList[i]->SetRoomIndex(i);
	}
	m_playersLock.Release();
}

///**
// * 更新房间中所有的用户--这个函数用于防止一些用户已经掉线，但没有离开房间
// */
//void Room::UpdateAllPlayers(void)
//{
//	m_playersLock.Acquire();
//	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
//	{
//		if(!m_PlayerList[i])
//			iter = m_PlayerList.erase(iter);
//		else
//			iter++;
//
//	}
//	m_playersLock.Release();
//}

/**
 * 游戏房间更新
 *
 * @param time 当前系统时间
 */
void Room::Update(DWORD time)
{
	//m_timerLock.Acquire();
	// 如果房间还处于游戏状态下，但所有的玩家已经全部断开连接，就清除这个房间，然后重新等待用户进入
	/**if(GetRoomState() == ROOMSTATE_GAMING)
	{
		bool isConn = false;

		m_playersLock.Acquire();
		for(int i=0;i<ROOM_MAX_PLAYERS;i++)
		{
			if(IsExistLostPlayer(i)) continue;

			if(m_PlayerList[i] != NULL ||
				m_PlayerList[i]->GetRoomId() != GetID())
			{
				isConn = true;
				break;
			}
		}
		m_playersLock.Release();

		if(!isConn)
		{
			ClearAllPlayers();
			Clear();
		}

		// 如果全部掉线的话，就关闭房间
		if(GetLostPlayerCount() >= GetMaxPlayer())
		{
			ClearAllPlayers();
			Clear();
		}
	}
	else if(GetRoomState() == ROOMSTATE_WAITING)
	{
		// 如果全部掉线的话，就关闭房间
		if(GetLostPlayerCount() >= GetMaxPlayer())
		{
			ClearAllPlayers();
			Clear();
		}

		//// 如果有玩家掉线的话，就从房间中清除这个用户
		//m_playersLock.Acquire();
		//std::vector<Player*>::iterator iter = m_PlayerList.begin();
		//for(;iter != m_PlayerList.end();)
		//{
		//	if(!(*iter)) 
		//	{
		//		iter = m_PlayerList.erase(iter);
		//	}
		//	else
		//	{
		//		iter++;
		//	}
		//}
		//m_playersLock.Release();

		if(!m_lostPlayerList.empty())
		{
			m_lostPlayerList.clear();
		}
	}*/
	//m_timerLock.Release();
}

/**
 * 根据玩家连接id得到玩家在当前房间中的索引
 *
 * @param connId 要得到的客户端连接ID
 *
 * @return 返回这个连接在房间中的索引
 */
int Room::GetPlayerIndex(int connId)
{
	int state = -1;

	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		if(m_PlayerList[i] == NULL) continue;

		if(m_PlayerList[i]->GetConnectID() == connId)
		{
			state = m_PlayerList[i]->GetRoomIndex();
			break;
		}
	}
	m_playersLock.Release();

	return state;
}

/**
 * 用于处理用户准备后的消息
 *
 * @param playerId 要处理的客户端的房间ID
 */
void Room::OnProcessPlayerReadyMes(int playerId)
{
	//m_scriptLock.Acquire();
	m_ScriptSystem.OnProcessPlayerReadyMes(this,playerId);
	//m_scriptLock.Release();
}

///**
// * 用于处理用户开始游戏后的消息
// *
// * @param playerId 要处理的客户端的房间ID
// * @param mes 接收的客户端发送的消息
// */
//void Room::OnProcessPlayerGamingMes(int playerId,CMolMessageIn *mes)
//{
//	m_scriptLock.Acquire();
//	m_ScriptSystem.OnProcessPlayerGamingMes(this,playerId,mes);
//	m_scriptLock.Release();
//}

/** 
 * 用于处理用户进入游戏房间后的消息
 *
 * @param playerId 要处理的客户端的房间ID
 * @param mes 接收的客户端发送的消息
 */
void Room::OnProcessPlayerRoomMes(int playerId,CMolMessageIn *mes)
{
	//m_scriptLock.Acquire();
	m_ScriptSystem.OnProcessPlayerRoomMes(this,playerId,mes);
	//m_scriptLock.Release();
}

/// 处理用户进入房间消息
void Room::OnProcessEnterRoomMsg(int playerId)
{
	//m_scriptLock.Acquire();
	m_ScriptSystem.OnProcessEnterRoomMsg(this,playerId);
	//m_scriptLock.Release();
}

/// 处理用户离开房间消息
void Room::OnProcessLeaveRoomMsg(int playerId)
{
	//m_scriptLock.Acquire();
	m_ScriptSystem.OnProcessLeaveRoomMsg(this,playerId);
	//m_scriptLock.Release();
}

/// 处理用户断开连接消息
void Room::OnProcessDisconnectNetMes(int playerId)
{
	//m_scriptLock.Acquire();
	m_ScriptSystem.OnProcessDisconnectNetMes(this,playerId);
	//m_scriptLock.Release();
}

/// 处理用户断线重连消息
void Room::OnProcessDisconnectBackNetMes(int playerId)
{
	//m_scriptLock.Acquire();
	m_ScriptSystem.OnProcessDisconnectBackNetMes(this,playerId);
	//m_scriptLock.Release();
}

/// 处理用户定时器消息
void Room::OnProcessTimerMsg()
{
	if(m_timerList.empty()) return;

	m_timerLock.Acquire();
	std::map<long,RoomTimer>::iterator iter = m_timerList.begin();
	for(;iter != m_timerList.end();iter++)
	{
		if(m_timerList.empty()) break;
		if((*iter).second.m_isEnable == false) continue;

		if((*iter).second.curTime > 0 )
		{
			(*iter).second.curTime-=1;

			m_ScriptSystem.OnProcessTimerMsg(this,(*iter).second.TimerId,(*iter).second.curTime);
		}

		if((*iter).second.curTime <= 0)
		{
			(*iter).second.curTime = (*iter).second.TimerSpace;
		}
	}
	m_timerLock.Release();
}

/**
 * 用于处理接收到的网络消息
 *
 * @param connId 要处理的客户端
 * @param mes 要处理的客户端发送的网络消息
 */
void Room::OnProcessNetMes(int connId,CMolMessageIn *mes)
{
	if(mes == NULL) return;

	//int mesId = mes->readShort();

	//switch(mesId)
	//{
	//case IDD_MESSAGE_READY_START:                 // 玩家准备开始
	//	{
	//		int playerId = GetPlayerIndex(connId);
	//		if(playerId == -1) return;

	//		OnProcessPlayerReadyMes(playerId);
	//	}
	//	break;
	//case IDD_MESSAGE_GAMING:                      // 玩家游戏中消息
	//	{
			int playerId = GetPlayerIndex(connId);
			if(playerId == -1) return;

			OnProcessPlayerRoomMes(playerId,mes);
	//	}
	//	break;
	//default:
	//	break;
	//}
}

/** 
 * 更新指定玩家的数据
 *
 * @param ChairID 要更新的玩家的ID
 */
void Room::UpdateUserScore(int ChairID)
{
	ServerDBOperator.UpdateUserData(GetPlayer(ChairID));
}

/** 
 * 游戏开始是调用
 */
void Room::GameStart(void)
{
	// 向当前服务器中所有用户广播当前这桌已经开始了游戏
	CMolMessageOut out(IDD_MESSAGE_FRAME);	
	out.writeShort(IDD_MESSAGE_GAME_START);
	out.writeLong(GetID());
	ServerPlayerManager.SendMsgToEveryone(out);

	// 设置房间状态为开始状态，所有用户状态为开始状态
	SetRoomState(ROOMSTATE_GAMING);
	SetAllPlayerState(PLAYERSTATE_GAMING);
}

/** 
 * 游戏结束时调用
 */
void Room::GameEnd(void)
{
	// 向当前服务器中所有用户广播当前这桌已经结束了游戏
	CMolMessageOut out(IDD_MESSAGE_FRAME);	
	out.writeShort(IDD_MESSAGE_GAME_END);
	out.writeLong(GetID());
	ServerPlayerManager.SendMsgToEveryone(out);

	// 从房间中剔除所有的机器人,并且更新所有玩家的数据
	m_playersLock.Acquire();
	for(int index = 0;index < GetMaxPlayer();index++)
	{
		if(m_PlayerList[index] == NULL) continue;

		// 更新玩家的结果信息
		CMolMessageOut out(IDD_MESSAGE_GET_PLAYER_MES);
		out.writeShort(IDD_MESSAGE_GET_SUCCESS);	
		out.writeLong(m_PlayerList[index]->GetID());
			out.writeString(m_PlayerList[index]->GetUserAvatar());
			out.writeShort(m_PlayerList[index]->GetLevel());
			out.writeDouble(m_PlayerList[index]->GetMoney());
			out.writeLong(m_PlayerList[index]->GetExperience());
			out.writeShort(m_PlayerList[index]->GetTotalBureau());
			out.writeShort(m_PlayerList[index]->GetSuccessBureau());
			out.writeShort(m_PlayerList[index]->GetFailBureau());
			out.writeFloat(m_PlayerList[index]->GetSuccessRate());
			out.writeFloat(m_PlayerList[index]->GetRunawayrate());
			ServerPlayerManager.SendMsgToEveryone(out);

			// 如果一局结束，用户是机器人，就离开房间
			if(m_PlayerList[index]->GetType() == PLAYERTYPE_ROBOT)
			{
				// 向当前服务器中所有用户发送玩家离开房间消息
				CMolMessageOut out(IDD_MESSAGE_FRAME);	
				out.writeShort(IDD_MESSAGE_LEAVE_ROOM);
				out.writeLong(m_PlayerList[index]->GetID());
				ServerPlayerManager.SendMsgToEveryone(out);

				ClearPlayer(m_PlayerList[index]);
				continue;
			}
			else if(m_PlayerList[index]->GetType() == PLAYERTYPE_NORMAL)
			{
				ServerDBOperator.UpdateUserData(m_PlayerList[index]);
			}

			if(m_PlayerList[index]->GetState() == PLAYERSTATE_LOSTLINE)          // 如果一局结束，但用户已经掉线而且没有回来，先离开房间，然后离开服务器，他需要重新登录才能进入游戏
			{
				// 向房间所有玩家广播玩家离开服务器消息
				CMolMessageOut out(IDD_MESSAGE_FRAME);
				out.writeShort(IDD_MESSAGE_LEAVE_SERVER);
				out.writeLong(m_PlayerList[index]->GetID());		
				ServerPlayerManager.SendMsgToEveryone(out);

				m_PlayerList[index]->SetRoomId(-1);
				m_PlayerList[index]->SetRoomIndex(-1);
				m_PlayerList[index]->SetState(PLAYERSTATE_NORAML);

				Disconnect(m_PlayerList[index]->GetConnectID());
				ServerPlayerManager.ClearPlayer(m_PlayerList[index]);

				m_PlayerList[index] = NULL;
				continue;
			}
			else
			{
				// 重新将状态设置成正常状态
				m_PlayerList[index]->SetState(PLAYERSTATE_NORAML);
			}
	}
	m_playersLock.Release();

	// 重置房间状态
	Clear();

	// 回收原来用过的内存
	m_ScriptSystem.ReGetMemory();
}