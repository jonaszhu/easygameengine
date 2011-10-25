#ifndef _PLAYER_H_INCLUDE_
#define _PLAYER_H_INCLUDE_

#include <string>

/**
 * 玩家状态
 */
enum PlayerState
{
	PLAYERSTATE_NORAML = 0,             // 正常状态
	PLAYERSTATE_QUEUE,                  // 排队状态
	PLAYERSTATE_READY,                  // 准备状态
	PLAYERSTATE_GAMING,                 // 游戏中状态
	PLAYERSTATE_CHANGEROOM,             // 改变房间
	PLAYERSTATE_LOSTLINE                // 掉线状态
};

/** 
 * 玩家类型
 */
enum PlayerType
{
	PLAYERTYPE_NORMAL = 0,              // 普通用户
	PLAYERTYPE_ROBOT                    // 机器人用户
};

class Player
{
public:
	Player();
	Player(int id,int conid);
	~Player();

	/// 设置玩家ID
	inline void SetID(int id) { m_Id = id; }
	/// 得到玩家ID
	inline int GetID(void) { return m_Id; }
	/// 设置玩家连接ID
	inline void SetConnectID(int id) { m_ConnectId = id; }
	/// 得到玩家连接ID
	inline int GetConnectID(void) { return m_ConnectId; }
	/// 设置玩家所在的房间ID
	inline void SetRoomId(int id) { m_roomId = id; }
	/// 得到玩家所在的房间ID
	inline int GetRoomId(void) { return m_roomId; }
	/// 设置玩家类型
	inline void SetType(PlayerType type) { m_PlayerType = type; }
	/// 得到玩家类型
	inline PlayerType GetType(void) { return m_PlayerType; }
	/// 设置玩家在房间中的索引
	inline void SetRoomIndex(int index) { m_roomIndex = index; }
	/// 得到玩家在房间中的索引
	inline int GetRoomIndex(void) { return m_roomIndex; }
	/// 设置玩家的心跳计数
	inline void SetHeartCount(int count) { m_heartJitter = count; }
	/// 得到玩家的心跳计数
	inline int GetHeartCount(void) { return m_heartJitter; }
	/// 设置玩家名称
	inline void SetName(std::string name) { m_Name = name; }
	/// 得到玩家名称
	inline std::string GetName(void) { return m_Name; }
	/// 得到玩家状态
	inline PlayerState GetState(void) { return m_PlayerState; }
	/// 设置玩家状态
	inline void SetState(PlayerState state) { m_PlayerState = state; }
	/// 设置是否旁观
	inline void SetLookOn(bool isLook) { m_isLookOn = isLook; }
	/// 得到是否旁观
	inline bool IsLookOn(void) { return m_isLookOn; }

	/// 设置玩家金钱数量
	inline void SetMoney(double money) { m_Money = money; }
	/// 得到玩家金币数量
	inline double GetMoney(void) { return m_Money; }
	/// 设置玩家等级
	inline void SetLevel(int level) { m_level = level; }
	/// 得到玩家等级
	inline int GetLevel(void) { return m_level; }
	/// 设置玩家经验值
	inline void SetExperience(unsigned int exp) { m_experience = exp; }
	/// 得到玩家经验值
	inline unsigned int GetExperience(void) { return m_experience; }
	/// 设置玩家头像
	inline void SetUserAvatar(std::string ava) { m_useravatar = ava; }
	/// 得到玩家头像
	inline std::string GetUserAvatar(void) { return m_useravatar; }
	/// 设置玩家总局
	inline void SetTotalBureau(int bureau) { m_totalbureau = bureau; }
	/// 得到玩家总局
	inline int GetTotalBureau(void) { return m_totalbureau; }
	/// 设置玩家赢局
	inline void SetSuccessBureau(int bureau) { m_successbureau = bureau; }
	/// 得到玩家赢局
	inline int GetSuccessBureau(void) { return m_successbureau; }
	/// 设置玩家输局
	inline void SetFailBureau(int bureau) { m_failbureau = bureau; }
	/// 得到玩家输局
	inline int GetFailBureau(void) { return m_failbureau; }
	/// 设置玩家胜率
	inline void SetSuccessRate(float rate) { m_successrate = rate; }
	/// 得到玩家胜率
	inline float GetSuccessRate(void) { return m_successrate; }
	/// 设置玩家逃跑率
	inline void SetRunawayrate(float rate) { m_runawayrate = rate; }
	/// 得到玩家逃跑率
	inline float GetRunawayrate(void) { return m_runawayrate; }

private:
	int m_Id;         /**< 玩家ID */
	int m_ConnectId;  /**< 玩家的连接ID */
	int m_roomId;     /**< 玩家所在的房间ID */
	int m_roomIndex;   /**< 用户在房间中的索引 */
	int m_heartJitter;   /**< 玩家的心跳计数 */
	PlayerState m_PlayerState;       /**< 玩家当前状态 */
	PlayerType m_PlayerType;           /**< 玩家类型 */
	bool m_isLookOn;                   /**< 是否为旁观 */

	std::string m_Name;  /**< 玩家的名称 */

	double m_Money;              /**< 玩家金钱数量 */
	int m_level;                       /**< 玩家等级 */
	unsigned int m_experience;         /**< 玩家经验值 */
	std::string m_useravatar;         /**< 用户头像 */
	int m_totalbureau;                 /**< 玩家总局 */
	int m_successbureau;               /**< 玩家赢局 */
	int m_failbureau;                  /**< 玩家输局 */
	float m_successrate;               /**< 玩家胜率 */
	float m_runawayrate;               /**< 玩家逃跑率 */
};

#endif
