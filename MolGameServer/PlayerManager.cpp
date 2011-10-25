#include "stdafx.h"

#include "MolServerCom.h"
#include "PlayerManager.h"
#include "RoomManager.h"

#include "defines.h"

#include "MolServerDlg.h"

initialiseSingleton(PlayerManager);

PlayerManager::PlayerManager()
{

}

PlayerManager::~PlayerManager()
{
	ClearAllPlayers();
}

/**
 * 清除所有的玩家
 */
void PlayerManager::ClearAllPlayers(void)
{
	if(m_PlayerList.empty() && m_RobotList.empty()) return;

	std::map<int,Player*>::iterator iter = m_PlayerList.begin();
	for(;iter != m_PlayerList.end();iter++)
	{
		if((*iter).second) delete (*iter).second;
		(*iter).second = NULL;
	}

	m_PlayerList.clear();

	iter = m_RobotList.begin();
	for(;iter != m_RobotList.end();iter++)
	{
		if((*iter).second) delete (*iter).second;
		(*iter).second = NULL;
	}

	m_RobotList.clear();
}

/**
 * 添加一个玩家到系统中
 *
 * @param pPlayer 要添加到系统中的玩家
 */
void PlayerManager::AddPlayer(Player *pPlayer)
{
	if(pPlayer == NULL) return;

	//char buf[256];
	//sprintf(buf,"添加一个玩家%d:%d\n",pPlayer->GetID(),pPlayer->GetConnectID());
	//CMolServerDlg::getSingleton().PrintLog(buf);

	// 检测玩家是否已经存在于服务器中，如果存在就不加入了
	if(GetPlayerById(pPlayer->GetID())) return;

	m_PlayersLock.Acquire();
	m_PlayerList.insert(std::pair<int,Player*>(pPlayer->GetConnectID(),pPlayer));
	m_PlayersLock.Release();
}

/// 添加一个机器人到系统中
void PlayerManager::AddRobot(Player *pPlayer)
{
	if(pPlayer == NULL) return;

	m_PlayersLock.Acquire();
	m_RobotList.insert(std::pair<int,Player*>(pPlayer->GetID(),pPlayer));
	m_PlayersLock.Release();
}

/**
 * 从系统中删除指定网络ID的玩家
 *
 * @param connId 要删除的客户端的ID
 */
void PlayerManager::ClearPlayerByconnId(int connId)
{
	if(m_PlayerList.empty()) return;

	m_PlayersLock.Acquire();
	std::map<int,Player*>::iterator iter = m_PlayerList.find(connId);
	if(iter != m_PlayerList.end())
	{
		Player *pPlayer = dynamic_cast<Player*>((*iter).second);
		if(pPlayer == NULL) 
		{
			m_PlayersLock.Release();
			return;
		}

		if(pPlayer->GetConnectID() == connId) 
		{
			delete pPlayer;
			pPlayer = NULL;

			m_PlayerList.erase(iter);
		}		
	}
	m_PlayersLock.Release();
}

/**
 * 通过客户端连接ID得到客户端
 *
 * @param connId 要得到的客户端的ID
 *
 * @return 如果这个客户端存在返回这个客户端，否则返回NULL
 */
Player* PlayerManager::GetPlayer(int connId)
{
	if(m_PlayerList.empty()) return NULL;

	Player *pPlayer = NULL;

	m_PlayersLock.Acquire();
	std::map<int,Player*>::iterator iter = m_PlayerList.find(connId);
	if(iter != m_PlayerList.end())
	{
		if((*iter).second &&
			(*iter).second->GetConnectID() == connId)          
		{
			pPlayer = (*iter).second;
		}		
	}
	m_PlayersLock.Release();

	return pPlayer;
}

/** 
 * 得到空闲的机器人
 */
