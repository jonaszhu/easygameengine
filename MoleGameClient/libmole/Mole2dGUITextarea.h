#ifndef _MOLE2D_GUI_TEXTAREA_H_
#define _MOLE2D_GUI_TEXTAREA_H_

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

#define IDD_ITEM_SPACE 2

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUITextarea : public CMolBaseGUIElement
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
			RowStruct(CMolColor col,std::string t)
				: color(col),text(t)
			{
			}

			CMolColor color;            // 这列文字显示的颜色
			std::string text;           // 这列文字显示的文本
		};

		/// 构造函数
		CMolGUITextarea();
		/// 带参数的构造函数
		CMolGUITextarea(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);

		/// 导入指定文本文件
		void LoadStringFromFile(std::string path);
		/// 添加字符串到控件中
		void AddString(std::string text,CMolColor col=CMolColor(255,0,0,0),bool isEnd=true);
		/// 设置是否使用滚动条
		void SetUseScrollBar(bool isuse);
		/// 得到读取的文件文件路径
		inline std::string GetReadFilePath(void) { return m_readfilepath; }
		/// 得到是否使用滚动条
		inline bool IsUseScrollBar(void) { return m_IsUseScrollbar; }
		/// 设置滚动条的宽度
		inline void SetScrollBarWidth(int w) { m_scrollbarWidth = w; }
		/// 得到滚动条的宽度
		inline int GetScrollBarWidth(void) { return m_scrollbarWidth; }
		/// 得到滚动条
		inline CMolGUIScrollBar* GetScrollBar(void) { return m_ScrollBar; }
		/// 得到当前控件可以显示多少行字符
		int GetDisplayLineCount(void);
		/// 清空所有的数据
		void Clear(void);

		/// 画控件
		virtual void Draw();
		/// 用于处理接收到的事件
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// 处理丢失焦点的事件
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		/// 得到指定位置的真实位置
		int GetRealPosWith(std::string text,int pos);
		/// 判断指定字符是否为中文
		bool IsChinese(char c);
		/// 得到当前有多少个字符
		int GetCharCount(std::string text);
		/// 得到从指定位置开始指定长度的字符串
		std::string GetSubString(std::string text,int startpos,int length);

	private:
		std::vector<RowStruct> m_Rows;                /**< 控件显示的文本 */
		int m_curRowIndex;                            /**< 当前显示行索引 */
		int m_scrollbarWidth;                         /**< 滚动条的宽度 */
	    std::string m_readfilepath;                  /**< 要读取的文本文件的路径 */

		bool m_IsUseScrollbar;                        /**< 是否使用滚动条 */

		CMolGUIScrollBar *m_ScrollBar;                /**< 文本显示框的滚动条 */
	};

	//}
//}

#endif
