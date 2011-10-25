#ifndef _MOLE2D_GUI_DRAG_CONTROL_H_
#define _MOLE2D_GUI_DRAG_CONTROL_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.9.3 拖动滑块控件
*/

#include "Mole2dBaseGUIElement.h"

//namespace mole2d
//{
//namespace graphics
//{

/** 
 * 滑动块结构
 */
class DragScrollBar
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
	DragScrollBar();
	/// 析构函数
	~DragScrollBar();

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

class MOLEXPORT CMolGUIDragControl : public CMolBaseGUIElement
{
public:
	/// 构造函数
	CMolGUIDragControl();
	/// 带参数的构造函数
	CMolGUIDragControl(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,std::string caption,CMolRect<int> rect);
	virtual ~CMolGUIDragControl();

	/// 设置背景图片1
	void SetBgImageOne(std::string imgpath);
	/// 得到背景图片1
	inline std::string GetBgImageOne(void) { return m_dragbgimgonepath; }
	/// 设置背景图片2
	void SetBgImageTwo(std::string imgpath);
	/// 得到背景图片2
	inline std::string GetBgImageTwo(void) { return m_dragbgimgtwopath; }
	/// 设置背景图片3
	void SetBgImageThree(std::string imgpath);
	/// 得到背景图片3
	inline std::string GetBgImageThree(void) { return m_dragbgimgthreepath; }
	/// 设置滑动块使用到的纹理
	void SetDragScrollBar(HTEXTURE tex);
	/// 得到当前滑动块进度
	inline int GetCurrentProcess(void) { return m_curProcess; }
	/// 设置当前滑动条进度
	void SetCurrentProcess(int pro);

	/// 画控件
	virtual void Draw();
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// 处理丢失焦点的事件
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);
	/// 移动控件到指定的位置
	virtual void Move(CMolPosition2d<int> pos);

private:
	std::string m_dragbgimgonepath,m_dragbgimgtwopath,m_dragbgimgthreepath;       /**< 控件使用到的图片的路径 */
	HTEXTURE m_dragbgimgone,m_dragbgimgtwo,m_dragbgimgthree;         /**< 控件所使用到的背景图片 */

	DragScrollBar m_DragScrollBar;                                                /**< 控件使用到的拖动条 */
	int m_curProcess;                                                             /**< 当前拖动进度 */
	bool m_isDragging;                                                            /**< 是否在拖动滑动条 */
};

//}
//}

#endif
