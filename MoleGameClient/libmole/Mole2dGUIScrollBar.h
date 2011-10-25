#ifndef _MOLE2D_GUI_SCROLL_BAR_H_
#define _MOLE2D_GUI_SCROLL_BAR_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.2.1
*/

#include "Mole2dBaseGUIElement.h"

#include "Mole2dGUIButton.h"

//namespace mole2d
//{
	//namespace graphics
	//{

		/** 
		 * 滑动块结构
		 */
		class MyScrollBar
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

			/// 构造函数
			MyScrollBar();
			/// 析构函数
			~MyScrollBar();

			/// 设置滑动块的显示范围
			inline void SetRect(CMolRect<s32> pRect) { rect = pRect; }
			/// 得到滑动块的显示范围
			inline CMolRect<s32> GetRect(void) { return rect; }
			/// 设置滑动块使用的纹理
			inline void SetTexture(HTEXTURE t) { tex = t; }
			/// 得到滑动块使用的纹理
			inline HTEXTURE GetTexture(void) { return tex; }
			/// 得到滑动块的移动间隔
			inline int GetMoveSpace(void) { return m_MoveSpace; }

			/// 显示滑动条
			void Draw(CMolBaseFrame* driver);
			/// 处理鼠标事件
			void OnProcessMouse(const CMolEvent& event);
			/// 处理鼠标丢失的事件
			void OnProcessLostFocusEvent(const CMolEvent& event);

		private:
			CMolRect<s32> rect;         // 滑动块的范围
			HTEXTURE tex;               // 滑动块的图片
			ButtonState mButtonState;   // 滑动块的状态

			int  m_MoveSpace;           /**< 滚动条移动的间隔 */
		};

		class MOLEXPORT CMolGUIScrollBar : public CMolBaseGUIElement
		{
		public:
			/// 构造函数
			CMolGUIScrollBar();
			/// 带参数的构造函数
			CMolGUIScrollBar(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
				s32 id,std::string caption,CMolRect<s32> rect);
			virtual ~CMolGUIScrollBar();

			/// 设置向上的按钮图片
			void SetUpBtnImg(std::string path);
			/// 得到向上的按钮图片
			inline std::string GetUpBtnImg(void) { return m_UpButtonImg; }
			/// 设置向下的按钮图片
			void SetDownButtonImg(std::string path);
			/// 得到向下的按钮图片
			inline std::string GetDownButtonImg(void) { return m_DownButtonImg; }
			/// 设置滑动块使用的图片
			void SetScrollBarImg(std::string path);
			/// 得到滑动块使用的图片
			inline std::string GetScrollBarImg(void) { return m_ScrollBarImg; }
			/// 设置滚动条的最大值
			inline void SetMaxValue(int value);
			/// 得到滚动条的最大值
			inline int GetMaxValue(void) { return m_MaxValue; }
			/// 设置滚动条的当前值
			void SetCurValue(int value);
			/// 得到滚动条的当前值
			inline int GetCurValue(void) { return m_CurValue; }
			/// 设置页面数
			inline void SetPageCount(int count) { m_PageCount = count; }
			/// 得到页面数
			inline int GetPageCount(void) { return m_PageCount; }
			/// 设置控件背面颜色
			inline void SetBackgroundColor(CMolColor col) { m_bgColor = col; }
			/// 得到控件背面颜色
			inline CMolColor GetBackgroundColor(void) { return m_bgColor; }
			/// 得到向上按钮
			inline CMolGUIButton* GetUpButton(void) { return m_UpButton; }
			/// 得到向下按钮
			inline CMolGUIButton* GetDownButton(void) { return m_DownButton; }
			/// 设置是否可以移动滚动条
			inline void SetMoveScrollBar(bool isMove) { m_isMoving = isMove; }
			/// 得到是否可以移动滚动条
			inline bool IsMoveScrollBar(void) { return m_isMoving; }

			/// 画控件
			virtual void Draw();
			/// 用于处理接收到的事件
			virtual bool OnProcessEvent(const CMolEvent& event);
			/// 处理丢失焦点的事件
			virtual void OnProcessLostFocusEvent(const CMolEvent& event);
			/// 移动控件到指定的位置
			virtual void Move(CMolPosition2d<int> pos);

		private:
			/// 显示滑动条
			void DrawScrollbar(CMolBaseFrame* driver);
			/// 拖动滚动条
			void MoveScrollBar(void);

		private:
			std::string m_UpButtonImg;                  /**< 向上的按钮图片 */
			std::string m_DownButtonImg;                /**< 向下的按钮图片 */
			std::string m_ScrollBarImg;                 /**< 滑动块使用的图片 */
			int m_UpButtonHeight;                       /**< 向上按钮的高度 */
			int m_MaxValue,m_CurValue;                  /**< 设置滚动条的最大值和当前值 */
			int m_PageCount;                            /**< 设置每页显示数量 */
			CMolColor m_bgColor;                        /**< 滚动条要显示的背景颜色 */

			DWORD m_curTime;                            /**< 用于控制滚动速度 */

			bool m_isMoving;                            /**< 是否移动滚动条 */
			bool m_BtnDown;                             /**< 移动按钮是否按下 */
			int  m_BtnDownIndex;                        /**< 当前按钮点击类型 */

			CMolGUIButton *m_UpButton;                  /**< 向上按钮 */
			CMolGUIButton *m_DownButton;                /**< 向下按钮 */
			MyScrollBar m_MyScrollBar;                  /**< 滑动块 */
		};

	//}
//}

#endif
