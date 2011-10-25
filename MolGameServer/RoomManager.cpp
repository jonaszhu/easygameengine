#include "stdafx.h"

#include "MolServerCom.h"

#include "RoomManager.h"
#include "PlayerManager.h"
#include "ScriptSystem.h"

#include "defines.h"
#include "MolServerDlg.h"
#include "Mole2dLogger.h"

#include <sstream>

initialiseSingleton(RoomManager);

RoomManager::RoomManager()
{

}

RoomManager::~RoomManager()
{
	ClearAllRooms();
}

/**
 * 清除所有的房间
 */
void RoomManager::ClearAllRooms(void)
{
	if(m_RoomList.empty()) return;

	m_RoomLock.Acquire();
	std::list<Room*>::iterator iter = m_RoomList.begin();
	for(;iter != m_RoomList.end();iter++)
	{
		if((*iter)) delete (*iter);
		(*iter) = NULL;
	}

	m_RoomList.clear();

	m_RoomLock.Release();
}

/** 
 * 重新导入并执行脚本
 */
void RoomManager::ReLoadAndRunScript(void)
{
	if(m_RoomList.empty()) return;

	m_RoomLock.Acquire();
	std::list<Room*>::iterator iter = m_RoomList.begin();
	for(;iter != m_RoomList.end();iter++)
	{
		if((*iter)) (*iter)->ReLoadAndRunScript();
	}
	m_RoomLock.Release();
}

/**
 * 添加一个房间到房间管理器中
 *
 * @param pRoom 要添加的房间
 */
void RoomManager::AddRoom(Room *pRoom)
{
	if(pRoom == NULL) return;

	pRoom->SetID((int)m_RoomList.size());

	m_RoomList.push_back(pRoom);
}

/**
 * 改变一个玩家的游戏房间
 *
 * @param pPlayer 要改变游戏房间的玩家
 */
bool RoomManager::ChangeGameRoom(Player *pPlayer)
{
	if(pPlayer == NULL ||
		m_RoomList.empty()) 
		return false;

	// 首先检测玩家当前的状态，如果玩家处于准备，等待，游戏中，掉线等状态时说明玩家已经在房间中，不能进入新的房间
	if(pPlayer->GetState() != PLAYERSTATE_NORAML)
		return false;

	// 得到原来玩家所在的房间
	Room *pSrcRoom = GetRoomById(pPlayer->GetRoomId());
	if(pSrcRoom == NULL || pSrcRoom->GetRoomState() != ROOMSTATE_WAITING) return false;

	// 向房间中其它用户发送用户离开消息
	CMolMessageOut out(IDD_MESSAGE_FRAME);
	out.writeShort(IDD_MESSAGE_LEAVE_ROOM);
	out.writeShort(pPlayer->GetID());

	ServerPlayerManager.SendMsgToEveryone(out);

	// 先处理用户在原来房间中离开消息
	pSrcRoom->OnProcessLeaveRoomMsg(pPlayer->GetRoomIndex());

	// 第一遍搜索当前房间中已经存在玩家在那里等待的房间
	bool state = false;

	m_RoomLock.Acquire();
	std::list<Room*>::iterator iter = m_RoomList.begin();
	for(;iter != m_RoomList.end();iter++)
	{
		if((*iter))
		{
			//(*iter)->UpdateAllPlayers();
			// 如果玩家不能满足房间要求的最少金币值，就不能进入房间
			if((*iter)->GetLastMoney() > pPlayer->GetMoney()) continue;

			if(!(*iter)->IsFull() &&
				(*iter)->GetPlayerCount() > 0 &&
				(*iter)->GetRoomState() != ROOMSTATE_GAMING)
			{
				// 找一个与原来不一样的房间
				if(pSrcRoom->GetID() != (*iter)->GetID())
				{
					//PlayerState oldstate = pPlayer->GetState();

					// 设置玩家状态为改变房间状态，这样可以防止服务器将玩家强行掉线
					//pPlayer->SetState(PLAYERSTATE_CHANGEROOM);

					// 先从原来的房间中删除这个玩家
					pSrcRoom->ClearPlayer(pPlayer);

					// 更新一下房间中的用户
					(*iter)->UpdateOnlinePlayers();

					pPlayer->SetRoomId((*iter)->GetID());
					//pPlayer->SetState(oldstate);
					
					int playerIndex = (*iter)->AddPlayer(pPlayer);
					pPlayer->SetRoomIndex(playerIndex);					

					state = true;
					break;
				}
			}
		}
	}	
	m_RoomLock.Release();

	if(state) return state;

	// 第二遍搜索当前房间中没有坐满的房间或者空房间
	state = false;

	m_RoomLock.Acquire();
	iter = m_RoomList.begin();
	for(;iter != m_RoomList.end();iter++)
	{
		if((*iter))
		{
			//(*iter)->UpdateAllPlayers();
			// 如果玩家不能满足房间要求的最少金币值，就不能进入房间
			if((*iter)->GetLastMoney() > pPlayer->GetMoney()) continue;

			if(!(*iter)->IsFull() &&
				(*iter)->GetRoomState() != ROOMSTATE_GAMING)
			{
				// 找一个与原来不一样的房间
				if(pSrcRoom->GetID() != (*iter)->GetID())
				{
					//PlayerState oldstate = pPlayer->GetState();

					// 设置玩家状态为改变房间状态，这样可以防止服务器将玩家强行掉线
					//pPlayer->SetState(PLAYERSTATE_CHANGEROOM);

					// 先从原来的房间中删除这个玩家
					pSrcRoom->ClearPlayer(pPlayer);

					// 更新一下房间中的用户
					(*iter)->UpdateOnlinePlayers();

					if(pPlayer == NULL) 
					{
						state = false;
						break;
					}

					pPlayer->SetRoomId((*iter)->GetID());
					//pPlayer->SetState(oldstate);

					int playerIndex = (*iter)->AddPlayer(pPlayer);
					pPlayer->SetRoomIndex(playerIndex);		

					state = true;
					break;
				}
			}
		}
	}	
	m_RoomLock.Release();

	return state;
}

