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
		CMolServerDlg::getSingleton().PrintLog("���䶨ʱ���������ɹ���");
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
 * ���µ��벢ִ�нű�
 */
void Room::ReLoadAndRunScript(void)
{
	m_ScriptSystem.LoadAndRunScript();
}

/**
 * ��ǰ�����Ƿ�Ϊ��
 *
 * @return �����ǰ����Ϊ�յĻ������棬���򷵻ؼ�
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
 * ������������е����
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
	//sprintf(buf,"�ӷ���:%d��������е���ҡ�\n",GetID());
	//CMolServerDlg::getSingleton().PrintLog(buf);
}

/** 
 * ��ǰ����������ҷ����û��뿪��������Ϣ
 */
void Room::AllPlayerLeveaServer(void)
{
	m_playersLock.Acquire();
	for(int i=0;i<ROOM_MAX_PLAYERS;i++)
	{
		//m_LookonPlayerList[i] = NULL;

		if(m_PlayerList[i] == NULL) continue;

		// �򷿼�������ҹ㲥����뿪��������Ϣ
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
 * �õ���ǰ����ָ��״̬����Ҹ���
 *
 * @param state Ҫ�õ�����ҵ�״̬
 *
 * @return ����ָ��������״̬����Ҹ���
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
 * ���õ�ǰ����������ҵ�״̬
 *
 * @param state Ҫ���õ���ҵ�״̬
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
 * ����ָ����ҵ�״̬
 *
 * @param index Ҫ���õ���ҵķ���ID
 * @param state Ҫ���õ����״̬
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
 * ���һ����ҵ���ǰ������
 *
 * @param pPlayer Ҫ��ӵ����
 * @param index Ҫ�������ӵ�ָ����λ���ϣ�������ó�-1,��ô��ʾ�����ӵ�������
 *
 * @return ��������ڷ����е�����
 */
int Room::AddPlayer(Player *pPlayer,int index)
{
	int playerIndex = -1;
	
	if(pPlayer == NULL ||
		GetPlayerCount() > m_MaxCount) 
		return playerIndex;

	// ����û��Ѿ��ڷ����У��Ͳ�������
	if(IsExist(pPlayer)) return playerIndex;

	// �����ҵĽ�������Ƿ����㵱ǰ����Ҫ��
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
 * ���һ���Թ���ҵ���ǰ������
 *
 * @param pPlayer Ҫ��ӵ����
 * @param index Ҫ�������ӵ�ָ����λ����
 *
 * @return ��������ڷ����е�����
 */
int Room::AddLookOnPlayer(Player *pPlayer,int index)
{
	int playerIndex = -1;
	
	if(pPlayer == NULL || 
		(index < 0 || index > m_MaxCount)) 
		return playerIndex;

	// ����û��Ѿ��ڷ����У��Ͳ�������
	if(IsExistLookOn(pPlayer)) return playerIndex;

	m_playersLock.Acquire();
	if(index >= 0 && index < ROOM_MAX_PLAYERS)
	{
		std::map<int,std::vector<Player*> >::iterator iter = m_LookonPlayerList.find(index);
		if(iter != m_LookonPlayerList.end())
		{
			// ����Ƿ�������û���û�в���ӽ�ȥ
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
 * ���õ�ǰ����ķ���
 *
 * @param playerId Ҫ���óɷ��������ID
 */
void Room::SetMaster(int playerId)
{
	// �����ǰ�����Ѿ������˷������Ͳ���������
	//if(m_masterId != -1) return;

	m_masterId = playerId;
	m_curPlayerId = m_masterId;
}

/**
 * �õ���ǰ��������һ�����
 */
int Room::GetCurNextPlayer(void)
{
	m_curPlayerId += 1;

	if(m_curPlayerId >= GetPlayerCount())
		m_curPlayerId = 0;

	return m_curPlayerId;
}

/**
 * �õ���ǰ��������һ���������
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
 * ��ʼһ����ʱ��
 *
 * @param timerId Ҫ�����Ķ�ʱ��ID
 * @param space ��ʱ���
 *
 * @return ��������ɹ������棬���򷵻ؼ�
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
 * �ر�һ����ʱ��
 *
 * @param id Ҫ�رյĶ�ʱ��ID
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
 * �ر����еĶ�ʱ��
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
 * �ӵ�ǰ���������ָ�������
 *
 * @param pPlayer Ҫ��������
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
			//sprintf(buf,"�ӷ���%d��������%d:%d\n",GetID(),(*iter)->GetID(),(*iter)->GetConnectID());
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
 * �ӵ�ǰ������ɾ��ָ�������
 *
 * @param pPlayer Ҫɾ�������
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
 * �����û�����ID�õ��û��ڷ����е�ID
 *
 * @param connId Ҫ�õ����û�������ID
 *
 * @return �������û�������������䣬��������û�����������е�ID�����򷵻�-1
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
 * ���ָ���������Ƿ��ڵ�������б���
 *
 * @param index Ҫ��������ڷ����е�����
 *
 * @return �������ڵ�������б��з����棬���򷵻ؼ�
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
 * �����������б������
 *
 * @param id Ҫ�������ҵ�ID
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
 * �ӵ�ǰ���������ָ������ID�����
 *
 * @param Id Ҫ���������ڷ����е�ID
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
 * �õ���ǰ��������
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
 * �õ�׼����״̬����ҵ�����
 *
 * @return ���ص�ǰ������׼���õ���ҵĸ���
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
 * ��յ�ǰ��������
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
 * ���ָ������Ƿ���ڵ�ǰ����
 *
 * @param pPlayer Ҫ�������
 *
 * @return ���Ҫ������Ҵ��ڷ����棬���򷵻ؼ�
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
 * ���ָ�����Թ�����Ƿ���ڵ�ǰ������
 *
 * @param pPlayer Ҫ�������
 *
 * @return ���Ҫ������Ҵ��ڷ����棬���򷵻ؼ�
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
 * ��ⷿ���Ƿ��Ѿ���Ա
 *
 * @return ��������Ѿ���Ա�����棬���򷵻ؼ�
 */
bool Room::IsFull(void)
{
	return GetPlayerCount() == m_MaxCount ? true : false;
}

/**
 * ��ⷿ���Ƿ�ȫ��׼�����
 *
 * @param �����ǰ������Ա����ȫ������׼��״̬�·����棬���򷵻ؼ�
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
 * ��ָ������ҷ�������
 *
 * @param index Ҫ���͵���ҵ�����,���Ϊ-1�Ļ�����ʾ���͸������ˣ������͸�ָ������
 * @param msg Ҫ���͵�����
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
	else if(index == -1)                    // ���͸�������
	{
		SendAllPlayerMsg(msg);
	}
}

/** 
 * ��ָ������ҷ����Թ�����
 *
 * @param index Ҫ���͵���ҵ�����,���Ϊ-1�Ļ�����ʾ���͸������ˣ������͸�ָ������
 * @param msg Ҫ���͵�����
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
	else if(index == -1)                    // ���͸�������
	{
		SendAllLookOnPlayerMsg(msg);
	}
}

///**
// * �����ָ����ҵ�������ҷ�������
// *
// * @param index Ҫ��������ҵ�����
// * @param msg Ҫ���͵�����
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
 * ��������ҷ�������
 *
 * @param msg Ҫ���͵�����
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
 * �������Թ���ҷ�������
 *
 * @param msg Ҫ���͵�����
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
 * ��ӡ������Ϣ
 *
 * @param info Ҫ��ӡ�ĵ�����Ϣ
 */
void Room::PrintDebugInfo(const char* info)
{
	if(info == NULL) return;

	CString tempStr;
	tempStr.Format("����Ϸ���䡿 %s",info);
	CMolServerDlg::getSingleton().PrintLog(tempStr.GetBuffer());
}

/**
 * �õ�ָ�����������
 *
 * @param index Ҫ�õ�����ҵ�����
 *
 * @return ������ָ����������Ҵ��ڷ��������ң����򷵻�NULL
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
 * ���·��������еĵ�ǰ�û�--����������ڷ�ֹ�û�ͻȻ�뿪����
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
// * ���·��������е��û�--����������ڷ�ֹһЩ�û��Ѿ����ߣ���û���뿪����
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
 * ��Ϸ�������
 *
 * @param time ��ǰϵͳʱ��
 */
void Room::Update(DWORD time)
{
	//m_timerLock.Acquire();
	// ������仹������Ϸ״̬�£������е�����Ѿ�ȫ���Ͽ����ӣ������������䣬Ȼ�����µȴ��û�����
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

		// ���ȫ�����ߵĻ����͹رշ���
		if(GetLostPlayerCount() >= GetMaxPlayer())
		{
			ClearAllPlayers();
			Clear();
		}
	}
	else if(GetRoomState() == ROOMSTATE_WAITING)
	{
		// ���ȫ�����ߵĻ����͹رշ���
		if(GetLostPlayerCount() >= GetMaxPlayer())
		{
			ClearAllPlayers();
			Clear();
		}

		//// �������ҵ��ߵĻ����ʹӷ������������û�
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
 * �����������id�õ�����ڵ�ǰ�����е�����
 *
 * @param connId Ҫ�õ��Ŀͻ�������ID
 *
 * @return ������������ڷ����е�����
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
 * ���ڴ����û�׼�������Ϣ
 *
 * @param playerId Ҫ����Ŀͻ��˵ķ���ID
 */
void Room::OnProcessPlayerReadyMes(int playerId)
{
	//m_scriptLock.Acquire();
	m_ScriptSystem.OnProcessPlayerReadyMes(this,playerId);
	//m_scriptLock.Release();
}

///**
// * ���ڴ����û���ʼ��Ϸ�����Ϣ
// *
// * @param playerId Ҫ����Ŀͻ��˵ķ���ID
// * @param mes ���յĿͻ��˷��͵���Ϣ
// */
//void Room::OnProcessPlayerGamingMes(int playerId,CMolMessageIn *mes)
//{
//	m_scriptLock.Acquire();
//	m_ScriptSystem.OnProcessPlayerGamingMes(this,playerId,mes);
//	m_scriptLock.Release();
//}

/** 
 * ���ڴ����û�������Ϸ��������Ϣ
 *
 * @param playerId Ҫ����Ŀͻ��˵ķ���ID
 * @param mes ���յĿͻ��˷��͵���Ϣ
 */
void Room::OnProcessPlayerRoomMes(int playerId,CMolMessageIn *mes)
{
	//m_scriptLock.Acquire();
	m_ScriptSystem.OnProcessPlayerRoomMes(this,playerId,mes);
	//m_scriptLock.Release();
}

/// �����û����뷿����Ϣ
void Room::OnProcessEnterRoomMsg(int playerId)
{
	//m_scriptLock.Acquire();
	m_ScriptSystem.OnProcessEnterRoomMsg(this,playerId);
	//m_scriptLock.Release();
}

/// �����û��뿪������Ϣ
void Room::OnProcessLeaveRoomMsg(int playerId)
{
	//m_scriptLock.Acquire();
	m_ScriptSystem.OnProcessLeaveRoomMsg(this,playerId);
	//m_scriptLock.Release();
}

/// �����û��Ͽ�������Ϣ
void Room::OnProcessDisconnectNetMes(int playerId)
{
	//m_scriptLock.Acquire();
	m_ScriptSystem.OnProcessDisconnectNetMes(this,playerId);
	//m_scriptLock.Release();
}

/// �����û�����������Ϣ
void Room::OnProcessDisconnectBackNetMes(int playerId)
{
	//m_scriptLock.Acquire();
	m_ScriptSystem.OnProcessDisconnectBackNetMes(this,playerId);
	//m_scriptLock.Release();
}

/// �����û���ʱ����Ϣ
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
 * ���ڴ�����յ���������Ϣ
 *
 * @param connId Ҫ����Ŀͻ���
 * @param mes Ҫ����Ŀͻ��˷��͵�������Ϣ
 */
void Room::OnProcessNetMes(int connId,CMolMessageIn *mes)
{
	if(mes == NULL) return;

	//int mesId = mes->readShort();

	//switch(mesId)
	//{
	//case IDD_MESSAGE_READY_START:                 // ���׼����ʼ
	//	{
	//		int playerId = GetPlayerIndex(connId);
	//		if(playerId == -1) return;

	//		OnProcessPlayerReadyMes(playerId);
	//	}
	//	break;
	//case IDD_MESSAGE_GAMING:                      // �����Ϸ����Ϣ
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
 * ����ָ����ҵ�����
 *
 * @param ChairID Ҫ���µ���ҵ�ID
 */
void Room::UpdateUserScore(int ChairID)
{
	ServerDBOperator.UpdateUserData(GetPlayer(ChairID));
}

/** 
 * ��Ϸ��ʼ�ǵ���
 */
void Room::GameStart(void)
{
	// ��ǰ�������������û��㲥��ǰ�����Ѿ���ʼ����Ϸ
	CMolMessageOut out(IDD_MESSAGE_FRAME);	
	out.writeShort(IDD_MESSAGE_GAME_START);
	out.writeLong(GetID());
	ServerPlayerManager.SendMsgToEveryone(out);

	// ���÷���״̬Ϊ��ʼ״̬�������û�״̬Ϊ��ʼ״̬
	SetRoomState(ROOMSTATE_GAMING);
	SetAllPlayerState(PLAYERSTATE_GAMING);
}

/** 
 * ��Ϸ����ʱ����
 */
void Room::GameEnd(void)
{
	// ��ǰ�������������û��㲥��ǰ�����Ѿ���������Ϸ
	CMolMessageOut out(IDD_MESSAGE_FRAME);	
	out.writeShort(IDD_MESSAGE_GAME_END);
	out.writeLong(GetID());
	ServerPlayerManager.SendMsgToEveryone(out);

	// �ӷ������޳����еĻ�����,���Ҹ���������ҵ�����
	m_playersLock.Acquire();
	for(int index = 0;index < GetMaxPlayer();index++)
	{
		if(m_PlayerList[index] == NULL) continue;

		// ������ҵĽ����Ϣ
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

			// ���һ�ֽ������û��ǻ����ˣ����뿪����
			if(m_PlayerList[index]->GetType() == PLAYERTYPE_ROBOT)
			{
				// ��ǰ�������������û���������뿪������Ϣ
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

			if(m_PlayerList[index]->GetState() == PLAYERSTATE_LOSTLINE)          // ���һ�ֽ��������û��Ѿ����߶���û�л��������뿪���䣬Ȼ���뿪������������Ҫ���µ�¼���ܽ�����Ϸ
			{
				// �򷿼�������ҹ㲥����뿪��������Ϣ
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
				// ���½�״̬���ó�����״̬
				m_PlayerList[index]->SetState(PLAYERSTATE_NORAML);
			}
	}
	m_playersLock.Release();

	// ���÷���״̬
	Clear();

	// ����ԭ���ù����ڴ�
	m_ScriptSystem.ReGetMemory();
}