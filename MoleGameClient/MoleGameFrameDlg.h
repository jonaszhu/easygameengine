#ifndef _MOLE2D_GAME_FRAME_DLG_H_INCLUDE_
#define _MOLE2D_GAME_FRAME_DLG_H_INCLUDE_

#include "Mole2d.h"

// CMole2dGameClientDlg 对话框
class CMole2dGameFrameDlg : public CMolBaseFrame
{
	// 构造
public:
	CMole2dGameFrameDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CMole2dGameFrameDlg();

	/// 连接登录服务器
	void ConnectLoginServer(std::string name,std::string pw);
	/// 连接游戏服务器
	void ConnectGameServer(std::string serverip,int serverport);
	/// 重置所有的数据
	void Reset(void);
	/// 得到玩家的数据
	Player* GetMySelf(void);

	/// 处理接收到网络消息
	virtual void OnProcessNetMessage(ConnectState state,CMolMessageIn &msg);
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event);

private:
	/// 用于处理接收到的网络消息
	void OnProcessNetMes(CMolMessageIn &mes);
	/// 处理用户登录系统消息
	void OnProcessUserLoginMes(CMolMessageIn &mes);
	/// 处理用户登录中心服务器消息
	void OnProcessUserCenterMes(CMolMessageIn &mes);
	/// 处理心跳消息
	void OnProcessHeartJitter();
	/// 先处理游戏框架消息
	void OnProcessFrameMes(CMolMessageIn &mes);
	/// 处理游戏房间消息
	void OnProcessGameRoomMes(CMolMessageIn &mes);
	/// 处理更新用户信息
	void OnProcessUpdateUserInfoMes(CMolMessageIn &mes);

	/// 关闭游戏窗口
	bool CloseMyGameFrame(void);

private:
	std::string m_loginName,m_loginPW;
	int m_curGameID,m_revPlayerCount;
	int m_totalOnlinePlayers;

protected:
	afx_msg void OnClose();
	/// 游戏对话框消息
	LRESULT OnGameFrameMessage(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()
};

#endif
