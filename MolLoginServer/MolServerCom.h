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

	char DBServerIp[128];             // ���ݿ������IP
	int DBServerPort;                   // ���ݿ�������˿�
	char DBName[128];                 // ���ݿ�����
	char DBUserName[128];             // ���ݿ��û���
	char DBUserPassword[128];         // ���ݿ��û�����
};

#endif