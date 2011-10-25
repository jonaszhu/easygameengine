#ifndef _GUI_GAME_ROOM_LIST_H_
#define _GUI_GAME_ROOM_LIST_H_

#include "Mole2dBaseGUIElement.h"
#include "Mole2dGUIImage.h"
#include "Mole2dGUIButton.h"
#include "Player.h"

#include <vector>
#include <map>

/**
 * ��������
 */
enum CMolRoomType
{
	ROOMTYPE_JINBIN = 0,             // ��ҷ���
	ROOMTYPE_JIFEN,                  // ���ַ���
	ROOMTYPE_BISAI,                  // ��������
	ROOMTYPE_LIANXI,                 // ��ϰ����
	ROOMTYPE_NULL
};

/**
 * ���䵱ǰ״̬
 */
enum CMolRoomState
{
	ROOMSTATE_NORMAL = 0,             // �ȴ���
	ROOMSTATE_GAMING,                  // ��Ϸ��
	ROOMSTATE_NULL
};

class CMolGUIRoomList;

/** 
 * ����Ҫ��ʾ�ķ���
 */
class MOLEXPORT CMolGUIRoom
{
public:
	/** 
	 * ���������ӽṹ
	 */
	struct CMolChair
	{
		CMolChair()
			:state(ROOMSTATE_NORMAL),/*tex(0),*/m_focus(false),m_player(NULL)
		{ }
		CMolChair(CMolDimension2d<s32> os,CMolDimension2d<s32> no)
			:avataroffset(os),nameoffset(no),state(ROOMSTATE_NORMAL),/*tex(0),*/m_focus(false),m_player(NULL)
		{}
		CMolChair(CMolDimension2d<s32> os,CMolDimension2d<s32> no,CMolRoomState s,HTEXTURE t)
			:avataroffset(os),nameoffset(no),state(s),/*tex(t),*/m_focus(false),m_player(NULL)
		{ }

		//�����������
		void Clear(void)
		{
			state = ROOMSTATE_NORMAL;
			//tex = 0;
			m_focus = false;
			m_player = NULL;
		}

		CMolDimension2d<s32> avataroffset;            // ͷ��ƫ��λ��
		CMolDimension2d<s32> nameoffset;              // �ǳ�ƫ��λ��
		CMolRoomState state;                          // ����״̬
		//HTEXTURE tex;                                 // ����ʹ�õ�����
		bool m_focus;                                 // �Ƿ��������������
		Player *m_player;                             // ���������ϵ����
	};

	///���캯��
	CMolGUIRoom(CMolGUIRoomList *rl);
	///��������
	~CMolGUIRoom();

	///������еķ�������
	void Clear(void);
	///���õ�ǰ���������
	inline void SetRoomIndex(int index) { m_roomIndex = index; }
	///�õ���ǰ���������
	inline int GetRoomIndex(void) { return m_roomIndex; }
	///���õ�ǰ�ؼ��ĸ��ؼ�
	inline void SetParent(CMolBaseGUIElement *ctl) { m_Parents = ctl; }
	///�õ���ǰ�ؼ��ĸ��ؼ�
	inline CMolBaseGUIElement* GetParent(void) { return m_Parents; }
	///���÷��������������ʾ�ĸ߿�
	inline void SetPlayerRectSize(CMolDimension2d<s32> size) { m_playerRectSize = size; }
	///�õ����������������ʾ�Ŀ��
	inline CMolDimension2d<s32> GetPlayerRectSize(void) { return m_playerRectSize; }
	///���һ�����ӵ�������
	void AddChair(CMolGUIRoom::CMolChair chair,HTEXTURE defAvt);
	///�õ�ָ������������
	CMolGUIRoom::CMolChair* GetChair(int index);
	///�õ���λ
	CMolGUIRoom::CMolChair* GetEmptyChair(int *index);
	///�����û�ID��������е�����
	bool ClearChair(int playerId);
	///���÷��������Χ
	inline void SetRoomRect(CMolRect<s32> rect) { m_roomRect = rect; }
	///�õ����������Χ
	inline CMolRect<s32> GetRoomRect(void) { return m_roomRect; }
	///���÷���ʹ�õ�������
	void SetRoomImage(HTEXTURE texn,HTEXTURE texg);
	///����ָ�����������ӵ�����ͼƬ
	void SetChairImage(int index,std::string imgtex);
	///���÷���״̬
	void SetRoomState(CMolRoomState state);
	///�õ�����״̬
	inline CMolRoomState GetRoomState(void) { return m_roomState; }
	///���÷�������λ��ƫ��
	inline void SetRoomOffset(CMolDimension2d<s32> offset) { m_roomOffset = offset; }
	///�õ���������λ��ƫ��
	inline CMolDimension2d<s32> GetRoomOffset(void) { return m_roomOffset; }
	///��⵱ǰ�Ƿ��п�λ
	bool IsFull(void);

