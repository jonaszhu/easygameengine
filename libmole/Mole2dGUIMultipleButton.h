#ifndef _MOLE2D_GUI_MULTIPLE_BUTTON_H_
#define _MOLE2D_GUI_MULTIPLE_BUTTON_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2009.12.5
*/

#include "Mole2dBaseGUIElement.h"

#include "Mole2dGUIButton.h"

#include <vector>

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIMultiButton : public CMolBaseGUIElement
	{
	public:
		/// 构造函数
		CMolGUIMultiButton();
		/// 带参数的构造函数
		CMolGUIMultiButton(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			s32 id,std::string caption,CMolRect<s32> rect);
		/// 析构函数
		virtual ~CMolGUIMultiButton();

		/// 设置显示方向
		inline void SetDirection(DirectionType dir) { m_DirectionType = dir; }
		/// 得到显示方向
		inline DirectionType GetDirection(void) { return m_DirectionType; }
		/// 添加一个按钮到多选按钮中
		void AddButton(std::string btnpath);
		/// 设置初始选中选项
		inline void SetDefSelectedItem(int item) 
		{ 
			m_DefaultSelected = item; 
			m_CurSelected = m_DefaultSelected;
		}
		/// 得到初始选中选项
		inline int GetDefSelectedItem(void) { return m_DefaultSelected; }
		/// 得到当前选中索引
		inline int GetCurSelectedItem(void) { return m_CurSelected; }

		/// 画控件
		virtual void Draw();
		/// 用于处理接收到的事件
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// 处理丢失焦点的事件
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		/// 得到所有按钮的显示位置
		void GetButtonsDisPos(void);
		/// 选中指定的按钮
		void SelectButton(CMolGUIButton* btn);

	private:
		std::vector<CMolGUIButton*> m_ButtonList;             /**< 用于保持所有的按钮组 */
		DirectionType m_DirectionType;                        /**< 多选按钮的方向 */
		int m_DefaultSelected;                                /**< 初始选中选项 */
		int m_CurSelected;                                    /**< 当前选中项 */
	};

	//}
//}

#endif
