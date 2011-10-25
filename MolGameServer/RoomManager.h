#ifndef _ROOM_MANAGER_H_INCLUDE_
#define _ROOM_MANAGER_H_INCLUDE_

#include "MolServerCom.h"

#include "Room.h"
#include "Player.h"

#include <list>

class RoomManager : public Singleton<RoomManager>
{
public:
	RoomManager();
	~RoomManager();

	/// ������еķ���
	void ClearAllRooms(void);
	/// ���µ��벢ִ�нű�
	void ReLoadAndRunScript(void);

	/// ���һ�����䵽�����������
	void AddRoom(Room *pRoom);
	/// ���һ����ҵ�������
	bool AddPlayer(Player *pPlayer,int roomIndex=-1,int chairIndex=-1);
	/// ���һ���Թ���ҵ�������
	bool AddLookOnPlayer(Player *pPlayer,int roomIndex,int chairIndex);
	/// �ı�һ����ҵ���Ϸ����
	bool ChangeGameRoom(Player *pPlayer);
	/// �ӷ��������ָ�������
	void ClearPlayer(Player *pPlayer);
	/// �ӵ�ǰ������ɾ��ָ�������
	bool DeletePlayer(Player *pPlayer);
	/// �������е���Ϸ����
	void ResetAllGameRooms(void);
	/// ���ݷ���ID�ŵõ�����
	Room* GetRoomById(int id);
	/// �õ���ǰϵͳ�еķ����б�
	inline std::list<Room*>& GetRoomList(void) { return m_RoomList; }
	/// �õ���ǰϵͳ�з�������
	inline int GetRoomCount(void) { return (int)m_RoomList.size(); }
	/// ��ס��ǰ����
	inline void LockRoomList(void) { m_RoomLock.Acquire(); }
	/// ������ǰ����
	inline void UnlockRoomList(void) { m_RoomLock.Release(); }

	/// ��Ϸ���з������
	void Update(DWORD time);
	/// ���ڴ�����յ���������Ϣ
	void OnProcessNetMes(int connId,CMolMessageIn *mes);
	/// ���ڴ������ڶϿ�����������Ϣ
	void OnProcessDisconnectNetMes(int connId);
	/// ���ڴ�����Ҹı���Ϸ����
	void OnProcessChangeGameRoomMes(int connId);

private:
	std::list<Room*> m_RoomList;           /**< �����б� */    
	Mutex m_RoomLock;                      /**< ���ڱ�����ǰ�����������еķ��� */
};

#define ServerRoomManager RoomManager::getSingleton()


#endif
