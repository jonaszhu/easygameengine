#ifndef _NORAML_ROOM_H_INCLUDE_
#define _NORAML_ROOM_H_INCLUDE_

#include "Room.h"

class NormalRoom : public Room
{
public:
	/// ���캯��
	NormalRoom(RoomType type=ROOMTYPE_JINBIN);
	/// ��������
	virtual ~NormalRoom();

	/// ��Ϸ�������
	virtual void Update(DWORD time);
	/// ���ڴ�����յ���������Ϣ
	virtual void OnProcessNetMes(int connId,CMolMessageIn *mes);
};

#endif
