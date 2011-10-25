// Mole2dGameClientDlg.cpp : 实现文件
//

#include "stdafx.h"

#include "Mole2dClientCommon.h"
#include "defines.h"
#include "MoleGameFrameDlg.h"

#include "Mole2dGameClientDlg.h"

// CMole2dGameClientDlg 对话框

BEGIN_MESSAGE_MAP(CMole2dGameFrameDlg, CMolBaseFrame)
	ON_WM_CLOSE()
	ON_MESSAGE(IDD_GAMEFRAM_MESSAGEBOX,OnGameFrameMessage)
END_MESSAGE_MAP()

CMole2dGameFrameDlg::CMole2dGameFrameDlg(CWnd* pParent /*=NULL*/)
: CMolBaseFrame(pParent),m_curGameID(0),m_revPlayerCount(0),m_totalOnlinePlayers(0)
{

}

CMole2dGameFrameDlg::~CMole2dGameFrameDlg()
{

}

/** 
 * 重置所有的数据
 */
void CMole2dGameFrameDlg::Reset(void)
{
	m_curGameID = -1;

	CMolGUIRoomList *pGameList = GetRoomList();
	if(pGameList != NULL) 
	{
		Player *mySelfPlayer = pGameList->IsExistPlayer(pGameList->GetMySelfID());
		if(mySelfPlayer) 
			CMole2dGameClientDlg::getSingleton().SetMySelfInfo(mySelfPlayer);

		pGameList->Clear();
	}
}

void CMole2dGameFrameDlg::OnClose()
{
	if(!CloseMyGameFrame()) return;
	//else
	//{
	//	EnableWindow(FALSE);
	//	pSwitchUserDlg.ShowWindow(SW_SHOW);
	//}

	Reset();
	ShowWindow(SW_HIDE);
	CloseConnect();
	CMole2dGameClientDlg::getSingleton().RefreshMyselfInfo();
	CMole2dGameClientDlg::getSingleton().ShowMainFrame();

	//CMolBaseFrame::OnClose();
}

/** 
 * 连接游戏服务器
 */
void CMole2dGameFrameDlg::ConnectLoginServer(std::string name,std::string pw)
{
	if(name.empty() || pw.empty()) return;

	m_totalOnlinePlayers=0;
	m_loginName = name;
	m_loginPW = pw;

	Ini_SetFile(IDD_CLIENT_CONFIG_FILE);

	std::string serverip = Ini_GetString("SystemSet","ServerIp","127.0.0.1");
	int serverport = Ini_GetInt("SystemSet","ServerPort",1234);

	if(!serverip.empty() && serverport > 0)
		Connect(serverip,serverport);

	AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,5,0);	
}

/** 
 * 连接游戏服务器
 */
void CMole2dGameFrameDlg::ConnectGameServer(std::string serverip,int serverport)
{
	if(!serverip.empty() && serverport > 0)
		Connect(serverip,serverport);

	AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,6,0);
}

/** 
 * 处理接收到网络消息
 *
 * @param state 要处理的网络状态
 * @param msg 如果处于连接状态，这里将是接收到的网络消息
 */
void CMole2dGameFrameDlg::OnProcessNetMessage(ConnectState state,CMolMessageIn &msg)
{
	switch(state)
	{
	case NOCONNECT:
		{
			AfxGetMainWnd()->PostMessage(IDD_SHOW_CONN_TIP,0,0);	

			UpdateState pUpdateState = CMole2dGameClientDlg::getSingleton().GetCurUpdateState();
			if(pUpdateState == UPDATESTATE_MAINFRAME)
			{
				MMessageBox("中心服务器连接失败，请检查本地网络设置。","登陆出错！",MB_OK);
				AfxGetMainWnd()->SendMessage(IDM_GAMEFRAME_MESSAGE,IDD_MESSAGE_GAME_CENTER_LOGIN_FAIL,0);	
			}
			else
			{
				MMessageBox("游戏服务器连接失败，请检查本地网络设置。","登陆出错！",MB_OK);
				AfxGetMainWnd()->SendMessage(IDM_GAMEFRAME_MESSAGE,IDD_MESSAGE_GAME_LOGIN_FAIL,0);
			}

			CloseConnect();
		}
		break;
	case CONNECTTING:
		{

		}
		break;
	case CONNECTED:
		{
			AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,0,0);

			UpdateState pUpdateState = CMole2dGameClientDlg::getSingleton().GetCurUpdateState();
			if(pUpdateState == UPDATESTATE_MAINFRAME)
			{
				// 连接成功后，开始验证用户的合法性
				CMolMessageOut out(IDD_MESSAGE_CENTER_LOGIN);
				out.writeString(m_loginName);
				out.writeString(GetStringMD5(m_loginPW));
				Send(out);
			}
			else 
			{
				// 连接成功后，开始验证用户的合法性
				CMolMessageOut out(IDD_MESSAGE_GAME_LOGIN);
				out.writeString(m_loginName);
				out.writeString(GetStringMD5(m_loginPW));
				Send(out);
			}
		}
		break;
	case MESPROCESS:
		{
			OnProcessNetMes(msg);
		}
		break;
	default:
		break;
	}
}

