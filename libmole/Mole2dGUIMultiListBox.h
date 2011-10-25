#ifndef _MOLE2D_GUI_MULTI_LISTBOX_H_
#define _MOLE2D_GUI_MULTI_LISTBOX_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2009.12.5
*/

#include "Mole2dBaseGUIElement.h"

#include "Mole2dRect.h"
#include "Mole2dGUIScrollBar.h"
#include "Mole2dGUIProcessBar.h"

#include <vector>

#define IDD_LIST_BOX_MOVE_SPACE 5
#define IDD_LIST_HEADER_HEIGHT 20
#define IDD_LIST_ROW_HEIGHT 22
#define IDD_LIST_PROCESSBAR_SPACE 3

//namespace mole2d
//{
//namespace graphics
//{

class MOLEXPORT CMolGUIMultiListBox : public CMolBaseGUIElement
{
public:
	/**
	 * 列表头结构
	 */
	struct LBHeader
	{
		LBHeader()
			: caption(""),tex(0),width(0)
		{		
		}
		LBHeader(std::string c,int w,HTEXTURE t)
			: caption(c),tex(t),width(w)
		{
		}

		CMolRect<s32> rect;                 // 范围
		int width;                          // 列表头的宽度
		std::string caption;                // 标题 
		HTEXTURE tex;                       // 纹理
	};

	/** 
	 * 文本框列结构
	 */
	struct RowStruct
	{
		RowStruct()
			: processbar(NULL),sortId(0)
		{
		}

		int sortId;                              // 用于排序的ID
		CMolRect<s32> rect;                      // 文本框的显示范围
		std::vector<HTEXTURE> texList;           // 要显示的一组图片
		std::string  text;                       // 要显示的文字
		CMolGUIProcessBar *processbar;           // 进度条
	};

	/// 构造函数
	CMolGUIMultiListBox();
	/// 带参数的构造函数
	CMolGUIMultiListBox(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		s32 id,std::string caption,CMolRect<s32> rect);
	/// 析构函数
	virtual ~CMolGUIMultiListBox();

	/// 得到滚动条
	inline CMolGUIScrollBar* GetScrollBar(void) { return m_ScrollBar; }
	/// 建立滚动条
	void CreateScrollBar(void);
	/// 设置滚动条的宽度
	inline void SetScrollBarWidth(int w) { m_scrollbarWidth = w; }
	/// 得到滚动条的宽度
	inline int GetScrollBarWidth(void) { return m_scrollbarWidth; }
	/// 得到当前控件可以显示多少行字符
	int GetDisplayLineCount(void);

	/// 设置是否排序
	inline void SetIsSort(bool sort) { m_HeaderIsMouse = sort; }
	/// 得到是否排序
	inline bool IsSort(void) { return m_HeaderIsMouse; }
	/// 设置列表头所使用的纹理
	void SetHeaderImage(std::string path);
	/// 得到列表头所使用的纹理
	inline std::string GetHeaderImage(void) { return m_headerImagePath; }
	/// 添加一个列表头
	void AddHeader(std::string caption,int width);
	/// 设置列表头显示信息
	inline void SetHeaderMessage(std::string mes) { m_HeaderMessage = mes; }
	/// 得到列表头显示信息
	inline std::string GetHeaderMessage(void) { return m_HeaderMessage; }
	/// 设置列表头背景颜色
	inline void SetHeaderBgColor(CMolColor col) { m_HeaderBgColor = col; }
	/// 得到列表头背景颜色
	inline CMolColor GetHeaderBgColor(void) { return m_HeaderBgColor; }
	/// 设置列表头文字颜色
	inline void SetHeaderTextColor(CMolColor col) { m_HeaderTextColor = col; }
	/// 得到列表头文字颜色
	inline CMolColor GetHeaderTextColor(void) { return m_HeaderTextColor; }

	/// 设置进度条提示字体颜色
	inline void SetProTipColor(CMolColor col) { m_tipColor = col; }
	/// 得到进度条提示字体颜色
	inline CMolColor GetProTipColor(void) { return m_tipColor; }
	/// 设置进度条第一张图片
	void SetBgImageOne(std::string path);
	/// 得到进度条第一张图片
	inline std::string GetBgImageOne(void) { return m_BgImageOnePath; }
	/// 设置进度条第二张图片
	void SetBgImageTwo(std::string path);
	/// 得到进度条第二张图片
	inline std::string GetBgImageTwo(void) { return m_BgImageTwoPath; }
	/// 设置进度条第三张图片
	void SetBgImageThree(std::string path);
	/// 得到进度条第三张图片
	inline std::string GetBgImageThree(void) { return m_BgImageThreePath; }
	/// 设置进度条第四张图片
	void SetBgImageFour(std::string path);
	/// 得到进度条第四张图片
	inline std::string GetBgImageFour(void) { return m_BgImageFourPath; }

