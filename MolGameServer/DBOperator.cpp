#include "stdafx.h"

#include "DBOperator.h"

#include "Player.h"

initialiseSingleton(DBOperator);

/**
 * ���캯��
 */
DBOperator::DBOperator()
: m_DataProvider(NULL)
{
	m_DataProvider = DataProviderFactory::createDataProvider();
}

/**
 * ��������
 */
DBOperator::~DBOperator()
{
	Shutdown();

	if(m_DataProvider)
		delete m_DataProvider;
	m_DataProvider = NULL;
}

/**
 * ��ʼ���ݿ�
 *
 * @param host Ҫ���ӵ����ݿ��IP��ַ
 * @param user �������ݿ���û���
 * @param pass �������ݿ���û�����
 * @param db Ҫ���ӵ����ݿ�����
 * @param port ���ݿ�˿ں�
 *
 * @return ������ݿ����ӳɹ������棬���򷵻ؼ�
 */
bool DBOperator::Initilize(std::string host,std::string user,std::string pass,std::string db,int port)
{
	if(m_DataProvider == NULL)
		return false;

	return m_DataProvider->connect(host,user,pass,db,port);
}

/**
 * �ر����ݿ�����
 */
void DBOperator::Shutdown(void)
{
	if(m_DataProvider == NULL)
		return;

	m_DataProvider->disconnect();
}

/** 
 * ����ָ����ҵĽ��
 *
 * @param UserId Ҫ���µ����ID
 * @param money Ҫ���µ���ҵĽ��
 *
 * @return ������³ɹ������棬���򷵻ؼ�
 */
bool DBOperator::UpdateUserMoney(unsigned int UserId,unsigned int money)
{
	if(m_DataProvider == NULL || UserId <= 0 || money == 0) return false;

	std::ostringstream sqlstr;
	sqlstr << "update mol_userdata set Money=Money+" << money << " where UserId=" << UserId << ";";

	m_DataProvider->execSql(sqlstr.str());

	return true;
}

/** 
 * ����������ƺ��������������Ƿ����
 *
 * @param name Ҫ������ҵ�����
 * @param password Ҫ������ҵ�����
 *
 * @return �����Ҵ��ڷ�����ҵ�ID�������ھͷ���-1
 */
unsigned int DBOperator::IsExistUser(std::string name,std::string password)
{
	if(m_DataProvider == NULL || name.empty() || password.empty()) return -1;

	std::ostringstream sqlstr;
	sqlstr << "select uid from mol_member where username='" << name << "' and password='" << password << "';";

	RecordSet pRecord = m_DataProvider->execSql(sqlstr.str());
	if(pRecord.isEmpty()) return -1;

	return atol(pRecord(0,0).c_str());
}

/** 
 * �����û�ID�õ��û�����Ϸ����
 *
 * @param UserId Ҫȡ�õ��û���ID
 * @param UserData ���ȡ���û����ݳɹ����������ڴ洢ȡ�õ��û�����
 *
 * @return ���ȡ���û����ݳɹ������棬���򷵻ؼ�
 */
bool DBOperator::GetUserData(unsigned int UserId,UserDataStru &UserData)
{
	if(m_DataProvider == NULL || UserId <= 0) return false;

	std::ostringstream sqlstr;
	sqlstr << "select * from mol_userdata where UserId=" << UserId << ";";

	RecordSet pRecord = m_DataProvider->execSql(sqlstr.str());
	if(pRecord.isEmpty()) return false;

	UserData.UserId = atol(pRecord(0,0).c_str());
	UserData.Money = _atoi64(pRecord(0,1).c_str());
	UserData.Level = atoi(pRecord(0,2).c_str());
	UserData.Experience = atoi(pRecord(0,3).c_str());
	strcpy(UserData.UserAvatar , pRecord(0,4).c_str());
	UserData.TotalBureau = atoi(pRecord(0,5).c_str());
	UserData.SBureau = atoi(pRecord(0,6).c_str());
	UserData.FailBureau = atoi(pRecord(0,7).c_str());
	UserData.SuccessRate = atof(pRecord(0,8).c_str());
	UserData.RunawayRate = atof(pRecord(0,9).c_str());

	return true;
}

/** 
 * ����ָ����ҵ�����
 *
 * @param pPlayer Ҫ������Ϣ�����
 * 
 * @return ��������Ϣ���³ɹ������棬���򷵻ؼ�
 */
bool DBOperator::UpdateUserData(Player *pPlayer)
{
	if(m_DataProvider == NULL || pPlayer == NULL) return false;

	std::ostringstream sqlstr;
	sqlstr << "update mol_userdata set Level=" << pPlayer->GetLevel() 
		   << ",Money=" << pPlayer->GetMoney()
		   << ",Experience=" << pPlayer->GetExperience()
		   << ",TotalBureau=" << pPlayer->GetTotalBureau()
		   << ",SBureau=" << pPlayer->GetSuccessBureau()
		   << ",FailBureau=" << pPlayer->GetFailBureau()
		   << ",SuccessRate=" << pPlayer->GetSuccessRate()
		   << ",RunawayRate=" << pPlayer->GetSuccessRate()
		   << " where UserId=" << pPlayer->GetID() << ";";

	m_DataProvider->execSql(sqlstr.str());

	return true;
}