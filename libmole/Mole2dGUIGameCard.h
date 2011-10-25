#ifndef _MOLE2D_GUI_GAME_CARD_H_
#define _MOLE2D_GUI_GAME_CARD_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.2.3 写于平武,图像控件,用于显示整副图像或图像一部分
*/

#include "Mole2dBaseGUIElement.h"
#include "Mole2dVector.h"

#include <map>
#include <vector>
#include <deque>

//namespace mole2d
//{
	//namespace graphics
	//{

	/** 
	 * 扑克出牌类型
	 */
	enum CardOutType
	{
		OUTTYPE_SINGLE = 0,                   // 单张
		OUTTYPE_YIDUI,                        // 一对
		OUTTYPE_SANZHANG,                     // 三张
		OUTTYPE_SANDAIYI,                     // 三带一
		OUTTYPE_SANDAIYIDUI,                  // 三带一对
		OUTTYPE_SHUIZI,                       // 顺子
		OUTTYPE_LIANDUI,                      // 连对
		OUTTYPE_SANZHANGSHUIZI,               // 三张的顺子
		OUTTYPE_SANZHANGSHUIZIDAIYI,          // 三张的顺子带一
		OUTTYPE_SANZHANGSUUIZIDAIYIDUI,       // 三张顺子带一对
		OUTTYPE_SIDAILIANGZHANG,              // 四带两张单牌
		OUTTYPE_SIDAILIANGDUI,                // 四带两队
		OUTTYPE_ZHADAN,                       // 炸弹
		OUTTYPE_HUOJIAN,                      // 火箭
		OUTTYPE_NULL                          
	};

	class MOLEXPORT CMolGUIGameCard : public CMolBaseGUIElement
	{
	public:
		/** 
		 * 扑克结构
		 */
		struct GameCard
		{
			GameCard():data(0),isUp(false),isSelected(false),isDisplay(false) { }
			GameCard(BYTE d,bool up=false,bool issel=false,bool isdis=true):data(d),isUp(up),isSelected(issel),isDisplay(isdis) { }

			BYTE data;                // 扑克数据
			bool isUp;                // 是否弹起来
			bool isSelected;          // 扑克是否选择
			bool isDisplay;           // 是否显示
		};

		/** 
		 * 扑克的方向
		 */
		enum CardDir
		{
			CARDDIR_HENGXIANG = 0,                // 横向显示扑克
			CARDDIR_ZONGXIANG                     // 纵向显示扑克
		};

		/** 
		 * 扑克的对齐方式
		 */
		enum CardSnapType
		{
			CARD_SNAP_LEFT = 0,                   // 居左
			CARD_SNAP_CENTER,                     // 居中
			CARD_SNAP_RIGHT                       // 居右
		};

		/**
		 * 扑克显示类型
		 */
		enum CardDisType
		{
			DISTYPE_NORMAL = 0,                   // 正常显示
			DISTYPE_LEFTSLOPE,                    // 向左倾斜显示
			DISTYPE_RIGHTSLOPE                    // 向右倾斜显示
		};

		/** 
		 * 分析后的扑克数据
		 */
		struct AnaCards
		{
			CardOutType type;                     // 类型
			int value;                            // 值
			std::vector<BYTE> data;               // 用于存储数据
		};

		/// 构造函数
		CMolGUIGameCard();
		/// 带参数的构造函数
		CMolGUIGameCard(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);

	/// 设置扑克高宽
	inline void SetCardWidthAndHeight(int w,int h) 
	{ 
		m_CardWidth = w;
		m_CardHeight = h;
	}
	/// 得到扑克宽度
	inline int GetCardWidth(void) { return m_CardWidth; }
	/// 得到扑克高度
	inline int GetCardHeight(void) { return m_CardHeight; }
	/// 得到指定扑克数据的花色
	inline int GetCardHuaSe(int card) { return ((BYTE)card >> 4) & 0x0F; }
	/// 得到指定扑克数据的数据
	inline int GetCardDianShu(int card) { return (BYTE)card & 0x0F; }
	/// 设置扑克数据
	void SetCardData(CMolVector<int> data,bool isdis=true);
	/// 得到扑克数据
	CMolVector<int> GetCardData(void);
	/// 得到当前有多少张扑克
	inline int GetCardCount(void) { return (int)m_CardData.size(); }
	/// 设置扑克之间的间隔
	inline void SetCardSpace(int space) { m_CardSpace = space; }
	/// 得到扑克之间的间隔
	inline int GetCardSpace(void) { return m_CardSpace; }
	/// 设置扑克抬起的间隔
	inline void SetCardUpSpace(int space) { m_CardUpSpace = space; }
	/// 得到扑克抬起的间隔
	inline int GetCardUpSpace(void) { return m_CardUpSpace; }
	/// 设置扑克背面图片
	inline void SetCardBackTex(HTEXTURE tex) { m_CardBackImg = tex; }
	/// 得到扑克背面图片
	inline HTEXTURE GetCardBackTex(void) { return m_CardBackImg; }
	/// 设置扑克的显示方向
	inline void SetCardDirection(CMolGUIGameCard::CardDir dir) { m_CardDir = dir; }
	/// 得到扑克的显示方向
	inline CMolGUIGameCard::CardDir GetCardDirection(void) { return m_CardDir; }
	/// 设置是否显示扑克
	inline void SetShowCards(bool isShow) { m_IsShowCard = isShow; }
	/// 得到是否显示扑克
	inline bool IsShowCards(void) { return m_IsShowCard; }
	/// 设置显示多少张扑克
	void SetDisplayCard(int count);
	/// 得到当前弹起多少张扑克
	inline int GetCardUpCount(void) 
	{ 
		int count = 0;
		for(int i=0;i<(int)m_CardData.size();i++) 
			if(m_CardData[i].isUp) count+=1;

		return count;
	}
	/// 设置是否反向显示扑克
	inline void SetReverseShowCards(bool isReverse) { m_IsReverse = isReverse; }
	/// 得到是否反向显示扑克
	inline bool IsReverseShowCards(void) { return m_IsReverse; }
	/// 设置扑克的对齐方式
	inline void SetSnapType(CMolGUIGameCard::CardSnapType type) { m_CardSnapType = type; }
	/// 得到扑克的对齐方式
	inline CMolGUIGameCard::CardSnapType GetSnapType(void) { return m_CardSnapType; }

		/// 设置扑克的显示类型
		inline void SetDisType(CMolGUIGameCard::CardDisType type) { m_carddistype = type; }
		/// 得到扑克的显示类型
		inline CMolGUIGameCard::CardDisType GetDisType(void) { return m_carddistype; }
		/// 设置扑克的倾斜范围
		inline void SetSlopeAngle(int angle) { m_slopeangle = angle; }
		/// 得到扑克的倾斜范围
		inline int GetSlopeAngle(void) { return m_slopeangle; }
		/// 设置扑克倾斜所使用的图片
		inline void SetSlopeImage(std::string path);
		/// 得到扑克倾斜使用的图片
		inline std::string GetSlopeImage(void) { return m_slopeimagepath; }
		/// 设置选中扑克后使用的图片
		inline void SetSelectedCardImage(std::string path);
		/// 得到选中扑克后使用的图片
		inline std::string GetSelectedCardImage(void) { return m_selecteimagepath; }
		/// 设置扑克的旋转角度
		inline void SetAngle(int angle) { m_angle = angle; }
		/// 得到扑克的旋转角度
		inline int GetAngle(void) { return m_angle; }

		/// 得到当前选择的牌的张数
		inline int GetSelectedCardCount(void) { return (int)m_CurSelCards.size(); }
		/// 出指定张数的扑克
		void OutRandomCards(int count);
		/// 得到当前选择的牌数据
		CMolVector<int> GetSelectedCards(void);
		/// 开始出牌
		void StartOutCards(void);
		/// 清空所有的牌数据
		void ClearAllCards(void);
		/// 重新设置牌
		void ResetAllCards(void);
		/// 对所有的牌进行排序
		void SortAllCards(void);
		/// 跟牌型牌值得到相应的牌数据
		void GetCardsByOutType(CMolVector<int> cards);
		/// 得到指定牌的类型
		CardOutType GetOutType(CMolVector<int> cards);
	/// 寻找指定位置到指定位置的连牌
	void FindGameCard(int startPos,int startEnd);
		/// 从当前控件中删除指定的牌数据
		void RemoveCards(CMolVector<int> cards);
		/// 得到指定索引的扑克数据
		int GetCardDataByIndex(int index);
		/// 得到指定类型的扑克的数量
		int GetCardTypeCount(CardOutType type);
	/// 得到所有扑克的高宽
	CMolDimension2d<s32> GetCardSize(void);
		/// 得到当前牌类型的牌值
		inline int GetCurOutCardValue(void) { return m_curcardvalue; }
		/// 用于分解指定字符串为牌数据
		CMolVector<int> ParseStringToCards(std::string str,std::string chr=";");
		/// 检测指定的牌数据是否大得过另一个牌数据
		bool Comparison(CMolVector<int> src,CMolVector<int> dec);

		/// 画控件
		virtual void Draw();
		/// 用于处理接收到的事件
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// 处理丢失焦点的事件
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		/// 弹起指定索引的数据
		void UpCardsByIndex(std::vector<int> data);
		/// 分析牌数据
		void AnalyseAllCards(void);
		/// 得到基本牌型的牌数据
		bool GetBaseCardsByOutType(std::map< BYTE,std::vector<int> > analycards,CardOutType type,int card,bool isUp=true);
		/// 得到连牌类型的牌数据
		bool GetLianPaiCardsByOutType(CardOutType type,int card,int count,bool isUp=true);
		/// 清空牌控件的选择状态
		void ClearCardSelecteState(void);
		/// 显示指定ID的扑克
		void DrawGameCard(int index);
		/// 得到所有扑克的宽度
		int GetWidthWidthAllCards(void);
		/// 根据扑克的对齐方式得到扑克的显示位置
		CMolPosition2d<s32> GetCardDisplayPos(void);
		/// 从小到大排序
		static bool sort1(const GameCard &t1,const GameCard &t2);
		/// 从大到小排序
		static bool sort2(const GameCard &t1,const GameCard &t2);
		/// 检测两个指定的牌是否相等
		bool IsEquation(CMolVector<int> src,CMolVector<int> dec);

	private:
		int m_CardWidth,m_CardHeight;                           /**< 扑克高宽 */
		int m_CardSpace,m_CardUpSpace;                          /**< 扑克之间的间隔，抬起的间隔 */
		std::deque<GameCard>  m_CardData;                      /**< 要显示的扑克数据 */

		CardDisType m_carddistype;                              /**< 扑克显示类型 */
		int m_slopeangle;                                       /**< 倾斜的范围 */
		std::string m_slopeimagepath;                           /**< 倾斜使用的图片路径 */
		HTEXTURE m_slopeimage;                                  /**< 倾斜使用的图片 */
		std::string m_selecteimagepath;                        /**< 选中后显示的牌图片路径 */
		HTEXTURE m_selecteimage;                                /**< 选中后显示的牌图片 */
		CMolDimension2d<s32> selImgSize;                        /**< 选中后牌图片的高宽 */

		bool m_IsForward;                                       /**< 排序方式 */

		std::map<CardOutType,int> m_sortpos;                    /**< 搜索扑克数据的位置 */
		std::map<CardOutType,int> m_sortstartpos;               /**< 搜索扑克数据初始的位置 */
		CMolVector<int> m_sordcarddata;                         /**< 当前搜索牌数据 */
		CardOutType m_sortouttype;                              /**< 当前搜索出牌扑克类型 */
		std::map< BYTE,std::vector<int> >  m_analysecards;        /**< 分析后的牌数据 */
		int m_curcardvalue;                                     /**< 当前牌值 */

		std::vector<std::string>  m_Parameters;                 /**< 要分解的参数 */

		bool m_CurSelected;                                     /**< 当前是否选择牌 */
		std::vector<int> m_CurSelCards;                         /**< 当前选择的牌数据 */
		int m_CurSelStart,m_CurSelEnd;                          /**< 当前选择开始和结束 */
		int m_CurMousePos;                                      /**< 当前鼠标所在牌的索引 */
		CardDir m_CardDir;                                      /**< 当前扑克的方向 */
		CardSnapType m_CardSnapType;                            /**< 当前扑克的对齐方式 */
		bool m_IsShowCard;                                      /**< 是否显示扑克 */
		bool m_IsReverse;                                       /**< 是否反向显示扑克 */
		int m_angle;                                            /**< 扑克旋转角度 */
		CMolVector<BYTE> m_AutoOut;                              /**< 智能提示的3个位置 */

		HTEXTURE m_CardBackImg;                                 /**< 扑克背面显示图片 */
	};

	//}
//}

#endif
