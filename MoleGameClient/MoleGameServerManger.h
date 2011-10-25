#ifndef _MOLE_GAME_SERVER_MANAGER_H_INCLUDE_
#define _MOLE_GAME_SERVER_MANAGER_H_INCLUDE_

#include "defines.h"

#include <string>
#include <vector>
#include <map>

#define IDD_GAME_ROOM_LIST         (WM_USER+600)          // 游戏列表消息
#define IDD_SHOW_GAME_SERVER       (WM_USER+601)          // 显示游戏服务器列表
#define IDD_GET_GAME_RULE          (WM_USER+602)          // 得到游戏规则信息
#define IDD_ENTER_GAME_SERVER      (WM_USER+603)          // 进入游戏服务器

//按钮类
class CRadioButton : public CButton
{
	//变量定义
protected:
	CImage  							m_ImageBack;					//按钮位图
	bool                                m_isCheck;                      

	//函数定义
public:
	//构造函数
	CRadioButton();
	//析构函数
	virtual ~CRadioButton();

	inline void SetCheck(bool check) { m_isCheck = check; }
	inline bool GetCheck(void) { return m_isCheck; }

	//重载函数
protected:
	//控件子类化
	virtual void PreSubclassWindow();
	//界面绘画函数
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:
	//调整位置
	bool FixButtonSize();
	//加载位图
	bool SetButtonImage(LPCTSTR pszFileName, bool bExpandImage=true);

	//消息函数
protected:
	//建立消息
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//鼠标移动
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//鼠标消息
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//鼠标离开
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	//背景消息
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);

	DECLARE_MESSAGE_MAP()
};


/**
 * 游戏参数设置
 */
struct GameParam
{
	GameParam():gameId(0) {}
	GameParam(int gi,std::string gl,std::string gr):gameId(gi),gamelogo(gamerule) {}

	int gameId;           // 游戏ID
	std::string gamelogo; // 游戏logo图片
	std::string gamerule; // 游戏规则图片
};

/** 
 * 按钮状态
 */
enum ButtonState
{
	BTN_STATE_NORMAL = 0,         // 正常
	BTN_STATE_OVER,               // 经过
	BTN_STATE_DOWN,               // 按下
	BTN_STATE_DISABLE             // 无用
};

//按钮类
class CSkinButton : public CButton
{
	//变量定义
protected:
	CImage							m_ImageBack;					//按钮位图
	COLORREF							m_crTextColor;					//字体颜色
	ButtonState                     m_ButtonState;                  //按钮状态

	//函数定义
public:
	//构造函数
	CSkinButton();
	//析构函数
	virtual ~CSkinButton();

	//重载函数
protected:
	//控件子类化
	virtual void PreSubclassWindow();
	//界面绘画函数
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	//设置函数
public:
	//调整位置
	bool FixButtonSize();
	//设置颜色
	bool SetTextColor(COLORREF crTextColor);
	//加载位图
	bool SetButtonImage(LPCTSTR pszFileName, bool bExpandImage=false);
	//默认按钮
	void SetDefaultButton(bool bResetIcon=true, bool bResetColor=true, bool bResetImage=true);

	//查询函数
public:
	//获取颜色
	COLORREF GetButtonColor() { return m_crTextColor; }

	//消息函数
protected:
	//建立消息
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//鼠标移动
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//鼠标离开
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	//背景消息
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinButton)
};

class CGameRoomNode : public CWnd
{
public:
	/** 
	 * 结点类型
	 */
	enum NodeType
	{
		NODETYPE_GAME = 0,          // 游戏
		NODETYPE_SERVER = 1         // 游戏服务器
	};

	/// 构造函数
	CGameRoomNode();
	/// 析构函数
	virtual ~CGameRoomNode();

	/// 设置结点图片参数
	void CreateNode(std::string bgImg,std::string logoImg,std::string enterImg,std::string ruleImg);

