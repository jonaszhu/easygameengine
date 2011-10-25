#include "stdafx.h"

#include "MolServerCom.h"
#include "GameFrameManager.h"
#include "dataprovider.h"

#include "MolServerDlg.h"
#include "DBOperator.h"

#include "defines.h"
#include "GameServerManager.h"

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
	case IDD_MESSAGE_REGISTER_GAME:                  // ��Ϸ������ע����Ϣ
		{
			OnProcessGameServerRegisterMes(connId,mes);
		}
		break;
	case IDD_MESSAGE_UPDATE_GAME_SERVER:             // ������Ϸ��������Ϣ
		{
			OnProcessUpdateGameServerPlayerCountMes(connId,mes);
		}
		break;
	case IDD_MESSAGE_CENTER_LOGIN:                     // �û���¼
		{
			OnProcessUserLoginMes(connId,mes);
		}
		break;
	case IDD_MESSAGE_GET_GAMESERVER:                 // �õ���Ϸ�������б�
		{
			OnProcessGetGameServersMes(connId,mes);
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
	// ����Ƿ���ָ������ID����Ϸ������
	GameServerInfo *pGameServerInfo = ServerGameServerManager.GetGameServerByConnId(connId);
	if(pGameServerInfo)
	{
		CMolMessageOut out(IDD_MESSAGE_CONNECT);
		out.writeShort(IDD_MESSAGE_CONNECT_EXIST);

		Send(connId,out);
	}
	else
	{
		CMolMessageOut out(IDD_MESSAGE_CONNECT);
		out.writeShort(IDD_MESSAGE_CONNECT_SUCESS);

		Send(connId,out);
	}
}

/**
 * ���ڴ������ڶϿ�����������Ϣ
 *
 * @param connId Ҫ����Ŀͻ��˵�����ID
 */
void GameFrameManager::OnProcessDisconnectNetMes(int connId)
{
	ServerGameServerManager.DeleteGameServerByConnId(connId);
}

/** 
 * ������Ϸ��������������
 *
 * @param connId ��Ϸ������������ID
 * @param mes ���յ��ķ�������Ϣ
 */
void GameFrameManager::OnProcessUpdateGameServerPlayerCountMes(int connId,CMolMessageIn *mes)
{
	if(mes == NULL) return;

	int GameId = mes->readLong();
	int OnlinePlayerCount = mes->readLong();

	GameServerInfo *pGameServerInfo = ServerGameServerManager.GetGameServerByConnId(connId);
	if(pGameServerInfo && pGameServerInfo->GameId == GameId)
	{
		pGameServerInfo->OnlinePlayerCount = OnlinePlayerCount;
	}
}

/** 
 * ������Ϸ������ע����Ϣ
 *
 * @param connId ��Ϸ������������ID
 * @param mes ���յ��ķ�������Ϣ
 */
void GameFrameManager::OnProcessGameServerRegisterMes(int connId,CMolMessageIn *mes)
{
	if(mes == NULL) return;

	int GameId = mes->readLong();
	CMolString ServerName = mes->readString();
	CMolString ServerIp = mes->readString();
	int ServerPort = mes->readShort();
	int OnlinePlayerCount = mes->readLong();
	int lastmoney = mes->readDouble();

	int state = ServerGameServerManager.AddGameServer(GameServerInfo(connId,GameId,ServerName.c_str(),ServerIp.c_str(),ServerPort,OnlinePlayerCount,lastmoney));

	// ������ݿ����Ƿ���������䣬�������ݿ���Ҫ����ͬ���Ƶ���Ϸ�������ע��ɹ�
	if(!ServerDBOperator.IsExistGameServer(GameId,ServerName.c_str()))
		state = 2;

	CMolMessageOut out(IDD_MESSAGE_REGISTER_GAME);

	if(state == 1)               // �ɹ�
		out.writeShort(IDD_MESSAGE_REGISTER_SUCCESS);
	else if(state == 2)          // ʧ��
		out.writeShort(IDD_MESSAGE_REGISTER_FAIL);
	else if(state == 3)          // �ظ�ע��
		out.writeShort(IDD_MESSAGE_RE_REGISTER);

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
		CMolMessageOut out(IDD_MESSAGE_CENTER_LOGIN);
		out.writeShort(IDD_MESSAGE_CENTER_LOGIN_FAIL);	
		Send(connId,out);		
		return;
	}

	// �õ��û�����
	UserDataStru pUserData;
	if(!ServerDBOperator.GetUserData(pUserId,pUserData)) 
	{
		CMolMessageOut out(IDD_MESSAGE_CENTER_LOGIN);
		out.writeShort(IDD_MESSAGE_CENTER_LOGIN_FAIL);	
		Send(connId,out);
		return;
	}

	// ����ҷ��ͳɹ���¼��������Ϣ
	CMolMessageOut out(IDD_MESSAGE_CENTER_LOGIN);
	out.writeShort(IDD_MESSAGE_CENTER_LOGIN_SUCESS);	
	out.writeLong(pUserId);
	out.writeString(pUserName.c_str());
	out.writeString(pUserData.UserAvatar);
	out.writeShort(pUserData.Level);
	out.writeDouble(pUserData.Money);
	out.writeLong(pUserData.Experience);
	out.writeShort(pUserData.TotalBureau);
	out.writeShort(pUserData.SBureau);
	out.writeShort(pUserData.FailBureau);
	out.writeFloat(pUserData.SuccessRate);
	out.writeFloat(pUserData.RunawayRate);			
	
	Send(connId,out);
}

/**
 * ����õ���Ϸ�������б���Ϣ
 *
 * @param connId Ҫ����Ŀͻ���
 * @param mes Ҫ����Ŀͻ��˵���Ϣ
 */
void GameFrameManager::OnProcessGetGameServersMes(int connId,CMolMessageIn *mes)
{
	if(mes == NULL) return;

	ServerGameServerManager.LockGameServerList();

	if(ServerGameServerManager.GetGameServerInfo().empty())
	{
		ServerGameServerManager.UnlockGameServerList();

		CMolMessageOut out(IDD_MESSAGE_CENTER_LOGIN);
		out.writeShort(IDD_MESSAGE_GET_GAMESERVER);
		out.writeShort(0);
		Send(connId,out);

		return;
	}

	CMolMessageOut out(IDD_MESSAGE_CENTER_LOGIN);
	out.writeShort(IDD_MESSAGE_GET_GAMESERVER);
	out.writeShort((int)ServerGameServerManager.GetGameServerInfo().size());

	std::map<int,GameServerInfo>::iterator iter = ServerGameServerManager.GetGameServerInfo().begin();
	for(;iter != ServerGameServerManager.GetGameServerInfo().end();iter++)
	{
		out.writeLong((*iter).second.GameId);
		out.writeString((*iter).second.ServerName);
		out.writeString((*iter).second.ServerIp);
		out.writeShort((*iter).second.ServerPort);
		out.writeShort((*iter).second.OnlinePlayerCount);
		out.writeDouble((*iter).second.lastMoney);
	}

	Send(connId,out);

	ServerGameServerManager.UnlockGameServerList();
}