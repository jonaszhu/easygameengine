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
 * 构造函数
 */
GameFrameManager::GameFrameManager()
{

}

/**
 * 析构函数
 */
GameFrameManager::~GameFrameManager()
{

}

/**
 * 先处理游戏框架消息
 *
 * @param connId 要处理的客户端
 * @param mes 要处理的客户端的消息
 */
void GameFrameManager::OnProcessFrameMes(int connId,CMolMessageIn *mes)
{
	switch(mes->readShort())
	{
	case IDD_MESSAGE_LOOKON_ENTER_ROOM:              // 旁观进入游戏房间
		{
			Player *pPlayer = ServerPlayerManager.GetNewPlayer(connId);
			if(pPlayer == NULL) return;

			int pRoomIndex = mes->readShort();
			int pChairIndex = mes->readShort();

			if(pRoomIndex >= 0 && pChairIndex >= 0) 
			{
				if(ServerRoomManager.AddLookOnPlayer(pPlayer,pRoomIndex,pChairIndex))
				{
					// 先向服务器中所有的在线玩家通告玩家进入游戏房间的消息
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

			// 向当前玩家发送进入游戏房间失败的消息
			CMolMessageOut out(IDD_MESSAGE_FRAME);	
			out.writeShort(IDD_MESSAGE_LOOKON_ENTER_ROOM);
			out.writeShort(IDD_MESSAGE_ENTER_ROOM_FAIL);
			out.writeShort(pPlayer->GetID());

			Send(pPlayer->GetConnectID(),out);
		}
		break;
	case IDD_MESSAGE_ENTER_ROOM:                     // 进入游戏房间
		{
			Player *pPlayer = ServerPlayerManager.GetNewPlayer(connId);
			if(pPlayer == NULL) return;

			int pRoomIndex = mes->readShort();
			int pChairIndex = mes->readShort();

			if(pRoomIndex < 0 || pRoomIndex >= 65535) pRoomIndex = -1;
			if(pChairIndex < 0 || pChairIndex >= 65535) pChairIndex = -1;

			// 检查用户的金币是否满足房间要求
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
	case IDD_MESSAGE_CHANGER_ROOM:                  // 交换游戏房间
		{
			ServerRoomManager.OnProcessChangeGameRoomMes(connId);
		}
		break;
	case IDD_MESSAGE_LEAVE_ROOM:                    // 离开游戏房间
		{
			Player *pPlayer = ServerPlayerManager.GetPlayer(connId);
			if(pPlayer == NULL) return;

			// 首先脚本处理了用户离开游戏房间
			Room *pRoom = ServerRoomManager.GetRoomById(pPlayer->GetRoomId());
			if(pRoom == NULL) return;

			// 向当前服务器中所有用户发送玩家离开房间消息
			CMolMessageOut out(IDD_MESSAGE_FRAME);	
			out.writeShort(IDD_MESSAGE_LEAVE_ROOM);
			out.writeLong(pPlayer->GetID());

			ServerPlayerManager.SendMsgToEveryone(out);

			// 如果用户不是旁观用户，那么就先结束游戏
			if(!pPlayer->IsLookOn())
			{
				pRoom->OnProcessLeaveRoomMsg(pPlayer->GetRoomIndex());
			}

			//// 如果用户不是旁观用户，那么就先结束游戏
			//if(!pPlayer->IsLookOn() && pRoom->GetRoomState() == ROOMSTATE_GAMING)
			//{
			//	pRoom->GameEnd();
			//}

			// 从房间中清除这个用户
			pRoom->ClearPlayer(pPlayer);		
		}
		break;
	case IDD_MESSAGE_GET_ONLINE_PLAYERS:             // 得到在线玩家
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
	case IDD_MESSAGE_GET_ROOM_LIST:                  // 得到当前服务器中房间列表
		{
			std::list<Room*> pRoomList = ServerRoomManager.GetRoomList();
			if(pRoomList.empty()) return;

			CMolMessageOut out(IDD_MESSAGE_FRAME);	
			out.writeShort(IDD_MESSAGE_GET_ROOM_LIST);

			// 首先写服务器中房间的数量
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

				// 发送房间状态
				out.writeByte((BYTE)(*iter)->GetRoomState());
				out.writeShort((*iter)->GetPlayerCount());

				// 开始发送房间中玩家信息
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
	case IDD_MESSAGE_GET_PLAYER_MES:                  // 取得玩家信息消息
		{
			OnProcessGetUserInfoMes(connId,mes);
		}		
		break;
	case IDD_MESSAGE_READY_START:                     // 玩家准备开始游戏
		{
			OnProcessGameReadyMes(connId,mes);	
		}
		break;
	case IDD_MESSAGE_REENTER_ROOM:                    // 重新回到游戏
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
 * 处理心跳消息
 *
 * @param connId 要处理的客户端连接ID
 */
void GameFrameManager::OnProcessHeartJitter(int connId)
{
	Player *pPlayer = ServerPlayerManager.GetPlayer(connId);
	if(pPlayer == NULL) return;

	pPlayer->SetHeartCount(0);
}

/** 
 * 处理获取玩家信息消息
 *
 * @param connId 要处理的客户端的网络ID
 * @param mes 接收到的客户端的消息
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

	// 将得到的玩家信息发送过去
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
 * 处理用户登录系统消息
 *
 * @param connId 要处理的客户端
 * @param mes 要处理的客户端的消息
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

	//检查当前人数是否超过指定在线人数
	if(ServerPlayerManager.GetPlayerCount() >= CMolServerDlg::getSingleton().GetMaxOnlinePlayers())
	{
		CMolMessageOut out(IDD_MESSAGE_GAME_LOGIN);
		out.writeShort(IDD_MESSAGE_GAME_LOGIN_FULL);	
		Send(connId,out);		
		return;
	}

	// 首先查找当前玩家列表中是否存在这个用户，如果存在,并且用户处于掉线状态下，就处理用户的掉线重连
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

	// 如果服务器存在这个用户，就直接设置这个用户的连接ID
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
			// 向玩家发送成功登录服务器消息
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

		// 如果登录成功，将玩家加入到服务器中
		ServerPlayerManager.AddPlayer(pPlayer);

		// 向玩家发送成功登录服务器消息
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
 * 用于处理接收到的网络消息
 *
 * @param connId 要处理的客户端的网络ID
 * @param mes 接收到的客户端的消息
 */
void GameFrameManager::OnProcessNetMes(int connId,CMolMessageIn *mes)
{
	if(mes == NULL) return;

	switch(mes->getId())
	{
	case IDD_MESSAGE_FRAME:                  // 框架消息
		{
			OnProcessFrameMes(connId,mes);
		}
		break;
	case IDD_MESSAGE_HEART_JITTER:           // 心跳消息
		{
			OnProcessHeartJitter(connId);
		}
		break;
	case IDD_MESSAGE_GAME_LOGIN:             // 用户登录
		{
			OnProcessUserLoginMes(connId,mes);
		}
		break;
	case IDD_MESSAGE_ROOM:              // 房间消息
		{
			ServerRoomManager.OnProcessNetMes(connId,mes);
		}
		break;
	default:
		break;
	}
}

/**
 * 用于处理接收网络连接消息
 *
 * @param connId 要处理的客户端的网络ID
 */
void GameFrameManager::OnProcessConnectedNetMes(int connId)
{
	// 如果服务器存在这个用户，就直接设置这个用户的连接ID
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
 * 用于处理用于断开网络连接消息
 *
 * @param connId 要处理的客户端的网络ID
 */
void GameFrameManager::OnProcessDisconnectNetMes(int connId)
{
	ServerRoomManager.OnProcessDisconnectNetMes(connId);

	Player *pPlayer = ServerPlayerManager.GetPlayer(connId);
	if(pPlayer != NULL) 
		pPlayer->SetHeartCount(0);

	//// 如果当前用户没有处于掉线状况下，就直接关闭这个客户端
	//if(pPlayer->GetRoomId() == -1)
	//{
	//	ServerPlayerManager.ClearPlayer(pPlayer);
	//}
}

/** 
 * 加入一个玩家到游戏房间中
 *
 * @param pPlayer 要加入的玩家
 * @param pRoomIndex 玩家在房间中的索引
 * @param pChairIndex 玩家在房间中的椅子索引
 */
void GameFrameManager::JoinPlayerToGameRoom(Player *pPlayer,int pRoomIndex,int pChairIndex)
{
	if(pPlayer == NULL) return;

	if(ServerRoomManager.AddPlayer(pPlayer,pRoomIndex,pChairIndex))
	{
		// 先向服务器中所有的在线玩家通告玩家进入游戏房间的消息
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
		// 向当前玩家发送进入游戏房间失败的消息
		CMolMessageOut out(IDD_MESSAGE_FRAME);	
		out.writeShort(IDD_MESSAGE_ENTER_ROOM);
		out.writeShort(IDD_MESSAGE_ENTER_ROOM_FAIL);
		out.writeLong(pPlayer->GetID());

		Send(pPlayer->GetConnectID(),out);
	}
}

/** 
 * 处理玩家准备开始游戏
 *
 *
 * @param connId 要处理的客户端
 * @param mes 要处理的客户端的消息
 */
void GameFrameManager::OnProcessGameReadyMes(int connId,CMolMessageIn *mes)
{
	Player *pPlayer = ServerPlayerManager.GetPlayer(connId);
	if(pPlayer == NULL) return;

	PlayerReadyStartGame(pPlayer);
}

/** 
 * 准备开始游戏
 *
 * @param pPlayer 要准备开始游戏的玩家
 */
void GameFrameManager::PlayerReadyStartGame(Player *pPlayer)
{
	if(pPlayer == NULL) return;

	Room *pRoom = ServerRoomManager.GetRoomById(pPlayer->GetRoomId());
	if(pRoom == NULL) return;

	// 如果房间处于游戏中状态下就不能准备成功
	if(pRoom->GetRoomState() == ROOMSTATE_GAMING) return;

	// 将玩家状态设置成准备状态
	pPlayer->SetState(PLAYERSTATE_READY);

	// 设置房间房主（如果房间人数为1的话）
	//if(pRoom->GetPlayerCount() <= 1)
	//{
		pRoom->SetMaster(pPlayer->GetRoomIndex());	
	//}

	// 向所有在线玩家广播这个玩家已经准备好了
	CMolMessageOut out(IDD_MESSAGE_FRAME);	
	out.writeShort(IDD_MESSAGE_READY_START);
	out.writeLong(pPlayer->GetID());
	ServerPlayerManager.SendMsgToEveryone(out);

	// 调用房间逻辑
	pRoom->OnProcessPlayerReadyMes(pPlayer->GetRoomIndex());
}