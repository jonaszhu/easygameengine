#include "stdafx.h"

#include "NormalRoom.h"

#include "MolServerCom.h"

/**
 * ���캯��
 *
 * @param type ��������
 */
NormalRoom::NormalRoom(RoomType type)
	: Room(type)
{

}

/**
 * ��������
 */
NormalRoom::~NormalRoom()
{

}

/**
 * ��Ϸ�������
 *
 * @param time ��ǰϵͳʱ��
 */
void NormalRoom::Update(DWORD time)
{

}

/**
 * ���ڴ�����յ���������Ϣ
 *
 * @param connId Ҫ����Ŀͻ���
 * @param mes Ҫ����Ŀͻ��˷��͵�������Ϣ
 */
void NormalRoom::OnProcessNetMes(int connId,CMolMessageIn *mes)
{
	Room::OnProcessNetMes(connId,mes);
}