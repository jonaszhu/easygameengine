#include "stdafx.h"

#include "MolServerCom.h"
#include "GameFrameManager.h"
#include "RoomManager.h"
#include "PlayerManager.h"
#include "ScriptSystem.h"
#include "dataprovider.h"

#include "MolServerDlg.h"
#include "DBOperator.h"

#include "defines.h"

initialiseSingleton(GameFrameManager);

/**
 * ���캯��
 */
GameFrameManager::GameFrameManager()
{

}

/**
 * ��������
 */
GameFrameManager::~GameFrameManager()
{

}

/**
 * �ȴ�����Ϸ�����Ϣ
 *
 * @param connId Ҫ����Ŀͻ���
 * @param mes Ҫ����Ŀͻ��˵���Ϣ
 */
void GameFrameManager::OnProcessFrameMes(int connId,CMolMessageIn *mes)
{
	switch(mes->readShort())
	{
	case IDD_MESSAGE_LOOKON_ENTER_ROOM:              // �Թ۽�����Ϸ����
		{
			Player *pPlayer = ServerPlayerManager.GetNewPlayer(connId);
			if(pPlayer == NULL) return;

			int pRoomIndex = mes->readShort();
			int pChairIndex = mes->readShort();

			if(pRoomIndex >= 0 && pChairIndex >= 0) 
			{
				if(ServerRoomManager.AddLookOnPlayer(pPlayer,pRoomIndex,pChairIndex))
				{
					// ��������������е��������ͨ����ҽ�����Ϸ�������Ϣ
					CMolMessageOut out(IDD_MESSAGE_FRAME);	
					out.writeShort(IDD_MESSAGE_LOOKON_ENTER_ROOM);
					out.writeShort(IDD_MESSAGE_ENTER_ROOM_SUCC);
					out.writeLong(pPlayer->GetID());
					out.writeShort(pPlayer->GetRoomId());
					out.writeShort(pPlayer->GetRoomIndex());

					ServerPlayerManager.SendMsgToEveryone(out);

					Room *pRoom = ServerRoomManager.GetRoomById(pPlayer->GetRoomId());
					if(pRoom) pRoom->OnProcessEnterRoomMsg(pPlayer->GetRoomIndex());

					return;
				}
			}

			// ��ǰ��ҷ��ͽ�����Ϸ����ʧ�ܵ���Ϣ
			CMolMessageOut out(IDD_MESSAGE_FRAME);	
			out.writeShort(IDD_MESSAGE_LOOKON_ENTER_ROOM);
			out.writeShort(IDD_MESSAGE_ENTER_ROOM_FAIL);
			out.writeShort(pPlayer->GetID());

			Send(pPlayer->GetConnectID(),out);
		}
		break;
	case IDD_MESSAGE_ENTER_ROOM:                     // ������Ϸ����
		{
			Player *pPlayer = ServerPlayerManager.GetNewPlayer(connId);
			if(pPlayer == NULL) return;

			int pRoomIndex = mes->readShort();
			int pChairIndex = mes->readShort();

			if(pRoomIndex < 0 || pRoomIndex >= 65535) pRoomIndex = -1;
			if(pChairIndex < 0 || pChairIndex >= 65535) pChairIndex = -1;

			// ����û��Ľ���Ƿ����㷿��Ҫ��
			if(pPlayer->GetMoney() <= CMolServerDlg::getSingleton().GetServerSet()->lastmoney)
			{
				CMolMessageOut out(IDD_MESSAGE_FRAME);	
				out.writeShort(IDD_MESSAGE_ENTER_ROOM);
				out.writeShort(IDD_MESSAGE_ENTER_ROOM_LASTMONEY);

				Send(pPlayer->GetConnectID(),out);
				return;
			}

			JoinPlayerToGameRoom(pPlayer,pRoomIndex,pChairIndex);
		}
		break;
	case IDD_MESSAGE_CHANGER_ROOM:                  // ������Ϸ����
		{
			ServerRoomManager.OnProcessChangeGameRoomMes(connId);
		}
		break;
	case IDD_MESSAGE_LEAVE_ROOM:                    // �뿪��Ϸ����
		{
			Player *pPlayer = ServerPlayerManager.GetPlayer(connId);
			if(pPlayer == NULL) return;

			// ���Ƚű��������û��뿪��Ϸ����
			Room *pRoom = ServerRoomManager.GetRoomById(pPlayer->GetRoomId());
			if(pRoom == NULL) return;

			// ��ǰ�������������û���������뿪������Ϣ
			CMolMessageOut out(IDD_MESSAGE_FRAME);	
			out.writeShort(IDD_MESSAGE_LEAVE_ROOM);
			out.writeLong(pPlayer->GetID());

			ServerPlayerManager.SendMsgToEveryone(out);

			// ����û������Թ��û�����ô���Ƚ�����Ϸ
			if(!pPlayer->IsLookOn())
			{
				pRoom->OnProcessLeaveRoomMsg(pPlayer->GetRoomIndex());
			}

			//// ����û������Թ��û�����ô���Ƚ�����Ϸ
			//if(!pPlayer->IsLookOn() && pRoom->GetRoomState() == ROOMSTATE_GAMING)
			//{
			//	pRoom->GameEnd();
			//}

			// �ӷ������������û�
			pRoom->ClearPlayer(pPlayer);		
		}
		break;
	case IDD_MESSAGE_GET_ONLINE_PLAYERS:             // �õ��������
		{
			ServerPlayerManager.LockPlayerList();
			//int pPlayerCount = ServerPlayerManager.GetPlayerCount()+ServerPlayerManager.GetRobotCount();

			int pPlayerCount = 0;
			std::vector<std::vector<Player*> > pPlayerList;
			std::vector<Player*> pNewPlayers;

			std::map<int,Player*>::iterator iter = ServerPlayerManager.GetPlayerList().begin();
			for(;iter != ServerPlayerManager.GetPlayerList().end();iter++)
			{
				if((*iter).second == NULL) continue;
				
				pPlayerCount+=1;
				pNewPlayers.push_back((*iter).second);

				if(pPlayerCount >= 360)
				{
					pPlayerList.push_back(pNewPlayers);
					pPlayerCount=0;
					pNewPlayers.clear();
				}
			}

			iter = ServerPlayerManager.GetRobotList().begin();
			for(;iter != ServerPlayerManager.GetRobotList().end();iter++)
			{
				if((*iter).second == NULL) continue;

				pPlayerCount+=1;
				pNewPlayers.push_back((*iter).second);

				if(pPlayerCount >= 360)
				{
					pPlayerList.push_back(pNewPlayers);
					pPlayerCount=0;
					pNewPlayers.clear();
				}
			}

			if(pPlayerCount > 0 && !pNewPlayers.empty())
				pPlayerList.push_back(pNewPlayers);

			for(int i=0;i<(int)pPlayerList.size();i++)
			{
				CMolMessageOut out(IDD_MESSAGE_FRAME);	
				out.writeShort(IDD_MESSAGE_GET_ONLINE_PLAYERS);	
				out.writeShort((int)pPlayerList[i].size());

				for(int k=0;k<(int)pPlayerList[i].size();k++)
				{
					out.writeLong(pPlayerList[i][k]->GetID());
					out.writeByte(pPlayerList[i][k]->GetState());
					out.writeByte(pPlayerList[i][k]->GetType());
					out.writeShort(pPlayerList[i][k]->GetRoomId());
					out.writeShort(pPlayerList[i][k]->GetRoomIndex());
					out.writeString(pPlayerList[i][k]->GetName());
					out.writeString(pPlayerList[i][k]->GetUserAvatar());
					out.writeShort(pPlayerList[i][k]->GetLevel());
					out.writeDouble(pPlayerList[i][k]->GetMoney());				
					out.writeLong(pPlayerList[i][k]->GetExperience());				
					out.writeShort(pPlayerList[i][k]->GetTotalBureau());
					out.writeShort(pPlayerList[i][k]->GetSuccessBureau());
					out.writeShort(pPlayerList[i][k]->GetFailBureau());
					out.writeFloat(pPlayerList[i][k]->GetSuccessRate());
					out.writeFloat(pPlayerList[i][k]->GetRunawayrate());
				}

				Send(connId,out);
			}
						
			ServerPlayerManager.UnlockPlayerList();	

			CMolMessageOut out(IDD_MESSAGE_FRAME);	
			out.writeShort(IDD_MESSAGE_GET_ONLINE_PLAYERS_END);		
			Send(connId,out);	
		}
		break;
	case IDD_MESSAGE_GET_ROOM_LIST:                  // �õ���ǰ�������з����б�
		{
			std::list<Room*> pRoomList = ServerRoomManager.GetRoomList();
			if(pRoomList.empty()) return;

			CMolMessageOut out(IDD_MESSAGE_FRAME);	
			out.writeShort(IDD_MESSAGE_GET_ROOM_LIST);

			// ����д�������з��������
			out.writeShort((int)pRoomList.size());
			out.writeLong(CMolServerDlg::getSingleton().GetServerSet()->GameId);
			out.writeByte(CMolServerDlg::getSingleton().GetServerSet()->GameType);			
			out.writeByte(CMolServerDlg::getSingleton().GetServerSet()->isQueueEnter);
			out.writeShort(CMolServerDlg::getSingleton().GetServerSet()->PlayerCount);

			ServerRoomManager.LockRoomList();
			std::list<Room*>::iterator iter = pRoomList.begin();
			for(;iter != pRoomList.end();iter++)
			{
				if((*iter) == NULL) continue;

				// ���ͷ���״̬
				out.writeByte((BYTE)(*iter)->GetRoomState());
				out.writeShort((*iter)->GetPlayerCount());

				// ��ʼ���ͷ����������Ϣ
				for(int i=0;i<(*iter)->GetMaxPlayer();i++)
				{
					Player *pPlayer = (*iter)->GetPlayer(i);
					if(pPlayer == NULL) continue;

					out.writeLong(pPlayer->GetID());
					out.writeShort(pPlayer->GetRoomId());
					out.writeShort(pPlayer->GetRoomIndex());
				}
			}
			ServerRoomManager.UnlockRoomList();

			Send(connId,out);
		}
		break;
	case IDD_MESSAGE_GET_PLAYER_MES:                  // ȡ�������Ϣ��Ϣ
		{
			OnProcessGetUserInfoMes(connId,mes);
		}		
		break;
	case IDD_MESSAGE_READY_START:                     // ���׼����ʼ��Ϸ
		{
			OnProcessGameReadyMes(connId,mes);	
		}
		break;
	case IDD_MESSAGE_REENTER_ROOM:                    // ���»ص���Ϸ
		{
			Player *pPlayer = ServerPlayerManager.GetPlayer(connId);
			if(pPlayer == NULL) return;
			
			pPlayer->SetState(PLAYERSTATE_GAMING);

			Room *pRoom = ServerRoomManager.GetRoomById(pPlayer->GetRoomId());
			if(pRoom == NULL) return;

			//int playerId = pRoom->GetPlayerIndex(pPlayer->GetConnectID());
			pRoom->OnProcessDisconnectBackNetMes(pPlayer->GetRoomIndex());
		}
		break;
	default:
		break;
	}
}

