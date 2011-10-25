#ifndef _NORAML_ROOM_H_INCLUDE_
#define _NORAML_ROOM_H_INCLUDE_

#include "Room.h"

class NormalRoom : public Room
{
public:
	/// 构造函数
	NormalRoom(RoomType type=ROOMTYPE_JINBIN);
	/// 析构函数
	virtual ~NormalRoom();

	/// 游戏房间更新
	virtual void Update(DWORD time);
	/// 用于处理接收到的网络消息
	virtual void OnProcessNetMes(int connId,CMolMessageIn *mes);
};

#endif
