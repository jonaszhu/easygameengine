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
 * ������еķ���
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
 * ���µ��벢ִ�нű�
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
 * ���һ�����䵽�����������
 *
 * @param pRoom Ҫ��ӵķ���
 */
void RoomManager::AddRoom(Room *pRoom)
{
	if(pRoom == NULL) return;

	pRoom->SetID((int)m_RoomList.size());

	m_RoomList.push_back(pRoom);
}

/**
 * �ı�һ����ҵ���Ϸ����
 *
 * @param pPlayer Ҫ�ı���Ϸ��������
 */
bool RoomManager::ChangeGameRoom(Player *pPlayer)
{
	if(pPlayer == NULL ||
		m_RoomList.empty()) 
		return false;

	// ���ȼ����ҵ�ǰ��״̬�������Ҵ���׼�����ȴ�����Ϸ�У����ߵ�״̬ʱ˵������Ѿ��ڷ����У����ܽ����µķ���
	if(pPlayer->GetState() != PLAYERSTATE_NORAML)
		return false;

	// �õ�ԭ��������ڵķ���
	Room *pSrcRoom = GetRoomById(pPlayer->GetRoomId());
	if(pSrcRoom == NULL || pSrcRoom->GetRoomState() != ROOMSTATE_WAITING) return false;

	// �򷿼��������û������û��뿪��Ϣ
	CMolMessageOut out(IDD_MESSAGE_FRAME);
	out.writeShort(IDD_MESSAGE_LEAVE_ROOM);
	out.writeShort(pPlayer->GetID());

	ServerPlayerManager.SendMsgToEveryone(out);

	// �ȴ����û���ԭ���������뿪��Ϣ
	pSrcRoom->OnProcessLeaveRoomMsg(pPlayer->GetRoomIndex());

	// ��һ��������ǰ�������Ѿ��������������ȴ��ķ���
	bool state = false;

	m_RoomLock.Acquire();
	std::list<Room*>::iterator iter = m_RoomList.begin();
	for(;iter != m_RoomList.end();iter++)
	{
		if((*iter))
		{
			//(*iter)->UpdateAllPlayers();
			// �����Ҳ������㷿��Ҫ������ٽ��ֵ���Ͳ��ܽ��뷿��
			if((*iter)->GetLastMoney() > pPlayer->GetMoney()) continue;

			if(!(*iter)->IsFull() &&
				(*iter)->GetPlayerCount() > 0 &&
				(*iter)->GetRoomState() != ROOMSTATE_GAMING)
			{
				// ��һ����ԭ����һ���ķ���
				if(pSrcRoom->GetID() != (*iter)->GetID())
				{
					//PlayerState oldstate = pPlayer->GetState();

					// �������״̬Ϊ�ı䷿��״̬���������Է�ֹ�����������ǿ�е���
					//pPlayer->SetState(PLAYERSTATE_CHANGEROOM);

					// �ȴ�ԭ���ķ�����ɾ��������
					pSrcRoom->ClearPlayer(pPlayer);

					// ����һ�·����е��û�
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

	// �ڶ���������ǰ������û�������ķ�����߿շ���
	state = false;

	m_RoomLock.Acquire();
	iter = m_RoomList.begin();
	for(;iter != m_RoomList.end();iter++)
	{
		if((*iter))
		{
			//(*iter)->UpdateAllPlayers();
			// �����Ҳ������㷿��Ҫ������ٽ��ֵ���Ͳ��ܽ��뷿��
			if((*iter)->GetLastMoney() > pPlayer->GetMoney()) continue;

			if(!(*iter)->IsFull() &&
				(*iter)->GetRoomState() != ROOMSTATE_GAMING)
			{
				// ��һ����ԭ����һ���ķ���
				if(pSrcRoom->GetID() != (*iter)->GetID())
				{
					//PlayerState oldstate = pPlayer->GetState();

					// �������״̬Ϊ�ı䷿��״̬���������Է�ֹ�����������ǿ�е���
					//pPlayer->SetState(PLAYERSTATE_CHANGEROOM);

					// �ȴ�ԭ���ķ�����ɾ��������
					pSrcRoom->ClearPlayer(pPlayer);

					// ����һ�·����е��û�
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
 * ���һ���Թ���ҵ�������
 *
 * @param pPlayer Ҫ��ӵ����
 * @param roomIndex ���Ҫ����ķ��������
 * @param chairIndex ���Ҫ����ķ�������ӵ�����
 */
bool RoomManager::AddLookOnPlayer(Player *pPlayer,int roomIndex,int chairIndex)
{
	if(pPlayer == NULL ||
		m_RoomList.empty()) 
		return false;

	// ���ȼ����ҵ�ǰ��״̬�������Ҵ���׼�����ȴ�����Ϸ�У����ߵ�״̬ʱ˵������Ѿ��ڷ����У����ܽ����µķ���
	if(pPlayer->GetState() != PLAYERSTATE_NORAML)
		return false;

	// ���Ҫ����ָ�����䣬ָ������λ
	Room *pRoom = GetRoomById(roomIndex);
	if(pRoom == NULL) return false;

	// ��������������߷���״̬������Ϸ�еĻ����ǽ����˷����
	if(/*pRoom->IsFull() ||*/
		pRoom->GetRoomState() != ROOMSTATE_GAMING)
		return false;

	// ��ⷿ����ָ������������Ƿ���ڣ���������ǲ��ܼ��뷿���
	if(!pRoom->GetPlayer(chairIndex))
		return false;

	// ����һ�·����е��û�
	pRoom->UpdateOnlinePlayers();

	pPlayer->SetRoomId(pRoom->GetID());
	pPlayer->SetRoomIndex(pRoom->AddLookOnPlayer(pPlayer,chairIndex));
	pPlayer->SetLookOn(true);

	return true;
}

/**
 * ���һ����ҵ�������
 *
 * @param pPlayer Ҫ��ӵ����
 * @param roomIndex ���Ҫ����ķ��������
 * @param chairIndex ���Ҫ����ķ�������ӵ�����
 */
bool RoomManager::AddPlayer(Player *pPlayer,int roomIndex,int chairIndex)
{
	if(pPlayer == NULL ||
		m_RoomList.empty()) 
		return false;

	// ���ȼ����ҵ�ǰ��״̬�������Ҵ���׼�����ȴ�����Ϸ�У����ߵ�״̬ʱ˵������Ѿ��ڷ����У����ܽ����µķ���
	if(pPlayer->GetState() != PLAYERSTATE_NORAML)
		return false;

	// ���roomIndex����-1,chairIndex����-1��ʾ��ǰ��Ҳ���Ҫ�Ŷӽ��뷿��
	if(roomIndex == -1 && chairIndex == -1)
	{
		// ��һ��������ǰ�������Ѿ��������������ȴ��ķ���
		bool state = false;

		m_RoomLock.Acquire();
		std::list<Room*>::iterator iter = m_RoomList.begin();
		for(;iter != m_RoomList.end();iter++)
		{
			if((*iter))
			{
				//(*iter)->UpdateAllPlayers();
				// �����Ҳ������㷿��Ҫ������ٽ��ֵ���Ͳ��ܽ��뷿��
				if((*iter)->GetLastMoney() > pPlayer->GetMoney()) continue;
				
				// �����ǰ���ǰ��˷��䣬��ô����״̬���벻����Ϸ״̬��
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
					// ����һ�·����е��û�
					(*iter)->UpdateOnlinePlayers();

					if(pPlayer == NULL) 
					{
						state = false;
						break;
					}

					//char str[1024];
					//sprintf(str,"���%d���뷿��%d,IDΪ%d,����������:%d",pPlayer->GetConnectID(),(*iter)->GetID(),pPlayer->GetRoomIndex(),(*iter)->GetPlayerCount());
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

		// �ڶ���������ǰ������û�������ķ�����߿շ���
		state = false;

		m_RoomLock.Acquire();
		iter = m_RoomList.begin();
		for(;iter != m_RoomList.end();iter++)
		{
			if((*iter))
			{
				//(*iter)->UpdateAllPlayers();
				// �����Ҳ������㷿��Ҫ������ٽ��ֵ���Ͳ��ܽ��뷿��
				if((*iter)->GetLastMoney() > pPlayer->GetMoney()) continue;
				
				// �����ǰ���ǰ��˷��䣬��ô����״̬���벻����Ϸ״̬��
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
					// ����һ�·����е��û�
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
		// ���Ҫ����ָ�����䣬ָ������λ
		Room *pRoom = GetRoomById(roomIndex);
		if(pRoom == NULL) return false;

		// ��������������߷���״̬������Ϸ�еĻ����ǽ����˷����
		if(pRoom->IsFull() ||
			pRoom->GetRoomState() == ROOMSTATE_GAMING)
			return false;

		// ��ⷿ����ָ������������Ƿ���ڣ���������ǲ��ܼ��뷿���
		if(pRoom->GetPlayer(chairIndex))
			return false;

		// ����һ�·����е��û�
		pRoom->UpdateOnlinePlayers();

		pPlayer->SetRoomId(pRoom->GetID());
		int playerIndex = pRoom->AddPlayer(pPlayer,chairIndex);
		pPlayer->SetRoomIndex(playerIndex);		

		return true;
	}

	return true;
}

/**
 * �ӷ��������ָ�������
 *
 * @param pPlayer Ҫ��������
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
 * �ӵ�ǰ������ɾ��ָ�������
 *
 * @param pPlayer Ҫɾ�������
 *
 * @return  ����������ɹ������棬���򷵻ؼ�
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
 * ���ݷ���ID�ŵõ�����
 *
 * @param id Ҫ�õ��ķ����ID
 *
 * @return ����������ID�ܵõ�������䣬����������䣬���򷵻�NULL
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
 * ��Ϸ���з������
 *
 * @param time ϵͳ��ǰʱ��
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
 * �������е���Ϸ����
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
 * ���ڴ�����Ҹı���Ϸ����
 *
 * @param connId Ҫ������������ӵĿͻ�������ID
 */
void RoomManager::OnProcessChangeGameRoomMes(int connId)
{
	Player *pPlayer = ServerPlayerManager.GetNewPlayer(connId);
	if(pPlayer != NULL) 
	{	
		if(ChangeGameRoom(pPlayer))
		{
			// ��������������е��������ͨ����ҽ�����Ϸ�������Ϣ
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
			// ��ǰ��ҷ��ͽ�����Ϸ����ʧ�ܵ���Ϣ
			CMolMessageOut out(IDD_MESSAGE_FRAME);	
			out.writeShort(IDD_MESSAGE_ENTER_ROOM);
			out.writeShort(IDD_MESSAGE_ENTER_ROOM_FAIL);
			out.writeLong(pPlayer->GetID());

			Send(pPlayer->GetConnectID(),out);
		}		

		//// �����������ɹ��Ļ���������ҽ����·�����Ϣ
		//Room *pRoom = GetRoomById(pPlayer->GetRoomId());

		//if(pRoom)
		//{
		//	int playerId = pRoom->GetPlayerIndex(pPlayer->GetConnectID());
		//	pRoom->OnProcessEnterRoomMsg(playerId);
		//}
	}
}

/**
 * ���ڴ������ڶϿ�����������Ϣ
 *
 * @param connId Ҫ�Ͽ��������ӵĿͻ�������ID
 */
void RoomManager::OnProcessDisconnectNetMes(int connId)
{
	// ���ȸ����û�����ID�õ��û���Ȼ������û���Ϣ�õ�������Ϣ����󽻸����䴦��
	Player *pPlayer = ServerPlayerManager.GetPlayer(connId);
	if(pPlayer == NULL) return;

	Room *pRoom = GetRoomById(pPlayer->GetRoomId());
	if(pRoom == NULL) 
	{
		// ����û�û�н����κη���Ļ���ɾ��������
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

		// �򷿼�������ҹ㲥����뿪������Ϣ
		CMolMessageOut out(IDD_MESSAGE_FRAME);
		out.writeShort(IDD_MESSAGE_FALLLINE_ROOM);
		out.writeLong(pPlayer->GetID());
		
		ServerPlayerManager.SendMsgToEveryone(out);
	}
	else 
	{
		// �򷿼�������ҹ㲥����뿪��������Ϣ
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

	// �����ǰ������Ϸ��״̬�µĻ����û��Ͳ����˳�����,�����˳�����
  //  if(pRoom->GetRoomState() == ROOMSTATE_GAMING)
		//pPlayer->SetState(PLAYERSTATE_LOSTLINE);

	if(pPlayer->GetState() != PLAYERSTATE_LOSTLINE)
		pRoom->ClearPlayer(pPlayer);

	// ��������е��û�ȫ�����ߣ�����շ���״̬
	if(pRoom->GetPlayerCount(PLAYERSTATE_LOSTLINE) == pRoom->GetMaxPlayer()/* ||
		pRoom->GetLostPlayerCount() >= pRoom->GetMaxPlayer()-1*/)
	{
		pRoom->GameEnd();
		pRoom->AllPlayerLeveaServer();
	}
	//m_RoomLock.Release();
}

/**
 * ���ڴ�����յ���������Ϣ
 *
 * @param connId Ҫ����Ŀͻ���
 * @param mes Ҫ����Ŀͻ��˵���Ϣ
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