/**
 * ����������Ϣ
 *
 * @param connId Ҫ����Ŀͻ�������ID
 */
void GameFrameManager::OnProcessHeartJitter(int connId)
{
	Player *pPlayer = ServerPlayerManager.GetPlayer(connId);
	if(pPlayer == NULL) return;

	pPlayer->SetHeartCount(0);
}

/** 
 * �����ȡ�����Ϣ��Ϣ
 *
 * @param connId Ҫ����Ŀͻ��˵�����ID
 * @param mes ���յ��Ŀͻ��˵���Ϣ
 */
void GameFrameManager::OnProcessGetUserInfoMes(int connId,CMolMessageIn *mes)
{
	if(connId < 0 || mes == NULL) return;

	unsigned int userId = mes->readLong();

	Player *pPlayer = ServerPlayerManager.GetPlayerById(userId);
	if(pPlayer == NULL)
	{
		CMolMessageOut out(IDD_MESSAGE_GET_PLAYER_MES);
		out.writeShort(IDD_MESSAGE_GET_FAIL);		
		Send(connId,out);
		return;
	}

	// ���õ��������Ϣ���͹�ȥ
	CMolMessageOut out(IDD_MESSAGE_GET_PLAYER_MES);
	out.writeShort(IDD_MESSAGE_GET_SUCCESS);	
	out.writeLong(pPlayer->GetID());
	out.writeString(pPlayer->GetUserAvatar());
	out.writeShort(pPlayer->GetLevel());
	out.writeDouble(pPlayer->GetMoney());
	out.writeLong(pPlayer->GetExperience());
	out.writeShort(pPlayer->GetTotalBureau());
	out.writeShort(pPlayer->GetSuccessBureau());
	out.writeShort(pPlayer->GetFailBureau());
	out.writeFloat(pPlayer->GetSuccessRate());
	out.writeFloat(pPlayer->GetRunawayrate());

	Send(connId,out);
}