/** 
 * 用于处理接收到的网络消息
 *
 * @param mes 接收到要处理的网络消息
 */
void CMole2dGameFrameDlg::OnProcessNetMes(CMolMessageIn &mes)
{
	if(mes.getLength() <= 0) return;

	switch(mes.getId())
	{
	case IDD_MESSAGE_GAME_LOGIN:             // 用户登录
		{
			OnProcessUserLoginMes(mes);
		}
		break;
	case IDD_MESSAGE_CENTER_LOGIN:           // 用户登录中心服务器
		{
			OnProcessUserCenterMes(mes);
		}
		break;
	case IDD_MESSAGE_HEART_JITTER:           // 心跳消息
		{
			OnProcessHeartJitter();
		}
		break;
	case IDD_MESSAGE_FRAME:                  // 框架消息
		{
			OnProcessFrameMes(mes);
		}
		break;
	case IDD_MESSAGE_ROOM:                   // 游戏房间消息
		{
			OnProcessGameRoomMes(mes);
		}
		break;
	case IDD_MESSAGE_GET_PLAYER_MES:         // 更新用户信息
		{
			OnProcessUpdateUserInfoMes(mes);
		}
		break;
	default:
		break;
	}
}

/** 
 * 处理心跳消息
 */
void CMole2dGameFrameDlg::OnProcessHeartJitter()
{
	CMolMessageOut out(IDD_MESSAGE_HEART_JITTER);
	Send(out);
}

/** 
 * 处理用户登录中心服务器消息
 *
 * @param mes 接收到要处理的网络消息
 */
void CMole2dGameFrameDlg::OnProcessUserCenterMes(CMolMessageIn &mes)
{
	switch(mes.readShort())
	{
	case IDD_MESSAGE_CENTER_LOGIN_SUCESS:
		{
			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			//int MyPlayerId = pGameList->GetMySelfID();

			//if(MyPlayerId == -1)
			//{
				unsigned int pPlayerId = mes.readLong();

				// 首先检查服务器中是否有这个玩家
				Player *pPlayer = pGameList->IsExistPlayer(pPlayerId);
				if(pPlayer == NULL)
				{
					pPlayer = new Player(pPlayerId);
					//pPlayer->SetState((PlayerState)mes.readByte());
					//pPlayer->SetType((PlayerType)mes.readByte());
					//pPlayer->SetRoomId(mes.readShort());
					//pPlayer->SetRoomIndex(mes.readShort());
					pPlayer->SetName(mes.readString());
					pPlayer->SetUserAvatar(mes.readString());
					pPlayer->SetLevel(mes.readShort());
					pPlayer->SetMoney(mes.readDouble());
					pPlayer->SetExperience(mes.readLong());			
					pPlayer->SetTotalBureau(mes.readShort());
					pPlayer->SetSuccessBureau(mes.readShort());
					pPlayer->SetFailBureau(mes.readShort());
					pPlayer->SetSuccessRate(mes.readFloat());
					pPlayer->SetRunawayrate(mes.readFloat());

					pGameList->AddGamePlayer(pPlayer);	
				}	

				if(pGameList->GetMySelfID() == -1)
				{
					pGameList->SetMySelfID(pPlayer->GetID());

					CMole2dGameClientDlg::getSingleton().SetMySelfInfo(pPlayer);
				}

				CMole2dGameClientDlg::getSingleton().RefreshMyselfInfo();
			//}

			// 获取在线玩家列表
			CMolMessageOut out(IDD_MESSAGE_GET_GAMESERVER);
			Send(out);

			AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,4,0);			
		}
		break;
	case IDD_MESSAGE_CENTER_LOGIN_FAIL:
		{
			MMessageBox("中心服务器登陆失败，请检查您的账户和密码。","登陆出错！",MB_OK);
			AfxGetMainWnd()->SendMessage(IDM_GAMEFRAME_MESSAGE,IDD_MESSAGE_GAME_CENTER_LOGIN_FAIL,0);
			CloseConnect();
		}
		break;
	case IDD_MESSAGE_GET_GAMESERVER:
		{
			int GameServerCount = mes.readShort();

			for(int index = 0;index < GameServerCount;index++)
			{
				int GameId = mes.readLong();
				std::string ServerName = mes.readString();
				std::string ServerIp = mes.readString();
				int ServerPort = mes.readShort();
				int OnlinePlayerCount = mes.readShort();
				int lastMoney = mes.readDouble();

				CMole2dGameClientDlg::getSingleton().AddGameServer(GameServerInfo(GameId,ServerName,ServerIp,ServerPort,OnlinePlayerCount,lastMoney));
			}

			AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,0,0);

			// 登录成功后就关闭连接
			CloseConnect();

			// 如果用户选择了保存用户，就将用户名写入数据库中
			if(CMole2dGameClientDlg::getSingleton().IsRegisterPWD())
				WriteRegisterKey("MOLEUSERNAME",m_loginName);

			// 显示主窗口
			CMole2dGameClientDlg::getSingleton().ShowMainFrame();
		}
		break;
	default:
		break;
	}
}