/** 
 * 添加一个旁观玩家到房间中
 *
 * @param pPlayer 要添加的玩家
 * @param roomIndex 玩家要进入的房间的索引
 * @param chairIndex 玩家要进入的房间的椅子的索引
 */
bool RoomManager::AddLookOnPlayer(Player *pPlayer,int roomIndex,int chairIndex)
{
	if(pPlayer == NULL ||
		m_RoomList.empty()) 
		return false;

	// 首先检测玩家当前的状态，如果玩家处于准备，等待，游戏中，掉线等状态时说明玩家已经在房间中，不能进入新的房间
	if(pPlayer->GetState() != PLAYERSTATE_NORAML)
		return false;

	// 玩家要进入指定房间，指定的座位
	Room *pRoom = GetRoomById(roomIndex);
	if(pRoom == NULL) return false;

	// 如果房间已满或者房间状态处于游戏中的话，是进不了房间的
	if(/*pRoom->IsFull() ||*/
		pRoom->GetRoomState() != ROOMSTATE_GAMING)
		return false;

	// 检测房间中指定索引的玩家是否存在，如果存在是不能加入房间的
	if(!pRoom->GetPlayer(chairIndex))
		return false;

	// 更新一下房间中的用户
	pRoom->UpdateOnlinePlayers();

	pPlayer->SetRoomId(pRoom->GetID());
	pPlayer->SetRoomIndex(pRoom->AddLookOnPlayer(pPlayer,chairIndex));
	pPlayer->SetLookOn(true);

	return true;
}

/**
 * 添加一个玩家到房间中
 *
 * @param pPlayer 要添加的玩家
 * @param roomIndex 玩家要进入的房间的索引
 * @param chairIndex 玩家要进入的房间的椅子的索引
 */
