#include "stdafx.h"

#include "NormalRoom.h"

#include "MolServerCom.h"

/**
 * 构造函数
 *
 * @param type 房间类型
 */
NormalRoom::NormalRoom(RoomType type)
	: Room(type)
{

}

/**
 * 析构函数
 */
NormalRoom::~NormalRoom()
{

}

/**
 * 游戏房间更新
 *
 * @param time 当前系统时间
 */
void NormalRoom::Update(DWORD time)
{

}

/**
 * 用于处理接收到的网络消息
 *
 * @param connId 要处理的客户端
 * @param mes 要处理的客户端发送的网络消息
 */
void NormalRoom::OnProcessNetMes(int connId,CMolMessageIn *mes)
{
	Room::OnProcessNetMes(connId,mes);
}