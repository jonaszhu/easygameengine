#ifndef _DB_OPERATOR_H_INCLUDE_
#define _DB_OPERATOR_H_INCLUDE_

#include "MolServerCom.h"

#include <string>

class Player;

/** 
 * 玩家用户信息
 */
struct UserDataStru
{
	int UserId;                   // 玩家ID
	__int64 Money;                // 玩家金钱
	int Level;                    // 玩家等级
	int Experience;               // 玩家经验值
	char UserAvatar[256];         // 玩家Avatar
	int TotalBureau;              // 玩家总的局数
	int SBureau;                  // 玩家胜利局数
	int FailBureau;               // 玩家失败局数
	float SuccessRate;            // 玩家胜利概率
	float RunawayRate;            // 玩家逃跑概率  
};

/**
 * 这个类用于游戏中所有的数据库操作
 */
class DBOperator : public Singleton<DBOperator>
{
public:
	/// 构造函数
	DBOperator();
	/// 析构函数
	~DBOperator();

	/// 初始数据库
	bool Initilize(std::string host,std::string user,std::string pass,std::string db,int port);
	/// 关闭数据库连接
	void Shutdown(void);

	/// 更新指定玩家的金币
	bool UpdateUserMoney(unsigned int UserId,unsigned int money);
	/// 更新指定玩家的数据
	bool UpdateUserData(Player *pPlayer);
	/// 根据玩家名称和密码检测这个玩家是否存在
	unsigned int IsExistUser(std::string name,std::string password);
	/// 根据用户ID得到用户的游戏数据
	bool GetUserData(unsigned int UserId,UserDataStru &UserData);

private:
	DataProvider *m_DataProvider;                               /**< 用于访问本地数据库 */
};

#define ServerDBOperator DBOperator::getSingleton()

#endif