/**
 * �����û���¼ϵͳ��Ϣ
 *
 * @param connId Ҫ����Ŀͻ���
 * @param mes Ҫ����Ŀͻ��˵���Ϣ
 */
void GameFrameManager::OnProcessUserLoginMes(int connId,CMolMessageIn *mes)
{
	if(mes == NULL) return;

	CMolString pUserName = mes->readString();
	CMolString pUserPW = mes->readString();

	unsigned int pUserId = ServerDBOperator.IsExistUser(pUserName.c_str(),pUserPW.c_str());

	if(pUserId <= 0) 
	{
		CMolMessageOut out(IDD_MESSAGE_GAME_LOGIN);
		out.writeShort(IDD_MESSAGE_GAME_LOGIN_FAIL);	
		Send(connId,out);		
		return;
	}

	//��鵱ǰ�����Ƿ񳬹�ָ����������
	if(ServerPlayerManager.GetPlayerCount() >= CMolServerDlg::getSingleton().GetMaxOnlinePlayers())
	{
		CMolMessageOut out(IDD_MESSAGE_GAME_LOGIN);
		out.writeShort(IDD_MESSAGE_GAME_LOGIN_FULL);	
		Send(connId,out);		
		return;
	}

	// ���Ȳ��ҵ�ǰ����б����Ƿ��������û����������,�����û����ڵ���״̬�£��ʹ����û��ĵ�������
	Player *pPlayer = ServerPlayerManager.GetPlayerById(pUserId);
	if(pPlayer && 
		pPlayer->GetState() == PLAYERSTATE_LOSTLINE)
	{
		if(connId != pPlayer->GetConnectID())
		{
			int oldConn = pPlayer->GetConnectID();
			pPlayer->SetConnectID(connId);

			ServerPlayerManager.Reset(oldConn,pPlayer);
		}

		pPlayer->SetHeartCount(0);
	}

	// �����������������û�����ֱ����������û�������ID
	pPlayer = ServerPlayerManager.GetPlayerById(pUserId);
	if(pPlayer) 
	{
		if(pPlayer->GetState() != PLAYERSTATE_LOSTLINE)
		{
			CMolMessageOut out(IDD_MESSAGE_GAME_LOGIN);
			out.writeShort(IDD_MESSAGE_GAME_LOGIN_EXIST);	
			Send(connId,out);
			return;
		}
		else
		{
			// ����ҷ��ͳɹ���¼��������Ϣ
			CMolMessageOut out(IDD_MESSAGE_GAME_LOGIN);
			out.writeShort(IDD_MESSAGE_GAME_LOGIN_SUCESS);	
			out.writeLong(pPlayer->GetID());
			out.writeByte((BYTE)pPlayer->GetState());
			out.writeByte((BYTE)pPlayer->GetType());
			out.writeShort(pPlayer->GetRoomId());
			out.writeShort(pPlayer->GetRoomIndex());
			out.writeString(pPlayer->GetName());
			out.writeString(pPlayer->GetUserAvatar());
			out.writeShort(pPlayer->GetLevel());
			out.writeDouble(pPlayer->GetMoney());
			out.writeLong(pPlayer->GetExperience());
			out.writeShort(pPlayer->GetTotalBureau());
			out.writeShort(pPlayer->GetSuccessBureau());
			out.writeShort(pPlayer->GetFailBureau());
			out.writeFloat(pPlayer->GetSuccessRate());
			out.writeFloat(pPlayer->GetRunawayrate());			
			ServerPlayerManager.SendMsgToEveryone(out);
			return;
		}
	}
	else
	{
		UserDataStru pUserData;
		if(!ServerDBOperator.GetUserData(pUserId,pUserData)) 
		{
			CMolMessageOut out(IDD_MESSAGE_GAME_LOGIN);
			out.writeShort(IDD_MESSAGE_GAME_LOGIN_FAIL);	
			Send(connId,out);
			return;
		}

		Player *pPlayer = new Player(pUserId,connId);
		pPlayer->SetName(pUserName.c_str());
		pPlayer->SetMoney(pUserData.Money);
		pPlayer->SetLevel(pUserData.Level);
		pPlayer->SetExperience(pUserData.Experience);
		pPlayer->SetUserAvatar(pUserData.UserAvatar);
		pPlayer->SetTotalBureau(pUserData.TotalBureau);
		pPlayer->SetSuccessBureau(pUserData.SBureau);
		pPlayer->SetFailBureau(pUserData.FailBureau);
		pPlayer->SetSuccessRate(pUserData.SuccessRate);
		pPlayer->SetRunawayrate(pUserData.RunawayRate);

		// �����¼�ɹ�������Ҽ��뵽��������
		ServerPlayerManager.AddPlayer(pPlayer);

		// ����ҷ��ͳɹ���¼��������Ϣ
		CMolMessageOut out(IDD_MESSAGE_GAME_LOGIN);
		out.writeShort(IDD_MESSAGE_GAME_LOGIN_SUCESS);	
		out.writeLong(pPlayer->GetID());
		out.writeByte((BYTE)pPlayer->GetState());
		out.writeByte((BYTE)pPlayer->GetType());
		out.writeShort(pPlayer->GetRoomId());
		out.writeShort(pPlayer->GetRoomIndex());
		out.writeString(pPlayer->GetName());
		out.writeString(pPlayer->GetUserAvatar());
		out.writeShort(pPlayer->GetLevel());
		out.writeDouble(pPlayer->GetMoney());
		out.writeLong(pPlayer->GetExperience());
		out.writeShort(pPlayer->GetTotalBureau());
		out.writeShort(pPlayer->GetSuccessBureau());
		out.writeShort(pPlayer->GetFailBureau());
		out.writeFloat(pPlayer->GetSuccessRate());
		out.writeFloat(pPlayer->GetRunawayrate());			
		ServerPlayerManager.SendMsgToEveryone(out);
	}
}

