#ifndef _DEFINES_H_INCLUDE_
#define _DEFINES_H_INCLUDE_

/*********************************************************************************************/
#define IDD_MESSAGE_CONNECTED           100         // �û����ӳɹ�

/*********************************************************************************************/
#define IDD_MESSAGE_ROOM                200         // ��Ϸ������Ϣ
#define IDD_MESSAGE_READY_START         201         // ���׼����ʼ��Ϸ
#define IDD_MESSAGE_GAME_START          202         // ��Ϸ��ʼ
#define IDD_MESSAGE_GAME_END            203         // ��Ϸ����

/*********************************************************************************************/
#define IDD_MESSAGE_CONNECT             400         // �û�������Ϣ
#define IDD_MESSAGE_CONNECT_SUCESS      401         // �û����ӳɹ�
#define IDD_MESSAGE_CONNECT_FAIL        402         // �û�����ʧ��
#define IDD_MESSAGE_CONNECT_EXIST       403         // �û����Ӵ���

/*********************************************************************************************/
#define IDD_MESSAGE_GAME_LOGIN               500         // �û���¼��Ϣ
#define IDD_MESSAGE_GAME_LOGIN_SUCESS        501         // �û���¼�ɹ�
#define IDD_MESSAGE_GAME_LOGIN_FAIL          502         // �û���¼ʧ��
#define IDD_MESSAGE_GAME_LOGIN_BUSY          503         // ϵͳæ,�û���¼����Ƶ��
#define IDD_MESSAGE_GAME_LOGIN_EXIST         504         // �û��Ѿ���ϵͳ��
#define IDD_MESSAGE_GAME_LOGIN_FULL          506         // ��������

/*********************************************************************************************/
#define IDD_MESSAGE_HEART_JITTER        600         // ����

/*********************************************************************************************/
#define IDD_MESSAGE_FRAME               700         // �����Ϣ
#define IDD_MESSAGE_ENTER_ROOM          701         // ������Ϸ����
#define IDD_MESSAGE_LEAVE_ROOM          702         // �뿪��Ϸ����
#define IDD_MESSAGE_REENTER_ROOM        703         // �û����ߺ����»ص���Ϸ����
#define IDD_MESSAGE_CHANGER_ROOM        704         // ����Ϸ����
#define IDD_MESSAGE_FALLLINE_ROOM       705         // �û�����Ϸ�����е���
#define IDD_MESSAGE_GET_ROOM_LIST       706         // �õ������б�
#define IDD_MESSAGE_LOOKON_ENTER_ROOM   707         // �Թ۽�����Ϸ����
#define IDD_MESSAGE_GET_ONLINE_PLAYERS  708         // �õ���ǰ�����������
#define IDD_MESSAGE_LEAVE_SERVER        709         // �뿪��Ϸ������
#define IDD_MESSAGE_GET_ONLINE_PLAYERS_END 710      // ��ȡ������ҽ���
#define IDD_MESSAGE_GET_ROOM_LIST_END   711         // ��ȡ�����б����

/*********************************************************************************************/
#define IDD_MESSAGE_GAMING              800         // �����Ϸ����Ϣ
#define IDD_MESSAGE_OUT_CARD            801         // ��ҳ���
#define IDD_MESSAGE_PASS_CARD           802         // ��ҹ���

/*********************************************************************************************/
#define IDD_MESSAGE_ENTER_ROOM_FAIL     901         // ������Ϸ����ʧ��
#define IDD_MESSAGE_ENTER_ROOM_SUCC     902         // ������Ϸ����ɹ�
#define IDD_MESSAGE_ENTER_ROOM_LASTMONEY 903        // ��Ҳ������㷿��Ҫ��

/*********************************************************************************************/
#define IDD_MESSAGE_GET_PLAYER_MES              2000                   // ȡ�������Ϣ
#define IDD_MESSAGE_GET_SUCCESS                 2001                   // ȡ�������Ϣ�ɹ�
#define IDD_MESSAGE_GET_FAIL                    2002                   // ȡ�������Ϣʧ��

/*********************************************************************************************/
#define IDD_MESSAGE_REGISTER_GAME               6000                   // ע����Ϸ
#define IDD_MESSAGE_REGISTER_SUCCESS            6001                   // ע����Ϸ�ɹ�
#define IDD_MESSAGE_REGISTER_FAIL               6002                   // ע����Ϸʧ��
#define IDD_MESSAGE_RE_REGISTER                 6003                   // �ظ�ע��

/*********************************************************************************************/
#define IDD_MESSAGE_UPDATE_GAME_SERVER          7000                   // ������Ϸ��������Ϣ
#define IDD_MESSAGE_UPDATE_GAME_SUCCESS         7001                   // ������Ϸ��������Ϣ�ɹ�
#define IDD_MESSAGE_UPDATE_GAME_FAIL            7002                   // ������Ϸ��������Ϣʧ��

#endif
