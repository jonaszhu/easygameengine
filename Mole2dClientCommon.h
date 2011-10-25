#ifndef _MOLE2D_COMMON_H_INCLUDE_
#define _MOLE2D_COMMON_H_INCLUDE_

/** 
 * �����������ṹ
 */
struct SerParamStru
{
	char IPAddress[128];                 // IP��ַ
	char Password[128];                  // ��������
	int  Port;                           // �˿�
};

#define IDD_CLIENT_CONFIG_FILE "clientconfig.ini"              // �ͻ��������ļ�
#define IDD_CLIENT_CAPTION  "Mole������Ϸƽ̨"

#define IDM_BTN_SERVER_LOGIN             WM_USER+100           // �û���¼������
#define IDM_GAMEFRAME_MESSAGE            WM_USER+101           // ��Ϸ�ͻ��˷��͵���Ϣ
#define IDD_CLOSE_GAME_FRAME             WM_USER+102           // �ر���Ϸ����
#define IDD_EXIT_GAME                    WM_USER+103           // �˳���Ϸ
#define IDD_REENTER_GAME                 WM_USER+104           // ���½�����Ϸ
#define IDD_SHOW_CONN_TIP                WM_USER+105           // ��ʾ������ʾ

#define IDD_MAINFRAME_HOMEPAGE            601                   // ��ҳ
#define IDD_MAINFRAME_LASTPAGE            602                   // ��һҳ
#define IDD_MAINFRAME_NEXTPAGE            603                   // ��һҳ
#define IDD_MAINFRAME_TAILPAGE            604                   // βҳ
#define IDD_MAINFRAME_AUTOJOIN            605                   // �Զ�����

//��������ά��
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))

#endif
