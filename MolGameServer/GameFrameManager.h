#ifndef _GAME_FRAME_MANAGER_H_INCLUDE_
#define _GAME_FRAME_MANAGER_H_INCLUDE_

#include "MolServerCom.h"

class Player;

class GameFrameManager : public Singleton<GameFrameManager>
{
public:
	/// 构造函数
	GameFrameManager();
	/// 析构函数
	~GameFrameManager();

	/// 用于处理接收到的网络消息
	void OnProcessNetMes(int connId,CMolMessageIn *mes);
	/// 用于处理接收网络连接消息
	void OnProcessConnectedNetMes(int connId);
	/// 用于处理用于断开网络连接消息
	void OnProcessDisconnectNetMes(int connId);

	/// 加入一个玩家到游戏房间中
	void JoinPlayerToGameRoom(Player *pPlayer,int pRoomIndex=-1,int pChairIndex=-1);
	/// 准备开始游戏
	void PlayerReadyStartGame(Player *pPlayer);

private:
	/// 先处理游戏框架消息
	void OnProcessFrameMes(int connId,CMolMessageIn *mes);
	/// 处理用户登录系统消息
	void OnProcessUserLoginMes(int connId,CMolMessageIn *mes);
	/// 处理心跳消息
	void OnProcessHeartJitter(int connId);
	/// 处理获取玩家信息消息
	void OnProcessGetUserInfoMes(int connId,CMolMessageIn *mes);
	/// 处理玩家准备开始游戏
	void OnProcessGameReadyMes(int connId,CMolMessageIn *mes);
};

#define ServerGameFrameManager GameFrameManager::getSingleton()

#endif
