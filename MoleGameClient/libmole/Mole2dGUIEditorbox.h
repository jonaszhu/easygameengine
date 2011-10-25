#ifndef _MOLE2D_GUI_EDITOR_BOX_H_
#define _MOLE2D_GUI_EDITOR_BOX_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.2.4
*/

#include "Mole2dBaseGUIElement.h"

//namespace mole2d
//{
	//namespace graphics
	//{

		class MOLEXPORT CMolGUIEditorBox : public CMolBaseGUIElement
		{
		public:
			/// 构造函数
			CMolGUIEditorBox();
			/// 带参数的构造函数
			CMolGUIEditorBox(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
				s32 id,std::string caption,CMolRect<s32> rect);

			/// 设置要显示的文字
			void SetText(std::string t);
			/// 得到要显示的文字
			inline std::string GetText(void)
			{
				return m_Text;
			}
			/// 设置要提示的文字
			inline void SetTipText(std::string text) { m_TipText = text; }
			/// 得到要提示的文字
			inline std::string GetTipText(void) { return m_TipText; }
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
			/// 设置文字的最大个数
			inline void SetMaxCount(int max)
			{
				m_maxcount = max;
			}
			/// 得到文字的最大个数
			inline int GetMaxCount(void)
			{
				return m_maxcount;
			}
			/// 设置是否为密码框
			inline void SetIsPassword(bool password) { m_isPassword = password; }
			/// 得到是否为密码框
			inline bool IsPassword(void) { return m_isPassword; }

			/// 画控件
			virtual void Draw();
			/// 用于处理接收到的事件
			virtual bool OnProcessEvent(const CMolEvent& event);
			/// 处理丢失焦点的事件
			virtual void OnProcessLostFocusEvent(const CMolEvent& event);
			/// 设置当前控件是否得到焦点
			virtual void SetFocus(bool focus);

		protected:
			/// 用于处理IME消息
			bool processIme(const CMolEvent& event);
			/// 用于处理鼠标消息
			bool processMouse(const CMolEvent& event);
			/// 用于处理按键消息
			bool processKey(const CMolEvent& event);
			/// 添加一段新的文本到编辑框中
			void inputString(std::string str);
			/// 计算当前的滚动坐标
			int calculateScrollPos();
			/// 计算当前光标显示坐标
			void calculateCursorPos(void);
			/// 判断指定字符是否为中文
			bool IsChinese(char c);
			/// 得到从指定位置开始指定长度的字符串
			std::string GetSubString(int startpos,int length);
			/// 在指定位置显示输入符号
			void DisplayInputSymbol(CMolPosition2d<s32> pos);
			/// 得到指定位置的真实位置
			int GetRealPosWith(int pos);
			/// 根据字符的真实位置得到字符在字符串中的索引
			int GetIndexWidth(int pos);
			/// 得到当前有多少个字符
			int GetCharCount(void);
			/// 得到指定字符串有多少个字符
			int GetCharCountFromString(std::string str);
			/// 得到当前页面显示多少个字符
			int GetChrCountPage(bool isstart=true);

		private:
			std::string m_Text;                             /**< 要显示的文字 */
			std::string m_TipText;                          /**< 提示的文字 */
			CMolColor m_Color;                              /**< 文字显示的颜色 */
			int m_startpos;                                 /**< 文字的字符开始位置 */
			int m_startIndex;                               /**< 文字在字符串中的索引 */
			int m_cursorStringIndex;                        /**< 光标在文字中的索引 */
			int m_cursorpos;                                /**< 光标位置 */
			int m_maxcount;                                 /**< 设置文字的最大个数 */

			std::string m_TempStr;                          /**< 用户刚刚输入的字符串 */
			MOLIME_EVENT_TYPE m_TempType;                   /**< 用于刚刚输入字符串的方式 */
			bool m_isPassword;                              /**< 是否是密码框 */

			DWORD m_curTime,m_TimeSpace;                    /**< 用于控制输入符号的显示 */
			CMolPosition2d<s32> m_inputpos;                 /**< 输入符号的显示位置 */
		};

	//}
//}

#endif