bool RoomManager::AddPlayer(Player *pPlayer,int roomIndex,int chairIndex)
{
	if(pPlayer == NULL ||
		m_RoomList.empty()) 
		return false;

	// 首先检测玩家当前的状态，如果玩家处于准备，等待，游戏中，掉线等状态时说明玩家已经在房间中，不能进入新的房间
	if(pPlayer->GetState() != PLAYERSTATE_NORAML)
		return false;

	// 如果roomIndex等于-1,chairIndex等于-1表示当前玩家不需要排队进入房间
	if(roomIndex == -1 && chairIndex == -1)
	{
		// 第一遍搜索当前房间中已经存在玩家在那里等待的房间
		bool state = false;

		m_RoomLock.Acquire();
		std::list<Room*>::iterator iter = m_RoomList.begin();
		for(;iter != m_RoomList.end();iter++)
		{
			if((*iter))
			{
				//(*iter)->UpdateAllPlayers();
				// 如果玩家不能满足房间要求的最少金币值，就不能进入房间
				if((*iter)->GetLastMoney() > pPlayer->GetMoney()) continue;
				
				// 如果当前不是百人房间，那么房间状态必须不在游戏状态下
				if(CMolServerDlg::getSingleton().GetServerSet()->TableCount > 1)
				{
					if((*iter)->GetRoomState() == ROOMSTATE_GAMING)
					{
						state = false;
						continue;
					}
				}

				if(!(*iter)->IsFull() &&
					(*iter)->GetPlayerCount() > 0)
				{				
					// 更新一下房间中的用户
					(*iter)->UpdateOnlinePlayers();

					if(pPlayer == NULL) 
					{
						state = false;
						break;
					}

					//char str[1024];
					//sprintf(str,"玩家%d进入房间%d,ID为%d,房间中人数:%d",pPlayer->GetConnectID(),(*iter)->GetID(),pPlayer->GetRoomIndex(),(*iter)->GetPlayerCount());
					//LOG_ERRORR(str);

					pPlayer->SetRoomId((*iter)->GetID());
					int playerIndex = (*iter)->AddPlayer(pPlayer);
					pPlayer->SetRoomIndex(playerIndex);		

					state = true;
					break;
				}
			}
		}	
		m_RoomLock.Release();

		if(state) return state;

		// 第二遍搜索当前房间中没有坐满的房间或者空房间
		state = false;

		m_RoomLock.Acquire();
		iter = m_RoomList.begin();
		for(;iter != m_RoomList.end();iter++)
		{
			if((*iter))
			{
				//(*iter)->UpdateAllPlayers();
				// 如果玩家不能满足房间要求的最少金币值，就不能进入房间
				if((*iter)->GetLastMoney() > pPlayer->GetMoney()) continue;
				
				// 如果当前不是百人房间，那么房间状态必须不在游戏状态下
				if(CMolServerDlg::getSingleton().GetServerSet()->TableCount > 1)
				{
					if((*iter)->GetRoomState() == ROOMSTATE_GAMING)
					{
						state = false;
						continue;
					}
				}				

				if(!(*iter)->IsFull())
				{			
					// 更新一下房间中的用户
					(*iter)->UpdateOnlinePlayers();

					if(pPlayer == NULL) 
					{
						state = false;
						break;
					}

					pPlayer->SetRoomId((*iter)->GetID());
					int playerIndex = (*iter)->AddPlayer(pPlayer);
					pPlayer->SetRoomIndex(playerIndex);		

					state = true;
					break;
				}
			}
		}	
		m_RoomLock.Release();

		return state;
	}
	else
	{
		// 玩家要进入指定房间，指定的座位
		Room *pRoom = GetRoomById(roomIndex);
		if(pRoom == NULL) return false;

		// 如果房间已满或者房间状态处于游戏中的话，是进不了房间的
		if(pRoom->IsFull() ||
			pRoom->GetRoomState() == ROOMSTATE_GAMING)
			return false;

		// 检测房间中指定索引的玩家是否存在，如果存在是不能加入房间的
		if(pRoom->GetPlayer(chairIndex))
			return false;

		// 更新一下房间中的用户
		pRoom->UpdateOnlinePlayers();

		pPlayer->SetRoomId(pRoom->GetID());
		int playerIndex = pRoom->AddPlayer(pPlayer,chairIndex);
		pPlayer->SetRoomIndex(playerIndex);		

		return true;
	}

	return true;
}

/**
 * 从房间中清除指定的玩家
 *
 * @param pPlayer 要清除的玩家
 */
