#ifndef _GUI_GAME_LIST_H_
#define _GUI_GAME_LIST_H_

#include "Mole2dBaseGUIElement.h"

#include "Mole2dGUIButton.h"

#include <vector>
#include <map>

class CMolGUIGameList;

/** 
 * 游戏规则
 */
struct CMolGameRule
{
	CMolGameRule()
		: Id(0)
	{}
	CMolGameRule(int pId,std::string pName,std::string pBgImg,std::string pEnterImg,std::string pRuleImg,std::string pRuleAddress)
		: Id(pId),Name(pName),bgImg(pBgImg),enterImg(pEnterImg),ruleImg(pRuleImg),ruleaddress(pRuleAddress)
	{}

	int Id;                  // 游戏ID
	std::string Name;       // 游戏名称
	std::string bgImg;      // 游戏的标志图片
	std::string enterImg;   // 游戏进入按钮图片
	std::string ruleImg;    // 游戏规则按钮图片
	std::string ruleaddress; // 游戏规则网址
};

/** 
 * 游戏房间结构
 */
class CMolGameRoom
{
public:
	/// 构造函数
	CMolGameRoom(CMolGUIGameList *gl,int index);
	/// 析构函数
	~CMolGameRoom();

	/// 设置游戏ID
	inline void SetGameID(int gameId) { m_gameId = gameId; }
	/// 得到游戏ID
	inline int GetGameID(void) { return m_gameId; }
	/// 设置游戏名称
	inline void SetGameName(std::string name) { m_gameName = name; }
	/// 得到游戏名称
	inline std::string GetGameName(void) { return m_gameName; }
	/// 设置游戏规则要打开的网址
	inline void SetGameRuleAddress(std::string address) { m_gameruleaddress = address; }
	/// 得到游戏规则要打开的网址
	inline std::string GetGameRuleAddress(void) { return m_gameruleaddress; }
	/// 设置游戏图片
	inline void SetGameImage(HTEXTURE tex) { m_gamebgimg = tex; }
	/// 设置游戏显示的区域
	inline void SetGameRect(CMolRect<s32> rect) { m_gameRect = rect; }
	/// 得到游戏显示的区域
	inline CMolRect<s32> GetGameRect(void) { return m_gameRect; }
	/// 设置游戏进入按钮偏移
	inline void SetGameEnterBtnOffset(CMolDimension2d<s32> offset) { m_gameenterbtnoffset = offset; }
	/// 得到游戏进入按钮偏移
	inline CMolDimension2d<s32> GetGameEnterBtnOffset(void) { return m_gameenterbtnoffset; }
	///设置游戏规则按钮偏移
	inline void SetGameRuleBtnOffset(CMolDimension2d<s32> offset) { m_gamerulebtnoffset = offset; }
	///得到游戏规则按钮偏移
	inline CMolDimension2d<s32> GetGameRuleBtnOffset(void) { return m_gamerulebtnoffset; }
	/// 设置游戏进入按钮
	void SetGameEnterBtn(std::string imgpath);
	/// 设置游戏规则按钮
	void SetGameRuleBtn(std::string imgpath);
	/// 得到游戏进入按钮
	inline CMolGUIButton* GetBtnGameEnter(void) { return m_gameenterbtn; }
	/// 得到游戏规则按钮
	inline CMolGUIButton* GetBtnGameRule(void) { return m_gamerulebtn; }
	/// 设置游戏是否显示
	void SetVisible(bool isVisible);
	/// 得到游戏是否显示
	inline bool IsVisible(void) { return m_isVisible; }

	/// 显示房间
	void Draw(CMolBaseFrame *pdriver);

private:
	int               m_gameId;                       /**< 游戏ID */
	std::string      m_gameName;                     /**< 游戏名称 */
	std::string      m_gameruleaddress;              /**< 游戏规则网址 */
	CMolRect<s32>	  m_gameRect;                     /**< 游戏的显示区域 */
	HTEXTURE          m_gamebgimg;                    /**< 游戏背景图片 */
	CMolGUIButton     *m_gameenterbtn;                /**< 游戏进入按钮 */
	CMolGUIButton     *m_gamerulebtn;                 /**< 游戏规则按钮 */

	CMolDimension2d<s32> m_gameenterbtnoffset;        /**< 游戏进入按钮偏移（相对于左上角） */
	CMolDimension2d<s32> m_gamerulebtnoffset;         /**< 游戏规则按钮偏移（相对于左上角） */
	CMolGUIGameList   *m_gamelist;                    /**< 游戏列表控件 */
	bool              m_isVisible;                    /**< 是否显示游戏 */
	int               m_gameIndex;                    /**< 游戏在列表中的索引 */
};

class MOLEXPORT CMolGUIGameList : public CMolBaseGUIElement
{
public:
	/// 构造函数
	CMolGUIGameList();
	/// 带参数的构造函数
	CMolGUIGameList(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		s32 id,std::string caption,CMolRect<s32> rect);
	/// 析构函数
	virtual ~CMolGUIGameList();

	/// 设置游戏显示的行和列
	inline void SetGameRowAndList(CMolDimension2d<s32> size) { m_gameRowList = size; }
	/// 得到游戏显示的行和列
	inline CMolDimension2d<s32> GetGameRowAndList(void) { return m_gameRowList; }
	/// 导入游戏规则
	void LoadGameRule(std::string configpath);
	/// 添加一个偏移到游戏列表中
	inline void AddGameOffset(CMolDimension2d<s32> offset) { m_gameoffsets.push_back(offset); }
	/// 添加一个游戏到游戏列表中
	void AddGameToList(int gameId);
	/// 检测指定按钮是否是规则按钮
	int IsRuleButton(CMolGUIButton *btn);
	/// 检测指定按钮是否是进入按钮
	int IsEnterButton(CMolGUIButton *btn);
	/// 得到指定索引的游戏
	CMolGameRoom* GetGameByIndex(int index);	
	/// 得到当前选中的游戏
	inline CMolGameRoom* GetGameSelected(void) { return GetGameByIndex(m_selectedGame); }
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
	CMolDimension2d<s32> m_gameRowList;                /**< 游戏显示的行和列 */
	std::map<int,CMolGameRule> m_gamerules;            /**< 游戏规则 */
	std::vector<CMolDimension2d<s32> > m_gameoffsets;   /**< 游戏中进入按钮，规则按钮的偏移 */
	std::vector<CMolGameRoom*> m_gamelist;              /**< 游戏房间列表 */
	int m_curRoomIndex;                                /**< 当前房间索引 */
	int m_selectedGame;                                /**< 当前选中的房间和椅子索引 */
};

#endif