/** 
 * 处理用户登录系统消息
 *
 * @param mes 接收到要处理的网络消息
 */
void CMole2dGameFrameDlg::OnProcessUserLoginMes(CMolMessageIn &mes)
{
	switch(mes.readShort())
	{
	case IDD_MESSAGE_GAME_LOGIN_SUCESS:
		{
			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			if(pGameList->GetMySelfID() != -1)
			{
				unsigned int pPlayerId = mes.readLong();

				// 首先检查服务器中是否有这个玩家
				Player *pPlayer = pGameList->IsExistPlayer(pPlayerId);
				if(pPlayer == NULL)
				{
					pPlayer = new Player(pPlayerId);
					pPlayer->SetState((PlayerState)mes.readByte());
					pPlayer->SetType((PlayerType)mes.readByte());
					pPlayer->SetRoomId(mes.readShort());
					pPlayer->SetRoomIndex(mes.readShort());
					pPlayer->SetName(mes.readString());
					pPlayer->SetUserAvatar(mes.readString());
					pPlayer->SetLevel(mes.readShort());
					pPlayer->SetMoney(mes.readDouble());
					pPlayer->SetExperience(mes.readLong());			
					pPlayer->SetTotalBureau(mes.readShort());
					pPlayer->SetSuccessBureau(mes.readShort());
					pPlayer->SetFailBureau(mes.readShort());
					pPlayer->SetSuccessRate(mes.readFloat());
					pPlayer->SetRunawayrate(mes.readFloat());

					pGameList->AddGamePlayer(pPlayer);	
				}	

				if(pPlayerId == pGameList->GetMySelfID())
				{
					m_revPlayerCount = 0;

					// 获取在线玩家列表
					CMolMessageOut out(IDD_MESSAGE_FRAME);
					out.writeShort(IDD_MESSAGE_GET_ONLINE_PLAYERS);
					Send(out);

					AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,1,0);
				}
			}
			else
			{
				//// 先清空原来的数据
				//pGameList->Clear();

				unsigned int pPlayerId = mes.readLong();

				// 首先检查服务器中是否有这个玩家
				Player *pPlayer = pGameList->IsExistPlayer(pPlayerId);
				if(pPlayer == NULL)
				{
					pPlayer = new Player(pPlayerId);
					pPlayer->SetState((PlayerState)mes.readByte());
					pPlayer->SetType((PlayerType)mes.readByte());
					pPlayer->SetRoomId(mes.readShort());
					pPlayer->SetRoomIndex(mes.readShort());
					pPlayer->SetName(mes.readString());
					pPlayer->SetUserAvatar(mes.readString());
					pPlayer->SetLevel(mes.readShort());
					pPlayer->SetMoney(mes.readDouble());
					pPlayer->SetExperience(mes.readLong());			
					pPlayer->SetTotalBureau(mes.readShort());
					pPlayer->SetSuccessBureau(mes.readShort());
					pPlayer->SetFailBureau(mes.readShort());
					pPlayer->SetSuccessRate(mes.readFloat());
					pPlayer->SetRunawayrate(mes.readFloat());

					if(pGameList->GetMySelfID() == -1)
					{
						pGameList->SetMySelfID(pPlayer->GetID());
					}

					pGameList->AddGamePlayer(pPlayer);	
				}	

				m_revPlayerCount = 0;

				// 获取在线玩家列表
				CMolMessageOut out(IDD_MESSAGE_FRAME);
				out.writeShort(IDD_MESSAGE_GET_ONLINE_PLAYERS);
				Send(out);

				AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,1,0);
			}
		}
		break;
	case IDD_MESSAGE_GAME_LOGIN_FAIL:
		{
			MMessageBox("游戏服务器登陆失败，请检查您的账户和密码。","登陆出错！",MB_OK);
			AfxGetMainWnd()->SendMessage(IDM_GAMEFRAME_MESSAGE,IDD_MESSAGE_GAME_LOGIN_FAIL,0);
			CloseConnect();
		}
		break;
	case IDD_MESSAGE_GAME_LOGIN_FULL:
		{
			MMessageBox("游戏服务器已满，请选择其它游戏服务器进入。","登陆出错！",MB_OK);
			AfxGetMainWnd()->SendMessage(IDM_GAMEFRAME_MESSAGE,IDD_MESSAGE_GAME_LOGIN_FULL,0);
			CloseConnect();
		}
		break;
	case IDD_MESSAGE_GAME_LOGIN_EXIST:
		{
			MMessageBox("当前您已经在游戏服务器中，不能重复登陆。","登陆出错！",MB_OK);
			AfxGetMainWnd()->SendMessage(IDM_GAMEFRAME_MESSAGE,IDD_MESSAGE_GAME_LOGIN_EXIST,0);
			CloseConnect();
		}
		break;
	default:
		break;
	}
}

