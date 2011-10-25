#ifndef _MOL_SERVER_COMMON_H_INCLUDE_
#define _MOL_SERVER_COMMON_H_INCLUDE_

#include "MolNet.h"

using namespace mole2d;
using namespace network;

/**
 * ���������ýṹ
 */
struct ServerSet
{
	char ServerName[128];             // ����������
	char ServerIp[128];               // ������IP
	int ServerPort;                     // �������˿�
	bool isQueueEnter;                  // �Ƿ��Ŷӽ�����Ϸ

	char CenterServerIp[128];           // ���ķ�����IP
	int CenterServerPort;               // ���ķ������˿�

	bool isStartDebug;                  // �Ƿ��������Է�����
	char DebugServerIP[128];            // ���Է�����IP
	int DebugServerPort;                // ���Է������˿�
	char DebugServerPW[256];            // ������Է���������

	int GameId;                         // ��ϷID
	char GameName[128];                 // ��Ϸ����
	BYTE GameType;                      // ��Ϸ����
	int PlayerCount;                    // �������
	int TableCount;                     // ��������
	float Revenue;                      // ˰��
	int lastmoney;                      // ��С���ֵ
	char ScriptPath[256];               // ���ԽŲ�·��

	int robotCount;                     // ��������������
	bool isStartRobot;                  // �Ƿ���������
	int robotStartID;                   // �����˿�ʼID
	char RobotConfigPath[256];          // �����������ļ�·��

	char DBServerIp[128];             // ���ݿ������IP
	int DBServerPort;                   // ���ݿ�������˿�
	char DBName[128];                 // ���ݿ�����
	char DBUserName[128];             // ���ݿ��û���
	char DBUserPassword[128];         // ���ݿ��û�����
};

#endif