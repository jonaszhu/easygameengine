#ifndef _MOLE2D_GAME_FRAME_DLG_H_INCLUDE_
#define _MOLE2D_GAME_FRAME_DLG_H_INCLUDE_

#include "Mole2d.h"

// CMole2dGameClientDlg �Ի���
class CMole2dGameFrameDlg : public CMolBaseFrame
{
	// ����
public:
	CMole2dGameFrameDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CMole2dGameFrameDlg();

	/// ���ӵ�¼������
	void ConnectLoginServer(std::string name,std::string pw);
	/// ������Ϸ������
	void ConnectGameServer(std::string serverip,int serverport);
	/// �������е�����
	void Reset(void);
	/// �õ���ҵ�����
	Player* GetMySelf(void);

	/// ������յ�������Ϣ
	virtual void OnProcessNetMessage(ConnectState state,CMolMessageIn &msg);
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);

private:
	/// ���ڴ�����յ���������Ϣ
	void OnProcessNetMes(CMolMessageIn &mes);
	/// �����û���¼ϵͳ��Ϣ
	void OnProcessUserLoginMes(CMolMessageIn &mes);
	/// �����û���¼���ķ�������Ϣ
	void OnProcessUserCenterMes(CMolMessageIn &mes);
	/// ����������Ϣ
	void OnProcessHeartJitter();
	/// �ȴ�����Ϸ�����Ϣ
	void OnProcessFrameMes(CMolMessageIn &mes);
	/// ������Ϸ������Ϣ
	void OnProcessGameRoomMes(CMolMessageIn &mes);
	/// ��������û���Ϣ
	void OnProcessUpdateUserInfoMes(CMolMessageIn &mes);

	/// �ر���Ϸ����
	bool CloseMyGameFrame(void);

private:
	std::string m_loginName,m_loginPW;
	int m_curGameID,m_revPlayerCount;
	int m_totalOnlinePlayers;

protected:
	afx_msg void OnClose();
	/// ��Ϸ�Ի�����Ϣ
	LRESULT OnGameFrameMessage(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()
};

#endif