/** 
 * 得到玩家的数据
 */
Player* CMole2dGameFrameDlg::GetMySelf(void)
{
	CMolGUIRoomList *pGameList = GetRoomList();
	if(pGameList == NULL) return NULL;

	Player *myselfInfo = pGameList->IsExistPlayer(pGameList->GetMySelfID());
	if(myselfInfo == NULL) return NULL;

	return myselfInfo;
}

/// 先处理游戏框架消息
void CMole2dGameFrameDlg::OnProcessFrameMes(CMolMessageIn &mes)
{
	switch(mes.readShort())
	{
	case IDD_MESSAGE_GET_ONLINE_PLAYERS:             // 得到当前在线玩家列表
		{
			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			int pPlayerCount = mes.readShort();
			m_totalOnlinePlayers+=pPlayerCount;			

			for(int index = 0;index < pPlayerCount;index++)
			{
				unsigned int pPlayerId = mes.readLong();

				// 首先检查服务器中是否有这个玩家
				Player *pPlayer = pGameList->IsExistPlayer(pPlayerId);
				if(pPlayer == NULL)
				{			
					pPlayer = new Player(pPlayerId);				
					pGameList->AddGamePlayer(pPlayer);	
				}
				
				pPlayer->SetState((PlayerState)mes.readByte());
				pPlayer->SetType((PlayerType)mes.readByte());
				pPlayer->SetRoomId(mes.readShort());
				pPlayer->SetRoomIndex(mes.readShort());
				pPlayer->SetName(mes.readString());
				pPlayer->SetUserAvatar(mes.readString());
				pPlayer->SetLevel(mes.readShort());
				pPlayer->SetMoney(mes.readDouble());
				pPlayer->SetExperience(mes.readLong());			
				pPlayer->SetTotalBureau(mes.readShort());
				pPlayer->SetSuccessBureau(mes.readShort());
				pPlayer->SetFailBureau(mes.readShort());
				pPlayer->SetSuccessRate(mes.readFloat());
				pPlayer->SetRunawayrate(mes.readFloat());
			}
		}
		break;
	case IDD_MESSAGE_GET_ONLINE_PLAYERS_END:         // 接收在线玩家结束
		{
			CMole2dGameClientDlg::getSingleton().SetCurServerOnlinePlayers(m_totalOnlinePlayers);
			m_totalOnlinePlayers = 0;
			AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,2,0);

			// 获取房间列表
			CMolMessageOut out(IDD_MESSAGE_FRAME);
			out.writeShort(IDD_MESSAGE_GET_ROOM_LIST);
			Send(out);		
		}
		break;
	case IDD_MESSAGE_GET_ROOM_LIST:                  // 得到当前服务器中房间列表
		{
			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			int roomCount = mes.readShort();
			m_curGameID = mes.readLong();	
			CMolRoomType pRoomType = (CMolRoomType)mes.readByte();
			bool m_isQueue = mes.readByte() > 0 ? true : false;
			int pRoomPlayerCount = mes.readShort();

			pGameList->SetRoomType(pRoomType);
			pGameList->SetChairCount(pRoomPlayerCount);
			
			// 如果房间数量只有一的话，只能排队进入
			if(roomCount == 1)
			{
				pGameList->SetQueueEnterRoom(true);
				
				CString imgDir;
				imgDir.Format("%s\\gameroomconfig\\bg_%d.png",GetProgressDirection().c_str(),m_curGameID);				
				pGameList->LoadOneTableImage(imgDir.GetBuffer());
			}
			else
			{
				pGameList->SetQueueEnterRoom(m_isQueue);
			}

			// 生成指定个数的房间
			pGameList->SetGameRoom(roomCount);

			for(int index=0;index<roomCount;index++)
			{
				CMolRoomState pRoomState = (CMolRoomState)mes.readByte();
				int pRoomRealPlayerCount = mes.readShort();

				CMolGUIRoom *pGameRoom = pGameList->GetGameRoomByIndex(index);
				if(pGameRoom == NULL) continue;

				pGameRoom->SetRoomState(pRoomState);

				for(int k=0;k<pRoomRealPlayerCount;k++)
				{
					unsigned int pPlayerId = mes.readLong();
					int pRoomIndex = mes.readShort();
					int pChairIndex = mes.readShort();

					pGameList->SetGamePlayerSeat(pPlayerId,pRoomIndex,pChairIndex);	
				}
			}

			AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,0,0);
			CMole2dGameClientDlg::getSingleton().ShowWindow(SW_HIDE);

			// 先显示大厅界面
			CString mainframeDir;
			mainframeDir.Format("%s\\gameroomconfig\\gameroomlistconfig.gui",GetProgressDirection().c_str());
			LoadGUIConfig(mainframeDir);
			ShowWindow(SW_RESTORE);
		
			// 如果用户处于断线状态下，那么就直接进入游戏
			Player *pPlayer = pGameList->IsExistPlayer(pGameList->GetMySelfID());
			if(pPlayer == NULL) return;
			
			if(pPlayer->GetState() == PLAYERSTATE_LOSTLINE)
			{
				pGameList->SetVisible(FALSE);
				
				// 转换到游戏脚本目录下
				CString gameDir;
				gameDir.Format("%s\\%d",GetProgressDirection().c_str(),m_curGameID);
				ChangePlayerWorkingDir(gameDir.GetBuffer());
				
				pPlayer->SetState(PLAYERSTATE_GAMING);
				
				// 向服务器请求重新回到房间
				CMolMessageOut out(IDD_MESSAGE_FRAME);
				out.writeShort(IDD_MESSAGE_REENTER_ROOM);
				Send(out);			
			}
		}
		break;
	case IDD_MESSAGE_ENTER_ROOM:                      // 进入游戏房间
		{
			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			switch(mes.readShort())
			{
			case IDD_MESSAGE_ENTER_ROOM_SUCC:
				{
					unsigned int pPlayerId = mes.readLong();
					int pRoomIndex = mes.readShort();
					int pChairIndex = mes.readShort();

					pGameList->SetGamePlayerSeat(pPlayerId,pRoomIndex,pChairIndex);						

					if(pGameList->GetMySelfID() == pPlayerId && pGameList->isVisible())
					{
						pGameList->SetVisible(FALSE);

						// 转换到游戏脚本目录下
						CString gameDir;
						gameDir.Format("%s\\%d",GetProgressDirection().c_str(),m_curGameID);
						ChangePlayerWorkingDir(gameDir.GetBuffer());
					}

					// 调用游戏脚本
					OnProcessEnterRoomMsg(GetUserChairID(pPlayerId),mes);
				}
				break;
			case IDD_MESSAGE_ENTER_ROOM_FAIL:
				{

				}
				break;
			case IDD_MESSAGE_ENTER_ROOM_LASTMONEY:
				{
					MMessageBox("当前你身上的金币不能满足房间最低要求,请重新充值！","进入房间错误",MB_OK,this);
				}
				break;
			default:
				break;
			}
		}
		break;
	case IDD_MESSAGE_LOOKON_ENTER_ROOM:             // 旁观进入游戏房间
		{
			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			switch(mes.readShort())
			{
			case IDD_MESSAGE_ENTER_ROOM_SUCC:
				{	
					unsigned int pPlayerId = mes.readLong();
					int pRoomIndex = mes.readShort();
					int pChairIndex = mes.readShort();

					// 如果是旁观用户的话，不用处理
					Player *pPlayer = pGameList->IsExistPlayer(pPlayerId);
					if(pPlayer == NULL) return;	

					pPlayer->SetLookOn(true);
					pPlayer->SetRoomId(pRoomIndex);
					pPlayer->SetRoomIndex(pChairIndex);
					//pGameList->SetGamePlayerSeat(pPlayerId,pRoomIndex,pChairIndex);	

					if(pGameList->GetMySelfID() == pPlayerId)
					{
						pGameList->SetVisible(FALSE);

						// 转换到游戏脚本目录下
						CString gameDir;
						gameDir.Format("%s\\%d",GetProgressDirection().c_str(),m_curGameID);
						ChangePlayerWorkingDir(gameDir.GetBuffer());
					}

					// 调用游戏脚本
					OnProcessEnterRoomMsg(GetUserChairID(pPlayerId),mes);
				}
				break;
			case IDD_MESSAGE_ENTER_ROOM_FAIL:
				{

				}
				break;
			default:
				break;
			}
		}
		break;
	case IDD_MESSAGE_LEAVE_ROOM:                    // 离开游戏房间
		{
			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			unsigned int pPlayerId = mes.readLong();

			Player *pPlayer = pGameList->IsExistPlayer(pPlayerId);
			if(pPlayer == NULL) return;	

			pPlayer->SetState(PLAYERSTATE_NORAML);
			pPlayer->SetRoomId(-1);
			pPlayer->SetRoomIndex(-1);

			// 如果是旁观用户的话，不用处理
			if(pPlayer->IsLookOn()) 
			{
				pPlayer->SetLookOn(false);
			}
			else
			{
				// 调用游戏脚本
				int state = GetUserChairID(pPlayerId);
				if(state != -1)
					OnProcessLeaveRoomMsg(state,mes);

				pGameList->ClearChairByPlayerID(pPlayerId);			
			}				
		}
		break;
	case IDD_MESSAGE_LEAVE_SERVER:              // 离开游戏服务器
		{
			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			unsigned int pPlayerId = mes.readLong();
			
			pGameList->ClearChairByPlayerID(pPlayerId);		
			pGameList->DeletePlayer(pPlayerId);		
		}
		break;
	case IDD_MESSAGE_REENTER_ROOM:                  // 断线后重新回到房间
		{
			unsigned int pPlayerId = mes.readLong();	

			// 断线后重回
			OnProcessDisconnectBackNetMes(GetUserChairID(pPlayerId),mes);
		}
		break;
	case IDD_MESSAGE_FALLLINE_ROOM:                 // 用户断线
		{
			unsigned int pPlayerId = mes.readLong();	

			// 断线
			OnProcessDisconnectNetMes(GetUserChairID(pPlayerId),mes);
		}
		break;
	case IDD_MESSAGE_READY_START:                   // 用户准备开始游戏
		{
			unsigned int pPlayerId = mes.readLong();

			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			Player *pPlayer = pGameList->IsExistPlayer(pPlayerId);
			if(pPlayer == NULL) return;

			pPlayer->SetState(PLAYERSTATE_READY);

			//用户准备消息
			OnProcessPlayerReadyMes(GetUserChairID(pPlayerId));
		}
		break;
	case IDD_MESSAGE_GAME_START:                    // 房间已经开始游戏
		{
			unsigned int pRoomId = mes.readLong();

			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			CMolGUIRoom *pRoom = pGameList->GetGameRoomByIndex(pRoomId);
			if(pRoom == NULL) return;

			pRoom->SetRoomState(ROOMSTATE_GAMING);
		}
		break;
	case IDD_MESSAGE_GAME_END:                      // 房间已经结束游戏
		{
			unsigned int pRoomId = mes.readLong();

			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			CMolGUIRoom *pRoom = pGameList->GetGameRoomByIndex(pRoomId);
			if(pRoom == NULL) return;

			pRoom->SetRoomState(ROOMSTATE_NORMAL);
		}
		break;
	default:
		break;
	}
}

