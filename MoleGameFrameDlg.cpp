// Mole2dGameClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "Mole2dClientCommon.h"
#include "defines.h"
#include "MoleGameFrameDlg.h"

#include "Mole2dGameClientDlg.h"

// CMole2dGameClientDlg �Ի���

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
 * �������е�����
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
 * ������Ϸ������
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
 * ������Ϸ������
 */
void CMole2dGameFrameDlg::ConnectGameServer(std::string serverip,int serverport)
{
	if(!serverip.empty() && serverport > 0)
		Connect(serverip,serverport);

	AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,6,0);
}

/** 
 * ������յ�������Ϣ
 *
 * @param state Ҫ���������״̬
 * @param msg �����������״̬�����ｫ�ǽ��յ���������Ϣ
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
				MMessageBox("���ķ���������ʧ�ܣ����鱾���������á�","��½����",MB_OK);
				AfxGetMainWnd()->SendMessage(IDM_GAMEFRAME_MESSAGE,IDD_MESSAGE_GAME_CENTER_LOGIN_FAIL,0);	
			}
			else
			{
				MMessageBox("��Ϸ����������ʧ�ܣ����鱾���������á�","��½����",MB_OK);
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
				// ���ӳɹ��󣬿�ʼ��֤�û��ĺϷ���
				CMolMessageOut out(IDD_MESSAGE_CENTER_LOGIN);
				out.writeString(m_loginName);
				out.writeString(GetStringMD5(m_loginPW));
				Send(out);
			}
			else 
			{
				// ���ӳɹ��󣬿�ʼ��֤�û��ĺϷ���
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
 * ���ڴ�����յ���������Ϣ
 *
 * @param mes ���յ�Ҫ�����������Ϣ
 */
void CMole2dGameFrameDlg::OnProcessNetMes(CMolMessageIn &mes)
{
	if(mes.getLength() <= 0) return;

	switch(mes.getId())
	{
	case IDD_MESSAGE_GAME_LOGIN:             // �û���¼
		{
			OnProcessUserLoginMes(mes);
		}
		break;
	case IDD_MESSAGE_CENTER_LOGIN:           // �û���¼���ķ�����
		{
			OnProcessUserCenterMes(mes);
		}
		break;
	case IDD_MESSAGE_HEART_JITTER:           // ������Ϣ
		{
			OnProcessHeartJitter();
		}
		break;
	case IDD_MESSAGE_FRAME:                  // �����Ϣ
		{
			OnProcessFrameMes(mes);
		}
		break;
	case IDD_MESSAGE_ROOM:                   // ��Ϸ������Ϣ
		{
			OnProcessGameRoomMes(mes);
		}
		break;
	case IDD_MESSAGE_GET_PLAYER_MES:         // �����û���Ϣ
		{
			OnProcessUpdateUserInfoMes(mes);
		}
		break;
	default:
		break;
	}
}

/** 
 * ����������Ϣ
 */
void CMole2dGameFrameDlg::OnProcessHeartJitter()
{
	CMolMessageOut out(IDD_MESSAGE_HEART_JITTER);
	Send(out);
}

