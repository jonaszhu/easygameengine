#ifndef _GUI_GAME_ROOM_LIST_H_
#define _GUI_GAME_ROOM_LIST_H_

#include "Mole2dBaseGUIElement.h"
#include "Mole2dGUIImage.h"
#include "Mole2dGUIButton.h"
#include "Player.h"

#include <vector>
#include <map>

/**
 * 房间类型
 */
enum CMolRoomType
{
	ROOMTYPE_JINBIN = 0,             // 金币房间
	ROOMTYPE_JIFEN,                  // 积分房间
	ROOMTYPE_BISAI,                  // 比赛房间
	ROOMTYPE_LIANXI,                 // 练习房间
	ROOMTYPE_NULL
};

/**
 * 房间当前状态
 */
enum CMolRoomState
{
	ROOMSTATE_NORMAL = 0,             // 等待中
	ROOMSTATE_GAMING,                  // 游戏中
	ROOMSTATE_NULL
};

class CMolGUIRoomList;

/** 
 * 我们要显示的房间
 */
class MOLEXPORT CMolGUIRoom
{
public:
	/** 
	 * 房间中椅子结构
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

		//清空这张椅子
		void Clear(void)
		{
			state = ROOMSTATE_NORMAL;
			//tex = 0;
			m_focus = false;
			m_player = NULL;
		}

		CMolDimension2d<s32> avataroffset;            // 头像偏移位置
		CMolDimension2d<s32> nameoffset;              // 昵称偏移位置
		CMolRoomState state;                          // 椅子状态
		//HTEXTURE tex;                                 // 椅子使用的纹理
		bool m_focus;                                 // 是否鼠标在椅子上面
		Player *m_player;                             // 坐在椅子上的玩家
	};

	///构造函数
	CMolGUIRoom(CMolGUIRoomList *rl);
	///析构函数
	~CMolGUIRoom();

	///清空所有的房间数据
	void Clear(void);
	///设置当前房间的索引
	inline void SetRoomIndex(int index) { m_roomIndex = index; }
	///得到当前房间的索引
	inline int GetRoomIndex(void) { return m_roomIndex; }
	///设置当前控件的父控件
	inline void SetParent(CMolBaseGUIElement *ctl) { m_Parents = ctl; }
	///得到当前控件的父控件
	inline CMolBaseGUIElement* GetParent(void) { return m_Parents; }
	///设置房间中玩家区域显示的高宽
	inline void SetPlayerRectSize(CMolDimension2d<s32> size) { m_playerRectSize = size; }
	///得到房间中玩家区域显示的宽高
	inline CMolDimension2d<s32> GetPlayerRectSize(void) { return m_playerRectSize; }
	///添加一把椅子到房间中
	void AddChair(CMolGUIRoom::CMolChair chair,HTEXTURE defAvt);
	///得到指定索引的椅子
	CMolGUIRoom::CMolChair* GetChair(int index);
	///得到空位
	CMolGUIRoom::CMolChair* GetEmptyChair(int *index);
	///根据用户ID清除房间中的椅子
	bool ClearChair(int playerId);
	///设置房间的区域范围
	inline void SetRoomRect(CMolRect<s32> rect) { m_roomRect = rect; }
	///得到房间的区域范围
	inline CMolRect<s32> GetRoomRect(void) { return m_roomRect; }
	///设置房间使用到的纹理
	void SetRoomImage(HTEXTURE texn,HTEXTURE texg);
	///设置指定索引的椅子的纹理图片
	void SetChairImage(int index,std::string imgtex);
	///设置房间状态
	void SetRoomState(CMolRoomState state);
	///得到房间状态
	inline CMolRoomState GetRoomState(void) { return m_roomState; }
	///设置房间索引位置偏移
	inline void SetRoomOffset(CMolDimension2d<s32> offset) { m_roomOffset = offset; }
	///得到房间索引位置偏移
	inline CMolDimension2d<s32> GetRoomOffset(void) { return m_roomOffset; }
	///检测当前是否有空位
	bool IsFull(void);

	///画房间
	void DrawRoom(CMolBaseFrame *pDriver);
	/// 用于处理接收到的事件
	bool OnProcessEvent(const CMolEvent& event);
	/// 处理丢失焦点的事件
	void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	std::vector<CMolChair>  m_chairs;                     /**< 当前房间中所有的椅子 */
	std::vector<HTEXTURE> m_chairAvator;                  /**< 椅子显示的玩家图片 */
	CMolRoomState m_roomState;                            /**< 房间状态 */
	CMolRect<s32> m_roomRect;                             /**< 房间的显示区域 */
	CMolDimension2d<s32> m_roomOffset;                    /**< 房间索引偏移位置 */
	CMolDimension2d<s32> m_playerRectSize;                /**< 房间中玩家区域的高宽 */
	HTEXTURE m_texTable,m_texChair;                       /**< 游戏中和正常情况下的两张图片 */
	int m_roomIndex;                                      /**< 当前房间在房间列表中的索引 */
	CMolBaseGUIElement *m_Parents;                        /**< 设置当前控件的父控件 */
	CMolGUIRoomList *m_RoomList;                          /**< 当前使用的房间列表 */
};