	/// 设置结点类型
	inline void SetNodeType(CGameRoomNode::NodeType type) { m_NodeType = type; }
	/// 得到结点类型
	inline CGameRoomNode::NodeType GetNodeType(void) { return m_NodeType; }
	/// 设置结点表示的游戏信息
	inline void SetGameServerInfo(GameServerInfo info) { m_GameServerInfo = info; }
	/// 得到结点表示的游戏信息
	inline GameServerInfo GetGameServerInfo(void) { return m_GameServerInfo; }
	/// 设置规则连接地址
	inline void SetRuleAddress(std::string address) { m_ruleAddress = address; }
	/// 得到规则连接地址
	inline std::string GetRuleAddress(void) { return m_ruleAddress; }
	/// 设置游戏ID
	inline void SetGameId(int gameId) { m_GameId = gameId; }
	/// 得到游戏ID
	inline int GetGameId(void) { return m_GameId; }
	/// 设置是否校正过
	inline void SetRegulate(bool regulate) { m_isRegulate = regulate; }
	/// 检测是否校正过
	inline bool IsRegulate(void) { return m_isRegulate; } 

	//艺术字体
	void DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, LPRECT lpRect);

protected:
	afx_msg void OnPaint();
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	DECLARE_MESSAGE_MAP()

private:
	GameServerInfo m_GameServerInfo;   /**< 结点数据 */
	CImage m_gameLogo;                 /**< 游戏logo图片 */
	CImage m_bgImg;                    /**< 结点背景图片 */
	NodeType m_NodeType;               /**< 结点类型 */
	CSkinButton m_enterBtn;                /**< 进入按钮 */
	CSkinButton m_ruleBtn;                 /**< 规则按钮 */
	std::string m_ruleAddress;             /**< 规则连接地址 */
	int m_GameId;                          /**< 游戏ID */
	bool m_isRegulate;                     /**< 是否已经校正过了 */

	DWORD m_dwWidth;		// mask width
	DWORD m_dwHeight;		// mask height

private:
	HRGN CreateRgnFromFile( HBITMAP hBmp, COLORREF color );
};

class CGameRoomManager : public CWnd
{
public:
	/// 构造函数
	CGameRoomManager();
	/// 析构函数
	virtual ~CGameRoomManager();

	/// 清除所有的房间
	void Clear(void);
	/// 导入房间配置
	bool LoadRoomConfig(std::string configfile);
	/// 得到当前选中游戏ID
	inline int GetCurSelGameID(void) { return m_curSelGameId; }
	/// 插入一个游戏结点到管理器中
	void InsertGameNode(int gameId);
	/// 插入一个服务器结点到管理器中
	void InsertServerNode(GameServerInfo gsf);
	/// 是否显示所有的游戏结点
	void ShowAllGameRoomNodes(int show);
	/// 是否显示指定游戏ID的服务器结点
	void ShowAllGameServerNodes(int gameId,int show);
	/// 清空当前选择
	inline void ClearCurSel(void) { m_curSelGameId = -1; }

	/// 校正游戏结点位置
	void RegulateGameNodes(void);
	/// 校正指定游戏的房间结点位置
	void RegulateGameServerNodes(int gameId);
	/// 显示主游戏列表界面
	void ShowMainGameNodes(void);

protected:
	afx_msg void OnPaint();
	//显示游戏服务器列表
	afx_msg LRESULT OnShowGameServerList(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()
private:
	std::map<int,std::vector<CGameRoomNode*> > m_GameRoomNodes;                /**< 用于保存所有的房间结点 */
	std::map<int,CGameRoomNode*>               m_GameServerNodes;              /**< 房间自己的结点 */

	CSize                                      m_rowlist;                      /**< 房间的行列设置 */
	CSize                                      m_rowlistspace;                 /**< 房间的行列间距 */
	CPoint                                     m_ShowPosition;                 /**< 房间列表的显示位置 */
	CImage                                     m_bgImage;                      /**< 房间显示背景图片 */
	std::string                                m_showbtnimg;                   /**< 显示房间列表按钮图片路径 */
	std::string                                m_enterbtnimg;                  /**< 进入游戏按钮图片路径 */
	std::string                                m_rulebtnimg;                   /**< 规则按钮图片路径 */
	std::string                                m_gamebgimg;                    /**< 游戏结点背景图片 */
	std::string                                m_gameroomimg;                  /**< 游戏房间背景图片 */
	int                                        m_curSelGameId;                 /**< 当前选中游戏ID */

	std::map<int,GameParam>                    m_GameParams;                   /**< 用于保存游戏参数 */
};

#endif