/** 
 * �����û���¼���ķ�������Ϣ
 *
 * @param mes ���յ�Ҫ�����������Ϣ
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

				// ���ȼ����������Ƿ���������
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

			// ��ȡ��������б�
			CMolMessageOut out(IDD_MESSAGE_GET_GAMESERVER);
			Send(out);

			AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,4,0);			
		}
		break;
	case IDD_MESSAGE_CENTER_LOGIN_FAIL:
		{
			MMessageBox("���ķ�������½ʧ�ܣ����������˻������롣","��½����",MB_OK);
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

			// ��¼�ɹ���͹ر�����
			CloseConnect();

			// ����û�ѡ���˱����û����ͽ��û���д�����ݿ���
			if(CMole2dGameClientDlg::getSingleton().IsRegisterPWD())
				WriteRegisterKey("MOLEUSERNAME",m_loginName);

			// ��ʾ������
			CMole2dGameClientDlg::getSingleton().ShowMainFrame();
		}
		break;
	default:
		break;
	}
}

/** 
 * �����û���¼ϵͳ��Ϣ
 *
 * @param mes ���յ�Ҫ�����������Ϣ
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

				// ���ȼ����������Ƿ���������
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

					// ��ȡ��������б�
					CMolMessageOut out(IDD_MESSAGE_FRAME);
					out.writeShort(IDD_MESSAGE_GET_ONLINE_PLAYERS);
					Send(out);

					AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,1,0);
				}
			}
			else
			{
				//// �����ԭ��������
				//pGameList->Clear();

				unsigned int pPlayerId = mes.readLong();

				// ���ȼ����������Ƿ���������
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

				// ��ȡ��������б�
				CMolMessageOut out(IDD_MESSAGE_FRAME);
				out.writeShort(IDD_MESSAGE_GET_ONLINE_PLAYERS);
				Send(out);

				AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,1,0);
			}
		}
		break;
	case IDD_MESSAGE_GAME_LOGIN_FAIL:
		{
			MMessageBox("��Ϸ��������½ʧ�ܣ����������˻������롣","��½����",MB_OK);
			AfxGetMainWnd()->SendMessage(IDM_GAMEFRAME_MESSAGE,IDD_MESSAGE_GAME_LOGIN_FAIL,0);
			CloseConnect();
		}
		break;
	case IDD_MESSAGE_GAME_LOGIN_FULL:
		{
			MMessageBox("��Ϸ��������������ѡ��������Ϸ���������롣","��½����",MB_OK);
			AfxGetMainWnd()->SendMessage(IDM_GAMEFRAME_MESSAGE,IDD_MESSAGE_GAME_LOGIN_FULL,0);
			CloseConnect();
		}
		break;
	case IDD_MESSAGE_GAME_LOGIN_EXIST:
		{
			MMessageBox("��ǰ���Ѿ�����Ϸ�������У������ظ���½��","��½����",MB_OK);
			AfxGetMainWnd()->SendMessage(IDM_GAMEFRAME_MESSAGE,IDD_MESSAGE_GAME_LOGIN_EXIST,0);
			CloseConnect();
		}
		break;
	default:
		break;
	}
}

/** 
 * �õ���ҵ�����
 */
Player* CMole2dGameFrameDlg::GetMySelf(void)
{
	CMolGUIRoomList *pGameList = GetRoomList();
	if(pGameList == NULL) return NULL;

	Player *myselfInfo = pGameList->IsExistPlayer(pGameList->GetMySelfID());
	if(myselfInfo == NULL) return NULL;

	return myselfInfo;
}

