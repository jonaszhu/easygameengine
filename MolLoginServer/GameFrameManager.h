#ifndef _GAME_FRAME_MANAGER_H_INCLUDE_
#define _GAME_FRAME_MANAGER_H_INCLUDE_

#include "MolServerCom.h"

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

private:
	/// �����û���¼ϵͳ��Ϣ
	void OnProcessUserLoginMes(int connId,CMolMessageIn *mes);
	/// ������Ϸ������ע����Ϣ
	void OnProcessGameServerRegisterMes(int connId,CMolMessageIn *mes);
	/// ������Ϸ��������������
	void OnProcessUpdateGameServerPlayerCountMes(int connId,CMolMessageIn *mes);
	/// ����õ���Ϸ�������б���Ϣ
	void OnProcessGetGameServersMes(int connId,CMolMessageIn *mes);
};

#define ServerGameFrameManager GameFrameManager::getSingleton()

#endif
