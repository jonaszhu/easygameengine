#ifndef _MOLE2D_GUI_BIAOQING_H_
#define _MOLE2D_GUI_BIAOQING_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.8.13
*/

#include "Mole2dBaseGUIElement.h"

#include "Mole2dGUIGameAnimator.h"
#include "Mole2dGUIButton.h"
#include "Mole2dDimension2d.h"

#include <vector>

/// 动画之间的显示间隔 
#define IDD_ANIMATOR_SPACE 5  

/// 选择面板高度
#define IDD_SELECT_PANELHEIGHT 20

//namespace mole2d
//{
//namespace graphics
//{

class MOLEXPORT CMolGUIBiqoQing : public CMolBaseGUIElement
{
public:
	/// 构造函数
	CMolGUIBiqoQing();
	/// 带参数的构造函数
	CMolGUIBiqoQing(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		s32 id,std::string caption,CMolRect<s32> rect);
	/// 析构函数
	virtual ~CMolGUIBiqoQing();

	/// 设置一页显示多少个动画
	void SetPageSize(CMolDimension2d<s32> size);
	/// 得到一页显示多少个动画
	inline CMolDimension2d<s32> GetPageSize(void) { return m_PageSize; }
	/// 从指定路径导入表情动画
	void LoadAnimators(std::string path);
	/// 清除所有的表情动画
	void ClearAllAnimator(void);
	/// 设置向左按钮
	void SetLeftButton(std::string btnImage);
	/// 得到向左按钮图片
	inline std::string GetLeftButton(void) { return m_LeftBtnImg; }
	/// 设置向右按钮
	void SetRightButton(std::string btnImage);
	/// 得到向右按钮图片
	inline std::string GetRightButton(void) { return m_RightBtnImg; }
	/// 重新设置所有的参数
	void Reset(void);
	/// 得到选中后的动画表情的相对路径
	std::string GetSelectedPath(void);

	/// 画控件
	virtual void Draw();
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// 处理丢失焦点的事件
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	/// 根据当前所在页面显示表情动画
	void DrawBiaoQingAnim();
	/// 隐藏所有的表情动画
	void HideAllBiaoQingAnims(void);
	/// 根据鼠标坐标检测玩家当前选中表情
	void GetSelectBiaoQingByMouse(CMolPosition2d<s32> pos);
	/// 根据当前鼠标选中画选择框
	void DrawSelectFrame(CMolBaseFrame* driver);

private:
	CMolDimension2d<s32> m_PageSize;                            /**< 一页显示多少个 */
	CMolDimension2d<s32> m_animSize;                        /**< 动画显示的高宽 */
	std::string m_animPath;                                 /**< 表情动画的路径 */

	int m_curPage;                                              /**< 当前显示页 */
	int m_curMouseIndex;                                        /**< 当前鼠标经过的表情 */
	int m_totalPage;                                            /**< 总的页面数 */

	std::vector<CMolGUIGameAnimator*> m_AnimList;           /**< 表情动画列表 */
	CMolGUIButton *m_LeftBtn;                               /**< 向左按钮 */
	std::string m_LeftBtnImg;                               /**< 向左按钮使用的图片 */
	CMolGUIButton *m_RightBtn;                              /**< 向右按钮 */
	std::string m_RightBtnImg;                              /**< 向右按钮使用的图片 */
};

//}
//}

#endif
