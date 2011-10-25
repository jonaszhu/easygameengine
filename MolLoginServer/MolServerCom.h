#ifndef _MOL_SERVER_COMMON_H_INCLUDE_
#define _MOL_SERVER_COMMON_H_INCLUDE_

#include "MolNet.h"

using namespace mole2d;
using namespace network;

/**
 * 服务器配置结构
 */
struct ServerSet
{
	char ServerName[128];             // 服务器名称
	char ServerIp[128];               // 服务器IP
	int ServerPort;                     // 服务器端口

	char DBServerIp[128];             // 数据库服务器IP
	int DBServerPort;                   // 数据库服务器端口
	char DBName[128];                 // 数据库名称
	char DBUserName[128];             // 数据库用户名
	char DBUserPassword[128];         // 数据库用户密码
};

#endif