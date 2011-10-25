#ifndef _GAME_FRAME_MANAGER_H_INCLUDE_
#define _GAME_FRAME_MANAGER_H_INCLUDE_

#include "MolServerCom.h"

class Player;

class GameFrameManager : public Singleton<GameFrameManager>
{
public:
	/// ���캯��
	GameFrameManager();
	/// ��������
	~GameFrameManager();

	/// ���ڴ�����յ���������Ϣ
	void OnProcessNetMes(int connId,CMolMessageIn *mes);
	/// ���ڴ����������������Ϣ
	void OnProcessConnectedNetMes(int connId);
	/// ���ڴ������ڶϿ�����������Ϣ
	void OnProcessDisconnectNetMes(int connId);

	/// ����һ����ҵ���Ϸ������
	void JoinPlayerToGameRoom(Player *pPlayer,int pRoomIndex=-1,int pChairIndex=-1);
	/// ׼����ʼ��Ϸ
	void PlayerReadyStartGame(Player *pPlayer);

private:
	/// �ȴ�����Ϸ�����Ϣ
	void OnProcessFrameMes(int connId,CMolMessageIn *mes);
	/// �����û���¼ϵͳ��Ϣ
	void OnProcessUserLoginMes(int connId,CMolMessageIn *mes);
	/// ����������Ϣ
	void OnProcessHeartJitter(int connId);
	/// �����ȡ�����Ϣ��Ϣ
	void OnProcessGetUserInfoMes(int connId,CMolMessageIn *mes);
	/// �������׼����ʼ��Ϸ
	void OnProcessGameReadyMes(int connId,CMolMessageIn *mes);
};

#define ServerGameFrameManager GameFrameManager::getSingleton()

#endif