/// �ȴ�����Ϸ�����Ϣ
void CMole2dGameFrameDlg::OnProcessFrameMes(CMolMessageIn &mes)
{
	switch(mes.readShort())
	{
	case IDD_MESSAGE_GET_ONLINE_PLAYERS:             // �õ���ǰ��������б�
		{
			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			int pPlayerCount = mes.readShort();
			m_totalOnlinePlayers+=pPlayerCount;			

			for(int index = 0;index < pPlayerCount;index++)
			{
				unsigned int pPlayerId = mes.readLong();

				// ���ȼ����������Ƿ���������
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
	case IDD_MESSAGE_GET_ONLINE_PLAYERS_END:         // ����������ҽ���
		{
			CMole2dGameClientDlg::getSingleton().SetCurServerOnlinePlayers(m_totalOnlinePlayers);
			m_totalOnlinePlayers = 0;
			AfxGetMainWnd()->SendMessage(IDD_SHOW_CONN_TIP,2,0);

			// ��ȡ�����б�
			CMolMessageOut out(IDD_MESSAGE_FRAME);
			out.writeShort(IDD_MESSAGE_GET_ROOM_LIST);
			Send(out);		
		}
		break;
	case IDD_MESSAGE_GET_ROOM_LIST:                  // �õ���ǰ�������з����б�
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
			
			// �����������ֻ��һ�Ļ���ֻ���Ŷӽ���
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

			// ����ָ�������ķ���
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

			// ����ʾ��������
			CString mainframeDir;
			mainframeDir.Format("%s\\gameroomconfig\\gameroomlistconfig.gui",GetProgressDirection().c_str());
			LoadGUIConfig(mainframeDir);
			ShowWindow(SW_RESTORE);
		
			// ����û����ڶ���״̬�£���ô��ֱ�ӽ�����Ϸ
			Player *pPlayer = pGameList->IsExistPlayer(pGameList->GetMySelfID());
			if(pPlayer == NULL) return;
			
			if(pPlayer->GetState() == PLAYERSTATE_LOSTLINE)
			{
				pGameList->SetVisible(FALSE);
				
				// ת������Ϸ�ű�Ŀ¼��
				CString gameDir;
				gameDir.Format("%s\\%d",GetProgressDirection().c_str(),m_curGameID);
				ChangePlayerWorkingDir(gameDir.GetBuffer());
				
				pPlayer->SetState(PLAYERSTATE_GAMING);
				
				// ��������������»ص�����
				CMolMessageOut out(IDD_MESSAGE_FRAME);
				out.writeShort(IDD_MESSAGE_REENTER_ROOM);
				Send(out);			
			}
		}
		break;
	case IDD_MESSAGE_ENTER_ROOM:                      // ������Ϸ����
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

						// ת������Ϸ�ű�Ŀ¼��
						CString gameDir;
						gameDir.Format("%s\\%d",GetProgressDirection().c_str(),m_curGameID);
						ChangePlayerWorkingDir(gameDir.GetBuffer());
					}

					// ������Ϸ�ű�
					OnProcessEnterRoomMsg(GetUserChairID(pPlayerId),mes);
				}
				break;
			case IDD_MESSAGE_ENTER_ROOM_FAIL:
				{

				}
				break;
			case IDD_MESSAGE_ENTER_ROOM_LASTMONEY:
				{
					MMessageBox("��ǰ�����ϵĽ�Ҳ������㷿�����Ҫ��,�����³�ֵ��","���뷿�����",MB_OK,this);
				}
				break;
			default:
				break;
			}
		}
		break;
	case IDD_MESSAGE_LOOKON_ENTER_ROOM:             // �Թ۽�����Ϸ����
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

					// ������Թ��û��Ļ������ô���
					Player *pPlayer = pGameList->IsExistPlayer(pPlayerId);
					if(pPlayer == NULL) return;	

					pPlayer->SetLookOn(true);
					pPlayer->SetRoomId(pRoomIndex);
					pPlayer->SetRoomIndex(pChairIndex);
					//pGameList->SetGamePlayerSeat(pPlayerId,pRoomIndex,pChairIndex);	

					if(pGameList->GetMySelfID() == pPlayerId)
					{
						pGameList->SetVisible(FALSE);

						// ת������Ϸ�ű�Ŀ¼��
						CString gameDir;
						gameDir.Format("%s\\%d",GetProgressDirection().c_str(),m_curGameID);
						ChangePlayerWorkingDir(gameDir.GetBuffer());
					}

					// ������Ϸ�ű�
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
	case IDD_MESSAGE_LEAVE_ROOM:                    // �뿪��Ϸ����
		{
			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			unsigned int pPlayerId = mes.readLong();

			Player *pPlayer = pGameList->IsExistPlayer(pPlayerId);
			if(pPlayer == NULL) return;	

			pPlayer->SetState(PLAYERSTATE_NORAML);
			pPlayer->SetRoomId(-1);
			pPlayer->SetRoomIndex(-1);

			// ������Թ��û��Ļ������ô���
			if(pPlayer->IsLookOn()) 
			{
				pPlayer->SetLookOn(false);
			}
			else
			{
				// ������Ϸ�ű�
				int state = GetUserChairID(pPlayerId);
				if(state != -1)
					OnProcessLeaveRoomMsg(state,mes);

				pGameList->ClearChairByPlayerID(pPlayerId);			
			}				
		}
		break;
	case IDD_MESSAGE_LEAVE_SERVER:              // �뿪��Ϸ������
		{
			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			unsigned int pPlayerId = mes.readLong();
			
			pGameList->ClearChairByPlayerID(pPlayerId);		
			pGameList->DeletePlayer(pPlayerId);		
		}
		break;
	case IDD_MESSAGE_REENTER_ROOM:                  // ���ߺ����»ص�����
		{
			unsigned int pPlayerId = mes.readLong();	

			// ���ߺ��ػ�
			OnProcessDisconnectBackNetMes(GetUserChairID(pPlayerId),mes);
		}
		break;
	case IDD_MESSAGE_FALLLINE_ROOM:                 // �û�����
		{
			unsigned int pPlayerId = mes.readLong();	

			// ����
			OnProcessDisconnectNetMes(GetUserChairID(pPlayerId),mes);
		}
		break;
	case IDD_MESSAGE_READY_START:                   // �û�׼����ʼ��Ϸ
		{
			unsigned int pPlayerId = mes.readLong();

			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			Player *pPlayer = pGameList->IsExistPlayer(pPlayerId);
			if(pPlayer == NULL) return;

			pPlayer->SetState(PLAYERSTATE_READY);

			//�û�׼����Ϣ
			OnProcessPlayerReadyMes(GetUserChairID(pPlayerId));
		}
		break;
	case IDD_MESSAGE_GAME_START:                    // �����Ѿ���ʼ��Ϸ
		{
			unsigned int pRoomId = mes.readLong();

			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return;

			CMolGUIRoom *pRoom = pGameList->GetGameRoomByIndex(pRoomId);
			if(pRoom == NULL) return;

			pRoom->SetRoomState(ROOMSTATE_GAMING);
		}
		break;
	case IDD_MESSAGE_GAME_END:                      // �����Ѿ�������Ϸ
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
 * ���ڴ�����յ����¼�
 *
 * @param event Ҫ����ı�����Ϸ�¼�
 *
 * @return ����¼�����ɹ������棬���򷵻ؼ�
 */