Player* PlayerManager::GetFreeRobot(void)
{
	if(m_RobotList.empty()) return NULL;

	Player *pPlayer = NULL;

	m_PlayersLock.Acquire();
	std::map<int,Player*>::iterator iter = m_RobotList.begin();
	for(;iter != m_RobotList.end();iter++)
	{
		if((*iter).second &&
			(*iter).second->GetState() == PLAYERSTATE_NORAML && 
			(*iter).second->GetRoomId() == -1 &&
			(*iter).second->GetMoney() > CMolServerDlg::getSingleton().GetServerSet()->lastmoney)          
		{
			pPlayer = (*iter).second;
			break;
		}		
	}
	m_PlayersLock.Release();

	return pPlayer;
}

/**
 * 通过客户端连接ID得到刚登陆的客户端
 *
 * @param connId 要得到的客户端的ID
 *
 * @return 如果这个客户端存在返回这个客户端，否则返回NULL
 */
Player* PlayerManager::GetNewPlayer(int connId)
{
	if(m_PlayerList.empty()) return NULL;

	Player *pPlayer = NULL;

	m_PlayersLock.Acquire();
	std::map<int,Player*>::iterator iter = m_PlayerList.find(connId);
	if(iter != m_PlayerList.end())
	{
		if((*iter).second &&
			(*iter).second->GetConnectID() == connId &&
			((*iter).second->GetState() == PLAYERSTATE_NORAML))          
		{
			pPlayer = (*iter).second;
		}		
	}
	m_PlayersLock.Release();

	return pPlayer;
}

/**
 * 通过玩家ID得到客户端
 *
 * @param id 要得到的用户的ID
 * 
 * @return 如果这个指定ID的用户存在返回这个客户端，否则返回NULL
 */
Player* PlayerManager::GetPlayerById(int id)
{
	if(m_PlayerList.empty()) return NULL;

	Player *pPlayer = NULL;

	m_PlayersLock.Acquire();
	std::map<int,Player*>::iterator iter = m_PlayerList.begin();
	for(;iter != m_PlayerList.end();iter++)
	{
		if((*iter).second &&
			(*iter).second->GetID() == id) 
		{
			pPlayer = (*iter).second;
			break;
		}		
	}
	m_PlayersLock.Release();

	return pPlayer;
}

/**
 * 从系统中删除指定的玩家
 *
 * @param pPlayer 要删除的玩家
 */
void PlayerManager::ClearPlayer(Player *pPlayer)
{
	if(pPlayer == NULL ||
		m_PlayerList.empty()) return;

	m_PlayersLock.Acquire();
	std::map<int,Player*>::iterator iter = m_PlayerList.find(pPlayer->GetConnectID());
	if(iter != m_PlayerList.end())
	{
		Player *pPlayer = dynamic_cast<Player*>((*iter).second);
		if(pPlayer == NULL) 
		{
			m_PlayersLock.Release();
			return;
		}

		delete pPlayer;
		pPlayer = NULL;

		m_PlayerList.erase(iter);
	}
	m_PlayersLock.Release();
}

/** 
 * 根据玩家的连接ID设置玩家
 *
 * @param pPlayer 要重新设置的玩家数据
 */
void PlayerManager::Reset(int oldConn,Player *pPlayer)
{
	if(pPlayer == NULL ||
		m_PlayerList.empty()) return;

	m_PlayersLock.Acquire();
	std::map<int,Player*>::iterator newiter = m_PlayerList.find(pPlayer->GetConnectID());
	std::map<int,Player*>::iterator olditer = m_PlayerList.find(oldConn);
	if(newiter != m_PlayerList.end())
	{
		if((*newiter).second) delete (*newiter).second;
		(*newiter).second = NULL;

		(*newiter).second = pPlayer;
	}
	else
	{
		m_PlayerList.insert(std::pair<int,Player*>(pPlayer->GetConnectID(),pPlayer));
	}
	if(olditer != m_PlayerList.end())
	{
		m_PlayerList.erase(olditer);
	}
	m_PlayersLock.Release();
}

/**
 * 发送消息给当前在线的所有玩家
 *
 * @param msg 要发送的消息
 */
void PlayerManager::SendMsgToEveryone(CMolMessageOut &msg)
{
	if(m_PlayerList.empty()) return;

	m_PlayersLock.Acquire();
	std::map<int,Player*>::iterator iter = m_PlayerList.begin();
	for(;iter != m_PlayerList.end();iter++)
	{
		Player *pPlayer = dynamic_cast<Player*>((*iter).second);
		if(pPlayer == NULL) continue;

		Send(pPlayer->GetConnectID(),msg);
	}
	m_PlayersLock.Release();
}

