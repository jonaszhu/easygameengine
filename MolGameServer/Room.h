#ifndef _ROOM_H_INCLUDE_
#define _ROOM_H_INCLUDE_

#include "MolServerCom.h"
#include "Player.h"

#include <vector>
#include <string>
#include <map>

#include "ScriptSystem.h"

// ��󷿼�����
#define ROOM_MAX_PLAYERS  500

/**
 * ��������
 */
enum RoomType
{
	ROOMTYPE_JINBIN = 0,             // ��ҷ���
	ROOMTYPE_JIFEN,                  // ���ַ���
	ROOMTYPE_BISAI,                  // ��������
	ROOMTYPE_LIANXI,                 // ��ϰ����
	ROOMTYPE_NULL
};

/**
 * ���䵱ǰ״̬
 */
enum RoomState
{
	ROOMSTATE_WAITING = 0,             // �ȴ���
	ROOMSTATE_GAMING,                  // ��Ϸ��
	ROOMSTATE_NULL
};

/** 
 * �������õ��Ķ�ʱ���ṹ
 */
struct RoomTimer
{
	RoomTimer():TimerId(0),TimerSpace(0),curTime(0),m_isEnable(false) {}
	RoomTimer(long ti,int ts):TimerId(ti),TimerSpace(ts),curTime(ts),m_isEnable(true) {}

	long TimerId;                      // ʱ��ID
	int TimerSpace;                    // ʱ����
	int curTime;                       // ��ǰʱ��
	bool m_isEnable;                   // �Ƿ����
};

class Room
{
public:
	Room(RoomType type=ROOMTYPE_NULL);
	virtual ~Room();

	/// ���µ��벢ִ�нű�
	void ReLoadAndRunScript(void);
	/// ���÷���ID
	inline void SetID(int id) { m_Id = id; }
	/// �õ�����ID
	inline int GetID(void) { return m_Id; }
	/// ���÷�������
	inline void SetRoomType(RoomType type) { m_RoomType = type; }
	/// �õ���������
	inline RoomType GetRoomType(void) { return m_RoomType; }
	/// ���÷����������
	inline void SetMaxPlayer(int max) 
	{ 
		if(max > ROOM_MAX_PLAYERS)
			m_MaxCount = ROOM_MAX_PLAYERS;
		else
			m_MaxCount = max; 
	}
	/// �õ������������
	inline int GetMaxPlayer(void) { return m_MaxCount; }
	/// ���÷���״̬
	inline void SetRoomState(RoomState state) { m_RoomState = state; }
	/// �õ�����״̬
	inline RoomState GetRoomState(void) { return m_RoomState; }
	/// ���÷�������
	inline void SetName(std::string name) { m_Name = name; }
	/// �õ���������
	inline std::string GetName(void) { return m_Name; }
	/// ������Ϸ��ˮֵ
	inline void SetChouShui(float cs) { m_RoomRevenue = cs; }
	/// �õ���Ϸ��ˮֵ
	inline float GetChouShui(void) { return m_RoomRevenue; }
	/// ������Ϸ��Ҫ�����ٽ��
	inline void SetLastMoney(unsigned int money) { m_RoomLastMoney = money; }
	/// �õ���Ϸ��Ҫ�����ٽ��
	inline unsigned int GetLastMoney(void) { return m_RoomLastMoney; }
	/// ��ǰ�����Ƿ�Ϊ��
	bool IsEmpty(void);
	/// �õ�ָ�����������
	Player* GetPlayer(int index);
	/// �õ���ǰ��������
	int GetPlayerCount(void);
	/// �õ�׼����״̬����ҵ�����
	int GetReadyPlayerCount(void);
	/// ���õ�ǰ����ķ���
	void SetMaster(int playerId);
	/// �õ���ǰ����ķ���������Ϊ��ǰ��һ׼����ʼ��Ϸ�����
	inline int GetMaster(void) { return m_masterId; }
	/// �õ������е�ǰ�����
	inline int GetCurrentPlayer(void) { return m_curPlayerId; }
	/// �����û�����ID�õ��û��ڷ����е�ID
	int GetPlayerRoomId(int connId);
	/// �õ���ǰ����ָ��״̬����Ҹ���
	int GetPlayerCount(PlayerState state);
	/// ���õ�ǰ����������ҵ�״̬
	void SetAllPlayerState(PlayerState state);
	/// ����ָ����ҵ�״̬
	void SetPlayerState(int index,PlayerState state);
	/// ���÷����е�ǰ���
	inline void SetCurrentPlayer(int playerId) { m_curPlayerId = playerId; }
	/// �õ���ǰ��������һ�����
	int GetCurNextPlayer(void);
	/// �õ���ǰ��������һ���������
	int GetCurNextWorkPlayer(void);

