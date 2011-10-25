#ifndef _PLAYER_H_INCLUDE_
#define _PLAYER_H_INCLUDE_

#include <string>

/**
 * ���״̬
 */
enum PlayerState
{
	PLAYERSTATE_NORAML = 0,             // ����״̬
	PLAYERSTATE_QUEUE,                  // �Ŷ�״̬
	PLAYERSTATE_READY,                  // ׼��״̬
	PLAYERSTATE_GAMING,                 // ��Ϸ��״̬
	PLAYERSTATE_CHANGEROOM,             // �ı䷿��
	PLAYERSTATE_LOSTLINE                // ����״̬
};

/** 
 * �������
 */
enum PlayerType
{
	PLAYERTYPE_NORMAL = 0,              // ��ͨ�û�
	PLAYERTYPE_ROBOT                    // �������û�
};

class Player
{
public:
	Player();
	Player(int id,int conid);
	~Player();

	/// �������ID
	inline void SetID(int id) { m_Id = id; }
	/// �õ����ID
	inline int GetID(void) { return m_Id; }
	/// �����������ID
	inline void SetConnectID(int id) { m_ConnectId = id; }
	/// �õ��������ID
	inline int GetConnectID(void) { return m_ConnectId; }
	/// ����������ڵķ���ID
	inline void SetRoomId(int id) { m_roomId = id; }
	/// �õ�������ڵķ���ID
	inline int GetRoomId(void) { return m_roomId; }
	/// �����������
	inline void SetType(PlayerType type) { m_PlayerType = type; }
	/// �õ��������
	inline PlayerType GetType(void) { return m_PlayerType; }
	/// ��������ڷ����е�����
	inline void SetRoomIndex(int index) { m_roomIndex = index; }
	/// �õ�����ڷ����е�����
	inline int GetRoomIndex(void) { return m_roomIndex; }
	/// ������ҵ���������
	inline void SetHeartCount(int count) { m_heartJitter = count; }
	/// �õ���ҵ���������
	inline int GetHeartCount(void) { return m_heartJitter; }
	/// �����������
	inline void SetName(std::string name) { m_Name = name; }
	/// �õ��������
	inline std::string GetName(void) { return m_Name; }
	/// �õ����״̬
	inline PlayerState GetState(void) { return m_PlayerState; }
	/// �������״̬
	inline void SetState(PlayerState state) { m_PlayerState = state; }
	/// �����Ƿ��Թ�
	inline void SetLookOn(bool isLook) { m_isLookOn = isLook; }
	/// �õ��Ƿ��Թ�
	inline bool IsLookOn(void) { return m_isLookOn; }

	/// ������ҽ�Ǯ����
	inline void SetMoney(double money) { m_Money = money; }
	/// �õ���ҽ������
	inline double GetMoney(void) { return m_Money; }
	/// ������ҵȼ�
	inline void SetLevel(int level) { m_level = level; }
	/// �õ���ҵȼ�
	inline int GetLevel(void) { return m_level; }
	/// ������Ҿ���ֵ
	inline void SetExperience(unsigned int exp) { m_experience = exp; }
	/// �õ���Ҿ���ֵ
	inline unsigned int GetExperience(void) { return m_experience; }
	/// �������ͷ��
	inline void SetUserAvatar(std::string ava) { m_useravatar = ava; }
	/// �õ����ͷ��
	inline std::string GetUserAvatar(void) { return m_useravatar; }
	/// ��������ܾ�
	inline void SetTotalBureau(int bureau) { m_totalbureau = bureau; }
	/// �õ�����ܾ�
	inline int GetTotalBureau(void) { return m_totalbureau; }
	/// �������Ӯ��
	inline void SetSuccessBureau(int bureau) { m_successbureau = bureau; }
	/// �õ����Ӯ��
	inline int GetSuccessBureau(void) { return m_successbureau; }
	/// ����������
	inline void SetFailBureau(int bureau) { m_failbureau = bureau; }
	/// �õ�������
	inline int GetFailBureau(void) { return m_failbureau; }
	/// �������ʤ��
	inline void SetSuccessRate(float rate) { m_successrate = rate; }
	/// �õ����ʤ��
	inline float GetSuccessRate(void) { return m_successrate; }
	/// �������������
	inline void SetRunawayrate(float rate) { m_runawayrate = rate; }
	/// �õ����������
	inline float GetRunawayrate(void) { return m_runawayrate; }

private:
	int m_Id;         /**< ���ID */
	int m_ConnectId;  /**< ��ҵ�����ID */
	int m_roomId;     /**< ������ڵķ���ID */
	int m_roomIndex;   /**< �û��ڷ����е����� */
	int m_heartJitter;   /**< ��ҵ��������� */
	PlayerState m_PlayerState;       /**< ��ҵ�ǰ״̬ */
	PlayerType m_PlayerType;           /**< ������� */
	bool m_isLookOn;                   /**< �Ƿ�Ϊ�Թ� */

	std::string m_Name;  /**< ��ҵ����� */

	double m_Money;              /**< ��ҽ�Ǯ���� */
	int m_level;                       /**< ��ҵȼ� */
	unsigned int m_experience;         /**< ��Ҿ���ֵ */
	std::string m_useravatar;         /**< �û�ͷ�� */
	int m_totalbureau;                 /**< ����ܾ� */
	int m_successbureau;               /**< ���Ӯ�� */
	int m_failbureau;                  /**< ������ */
	float m_successrate;               /**< ���ʤ�� */
	float m_runawayrate;               /**< ��������� */
};

#endif
