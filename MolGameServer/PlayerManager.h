#ifndef _PLAYER_MANAGER_H_INCLUDE_
#define _PLAYER_MANAGER_H_INCLUDE_

#include "MolServerCom.h"

#include "Player.h"

#include <map>

class PlayerManager : public Singleton<PlayerManager>
{
public:
	PlayerManager();
	~PlayerManager();

	/// ������е����
	void ClearAllPlayers(void);
	/// ���һ����ҵ�ϵͳ��
	void AddPlayer(Player *pPlayer);
	/// ���һ�������˵�ϵͳ��
	void AddRobot(Player *pPlayer);
	/// ������ҵ�����ID�������
	void Reset(int oldConn,Player *pPlayer);
	/// �õ����еĻ�����
	Player* GetFreeRobot(void);
	/// ��ϵͳ��ɾ��ָ�������
	void ClearPlayer(Player *pPlayer);
	/// ��ϵͳ��ɾ��ָ������ID�����
	void ClearPlayerByconnId(int connId);
	/// ͨ���ͻ�������ID�õ��ͻ���
	Player* GetPlayer(int connId);
	/// ͨ���ͻ�������ID�õ��յ�½�Ŀͻ���
	Player* GetNewPlayer(int connId);
	/// ͨ�����ID�õ��ͻ���
	Player* GetPlayerById(int id);
	/// �õ���ǰϵͳ��Ҹ���
	inline int GetPlayerCount(void) { return (int)m_PlayerList.size(); } 
	/// �õ���ǰϵͳ�����˸���
	inline int GetRobotCount(void) { return (int)m_RobotList.size(); }
	/// �õ���ǰϵͳ�ܵ��������
	inline int GetTotalCount(void) { return GetPlayerCount() + GetRobotCount(); }
	/// ������ǰ���
	inline void LockPlayerList(void) { m_PlayersLock.Acquire(); }
	/// ������ǰ���
	inline void UnlockPlayerList(void) { m_PlayersLock.Release(); }
	/// �õ���������б�
	inline std::map<int,Player*>& GetPlayerList(void) { return m_PlayerList; }
	/// �õ����߻������б�
	inline std::map<int,Player*>& GetRobotList(void) { return m_RobotList; }

	/// ������Ϣ����ǰ���ߵ��������
	void SendMsgToEveryone(CMolMessageOut &msg);
	/// ������Ϣ������ָ����ҵ������������
	void SendMsgToOtherPlayer(int connId,CMolMessageOut &msg);
	/// ���͸��������������
	void SendAllPlayersHeartJitter(void);
	/// ����ά����ǰ���е����
	void OnProcessAllPlayersHeart(void);

private:
	std::map<int,Player*> m_PlayerList;                 /**< ����б� */
	std::map<int,Player*> m_RobotList;                  /**< �������б� */
	Mutex m_PlayersLock;                                /**< ������ǰ������� */
};

#define ServerPlayerManager PlayerManager::getSingleton()

#endif
