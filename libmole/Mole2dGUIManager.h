#ifndef _MOLE2D_GUI_MANAGER_H_
#define _MOLE2D_GUI_MANAGER_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2009.11.21
*/

#include "Mole2dBaseGUIContainer.h"

namespace mole2d
{
//namespace graphics
//{

class MOLEXPORT CMolGUIManager : public CMolBaseGUIContainer
{
public:
	/// 构造函数
	CMolGUIManager();
	/// 带参数的构造函数
	CMolGUIManager(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		s32 id,CMolRect<s32> rect);
	/// 析构函数
	virtual ~CMolGUIManager();

	/// 设置指定控件的显示状态
	void ShowControlById(int id,bool isShow);
	/// 设置指定控件的使用状态
	void EnableControlById(int id,bool isEnable);

	/// 画控件
	virtual void Draw();

protected:
	/// 传送一个事件到系统中
	virtual bool postEventFromUser(const CMolEvent& event);

protected:
	CMolBaseGUIElement *m_Focus;                     /**< 当前焦点控件 */
	CMolBaseGUIElement *m_Active;                    /**< 当前激活控件 */
};

//}
}

#endif