/**
 * 发送消息给除了指定玩家的所有在线玩家
 *
 * @param connId 要排除在外的玩家的连接ID
 * @param msg 要发送的消息
 */
void PlayerManager::SendMsgToOtherPlayer(int connId,CMolMessageOut &msg)
{
	if(m_PlayerList.empty()) return;

	m_PlayersLock.Acquire();
	std::map<int,Player*>::iterator iter = m_PlayerList.begin();
	for(;iter != m_PlayerList.end();iter++)
	{
		Player *pPlayer = dynamic_cast<Player*>((*iter).second);
		if(pPlayer == NULL || pPlayer->GetConnectID() == connId) continue;

		Send(pPlayer->GetConnectID(),msg);
	}
	m_PlayersLock.Release();
}

/**
 * 发送给所有玩家心跳包
 */
void PlayerManager::SendAllPlayersHeartJitter(void)
{
	if(m_PlayerList.empty()) return;

	m_PlayersLock.Acquire();
	std::map<int,Player*>::iterator iter = m_PlayerList.begin();
	for(;iter != m_PlayerList.end();iter++)
	{
		Player *pPlayer = dynamic_cast<Player*>((*iter).second);
		if(pPlayer == NULL) continue;

		CMolMessageOut out(IDD_MESSAGE_HEART_JITTER);

		Send(pPlayer->GetConnectID(),out);

		// 心跳计数加一次
		pPlayer->SetHeartCount(pPlayer->GetHeartCount()+1);
	}
	m_PlayersLock.Release();
}

/**
 * 用于维护当前所有的玩家
 */
void PlayerManager::OnProcessAllPlayersHeart(void)
{
	if(m_PlayerList.empty()) return;

	m_PlayersLock.Acquire();
    std::map<int,Player*>::iterator iter = m_PlayerList.begin();
	for(;iter != m_PlayerList.end();)
	{
		Player *pPlayer = dynamic_cast<Player*>((*iter).second);
		if(pPlayer == NULL) 
		{
			iter++;
			continue;
		}

		if(pPlayer->GetHeartCount() > 10 /*|| pPlayer->GetRoomId() == -1*/) 
		{
			/*// 如果用户处于换房间状态就不用掉线了
			if(pPlayer->GetState() == PLAYERSTATE_CHANGEROOM && pPlayer->GetRoomId() == -1)
			{
				iter++;
				continue;
			}*/

			// 如果用户处于掉线状态，但房间状态还在游戏中，就不能删除玩家
			Room *pRoom = ServerRoomManager.GetRoomById(pPlayer->GetRoomId());
			if(pRoom)
			{
				if(pPlayer->GetState() == PLAYERSTATE_LOSTLINE && pRoom->GetRoomState() == ROOMSTATE_GAMING)
				{
					iter++;
					continue;
				}
			}

			//char buf[256];
			//sprintf(buf,"断开%d,心跳%d,房间%d,状态%d\n",(*iter)->GetID(),(*iter)->GetHeartCount(),(*iter)->GetRoomId());
			//::OutputDebugString(buf);

			// 向当前服务器中所有用户发送玩家离开服务器消息
			CMolMessageOut out(IDD_MESSAGE_FRAME);	
			out.writeShort(IDD_MESSAGE_LEAVE_SERVER);
			out.writeShort(pPlayer->GetID());

			ServerPlayerManager.SendMsgToEveryone(out);

			ServerRoomManager.ClearPlayer(pPlayer);
			
			// 如果用户5次丢包的话，就关闭这个客户端的连接，从在线玩家列表中清除
			Disconnect(pPlayer->GetConnectID());

			if(pPlayer) delete pPlayer;
			pPlayer = NULL;

			iter = m_PlayerList.erase(iter);
		}		
		else
		{
			iter++;
		}
	}
	m_PlayersLock.Release();
}