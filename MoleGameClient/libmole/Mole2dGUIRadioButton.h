#ifndef _GUI_RADIO_BUTTON_H_
#define _GUI_RADIO_BUTTON_H_

#include "Mole2dBaseGUIElement.h"

/** 
 * 选择按钮状态
 */
enum CMolRButtonState
{
	STATE_NORMAL = 0,                // 选择后的状态
	STATE_SELECTED                   // 正常的状态
};

class MOLEXPORT CMolGUIRadioButton : public CMolBaseGUIElement
{
public:
	/// 构造函数
	CMolGUIRadioButton();
	/// 带参数的构造函数
	CMolGUIRadioButton(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,std::string caption,CMolRect<int> rect);
	virtual ~CMolGUIRadioButton();

	/// 设置按钮状态
	inline void SetButtonState(CMolRButtonState state) { m_BtnState = state; }
	/// 得到按钮状态
	inline CMolRButtonState GetButtonState(void) { return m_BtnState; }

	/// 画控件
	virtual void Draw();
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// 处理丢失焦点的事件
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	CMolRButtonState m_BtnState;                          /**< 按钮状态 */
};

#endif
