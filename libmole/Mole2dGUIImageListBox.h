#ifndef _MOLE2D_GUI_IMAGE_LIST_BOX_H_
#define _MOLE2D_GUI_IMAGE_LIST_BOX_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.2.3
*/

#include "Mole2dBaseGUIElement.h"
#include "Mole2dBaseFont.h"

#include "Mole2dGUIScrollBar.h"
#include "Mole2dGUIImage.h"

#include <vector>

#define IDD_LIST_BOX_SPACE 6
#define IDD_LIST_BOX_MOVE_SPACE 5

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIImageListBox : public CMolBaseGUIElement
	{
	public:
		/**
		 * 文本框中字体结构
		 */
		struct RowFontStruct
		{
			RowFontStruct()
				: color(CMolColor(255,255,255,255))
			{
			}
			RowFontStruct(std::string t,CMolColor col=CMolColor(255,255,255,255))
				: color(col),text(t)
			{
			}

			CMolColor color;            // 这列文字显示的颜色
			std::string text;           // 这列文字显示的文本
		};

		/** 
		 * 文本框列结构
		 */
		struct RowStruct
		{
			RowStruct()
				: image(NULL)
			{
			}
			RowStruct(CMolRect<s32> r,std::string path)
				: imgPath(path),rect(r),image(NULL)
			{
			}

			/// 添加一个字符串到文本框中
			void AddString(std::string text,CMolColor col=CMolColor(255,255,255,255))
			{
				TextRows.push_back(RowFontStruct(text,col));
			}

			CMolRect<s32> rect;                    // 文本框的显示范围
			std::string imgPath;                   // 文本框图片路径
			CMolGUIImage *image;                   // 要显示的图片
			CMolPosition2d<s32> startPos;          // 控件的开始初始位置
			std::vector<RowFontStruct> TextRows;     // 文本框中的字体数组
		};

		/// 构造函数
		CMolGUIImageListBox();
		/// 带参数的构造函数
		CMolGUIImageListBox(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);
		/// 析构函数
		virtual ~CMolGUIImageListBox();

		/// 设置控件的背景颜色
		inline void SetBgColor(CMolColor col) { m_BgColor = col; }
		/// 得到控件的背景颜色
		inline CMolColor GetBgColor(void) { return m_BgColor; }
		/// 设置控件的初始显示图片
		inline void SetDefaultImage(std::string path) { m_DefaultImage = path; }
		/// 得到控件的初始显示图片
		inline std::string GetDefaultImage(void) { return m_DefaultImage; }
		/// 设置滚动条的宽度
		inline void SetScrollBarWidth(int w) { m_scrollbarWidth = w; }
		/// 得到滚动条的宽度
		inline int GetScrollBarWidth(void) { return m_scrollbarWidth; }
		/// 设置选中后显示的颜色
		inline void SetSelectColor(CMolColor col) { m_SelectColor = col; }
		/// 得到选中后显示的颜色
		inline CMolColor GetSelectColor(void) { return m_SelectColor; }
		/// 得到滚动条
		inline CMolGUIScrollBar* GetScrollBar(void) { return m_ScrollBar; }
		/// 建立滚动条
		void CreateScrollBar(void);
		/// 设置图片的高宽
		inline void SetImageSize(CMolDimension2d<s32> size) { m_imageSize = size; }
		/// 得到图片的高宽
		CMolDimension2d<s32> GetImageSize(void) { return m_imageSize; }
		/// 得到当前控件可以显示多少行字符
		int GetDisplayLineCount(void);
		/// 添加一个图片到列表框中
		void AddImageToListBox(std::string path);
		/// 添加指定的文字到指定的行中
		void AddTextToListBox(int index,std::string text,CMolColor col=CMolColor(255,255,255,255));
		/// 得到当前列表框中有多少行
		inline int GetTotalRows(void) { return (int)m_Rows.size(); }
		/// 清空所有的列
		void ClearAllRows(void);
		/// 得到当前选择行索引
		inline int GetCurrentSelected(void) { return m_curMouseRowIndex; }
		/// 得到指定索引的图片路径
		std::string GetImageByIndex(int index);
		/// 得到指定索引指定行的文本
		std::string GetStringByIndex(int rowIndex,int tIndex);

		/// 画控件
		virtual void Draw();
		/// 用于处理接收到的事件
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// 处理丢失焦点的事件
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);
		/// 移动控件到指定的位置
		virtual void Move(CMolPosition2d<int> pos);

	private:
		/// 绘制所有的文本
		void DrawAllRows(CMolBaseFrame* driver);
		/// 得到所有图片的显示位置
		void GetImagesPosition();
		/// 得到当前总共有多少个文本
		int GetTotalLineCount(void);
		/// 从指定坐标开始显示所有文本
		void DrawAllImages(CMolPosition2d<s32> position);

	private:
		CMolColor m_BgColor;                          /**< 背景颜色 */
		CMolColor m_SelectColor;                      /**< 选择后显示的颜色 */
		int m_scrollbarWidth;                         /**< 滚动条的宽度 */
		CMolDimension2d<s32> m_imageSize;             /**< 图片显示的高宽 */
		int m_curRowIndex;                            /**< 当前显示行索引 */
		int m_curMouseRowIndex;                       /**< 当前鼠标经过那一行文本 */ 
		std::string m_DefaultImage;                   /**< 初始的显示图片，如果图片加载失败，就显示这个图片 */

		std::vector<RowStruct*> m_Rows;               /**< 控件显示的文本 */

		CMolGUIScrollBar *m_ScrollBar;                /**< 文本显示框的滚动条 */
	};

	//}
//}

#endif