	/// ������������е����
	void ClearAllPlayers(void);
	/// ���һ����ҵ���ǰ������
	int AddPlayer(Player *pPlayer,int index=-1);
	/// ���һ���Թ���ҵ���ǰ������
	int AddLookOnPlayer(Player *pPlayer,int index);
	/// �ӵ�ǰ���������ָ�������
	void ClearPlayer(Player *pPlayer);
	/// �ӵ�ǰ������ɾ��ָ�������
	void DeletePlayer(Player *pPlayer);
	/// �ӵ�ǰ���������ָ������ID�����
	void ClearPlayerById(int Id);
	/// ���ָ������Ƿ���ڵ�ǰ����
	bool IsExist(Player *pPlayer);
	/// ���ָ�����Թ�����Ƿ���ڵ�ǰ������
	bool IsExistLookOn(Player *pPlayer);
	/// ��ⷿ���Ƿ��Ѿ���Ա
	bool IsFull(void);
	/// ��ⷿ���Ƿ�ȫ��׼�����
	bool IsReadyed(void);
	/// �����������id�õ�����ڵ�ǰ�����е�����
	int GetPlayerIndex(int connId);
	/// �õ���ǰ�����е����������
	inline int GetLostPlayerCount(void) { return (int)m_lostPlayerList.size(); }
	/// �����������б������
	void ClearLostPlayerById(int id);
	/// ��յ�ǰ��������
	void Clear(void);
	/// ����ָ����ҵ�����
	void UpdateUserScore(int ChairID);
	/// ��Ϸ����ʱ����
	void GameEnd(void);
	/// ��Ϸ��ʼ�ǵ���
	void GameStart(void);

	/// ��ǰ����������ҷ����û��뿪��������Ϣ
	void AllPlayerLeveaServer(void);
	
	/// ��ָ������ҷ�������
	void SendTableMsg(int index,CMolMessageOut &msg);
	/// ��ָ������ҷ����Թ�����
	void SendLookOnMes(int index,CMolMessageOut &msg);
	/// ��������ҷ�������
	void SendAllPlayerMsg(CMolMessageOut &msg);
	///// �����ָ����ҵ�������ҷ�������
	//void SendOtherPlayerMsg(int index,CMolMessageOut &msg);

	/// ��ӡ������Ϣ
	void PrintDebugInfo(const char* info);
	/// ��ʼһ����ʱ��
	bool StartTimer(int timerId,int space);
	/// �ر�һ����ʱ��
	void StopTimer(int id);
	/// �ر����еĶ�ʱ��
	void StopAllTimer(void);

	/// ��Ϸ�������
	virtual void Update(DWORD time);
	/// ���ڴ�����յ���������Ϣ
	virtual void OnProcessNetMes(int connId,CMolMessageIn *mes);
	/// ���·��������еĵ�ǰ�û�--����������ڷ�ֹ�û�ͻȻ�뿪����
	void UpdateOnlinePlayers(void);
	///// ���·��������е��û�--����������ڷ�ֹһЩ�û��Ѿ����ߣ���û���뿪����
	//void UpdateAllPlayers(void);

	/// ���ڴ����û�׼�������Ϣ
	void OnProcessPlayerReadyMes(int playerId);
	///// ���ڴ����û���ʼ��Ϸ�����Ϣ
	//void OnProcessPlayerGamingMes(int playerId,CMolMessageIn *mes);
	/// ���ڴ����û�������Ϸ��������Ϣ
	void OnProcessPlayerRoomMes(int playerId,CMolMessageIn *mes);
	/// �����û����뷿����Ϣ
	void OnProcessEnterRoomMsg(int playerId);
	/// �����û��뿪������Ϣ
	void OnProcessLeaveRoomMsg(int playerId);
	/// �����û��Ͽ�������Ϣ
	void OnProcessDisconnectNetMes(int playerId);
	/// �����û�����������Ϣ
	void OnProcessDisconnectBackNetMes(int playerId);
	/// �����û���ʱ����Ϣ
	void OnProcessTimerMsg();

private:
	/// �������Թ���ҷ�������
	void SendAllLookOnPlayerMsg(CMolMessageOut &msg);
	/// ���ָ���������Ƿ��ڵ�������б���
	bool IsExistLostPlayer(int index);
	static void CALLBACK MyTimeProc(void*, BOOLEAN);  

private:
	int m_Id;                   /**< ����ID */
	std::string m_Name;         /**< �������� */
	int m_MaxCount;             /**< �����������Ҹ��� */
	RoomType m_RoomType;        /**< �������� */
	RoomState m_RoomState;      /**< ���䵱ǰ״̬ */
	float m_RoomRevenue;        /**< ����˰�� */
	int m_RoomLastMoney;        /**< ������С��� */

	int m_masterId;             /**< ��ǰ����ID */
	int m_curPlayerId;          /**< ��ǰ���ID */

	Player *m_PlayerList[ROOM_MAX_PLAYERS];       /**< ��������Ϸ����б� */
	std::map<int,std::vector<Player*> > m_LookonPlayerList;       /**< �������Թ�����б� */
	std::vector<int> m_lostPlayerList;            /**< �����е�������б� */
	std::map<long,RoomTimer> m_timerList;                /**< �������õ��Ķ�ʱ�� */
	HANDLE hRoomTimer;

	ScriptSystem m_ScriptSystem;                  /**< �ű�ϵͳ */
	Mutex m_playersLock;                          /**< ������Ҳ��� */
	Mutex m_timerLock;                            /**< ���ڱ��������еĶ�ʱ�� */
	//Mutex m_scriptLock;                           /**< ���ڱ����ű����� */
};

#endif
