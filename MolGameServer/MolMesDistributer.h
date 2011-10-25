#ifndef _MOL_MES_DISTRIBUTER_H_INCLUDE
#define _MOL_MES_DISTRIBUTER_H_INCLUDE

#include "MolServerCom.h"

/**
 * ���ڴ���������Ϣ
 */
class CMolMesDistributer : public ThreadBase
{
public:
	/// ���캯��
	CMolMesDistributer();
	/// ��������
	~CMolMesDistributer();

	bool run();

private:
	NetMessage myMes;
	//Mutex m_MesLock;
};

/**
 * ����ά����ǰ�����������е����
 */
class CMolGameServerPlayersUpdate : public ThreadBase
{
public:
	/// ���캯��
	CMolGameServerPlayersUpdate();
	/// ��������
	~CMolGameServerPlayersUpdate();

	bool run();

private:
	Mutex m_RoomPlayersLock;       
	DWORD m_curTimer;
};

/**
 * ������Ϸ�з������
 */
class CMolGameRoomUpdate : public ThreadBase
{
public:
	/// ���캯��
	CMolGameRoomUpdate();
	/// ��������
	~CMolGameRoomUpdate();

	bool run();

private:
	Mutex m_RoomLock;                
};
#endif