/** 
 * 用于处理接收到的事件
 *
 * @param event 要处理的本地游戏事件
 *
 * @return 如果事件处理成功返回真，否则返回假
 */
bool CMole2dGameFrameDlg::OnProcessEvent(const CMolEvent& event)
{
	switch(event.mEventType)
	{
	case MOLET_GUI_EVENT:                               // GUI事件
		{
			switch(event.mGuiEvent.EventType)
			{
			case MOLGET_ELEMENT_SELECTED:               // 控件被选中
				{
					int eventid = event.mGuiEvent.Caller->GetID();

					if(eventid == MOLE2D_GUI_ROOM_LIST)
					{
						CMolGUIRoomList *pRooList = static_cast<CMolGUIRoomList*>(event.mGuiEvent.Caller);
						if(pRooList)
						{
							if(!pRooList->isQueueEnterRoom())
							{
								CMolGUIRoom *pRoom = pRooList->GetGameRoomSelected();
								if(pRoom == NULL) return CMolBaseFrame::OnProcessEvent(event);

								// 如果这桌还没有开始游戏，那么进入游戏桌
								if(pRoom->GetRoomState() != ROOMSTATE_GAMING &&
									pRooList->GetGameRoomChairSelected()->m_player == NULL)
								{
									Player *myselfInfo = GetMySelf();
									if(myselfInfo == NULL) return true;

									if(myselfInfo->GetMoney() < CMole2dGameClientDlg::getSingleton().GetCurrentGameServer()->lastMoney)
									{
										PostMessage(IDD_GAMEFRAM_MESSAGEBOX,3,0);
										return true;
									}

									CMolMessageOut out(IDD_MESSAGE_FRAME);
									out.writeShort(IDD_MESSAGE_ENTER_ROOM);
									out.writeShort(pRooList->GetGameRoomIndexSelected());
									out.writeShort(pRooList->GetGameChairIndexSelected());
									Send(out);
								}
								else if(pRoom->GetRoomState() == ROOMSTATE_GAMING &&
									pRooList->GetGameRoomChairSelected()->m_player != NULL)
								{
									// 旁观进入
									CMolMessageOut out(IDD_MESSAGE_FRAME);
									out.writeShort(IDD_MESSAGE_LOOKON_ENTER_ROOM);
									out.writeShort(pRooList->GetGameRoomIndexSelected());
									out.writeShort(pRooList->GetGameChairIndexSelected());
									Send(out);
								}
							}
							else
							{
								Player *myselfInfo = GetMySelf();
								if(myselfInfo == NULL) return true;

								if(myselfInfo->GetMoney() < CMole2dGameClientDlg::getSingleton().GetCurrentGameServer()->lastMoney)
								{
									PostMessage(IDD_GAMEFRAM_MESSAGEBOX,3,0);
									return true;
								}

								CMolMessageOut out(IDD_MESSAGE_FRAME);
								out.writeShort(IDD_MESSAGE_ENTER_ROOM);
								out.writeShort(-1);
								out.writeShort(-1);
								Send(out);
							}
						}
					}
				}
				break;
			case MOLGET_BUTTON_CLICKED:                 // 按钮点击事件
				{
					int eventid = event.mGuiEvent.Caller->GetID();

					if(eventid == MOLE2D_GUI_MIN_FRAME)
					{
						MinGameFrame();
					}
					else if(eventid == IDD_MAINFRAME_HOMEPAGE)
					{
						CMolGUIRoomList *pGameList = GetRoomList();
						if(pGameList == NULL) return false;

						pGameList->Home();
					}
					else if(eventid == IDD_MAINFRAME_LASTPAGE)
					{
						CMolGUIRoomList *pGameList = GetRoomList();
						if(pGameList == NULL) return false;

						pGameList->PageUp();
					}
					else if(eventid == IDD_MAINFRAME_NEXTPAGE)
					{
						CMolGUIRoomList *pGameList = GetRoomList();
						if(pGameList == NULL) return false;

						pGameList->PageDown();
					}
					else if(eventid == IDD_MAINFRAME_TAILPAGE)
					{
						CMolGUIRoomList *pGameList = GetRoomList();
						if(pGameList == NULL) return false;

						pGameList->End();
					}
					else if(eventid == IDD_MAINFRAME_AUTOJOIN)
					{
						CMolGUIRoomList *pGameList = GetRoomList();
						if(pGameList == NULL) return false;

						Player *mySelfPlayer = pGameList->IsExistPlayer(pGameList->GetMySelfID());
						if(mySelfPlayer == NULL) return false;

						pGameList->AutoJoin(mySelfPlayer->GetID());
					}
					else if(eventid == MOLE2D_GUI_CLOSE_CONTAINER)
					{
						if(CloseMyGameFrame())
						{
							Reset();
							ShowWindow(SW_HIDE);
							CloseConnect();

							CMole2dGameClientDlg::getSingleton().RefreshMyselfInfo();
							CMole2dGameClientDlg::getSingleton().ShowMainFrame();
							//EnableWindow(FALSE);
							//pSwitchUserDlg.ShowWindow(SW_SHOW);
							return false;
						}

						return true;
					}
				}
				break;

			default:
				break;
			}
		}
		break;
	default:
		break;
	}

	return CMolBaseFrame::OnProcessEvent(event);
}

