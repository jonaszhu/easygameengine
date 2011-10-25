#ifndef _MOLE2D_GUI_BUTTON_H_
#define _MOLE2D_GUI_BUTTON_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2009.12.5
*/

#include "Mole2dBaseGUIElement.h"

//namespace mole2d
//{
//namespace graphics
//{

class MOLEXPORT CMolGUIButton : public CMolBaseGUIElement
{
public:
	/** 
	 * 按钮状态
	 */
	enum ButtonState
	{
		STATE_NORMAL = 0,            // 正常状态
		STATE_DOWND,                 // 按下状态
		STATE_HOVERED,               // 鼠标经过状态
		STATE_DISABLED,              // 按钮不可用状态
		STATE_NULL
	};

	/** 
	 * 按钮类型
	 */
	enum ButtonType
	{
		TYPE_SINGLE = 0,             // 单选按钮
		TYPE_MULTIPLE                // 多选按钮
	};

	/// 构造函数
	CMolGUIButton();
	/// 带参数的构造函数
	CMolGUIButton(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		s32 id,std::string caption,CMolRect<s32> rect);

	/// 设置按钮状态
	inline void SetState(ButtonState state)
	{
		m_ButtonState = state;
	}
	/// 得到按钮状态
	inline ButtonState GetState(void)
	{
		return m_ButtonState;
	}
	/// 设置当前控件是否可用
	virtual void SetEnabled(bool enabled);
	/// 设置按钮类型
	inline void SetType(CMolGUIButton::ButtonType type) { m_ButtoneType = type; }
	/// 得到按钮类型
	inline CMolGUIButton::ButtonType GetType(void) { return m_ButtoneType; }
	/// 设置要显示的文字
	inline void SetText(std::string t) { m_Text = t; }
	/// 得到要显示的文字
	inline std::string GetText(void) { return m_Text; }
	/// 设置当前按钮是否被选中
	void SetSelected(bool sel);
	/// 得到当前按钮是否被选中
	inline bool IsSelected(void) { return m_isSelected; }

	/// 画控件
	virtual void Draw();
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// 处理丢失焦点的事件
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	/// 检查鼠标是否在图像区域范围内
	bool CheckMouseInImage(CMolPosition2d<s32> pos);

private:
	ButtonState m_ButtonState;          /**< 按钮状态 */
	ButtonType m_ButtoneType;           /**< 按钮类型 */

	bool m_isSelected;                  /**< 按钮是否被选中，用于处理多选的情况 */

	std::string m_Text;                 /**< 按钮要显示的文字 */
};

////}
//}

#endif
