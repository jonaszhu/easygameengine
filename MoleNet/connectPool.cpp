#include "stdafx.h"

#include "connectPool.h"
#include "dalexcept.h"

/**
 * ���캯��
 */
ConnectPool::ConnectPool()
	: m_max(0),m_BusyCount(0),m_port(3306)
{

}

/**
 * ��������
 */
ConnectPool::~ConnectPool()
{
	Close();
}

/**
 * ��ʼ�����ӳ�
 *
 * @param max ���ӳ�����������
 * @param host ���ݿ�IP��ַ
 * @param user �������ݿ��û���
 * @param password �û�����
 * @param db Ҫ���ʵ����ݿ�����
 * @param port Ҫ���ʵ����ݿ�˿�
 *
 * @return ������ݿ����ӳؽ����ɹ������棬���򷵻ؼ�
 */
bool ConnectPool::Init(int max,std::string host,std::string user,std::string password,std::string db,int port)
{
	m_max = max;
	m_host = host;
	m_user = user;
	m_password = password;
	m_db = db;
	m_port = port;

	MYSQL *mDb = NULL;
	
	for(int i=0;i<m_max;i++)
	{
		mDb = mysql_init(NULL);

		if(!mDb)
		{
			throw DbConnectionFailure("���ܹ���ʼMySql:û���㹻���ڴ档");
			return false;
		}

		if(!mysql_real_connect(mDb,
							   m_host.c_str(),
							   m_user.c_str(),
							   m_password.c_str(),
							   m_db.c_str(),
							   m_port,
							   NULL,
							   0))
		{
			std::string msg(mysql_error(mDb));
			mysql_close(mDb);

			throw DbConnectionFailure(msg);
			return false;
		}

		mysql_query(mDb,"set names gb2312");

		m_connlist.push_back(mDb);
	}

	return true;
}

/**
 * �ر����ӳ�
 */
void ConnectPool::Close(void)
{
	MYSQL *pcurConn = NULL;
	while(!m_connlist.empty())
	{
		pcurConn = m_connlist.front();
		m_connlist.pop_front();
		if(pcurConn)
			mysql_close(pcurConn);
	}
}

/**
 * ���½������ݿ�����
 *
 * @param pMysql Ҫ���������ݿ�����
 *
 * @return ������ݿ����ӽ����ɹ������棬���򷵻ؼ�
 */
bool ConnectPool::ResetConnet(MYSQL* pMysql)
{
	mysql_close(pMysql);

	pMysql = mysql_init(NULL);

	if(!pMysql)
	{
		throw DbConnectionFailure("���ܹ���ʼMySql:û���㹻���ڴ档");
		return false;
	}

	if(!mysql_real_connect(pMysql,
						   m_host.c_str(),
						   m_user.c_str(),
						   m_password.c_str(),
						   m_db.c_str(),
						   m_port,
						   NULL,
						   0))
	{
		std::string msg(mysql_error(pMysql));
		mysql_close(pMysql);

		throw DbConnectionFailure(msg);
		return false;
	}

	return true;
}

/**
 * �õ���ǰ���е����ݿ�����
 */
MYSQL* ConnectPool::GetConnet()
{
	MYSQL *pmySql = NULL;

	m_connlistlock.Acquire();

	// ���ڿ��е��߳�
	if(!m_connlist.empty())
	{
		//���ӳ���
		m_BusyCount++;

		pmySql = m_connlist.front();
		m_connlist.pop_front();
	}

	m_connlistlock.Release();

	return pmySql;
}

/**
 * �ͷ����ݿ�����
 *
 * @param pMysql �������Ҫ�ͷŵ�����
 */
void ConnectPool::PutConnet(MYSQL* pMysql)
{
	if(pMysql == NULL) return;

	m_connlistlock.Acquire();

	m_BusyCount--;
	m_connlist.push_back(pMysql);

	m_connlistlock.Release();
}