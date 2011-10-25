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
	bool isQueueEnter;                  // 是否排队进入游戏

	char CenterServerIp[128];           // 中心服务器IP
	int CenterServerPort;               // 中心服务器端口

	bool isStartDebug;                  // 是否启动调试服务器
	char DebugServerIP[128];            // 调试服务器IP
	int DebugServerPort;                // 调试服务器端口
	char DebugServerPW[256];            // 进入调试服务器密码

	int GameId;                         // 游戏ID
	char GameName[128];                 // 游戏名称
	BYTE GameType;                      // 游戏类型
	int PlayerCount;                    // 玩家人数
	int TableCount;                     // 桌子数量
	float Revenue;                      // 税收
	int lastmoney;                      // 最小金币值
	char ScriptPath[256];               // 调试脚步路径

	int robotCount;                     // 启动机器人数量
	bool isStartRobot;                  // 是否开启机器人
	int robotStartID;                   // 机器人开始ID
	char RobotConfigPath[256];          // 机器人配置文件路径

	char DBServerIp[128];             // 数据库服务器IP
	int DBServerPort;                   // 数据库服务器端口
	char DBName[128];                 // 数据库名称
	char DBUserName[128];             // 数据库用户名
	char DBUserPassword[128];         // 数据库用户密码
};

#endif