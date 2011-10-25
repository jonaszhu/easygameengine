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
 * ������е����
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
 * ���һ����ҵ�ϵͳ��
 *
 * @param pPlayer Ҫ��ӵ�ϵͳ�е����
 */
void PlayerManager::AddPlayer(Player *pPlayer)
{
	if(pPlayer == NULL) return;

	//char buf[256];
	//sprintf(buf,"���һ�����%d:%d\n",pPlayer->GetID(),pPlayer->GetConnectID());
	//CMolServerDlg::getSingleton().PrintLog(buf);

	// �������Ƿ��Ѿ������ڷ������У�������ھͲ�������
	if(GetPlayerById(pPlayer->GetID())) return;

	m_PlayersLock.Acquire();
	m_PlayerList.insert(std::pair<int,Player*>(pPlayer->GetConnectID(),pPlayer));
	m_PlayersLock.Release();
}

/// ���һ�������˵�ϵͳ��
void PlayerManager::AddRobot(Player *pPlayer)
{
	if(pPlayer == NULL) return;

	m_PlayersLock.Acquire();
	m_RobotList.insert(std::pair<int,Player*>(pPlayer->GetID(),pPlayer));
	m_PlayersLock.Release();
}

/**
 * ��ϵͳ��ɾ��ָ������ID�����
 *
 * @param connId Ҫɾ���Ŀͻ��˵�ID
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
 * ͨ���ͻ�������ID�õ��ͻ���
 *
 * @param connId Ҫ�õ��Ŀͻ��˵�ID
 *
 * @return �������ͻ��˴��ڷ�������ͻ��ˣ����򷵻�NULL
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
 * �õ����еĻ�����
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
 * ͨ���ͻ�������ID�õ��յ�½�Ŀͻ���
 *
 * @param connId Ҫ�õ��Ŀͻ��˵�ID
 *
 * @return �������ͻ��˴��ڷ�������ͻ��ˣ����򷵻�NULL
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
 * ͨ�����ID�õ��ͻ���
 *
 * @param id Ҫ�õ����û���ID
 * 
 * @return ������ָ��ID���û����ڷ�������ͻ��ˣ����򷵻�NULL
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
 * ��ϵͳ��ɾ��ָ�������
 *
 * @param pPlayer Ҫɾ�������
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
 * ������ҵ�����ID�������
 *
 * @param pPlayer Ҫ�������õ��������
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
 * ������Ϣ����ǰ���ߵ��������
 *
 * @param msg Ҫ���͵���Ϣ
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
 * ������Ϣ������ָ����ҵ������������
 *
 * @param connId Ҫ�ų��������ҵ�����ID
 * @param msg Ҫ���͵���Ϣ
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
 * ���͸��������������
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

		// ����������һ��
		pPlayer->SetHeartCount(pPlayer->GetHeartCount()+1);
	}
	m_PlayersLock.Release();
}

/**
 * ����ά����ǰ���е����
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
			/*// ����û����ڻ�����״̬�Ͳ��õ�����
			if(pPlayer->GetState() == PLAYERSTATE_CHANGEROOM && pPlayer->GetRoomId() == -1)
			{
				iter++;
				continue;
			}*/

			// ����û����ڵ���״̬��������״̬������Ϸ�У��Ͳ���ɾ�����
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
			//sprintf(buf,"�Ͽ�%d,����%d,����%d,״̬%d\n",(*iter)->GetID(),(*iter)->GetHeartCount(),(*iter)->GetRoomId());
			//::OutputDebugString(buf);

			// ��ǰ�������������û���������뿪��������Ϣ
			CMolMessageOut out(IDD_MESSAGE_FRAME);	
			out.writeShort(IDD_MESSAGE_LEAVE_SERVER);
			out.writeShort(pPlayer->GetID());

			ServerPlayerManager.SendMsgToEveryone(out);

			ServerRoomManager.ClearPlayer(pPlayer);
			
			// ����û�5�ζ����Ļ����͹ر�����ͻ��˵����ӣ�����������б������
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