/** 
 * 关闭游戏窗口
 *
 * @return 如果要真的关闭游戏窗口返回真，否则返回假
 */
bool CMole2dGameFrameDlg::CloseMyGameFrame(void)
{
	CMolGUIRoomList *pGameList = GetRoomList();
	if(pGameList == NULL) return false;

	Player *mySelfPlayer = pGameList->IsExistPlayer(pGameList->GetMySelfID());
	if(mySelfPlayer == NULL) return false;

	CMolGUIRoom *pGameRoom = pGameList->GetGameRoomByIndex(mySelfPlayer->GetRoomId());
	if(pGameRoom == NULL)
	{
		return true;
	}

	if(pGameRoom->GetRoomState() == ROOMSTATE_GAMING && !mySelfPlayer->IsLookOn())
	{
		PostMessage(IDD_GAMEFRAM_MESSAGEBOX,1,0);
	}
	else if(mySelfPlayer->IsLookOn() || pGameRoom->GetRoomState() == ROOMSTATE_NORMAL)
	{
		PostMessage(IDD_GAMEFRAM_MESSAGEBOX,2,0);
	}

	return false;
}

/** 
 * 处理游戏房间消息
 *
 * @param mes 玩家进入游戏房间后要处理的消息
 */
void CMole2dGameFrameDlg::OnProcessGameRoomMes(CMolMessageIn &mes)
{
	if(mes.getLength() <= 0) return;

	OnProcessPlayerGameRoomMsg(mes);
}