class MOLEXPORT CMolGUIRoomList : public CMolBaseGUIElement
{
public:
	/// 构造函数
	CMolGUIRoomList();
	/// 带参数的构造函数
	CMolGUIRoomList(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,std::string caption,CMolRect<int> rect);
	virtual ~CMolGUIRoomList();

	/// 导入房间配置文件
	void LoadRoomConfig(std::string path);
	/// 添加房间进入按钮
	void AddEnterRoomButton(std::string btnimg);
	/// 读取一张桌子的背景图片
	void LoadOneTableImage(std::string imgpath);
	/// 设置玩家自己的ID
	inline void SetMySelfID(unsigned int id) { m_myselfID = id; }
	/// 得到玩家自己的ID
	inline unsigned int GetMySelfID(void) { return m_myselfID; }
	/// 设置房间类型
	inline void SetRoomType(CMolRoomType type) { m_roomType = type; }
	/// 得到房间类型
	inline CMolRoomType GetRoomType(void) { return m_roomType; }
	///清空房间列表中所有的房间
	void Clear(void);
	///重置房间状态
	void Reset(void);
	///设置房间列表显示的行列
	inline void SetRowSize(CMolDimension2d<s32> size) { m_roomRowSize = size; }
	///得到房间列表的高宽
	inline CMolDimension2d<s32> GetRowSize(void) { return m_roomRowSize; }
	///导入桌子图片
	void LoadTableImage(std::string path);
    ///得到桌子图片路径
	inline std::string GetTableImagePath(void) { return m_texTablePath; }
	///导入椅子图片
	void LoadChairImage(std::string path);
	///设置玩家初始Avator
	inline void SetPlayerDefAvt(HTEXTURE tex) { m_texDefAvt = tex; }
	///得到玩家初始Avator
	inline HTEXTURE GetPlayerDefAvt(void) { return m_texDefAvt; }
	///得到椅子图片路径
	inline std::string GetChairImagePath(void) { return m_texChairPath; }
	///设置进入按钮的显示偏移位置
	inline void SetEnterBtnOffset(CMolDimension2d<s32> offset) { m_EnterBtnOffset = offset; }
	///得到进入按钮的显示偏移位置
	inline CMolDimension2d<s32> GetEnterBtnOffset(void) { return m_EnterBtnOffset; }
	///设置是否排队进入房间
	inline void SetQueueEnterRoom(bool isQueue);
	/// 得到是否排队进入房间
	inline bool isQueueEnterRoom(void) { return m_isQueueEnter; } 
	///添加椅子偏移到偏移列表中
	inline void AddChairOffset(int playerCount,std::vector<CMolDimension2d<s32> > offsets) 
	{ 
		std::map<int,std::vector<CMolDimension2d<s32> > >::iterator iter = m_chairoffsets.find(playerCount);
		if(iter != m_chairoffsets.end())
			(*iter).second = offsets;
		else
			m_chairoffsets.insert(std::pair<int,std::vector<CMolDimension2d<s32> > >(playerCount,offsets));
	}
	///添加椅子头像偏移到偏移列表中
	inline void AddChairNameOffset(int playerCount,std::vector<CMolDimension2d<s32> > offsets) 
	{ 
		std::map<int,std::vector<CMolDimension2d<s32> > >::iterator iter = m_chairnameoffsets.find(playerCount);
		if(iter != m_chairnameoffsets.end())
			(*iter).second = offsets;
		else
			m_chairnameoffsets.insert(std::pair<int,std::vector<CMolDimension2d<s32> > >(playerCount,offsets));
	}
	///添加指定个数的房间到房间列表中
	void SetGameRoom(int count);
	///根据房间索引得到房间
	CMolGUIRoom* GetGameRoomByIndex(int index);
	///得到当前选中的房间
	CMolGUIRoom* GetGameRoomSelected(void);
	///得到当前选中的房间椅子
	CMolGUIRoom::CMolChair* GetGameRoomChairSelected(void);
	///通过用户ID清除当前房间中的椅子
	void ClearChairByPlayerID(int playerId);
	///得到当前选中的房间索引
	inline int GetGameRoomIndexSelected(void) { return m_selectedRoom; }
	///得到当前选中的椅子索引
	inline int GetGameChairIndexSelected(void) { return m_selectedChair; }
	///自动寻找房间椅子，然后加入
	void AutoJoin(int playerId);
	///设置选中的房间指定椅子的玩家数据
	void SeletGamerChairSelected(int playerId);
	///设置房间中椅子的显示大小
	inline void SetRoomChairSize(CMolDimension2d<s32> size) { m_chairoffset = size; }
	///设置当前房间列表中房间选中和椅子选中
	inline void SetRoomSelected(int sr,int sc) { m_selectedRoom = sr; m_selectedChair = sc; }
	///设置当前房间中椅子选中
	inline void SetRoomSelectedChair(int sc) { m_selectedChair = sc; }
	///得到房间中椅子的显示大小
	inline CMolDimension2d<s32> GetRoomChairSize(void) { return m_chairoffset; }
	///设置房间中椅子数量
	inline void SetChairCount(int count) { m_chairCount = count; }
	///得到房间中椅子数量
	inline int GetChairCount(void) { return m_chairCount; }
	///设置房间索引位置偏移
	inline void SetRoomOffset(CMolDimension2d<s32> offset) { m_roomOffset = offset; }
	///得到房间索引位置偏移
	inline CMolDimension2d<s32> GetRoomOffset(void) { return m_roomOffset; }	
	