	///������
	void DrawRoom(CMolBaseFrame *pDriver);
	/// ���ڴ�����յ����¼�
	bool OnProcessEvent(const CMolEvent& event);
	/// ����ʧ������¼�
	void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	std::vector<CMolChair>  m_chairs;                     /**< ��ǰ���������е����� */
	std::vector<HTEXTURE> m_chairAvator;                  /**< ������ʾ�����ͼƬ */
	CMolRoomState m_roomState;                            /**< ����״̬ */
	CMolRect<s32> m_roomRect;                             /**< �������ʾ���� */
	CMolDimension2d<s32> m_roomOffset;                    /**< ��������ƫ��λ�� */
	CMolDimension2d<s32> m_playerRectSize;                /**< �������������ĸ߿� */
	HTEXTURE m_texTable,m_texChair;                       /**< ��Ϸ�к���������µ�����ͼƬ */
	int m_roomIndex;                                      /**< ��ǰ�����ڷ����б��е����� */
	CMolBaseGUIElement *m_Parents;                        /**< ���õ�ǰ�ؼ��ĸ��ؼ� */
	CMolGUIRoomList *m_RoomList;                          /**< ��ǰʹ�õķ����б� */
};

class MOLEXPORT CMolGUIRoomList : public CMolBaseGUIElement
{
public:
	/// ���캯��
	CMolGUIRoomList();
	/// �������Ĺ��캯��
	CMolGUIRoomList(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,std::string caption,CMolRect<int> rect);
	virtual ~CMolGUIRoomList();

	/// ���뷿�������ļ�
	void LoadRoomConfig(std::string path);
	/// ��ӷ�����밴ť
	void AddEnterRoomButton(std::string btnimg);
	/// ��ȡһ�����ӵı���ͼƬ
	void LoadOneTableImage(std::string imgpath);
	/// ��������Լ���ID
	inline void SetMySelfID(unsigned int id) { m_myselfID = id; }
	/// �õ�����Լ���ID
	inline unsigned int GetMySelfID(void) { return m_myselfID; }
	/// ���÷�������
	inline void SetRoomType(CMolRoomType type) { m_roomType = type; }
	/// �õ���������
	inline CMolRoomType GetRoomType(void) { return m_roomType; }
	///��շ����б������еķ���
	void Clear(void);
	///���÷���״̬
	void Reset(void);
	///���÷����б���ʾ������
	inline void SetRowSize(CMolDimension2d<s32> size) { m_roomRowSize = size; }
	///�õ������б�ĸ߿�
	inline CMolDimension2d<s32> GetRowSize(void) { return m_roomRowSize; }
	///��������ͼƬ
	void LoadTableImage(std::string path);
    ///�õ�����ͼƬ·��
	inline std::string GetTableImagePath(void) { return m_texTablePath; }
	///��������ͼƬ
	void LoadChairImage(std::string path);
	///������ҳ�ʼAvator
	inline void SetPlayerDefAvt(HTEXTURE tex) { m_texDefAvt = tex; }
	///�õ���ҳ�ʼAvator
	inline HTEXTURE GetPlayerDefAvt(void) { return m_texDefAvt; }
	///�õ�����ͼƬ·��
	inline std::string GetChairImagePath(void) { return m_texChairPath; }
	///���ý��밴ť����ʾƫ��λ��
	inline void SetEnterBtnOffset(CMolDimension2d<s32> offset) { m_EnterBtnOffset = offset; }
	///�õ����밴ť����ʾƫ��λ��
	inline CMolDimension2d<s32> GetEnterBtnOffset(void) { return m_EnterBtnOffset; }
	///�����Ƿ��Ŷӽ��뷿��
	inline void SetQueueEnterRoom(bool isQueue);
	/// �õ��Ƿ��Ŷӽ��뷿��
	inline bool isQueueEnterRoom(void) { return m_isQueueEnter; } 
	///�������ƫ�Ƶ�ƫ���б���
	inline void AddChairOffset(int playerCount,std::vector<CMolDimension2d<s32> > offsets) 
	{ 
		std::map<int,std::vector<CMolDimension2d<s32> > >::iterator iter = m_chairoffsets.find(playerCount);
		if(iter != m_chairoffsets.end())
			(*iter).second = offsets;
		else
			m_chairoffsets.insert(std::pair<int,std::vector<CMolDimension2d<s32> > >(playerCount,offsets));
	}
	///�������ͷ��ƫ�Ƶ�ƫ���б���
	inline void AddChairNameOffset(int playerCount,std::vector<CMolDimension2d<s32> > offsets) 
	{ 
		std::map<int,std::vector<CMolDimension2d<s32> > >::iterator iter = m_chairnameoffsets.find(playerCount);
		if(iter != m_chairnameoffsets.end())
			(*iter).second = offsets;
		else
			m_chairnameoffsets.insert(std::pair<int,std::vector<CMolDimension2d<s32> > >(playerCount,offsets));
	}
	///���ָ�������ķ��䵽�����б���
	void SetGameRoom(int count);
	///���ݷ��������õ�����
	CMolGUIRoom* GetGameRoomByIndex(int index);
	///�õ���ǰѡ�еķ���
	CMolGUIRoom* GetGameRoomSelected(void);
	///�õ���ǰѡ�еķ�������
	CMolGUIRoom::CMolChair* GetGameRoomChairSelected(void);
	///ͨ���û�ID�����ǰ�����е�����
	void ClearChairByPlayerID(int playerId);
	///�õ���ǰѡ�еķ�������
	inline int GetGameRoomIndexSelected(void) { return m_selectedRoom; }
	///�õ���ǰѡ�е���������
	inline int GetGameChairIndexSelected(void) { return m_selectedChair; }
	///�Զ�Ѱ�ҷ������ӣ�Ȼ�����
	void AutoJoin(int playerId);
	///����ѡ�еķ���ָ�����ӵ��������
	void SeletGamerChairSelected(int playerId);
	///���÷��������ӵ���ʾ��С
	inline void SetRoomChairSize(CMolDimension2d<s32> size) { m_chairoffset = size; }
	///���õ�ǰ�����б��з���ѡ�к�����ѡ��
	inline void SetRoomSelected(int sr,int sc) { m_selectedRoom = sr; m_selectedChair = sc; }
	///���õ�ǰ����������ѡ��
	inline void SetRoomSelectedChair(int sc) { m_selectedChair = sc; }
	///�õ����������ӵ���ʾ��С
	inline CMolDimension2d<s32> GetRoomChairSize(void) { return m_chairoffset; }
	///���÷�������������
	inline void SetChairCount(int count) { m_chairCount = count; }
	///�õ���������������
	inline int GetChairCount(void) { return m_chairCount; }
	///���÷�������λ��ƫ��
	inline void SetRoomOffset(CMolDimension2d<s32> offset) { m_roomOffset = offset; }
	///�õ���������λ��ƫ��
	inline CMolDimension2d<s32> GetRoomOffset(void) { return m_roomOffset; }	
	
