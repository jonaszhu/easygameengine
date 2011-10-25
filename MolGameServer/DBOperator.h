#ifndef _DB_OPERATOR_H_INCLUDE_
#define _DB_OPERATOR_H_INCLUDE_

#include "MolServerCom.h"

#include <string>

class Player;

/** 
 * ����û���Ϣ
 */
struct UserDataStru
{
	int UserId;                   // ���ID
	__int64 Money;                // ��ҽ�Ǯ
	int Level;                    // ��ҵȼ�
	int Experience;               // ��Ҿ���ֵ
	char UserAvatar[256];         // ���Avatar
	int TotalBureau;              // ����ܵľ���
	int SBureau;                  // ���ʤ������
	int FailBureau;               // ���ʧ�ܾ���
	float SuccessRate;            // ���ʤ������
	float RunawayRate;            // ������ܸ���  
};

/**
 * �����������Ϸ�����е����ݿ����
 */
class DBOperator : public Singleton<DBOperator>
{
public:
	/// ���캯��
	DBOperator();
	/// ��������
	~DBOperator();

	/// ��ʼ���ݿ�
	bool Initilize(std::string host,std::string user,std::string pass,std::string db,int port);
	/// �ر����ݿ�����
	void Shutdown(void);

	/// ����ָ����ҵĽ��
	bool UpdateUserMoney(unsigned int UserId,unsigned int money);
	/// ����ָ����ҵ�����
	bool UpdateUserData(Player *pPlayer);
	/// ����������ƺ��������������Ƿ����
	unsigned int IsExistUser(std::string name,std::string password);
	/// �����û�ID�õ��û�����Ϸ����
	bool GetUserData(unsigned int UserId,UserDataStru &UserData);

private:
	DataProvider *m_DataProvider;                               /**< ���ڷ��ʱ������ݿ� */
};

#define ServerDBOperator DBOperator::getSingleton()

#endif
