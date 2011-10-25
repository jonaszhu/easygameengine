#ifndef _GAME_SERVER_MANAGER_H_INCLUDE_
#define _GAME_SERVER_MANAGER_H_INCLUDE_

#include <string>
#include <map>

#include "MolServerCom.h"

/** 
 * ���ڴ洢���е���Ϸ��������Ϣ
 */
struct GameServerInfo
{
	GameServerInfo()
		: ConnId(0),GameId(0),ServerPort(0),OnlinePlayerCount(0),lastMoney(0)
	{
	}
	GameServerInfo(int ci,int gi,std::string sn,std::string si,int sp,int opc,int money)
		: ConnId(ci),GameId(gi),ServerName(sn),ServerIp(si),ServerPort(sp),OnlinePlayerCount(opc),lastMoney(money)
	{
	}

	int ConnId;                 // ����ID
	int GameId;                 // ��ϷID
	std::string ServerName;     // ����������
	std::string ServerIp;       // ������IP
	int ServerPort;             // �������˿�
	int OnlinePlayerCount;      // ��������
	int lastMoney;                // ��Ϸ�������ٽ��ֵ
};

class GameServerManager : public Singleton<GameServerManager>
{
public:
	/// ���캯��
	GameServerManager();
	/// ��������
	~GameServerManager();

	/// ���һ����Ϸ�������������б���
	int AddGameServer(GameServerInfo pGameServerInfo);
	/// ɾ��ָ������ID�ķ������ӹ����б���
	void DeleteGameServerByConnId(int connId);
	/// ����ָ������ID�ķ���������
	void UpdateGameServerByConnId(int connId,int playerCount);
	/// �õ�ָ������ID�ķ�������Ϣ
	GameServerInfo* GetGameServerByConnId(int connId);

	/// �õ���Ϸ�������б���Ϣ
	inline std::map<int,GameServerInfo>& GetGameServerInfo(void) { return m_GameServerInfoList; }
	/// ��ס��Ϸ�������б�
	inline void LockGameServerList(void) { m_GameServerLock.Acquire(); }
	/// ������Ϸ�������б�
	inline void UnlockGameServerList(void) { m_GameServerLock.Release(); }

private:
	std::map<int,GameServerInfo> m_GameServerInfoList;      /**< ���ڱ������е���Ϸ��������Ϣ */
	Mutex m_GameServerLock;                                 /**< ���ڱ������е���Ϸ������ */
};

#define ServerGameServerManager GameServerManager::getSingleton()

#endif