/**
 * ���ڴ�����յ���������Ϣ
 *
 * @param connId Ҫ����Ŀͻ��˵�����ID
 * @param mes ���յ��Ŀͻ��˵���Ϣ
 */
void GameFrameManager::OnProcessNetMes(int connId,CMolMessageIn *mes)
{
	if(mes == NULL) return;

	switch(mes->getId())
	{
	case IDD_MESSAGE_FRAME:                  // �����Ϣ
		{
			OnProcessFrameMes(connId,mes);
		}
		break;
	case IDD_MESSAGE_HEART_JITTER:           // ������Ϣ
		{
			OnProcessHeartJitter(connId);
		}
		break;
	case IDD_MESSAGE_GAME_LOGIN:             // �û���¼
		{
			OnProcessUserLoginMes(connId,mes);
		}
		break;
	case IDD_MESSAGE_ROOM:              // ������Ϣ
		{
			ServerRoomManager.OnProcessNetMes(connId,mes);
		}
		break;
	default:
		break;
	}
}

/**
 * ���ڴ����������������Ϣ
 *
 * @param connId Ҫ����Ŀͻ��˵�����ID
 */
void GameFrameManager::OnProcessConnectedNetMes(int connId)
{
	// �����������������û�����ֱ����������û�������ID
	Player *pPlayer = ServerPlayerManager.GetPlayer(connId);
	if(pPlayer) 
	{
		pPlayer->SetHeartCount(0);
	}

	CMolMessageOut out(IDD_MESSAGE_CONNECT);
	out.writeShort(IDD_MESSAGE_CONNECT_SUCESS);

	Send(connId,out);
}

