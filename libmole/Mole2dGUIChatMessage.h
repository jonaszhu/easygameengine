#ifndef _MOLE2D_GUI_CHAT_MESSAGE_H_
#define _MOLE2D_GUI_CHAT_MESSAGE_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.2.3
*/

#include "Mole2dBaseGUIElement.h"
#include "Mole2dBaseFont.h"

#include "Mole2dGUIScrollBar.h"

#include <vector>

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIChatMessage : public CMolBaseGUIElement
	{
	public:
		/** 
		 * 文本框列结构
		 */
		struct RowStruct
		{
			RowStruct()
				: color(CMolColor(255,0,0,0))
			{
			}
			RowStruct(std::string t,CMolColor col=CMolColor(255,0,0,0))
				: color(col),text(t)
			{
			}

			CMolColor color;            // 这列文字显示的颜色
			std::string text;           // 这列文字显示的文本
		};

		/// 构造函数
		CMolGUIChatMessage();
		/// 带参数的构造函数
		CMolGUIChatMessage(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);

		/// 设置文本显示颜色
		inline void SetTextColor(CMolColor col) { m_TextColor = col; }
		/// 得到文本显示颜色
		inline CMolColor GetTextColor(void) { return m_TextColor; }
		/// 设置选择文本后显示的颜色
		inline void SetSelectTextColor(CMolColor col) { m_SelectTextColor = col; }
		/// 得到选择文本后显示的颜色
		inline CMolColor GetSelectTextColor(void) { return m_SelectTextColor; }
		/// 得到滚动条
		CMolGUIScrollBar* GetScrollBar(void) { return m_ScrollBar; }
		/// 建立滚动条
		void CreateScrollBar(void);
		/// 添加字符串到聊天信息提示框中
		void AddString(std::string text);
		/// 取得指定指定索引的字符串
		std::string GetStringByIndex(int index);
		/// 得到当前选择的字符串
		std::string GetSelectString(void);
		/// 设置滚动条的宽度
		inline void SetScrollBarWidth(int w) { m_scrollbarWidth = w; }
		/// 得到滚动条的宽度
		inline int GetScrollBarWidth(void) { return m_scrollbarWidth; }
		/// 得到当前控件可以显示多少行字符
		int GetDisplayLineCount(void);
		/// 重新设置当前控件状态
		void Reset(void);

		/// 画控件
		virtual void Draw();
		/// 用于处理接收到的事件
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// 处理丢失焦点的事件
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		CMolColor m_TextColor;                          /**< 文字显示颜色 */
		CMolColor m_SelectTextColor;                    /**< 选择文本后的颜色 */

		std::vector<RowStruct> m_Rows;                /**< 控件显示的文本 */
		int m_curRowIndex;                            /**< 当前显示行索引 */
		int m_scrollbarWidth;                         /**< 滚动条的宽度 */
		int m_curMouseRowIndex;                         /**< 当前鼠标所在行索引 */

		CMolGUIScrollBar *m_ScrollBar;                  /**< 聊天信息框的滚动条 */
	};

	//}
//}

#endif