void RoomManager::ClearPlayer(Player *pPlayer)
{
	if(pPlayer == NULL ||
		m_RoomList.empty()) 
		return;

	m_RoomLock.Acquire();
	std::list<Room*>::iterator iter = m_RoomList.begin();
	for(;iter != m_RoomList.end();iter++)
	{
		if((*iter) && 
			(*iter)->IsExist(pPlayer))
		{
			(*iter)->ClearPlayer(pPlayer);
			break;
		}
	}
	m_RoomLock.Release();
}

/**
 * 从当前房间中删除指定的玩家
 *
 * @param pPlayer 要删除的玩家
 *
 * @return  如果玩家清除成功返回真，否则返回假
 */
bool RoomManager::DeletePlayer(Player *pPlayer)
{
	if(pPlayer == NULL ||
		m_RoomList.empty()) 
		return false;

	bool state = false;

	m_RoomLock.Acquire();
	std::list<Room*>::iterator iter = m_RoomList.begin();
	for(;iter != m_RoomList.end();iter++)
	{
		if((*iter) && 
			(*iter)->IsExist(pPlayer))
		{
			(*iter)->DeletePlayer(pPlayer);
			state = true;
			break;
		}
	}	
	m_RoomLock.Release();

	return state;
}

/**
 * 根据房间ID号得到房间
 *
 * @param id 要得到的房间的ID
 *
 * @return 如果根据这个ID能得到这个房间，返回真个房间，否则返回NULL
 */
Room* RoomManager::GetRoomById(int id)
{
	if(m_RoomList.empty()) return NULL;

	Room *pRoom = NULL;

	m_RoomLock.Acquire();
	std::list<Room*>::iterator iter = m_RoomList.begin();
	for(;iter != m_RoomList.end();iter++)
	{
		if((*iter)->GetID() == id) 
		{
			pRoom = (*iter);
			break;
		}
	}
	m_RoomLock.Release();

	return pRoom;
}

/**
 * 游戏所有房间更新
 *
 * @param time 系统当前时间
 */
void RoomManager::Update(DWORD time)
{
	if(m_RoomList.empty())
		return;

	m_RoomLock.Acquire();
	std::list<Room*>::iterator iter = m_RoomList.begin();
	for(;iter != m_RoomList.end();iter++)
	{
		if((*iter))
			(*iter)->Update(time);
	}
	m_RoomLock.Release();
}

/**
 * 重置所有的游戏房间
 */
void RoomManager::ResetAllGameRooms(void)
{
	if(m_RoomList.empty())
		return;

	m_RoomLock.Acquire();
	std::list<Room*>::iterator iter = m_RoomList.begin();
	for(;iter != m_RoomList.end();iter++)
	{
		if((*iter))
			(*iter)->ClearAllPlayers();
	}
	m_RoomLock.Release();
}

/**
 * 用于处理玩家改变游戏房间
 *
 * @param connId 要处理的网络连接的客户端连接ID
 */
void RoomManager::OnProcessChangeGameRoomMes(int connId)
{
	Player *pPlayer = ServerPlayerManager.GetNewPlayer(connId);
	if(pPlayer != NULL) 
	{	
		if(ChangeGameRoom(pPlayer))
		{
			// 先向服务器中所有的在线玩家通告玩家进入游戏房间的消息
			CMolMessageOut out(IDD_MESSAGE_FRAME);	
			out.writeShort(IDD_MESSAGE_ENTER_ROOM);
			out.writeShort(IDD_MESSAGE_ENTER_ROOM_SUCC);
			out.writeLong(pPlayer->GetID());
			out.writeShort(pPlayer->GetRoomId());
			out.writeShort(pPlayer->GetRoomIndex());

			ServerPlayerManager.SendMsgToEveryone(out);
		}
		else
		{
			// 向当前玩家发送进入游戏房间失败的消息
			CMolMessageOut out(IDD_MESSAGE_FRAME);	
			out.writeShort(IDD_MESSAGE_ENTER_ROOM);
			out.writeShort(IDD_MESSAGE_ENTER_ROOM_FAIL);
			out.writeLong(pPlayer->GetID());

			Send(pPlayer->GetConnectID(),out);
		}		

		//// 如果交换房间成功的话，处理玩家进入新房间消息
		//Room *pRoom = GetRoomById(pPlayer->GetRoomId());

		//if(pRoom)
		//{
		//	int playerId = pRoom->GetPlayerIndex(pPlayer->GetConnectID());
		//	pRoom->OnProcessEnterRoomMsg(playerId);
		//}
	}
}

