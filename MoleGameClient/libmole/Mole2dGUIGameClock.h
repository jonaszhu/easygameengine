#ifndef _MOLE2D_GUI_GAME_CLOCK_H_
#define _MOLE2D_GUI_GAME_CLOCK_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.2.3 写于平武,图像控件,用于显示整副图像或图像一部分
*/

#include "Mole2dBaseGUIElement.h"

#include <vector>
#include <string>

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIGameClock : public CMolBaseGUIElement
	{
	public:
		/** 
		* 时钟的对齐方式
		*/
		enum ClockSnapType
		{
			CLOCK_SNAP_LEFT = 0,                   // 居左
			CLOCK_SNAP_CENTER,                     // 居中
			CLOCK_SNAP_RIGHT                       // 居右
		};

		/// 构造函数
		CMolGUIGameClock();
		/// 带参数的构造函数
		CMolGUIGameClock(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);

		/// 设置时钟控件数字用到的图片
		inline void SetClockNumImg(HTEXTURE tex) { m_clocknumtex = tex; }
		/// 得到时钟控件数字用到的图片
		inline HTEXTURE GetClockNumImg(void) { return m_clocknumtex; }
		/// 设置时钟控件显示的数字
		void SetClockNum(int num);
		/// 得到时钟控件显示的数字
		inline int GetClockNum(void) { return m_DefaultNum; }
		/// 设置时钟控件的对齐方式
		inline void SetSnapType(CMolGUIGameClock::ClockSnapType type) { m_ClockSnapType = type; }
		/// 得到时钟控件的对齐方式
		inline CMolGUIGameClock::ClockSnapType GetSnapType(void) { return m_ClockSnapType; }
		/// 设置时钟控件数字之间的显示间隔
		inline void SetNumSpace(int space) { m_NumSpace = space; }
		/// 得到时钟控件数字之间的显示间隔
		inline int GetNumSpace(void) { return m_NumSpace; }

		/// 画控件
		virtual void Draw();
		/// 用于处理接收到的事件
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// 处理丢失焦点的事件
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		/// 在指定位置显示自定义数字
		void DrawGameClockNum(CMolPosition2d<s32> pos);

	private:
		HTEXTURE m_clocknumtex;                            /**< 时钟控件数字用到的图片 */
		int m_DefaultNum;                                  /**< 时钟控件显示的数字 */
		int m_NumSpace;                                    /**< 数字之间的显示间隔 */
		ClockSnapType m_ClockSnapType;                     /**< 时钟控件的对齐方式 */

		int m_DisNums[100];                                /**< 要显示的数字 */
		int m_numcount;                                    /**< 当前显示个数 */
	};

	//}
//}

#endif