bool CMole2dGameFrameDlg::OnProcessEvent(const CMolEvent& event)
{
	switch(event.mEventType)
	{
	case MOLET_GUI_EVENT:                               // GUI�¼�
		{
			switch(event.mGuiEvent.EventType)
			{
			case MOLGET_ELEMENT_SELECTED:               // �ؼ���ѡ��
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

								// ���������û�п�ʼ��Ϸ����ô������Ϸ��
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
									// �Թ۽���
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
			case MOLGET_BUTTON_CLICKED:                 // ��ť����¼�
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
 * �ر���Ϸ����
 *
 * @return ���Ҫ��Ĺر���Ϸ���ڷ����棬���򷵻ؼ�
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
 * ������Ϸ������Ϣ
 *
 * @param mes ��ҽ�����Ϸ�����Ҫ�������Ϣ
 */
void CMole2dGameFrameDlg::OnProcessGameRoomMes(CMolMessageIn &mes)
{
	if(mes.getLength() <= 0) return;

	OnProcessPlayerGameRoomMsg(mes);
}

/** 
 * ��������û���Ϣ
 *
 * @param mes Ҫ�����������Ϣ
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

			// ���ȼ����������Ƿ���������
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

/// ��Ϸ�Ի�����Ϣ
LRESULT CMole2dGameFrameDlg::OnGameFrameMessage(WPARAM wparam, LPARAM lparam)
{
	int type = (int)wparam;

	switch(type)
	{
	case 1:
		{
			int state = MMessageBox("��ǰ��������Ϸ�У����ǿ�˽����۷֣���ȷ��Ҫ�˳���Ϸ��","�˳���Ϸ",MB_OKCANCEL,this);
			if(state==2) return 0;

			CMolGUIRoomList *pGameList = GetRoomList();
			if(pGameList == NULL) return false;

			DestroyScriptSystem();
			CloseAllRoomTimers();

			// ת������������Ŀ¼��
			CString gameDir;
			gameDir.Format("%s",GetProgressDirection().c_str());
			ChangePlayerWorkingDir(gameDir.GetBuffer(),false);
			LoadGUIConfig("gameroomconfig\\gameroomlistconfig.gui");

			pGameList->Reset();
			pGameList->SetVisible(TRUE);

			// �����뿪������Ϣ
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

			// ת������������Ŀ¼��
			CString gameDir;
			gameDir.Format("%s",GetProgressDirection().c_str());
			ChangePlayerWorkingDir(gameDir.GetBuffer(),false);
			LoadGUIConfig("gameroomconfig\\gameroomlistconfig.gui");

			pGameList->Reset();
			pGameList->SetVisible(TRUE);

			// �����뿪������Ϣ
			CMolMessageOut out(IDD_MESSAGE_FRAME);
			out.writeShort(IDD_MESSAGE_LEAVE_ROOM);
			Send(out);
		}
		break;
	case 3:
		{
			MMessageBox("��ǰ�����ϵĽ�Ҳ������㷿�����Ҫ��,�����³�ֵ��","���뷿�����",MB_OK,this);
		}
		break;
	default:
		break;
	}

	return 0;
}