/**
 * 用于处理用于断开网络连接消息
 *
 * @param connId 要断开网络连接的客户端连接ID
 */
void RoomManager::OnProcessDisconnectNetMes(int connId)
{
	// 首先根据用户连接ID得到用户，然后根据用户信息得到房间信息，最后交给房间处理
	Player *pPlayer = ServerPlayerManager.GetPlayer(connId);
	if(pPlayer == NULL) return;

	Room *pRoom = GetRoomById(pPlayer->GetRoomId());
	if(pRoom == NULL) 
	{
		// 如果用户没有进入任何房间的话，删除这个玩家
		CMolMessageOut out(IDD_MESSAGE_FRAME);	
		out.writeShort(IDD_MESSAGE_LEAVE_SERVER);
		out.writeShort(pPlayer->GetID());

		ServerPlayerManager.SendMsgToEveryone(out);

		Disconnect(pPlayer->GetConnectID());
		ServerPlayerManager.ClearPlayer(pPlayer);
		return;
	}

	//m_RoomLock.Acquire();
	//int playerId = pRoom->GetPlayerIndex(pPlayer->GetConnectID());

	if(pPlayer->GetState() == PLAYERSTATE_GAMING)
	{
		pPlayer->SetState(PLAYERSTATE_LOSTLINE);

		// 向房间所有玩家广播玩家离开房间消息
		CMolMessageOut out(IDD_MESSAGE_FRAME);
		out.writeShort(IDD_MESSAGE_FALLLINE_ROOM);
		out.writeLong(pPlayer->GetID());
		
		ServerPlayerManager.SendMsgToEveryone(out);
	}
	else 
	{
		// 向房间所有玩家广播玩家离开服务器消息
		CMolMessageOut out(IDD_MESSAGE_FRAME);
		out.writeShort(IDD_MESSAGE_LEAVE_SERVER);
		out.writeLong(pPlayer->GetID());		
		ServerPlayerManager.SendMsgToEveryone(out);

		pRoom->ClearPlayer(pPlayer);

		Disconnect(pPlayer->GetConnectID());
		ServerPlayerManager.ClearPlayer(pPlayer);
		return;
	}

	pRoom->OnProcessDisconnectNetMes(pPlayer->GetRoomIndex());

	// 如果当前处于游戏中状态下的话，用户就不用退出房间,否则退出房间
  //  if(pRoom->GetRoomState() == ROOMSTATE_GAMING)
		//pPlayer->SetState(PLAYERSTATE_LOSTLINE);

	if(pPlayer->GetState() != PLAYERSTATE_LOSTLINE)
		pRoom->ClearPlayer(pPlayer);

	// 如果房间中的用户全部掉线，就清空房间状态
	if(pRoom->GetPlayerCount(PLAYERSTATE_LOSTLINE) == pRoom->GetMaxPlayer()/* ||
		pRoom->GetLostPlayerCount() >= pRoom->GetMaxPlayer()-1*/)
	{
		pRoom->GameEnd();
		pRoom->AllPlayerLeveaServer();
	}
	//m_RoomLock.Release();
}

/**
 * 用于处理接收到的网络消息
 *
 * @param connId 要处理的客户端
 * @param mes 要处理的客户端的消息
 */
void RoomManager::OnProcessNetMes(int connId,CMolMessageIn *mes)
{
	if(mes == NULL || m_RoomList.empty()) return;

	Player *pPlayer = ServerPlayerManager.GetPlayer(connId);
	if(pPlayer == NULL) return;

	Room *pRoom = ServerRoomManager.GetRoomById(pPlayer->GetRoomId());
	if(pRoom == NULL) return;

	pRoom->OnProcessNetMes(connId,mes);	
}