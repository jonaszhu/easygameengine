#ifndef _MOLE2D_GUI_INFO_SCROLLER_H_
#define _MOLE2D_GUI_INFO_SCROLLER_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.2.3 写于平武,图像控件,用于显示整副图像或图像一部分
*/

#include "Mole2dBaseGUIElement.h"
#include "Mole2dBaseFont.h"

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIInfoScroller : public CMolBaseGUIElement
	{
	public:
		/** 
		 * 信息的滚动方式
		 */
		enum InfoScrType
		{
			SCRTYPE_LEFT_TO_RIGHT = 0,            // 从左到右
			SCRTYPE_RIGHT_TO_LEFT                 // 从右到左
		};

		/// 构造函数
		CMolGUIInfoScroller();
		/// 带参数的构造函数
		CMolGUIInfoScroller(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);

		/// 设置画文字的字体
		inline void SetFont(CMolGUIBaseFont *font)
		{
			m_Font = font;
		}
		/// 得到画文字的字体
		inline CMolGUIBaseFont* GetFont(void)
		{
			return m_Font;
		}
		/// 设置文字大小
		inline void SetSize(int s)
		{
			m_Size = s;
		}
		/// 得到文字大小
		inline int GetSize(void)
		{
			return m_Size;
		}
		/// 设置要显示的文字
		inline void SetText(std::string t)
		{
			m_Text = t;
		}
		/// 得到要显示的文字
		inline std::string GetText(void)
		{
			return m_Text;
		}
		/// 设置文字显示的颜色
		inline void SetColor(CMolColor color)
		{
			m_Color = color;
		}
		/// 得到文字显示的颜色
		inline CMolColor GetColor(void)
		{
			return m_Color;
		}
		/// 设置信息滚动方式
		inline void SetInfoScrType(CMolGUIInfoScroller::InfoScrType type) { m_InfoScrType = type; }
		/// 得到信息滚动方式
		inline CMolGUIInfoScroller::InfoScrType GetInfoScrType(void) { return m_InfoScrType; }

		/// 画控件
		virtual void Draw();
		/// 用于处理接收到的事件
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// 处理丢失焦点的事件
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		CMolGUIBaseFont *m_Font;                        /**< 要画文字的字体 */
		int m_Size;                                     /**< 文字的显示大小 */
		std::string m_Text;                             /**< 要显示的文字 */
		CMolColor m_Color;                              /**< 文字显示的颜色 */
		InfoScrType m_InfoScrType;                      /**< 信息的滚动方向 */

		int m_StartPos,m_ctrlWidth;                     /**< 用于控制控件的显示 */
		CMolPosition2d<s32> m_ctlStartPos;              /**< 控件的开始显示位置 */
		DWORD m_curTime;
	};

	//}
//}

#endif