	///�����û�ID��������е��û�
	void DeletePlayer(int playerId);
	///���һ����ҵ�������
	void AddGamePlayer(Player *pPlayer);
	///�������ID�����Ӻţ����Ӻ��������λ��
	void SetGamePlayerSeat(unsigned int playerId,int roomIndex,int chairIndex);
	///���ָ��ID������Ƿ����
	Player* IsExistPlayer(unsigned int playerId);
	
	/// ���ڷֽ�ָ���ַ���Ϊ��ͬ�Ĳ���
	int ParseStringToParameter(std::string str,std::string chr=";");

	///��һҳ
	void PageUp(void);
	///��һҳ
	void PageDown(void);
	///��ҳ
	void Home(void);
	///βҳ
	void End(void);

	/// ���ؼ�
	virtual void Draw();
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// ����ʧ������¼�
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	unsigned int m_myselfID;                              /**< ����Լ����û�ID */
	std::vector<CMolGUIRoom>  m_roomList;                 /**< �����б� */
	std::map<unsigned int,Player*> m_playerList;          /**< ����б� */
	CMolDimension2d<s32> m_roomRowSize;                   /**< ��ʾ���к��и߶� */
	CMolDimension2d<s32> m_roomOffset;                    /**< ��������ƫ��λ�� */	
	int m_curRoomIndex;                                   /**< ��ǰ�������� */
	CMolRoomType m_roomType;                              /**< �������� */

	std::string m_texTablePath,m_texChairPath;           /**< ���Ӻ�����ͼƬ·�� */
	HTEXTURE m_texTable,m_texChair,m_texDefAvt;           /**< ���Ӻ�����ͼƬ */
	HTEXTURE m_texOneTable;                               /**< �����һ������Ļ�����ʾ����ͼƬ�����ͼƬ������ϷID����ȡ�� */
	CMolDimension2d<s32> m_chairoffset;                   /**< ������λ�ĸ߿� */
	std::map<int,std::vector<CMolDimension2d<s32> > > m_chairoffsets;     /**< �������������ӵ�ƫ�� */
	std::map<int,std::vector<CMolDimension2d<s32> > > m_chairnameoffsets; /**< ��������������ͷ���ƫ�� */
	int m_chairCount;                                     /**< �������������� */
	int m_selectedRoom,m_selectedChair;                   /**< ��ǰѡ�еķ������������ */
	
	CMolGUIButton *m_EnterBtn;                            /**< ��Ϸ���밴ť */
	CMolDimension2d<s32> m_EnterBtnOffset;                /**< ���밴ť��ƫ��λ�� */
	bool m_isQueueEnter;                                  /**< �Ƿ��Ŷӽ��뷿�� */

	std::vector<std::string>  m_Parameters;                        /**< Ҫ�ֽ�Ĳ��� */
};

#endif