/**
 * ���ڴ������ڶϿ�����������Ϣ
 *
 * @param connId Ҫ����Ŀͻ��˵�����ID
 */
void GameFrameManager::OnProcessDisconnectNetMes(int connId)
{
	ServerRoomManager.OnProcessDisconnectNetMes(connId);

	Player *pPlayer = ServerPlayerManager.GetPlayer(connId);
	if(pPlayer != NULL) 
		pPlayer->SetHeartCount(0);

	//// �����ǰ�û�û�д��ڵ���״���£���ֱ�ӹر�����ͻ���
	//if(pPlayer->GetRoomId() == -1)
	//{
	//	ServerPlayerManager.ClearPlayer(pPlayer);
	//}
}

/** 
 * ����һ����ҵ���Ϸ������
 *
 * @param pPlayer Ҫ��������
 * @param pRoomIndex ����ڷ����е�����
 * @param pChairIndex ����ڷ����е���������
 */
void GameFrameManager::JoinPlayerToGameRoom(Player *pPlayer,int pRoomIndex,int pChairIndex)
{
	if(pPlayer == NULL) return;

	if(ServerRoomManager.AddPlayer(pPlayer,pRoomIndex,pChairIndex))
	{
		// ��������������е��������ͨ����ҽ�����Ϸ�������Ϣ
		CMolMessageOut out(IDD_MESSAGE_FRAME);	
		out.writeShort(IDD_MESSAGE_ENTER_ROOM);
		out.writeShort(IDD_MESSAGE_ENTER_ROOM_SUCC);
		out.writeLong(pPlayer->GetID());
		out.writeShort(pPlayer->GetRoomId());
		out.writeShort(pPlayer->GetRoomIndex());

		ServerPlayerManager.SendMsgToEveryone(out);

		//Room *pRoom = ServerRoomManager.GetRoomById(pPlayer->GetRoomId());
		//int playerId = pRoom->GetPlayerIndex(pPlayer->GetConnectID());

		//pRoom->OnProcessEnterRoomMsg(playerId);
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
}

/** 
 * �������׼����ʼ��Ϸ
 *
 *
 * @param connId Ҫ����Ŀͻ���
 * @param mes Ҫ����Ŀͻ��˵���Ϣ
 */
void GameFrameManager::OnProcessGameReadyMes(int connId,CMolMessageIn *mes)
{
	Player *pPlayer = ServerPlayerManager.GetPlayer(connId);
	if(pPlayer == NULL) return;

	PlayerReadyStartGame(pPlayer);
}

/** 
 * ׼����ʼ��Ϸ
 *
 * @param pPlayer Ҫ׼����ʼ��Ϸ�����
 */
void GameFrameManager::PlayerReadyStartGame(Player *pPlayer)
{
	if(pPlayer == NULL) return;

	Room *pRoom = ServerRoomManager.GetRoomById(pPlayer->GetRoomId());
	if(pRoom == NULL) return;

	// ������䴦����Ϸ��״̬�¾Ͳ���׼���ɹ�
	if(pRoom->GetRoomState() == ROOMSTATE_GAMING) return;

	// �����״̬���ó�׼��״̬
	pPlayer->SetState(PLAYERSTATE_READY);

	// ���÷��䷿���������������Ϊ1�Ļ���
	//if(pRoom->GetPlayerCount() <= 1)
	//{
		pRoom->SetMaster(pPlayer->GetRoomIndex());	
	//}

	// ������������ҹ㲥�������Ѿ�׼������
	CMolMessageOut out(IDD_MESSAGE_FRAME);	
	out.writeShort(IDD_MESSAGE_READY_START);
	out.writeLong(pPlayer->GetID());
	ServerPlayerManager.SendMsgToEveryone(out);

	// ���÷����߼�
	pRoom->OnProcessPlayerReadyMes(pPlayer->GetRoomIndex());
}