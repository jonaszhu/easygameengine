#ifndef _MOLE2D_BASE_GUI_CONTAINER_H_
#define _MOLE2D_BASE_GUI_CONTAINER_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2009.12.1
*/

#include "Mole2dBaseGUIElement.h"

#include "tinyxml/tinyxml.h"

#include <vector>
#include <string>

//namespace mole2d
//{
//namespace graphics
//{

class CMolGUIButton;
class CMolGUIProcessBar;
class CMolGUIImage;
class CMolGUIStatic;
class CMolGUIEditorBox;
class CMolGUIVideo;
class CMolGUIGameCard;
class CMolGUIGameClock;
class CMolGUIGameAnimator;
class CMolGUIInfoScroller;
class CMolGUITextarea;
class CMolGUIScrollBar;
class CMolGUIChatMessage;
class CMolGUIImageListBox;
class CMolGUIMultiButton;
class CMolGUIMultiListBox;
class CMolGUIBiqoQing;
class CMolGUIMoveAnimator;
class CMolGUIDragControl;
class CMolGUIRoomList;
class CMolGUIGameList;
class CMolGUIRadioButton;
class CMolGUIFlash;

class MOLEXPORT CMolBaseGUIContainer : public CMolBaseGUIElement
{
public:
	/// 构造函数
	CMolBaseGUIContainer();
	/// 带参数的构造函数
	CMolBaseGUIContainer(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		s32 id,CMolRect<s32> rect);
	/// 析构函数
	virtual ~CMolBaseGUIContainer();

	/// 设置是否为模式包容器
	virtual void SetModal(bool modal);
	/// 得到是否为模式包容器
	virtual bool IsModal(void) { return isModal; }
	/// 设置是否模式包容器下窗体变暗
	inline void SetBianAn(bool ba) { IsHeiPin = ba; }
	/// 得到是否模式包容器下窗体变暗
	inline bool IsBianAn(void) { return IsHeiPin; }
	/// 设置指定控件的显示状态
	void ShowControlById(int id,bool isShow);
	/// 设置指定控件的使用状态
	void EnableControlById(int id,bool isEnable);
	/// 得到当前焦点控件
	inline CMolBaseGUIElement* GetCurFocusControl(void) { return m_Focus; }
	/// 设置当前焦点控件
	inline void SetCurFocusControl(CMolBaseGUIElement *ctl);
	/// 得到当前激活控件
	inline CMolBaseGUIElement* GetCurActiveControl(void) { return m_Active; }
	/// 设置当前激活控件
	inline void SetCurActiveControl(CMolBaseGUIElement *ctl) { m_Active = ctl; }

	/// 设置当前鼠标是否按下
	inline void SetMousePress(bool p) { isPressed = p; }
	/// 得到当前鼠标是否按下
	inline bool GetMousePress(void) { return isPressed; }
	/// 处理tab事件
	bool OnProcessTabEvent(CMolBaseGUIElement *ctl);

	/// 从配置文件中导入GUI界面
	virtual bool LoadGUIConfig(const char* filepath);
	/// 保存GUI界面
	virtual void SaveGUIConfig(std::string filepath);
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// 画控件
	virtual void Draw();
	/// 处理丢失焦点的事件
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);
	/// 处理鼠标离开游戏主窗口事件
	virtual void OnProcessMouseLeaveFrame(const CMolEvent& event);

	/// 添加一个按钮
	CMolGUIButton* AddButton(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个图像控件
	CMolGUIImage* AddImage(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个flash控件
	CMolGUIFlash* AddFlash(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个滚动条
	CMolGUIProcessBar* AddProcessBar(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个标签控件
	CMolGUIStatic* AddStaticText(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个信息滚动条
	CMolGUIInfoScroller* AddInfoScroller(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个输入框控件
	CMolGUIEditorBox* AddEditorBox(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个视频显示框控件
	CMolGUIVideo* AddVideoBox(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个牌控件
	CMolGUIGameCard* AddGameCard(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个游戏时钟控件
	CMolGUIGameClock* AddGameClock(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个游戏动画控件
	CMolGUIGameAnimator* AddGameAnimator(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// 添加一个文本显示框
	CMolGUITextarea* AddTextarea(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// 添加一个滚动条控件
	CMolGUIScrollBar* AddScrollBar(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// 添加一个聊天信息提示框控件
	CMolGUIChatMessage* AddChatMessage(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// 添加一个图像列表框控件
	CMolGUIImageListBox* AddImageListBox(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// 添加一个多选按钮控件
	CMolGUIMultiButton* AddMultiButton(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// 添加一个多项列表框控件
	CMolGUIMultiListBox* AddMultiListBox(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// 添加一个表情选择控件
	CMolGUIBiqoQing* AddBiaoQingCtrl(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个移动动画控件
	CMolGUIMoveAnimator* AddMoveAnimator(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个拖动滑条控件
	CMolGUIDragControl* AddDragControl(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个房间列表控件
	CMolGUIRoomList* AddRoomListCtl(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个游戏列表控件
	CMolGUIGameList* AddGameListCtl(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// 添加一个单选按钮控件
	CMolGUIRadioButton* AddRadioButton(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// 添加一个包容器
	CMolBaseGUIContainer* AddContainer(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent,bool isVisible=false);

protected:
	/// 传送一个事件到系统中
	virtual bool postEventFromUser(const CMolEvent& event);
	/// 导入指定容器下所有子结点
	bool LoadControlsFromTheNode(CMolBaseGUIContainer *pRoot,TiXmlElement *pNode);
	/// 用于分解指定字符串为不同的参数
	int ParseStringToParameter(std::string str,std::string chr=";");

protected:
	bool isModal;                  /**< 是否模式包容器 */
	bool IsHeiPin;                 /**< 是否在模式包容器下窗口变暗 */

	CMolBaseGUIElement *m_Focus;                     /**< 当前焦点控件 */
	CMolBaseGUIElement *m_Active;                    /**< 当前激活控件 */
	CMolBaseGUIElement *m_CurScrollBar;              /**< 对滚动条进行特殊处理，以便于能在任何地方都能操作滚动条 */	

	std::vector<std::string>  m_Parameters;                        /**< 要分解的参数 */

	CMolGUIRoomList            *m_MainRoomList;                               /**< 房间列表 */

private:
	bool isPressed;                /**< 鼠标是否按下 */
	CMolPosition2d<s32> m_OldPosition;            /**< 老的鼠标位置 */
};

//}
//}

#endif