	/// 清除所有的列数据
	void ClearAllRows(void);
	/// 建立新的一行
	int CreateNewRow(void);
	/// 添加指定行指定列指定的字符串
	void AddText(std::string text,int sortId,int row,int list);
	/// 添加图片到指定行指定列中
	void AddImage(std::string path,int sortId,int row,int list);
	/// 添加进度条到指定行指定列中
	void AddProcessBar(int cur,int max,int sortId,int row,int list);

	/// 得到当前选中项索引
	inline int GetSelectedItem(void) { return m_curSeletecRowIndex; }
	/// 设置背景颜色
	inline void SetBgColor(CMolColor col) { m_bgColor = col; }
	/// 得到背景颜色
	inline CMolColor GetBgColor(void) { return m_bgColor; }
	/// 设置字体颜色
	inline void SetTextColor(CMolColor col) { m_TextColor = col; }
	/// 得到字体颜色
	inline CMolColor GetTextColor(void) { return m_TextColor; }
	/// 设置选择的颜色
	inline void SetSelectColor(CMolColor col) { m_SelectColor = col; }
	/// 得到选择的颜色
	inline CMolColor GetSelectColor(void) { return m_SelectColor; }
	/// 设置选择后的颜色
	inline void SetSelectedColor(CMolColor col) { m_SelectedColor = col; }
	/// 得到选择后的颜色
	inline CMolColor GetSelectedColor(void) { return m_SelectedColor; }

	/// 画控件
	virtual void Draw();
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// 处理丢失焦点的事件
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);
	/// 移动控件到指定的位置
	virtual void Move(CMolPosition2d<int> pos);
	/// 按照指定列对所有数据进行排序
	void SortAllData(int list,bool isForward=true);
	/// 从小到大排序
	static bool sort1(const std::vector<RowStruct> &t1,const std::vector<RowStruct> &t2);
	/// 从大到小排序
	static bool sort2(const std::vector<RowStruct> &t1,const std::vector<RowStruct> &t2);

private:
	/// 得到当前列表头的宽度
	int GetCurHeadersWidth(int index);
	/// 得到当前总共有多少个文本
	int GetTotalLineCount(void);
	/// 显示列表头
	void DrawListBoxHeader(CMolBaseFrame* driver);
	/// 显示所有的行
	void DrawAllRows(CMolBaseFrame* driver);
	/// 得到所有行的显示位置
	void GetRowsPosition();
	/// 从指定坐标开始得到所有文本的显示位置
	void GetAllRows(CMolPosition2d<s32> position);

private:
	CMolGUIScrollBar *m_ScrollBar;                /**< 文本显示框的滚动条 */
	int m_scrollbarWidth;                         /**< 滚动条的宽度 */

	CMolColor m_bgColor;                          /**< 多项列表框背景颜色 */
	CMolColor m_TextColor;                        /**< 多项列表框字体颜色 */
	CMolColor m_SelectColor;                      /**< 多项列表框选择的颜色 */
	CMolColor m_SelectedColor;                    /**< 多项列表框选中后的颜色 */

	int m_curMouseRowIndex;                       /**< 当前鼠标经过那一行文本 */ 
	int m_curSeletecRowIndex;                     /**< 当前鼠标选中的那一行文本 */
	int m_curMouseHeaderIndex;                    /**< 当前鼠标经过头文本 */
	
	bool m_HeaderIsMouse;                         /**< 是否进行排序 */
	std::string m_HeaderMessage;                  /**< 列表头所显示的信息 */
	std::string m_headerImagePath;                /**< 列表头所使用纹理的路径 */
	HTEXTURE m_headerImage;                       /**< 列表头所使用的纹理 */
	CMolColor m_HeaderBgColor;                    /**< 列表头所使用的背景颜色 */
	CMolColor m_HeaderTextColor;                  /**< 列表头所使用的文字颜色 */
	int m_curRowIndex;                            /**< 当前显示行索引 */

	bool m_IsForward;                             /**< 排序方式 */
	static int m_sortIndex;                       /**< 排序索引 */

	CMolColor m_tipColor;                      /**< 当前进度条进度提示颜色 */
	std::string m_BgImageOnePath;              /**< 进度条第一张图片路径 */
	std::string m_BgImageTwoPath;              /**< 进度条第二张图片路径 */
	std::string m_BgImageThreePath;            /**< 进度条第三张图片路径 */
	std::string m_BgImageFourPath;             /**< 进度条第四张图片路径 */

	std::vector<LBHeader> m_LBHeaderList;         /**< 列表头 */
	std::vector< std::vector<RowStruct> > m_LBRowList;  /**< 列数据 */
};

//}
//}

#endif