/** 
 * 处理更新用户信息
 *
 * @param mes 要处理的网络消息
 */
void CMole2dGameFrameDlg::OnProcessUpdateUserInfoMes(CMolMessageIn &mes)
{
	if(mes.getLength() <= 0) return;

	int state = mes.readShort();

	switch(state)
	{
	case IDD_MESSAGE_GET_SUCCESS:
		{	
			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			unsigned int pPlayerId = mes.readLong();

			// 首先检查服务器中是否有这个玩家
			Player *pPlayer = pGameList->IsExistPlayer(pPlayerId);
			if(pPlayer == NULL) return;

			pPlayer->SetUserAvatar(mes.readString());
			pPlayer->SetLevel(mes.readShort());
			pPlayer->SetMoney(mes.readDouble());
			pPlayer->SetExperience(mes.readLong());			
			pPlayer->SetTotalBureau(mes.readShort());
			pPlayer->SetSuccessBureau(mes.readShort());
			pPlayer->SetFailBureau(mes.readShort());
			pPlayer->SetSuccessRate(mes.readFloat());
			pPlayer->SetRunawayrate(mes.readFloat());
		}
		break;
	case IDD_MESSAGE_GET_FAIL:
		{

		}
		break;
	default:
		break;
	}
}

/// 游戏对话框消息
LRESULT CMole2dGameFrameDlg::OnGameFrameMessage(WPARAM wparam, LPARAM lparam)
{
	int type = (int)wparam;

	switch(type)
	{
	case 1:
		{
			int state = MMessageBox("当前您正在游戏中，如果强退将被扣分，您确定要退出游戏吗？","退出游戏",MB_OKCANCEL,this);
			if(state==2) return 0;

			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return false;

			DestroyScriptSystem();
			CloseAllRoomTimers();

			// 转换到大厅房间目录下
			CString gameDir;
			gameDir.Format("%s",GetProgressDirection().c_str());
			ChangePlayerWorkingDir(gameDir.GetBuffer(),false);
			LoadGUIConfig("gameroomconfig\\gameroomlistconfig.gui");

			pGameList->Reset();
			pGameList->SetVisible(TRUE);

			// 发送离开房间消息
			CMolMessageOut out(IDD_MESSAGE_FRAME);
			out.writeShort(IDD_MESSAGE_LEAVE_ROOM);
			Send(out);
		}
		break;
	case 2:
		{
			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return false;

			DestroyScriptSystem();
			CloseAllRoomTimers();

			// 转换到大厅房间目录下
			CString gameDir;
			gameDir.Format("%s",GetProgressDirection().c_str());
			ChangePlayerWorkingDir(gameDir.GetBuffer(),false);
			LoadGUIConfig("gameroomconfig\\gameroomlistconfig.gui");

			pGameList->Reset();
			pGameList->SetVisible(TRUE);

			// 发送离开房间消息
			CMolMessageOut out(IDD_MESSAGE_FRAME);
			out.writeShort(IDD_MESSAGE_LEAVE_ROOM);
			Send(out);
		}
		break;
	case 3:
		{
			MMessageBox("当前你身上的金币不能满足房间最低要求,请重新充值！","进入房间错误",MB_OK,this);
		}
		break;
	default:
		break;
	}

	return 0;
}