	///根据用户ID清除房间中的用户
	void DeletePlayer(int playerId);
	///添加一个玩家到房间中
	void AddGamePlayer(Player *pPlayer);
	///根据玩家ID，桌子号，椅子号设置玩家位置
	void SetGamePlayerSeat(unsigned int playerId,int roomIndex,int chairIndex);
	///检测指定ID的玩家是否存在
	Player* IsExistPlayer(unsigned int playerId);
	
	/// 用于分解指定字符串为不同的参数
	int ParseStringToParameter(std::string str,std::string chr=";");

	///上一页
	void PageUp(void);
	///下一页
	void PageDown(void);
	///首页
	void Home(void);
	///尾页
	void End(void);

	/// 画控件
	virtual void Draw();
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// 处理丢失焦点的事件
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	unsigned int m_myselfID;                              /**< 玩家自己的用户ID */
	std::vector<CMolGUIRoom>  m_roomList;                 /**< 房间列表 */
	std::map<unsigned int,Player*> m_playerList;          /**< 玩家列表 */
	CMolDimension2d<s32> m_roomRowSize;                   /**< 显示的行和列高度 */
	CMolDimension2d<s32> m_roomOffset;                    /**< 房间索引偏移位置 */	
	int m_curRoomIndex;                                   /**< 当前房间索引 */
	CMolRoomType m_roomType;                              /**< 房间类型 */

	std::string m_texTablePath,m_texChairPath;           /**< 桌子和椅子图片路径 */
	HTEXTURE m_texTable,m_texChair,m_texDefAvt;           /**< 桌子和椅子图片 */
	HTEXTURE m_texOneTable;                               /**< 如果是一个房间的话，显示房间图片，这个图片是以游戏ID来读取的 */
	CMolDimension2d<s32> m_chairoffset;                   /**< 椅子座位的高宽 */
	std::map<int,std::vector<CMolDimension2d<s32> > > m_chairoffsets;     /**< 房间中所有椅子的偏移 */
	std::map<int,std::vector<CMolDimension2d<s32> > > m_chairnameoffsets; /**< 房间中所有椅子头像的偏移 */
	int m_chairCount;                                     /**< 房间中椅子数量 */
	int m_selectedRoom,m_selectedChair;                   /**< 当前选中的房间和椅子索引 */
	
	CMolGUIButton *m_EnterBtn;                            /**< 游戏进入按钮 */
	CMolDimension2d<s32> m_EnterBtnOffset;                /**< 进入按钮的偏移位置 */
	bool m_isQueueEnter;                                  /**< 是否排队进入房间 */

	std::vector<std::string>  m_Parameters;                        /**< 要分解的参数 */
};

#endif
