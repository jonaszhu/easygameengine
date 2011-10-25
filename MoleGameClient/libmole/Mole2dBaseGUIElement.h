#ifndef _MOLE2D_BASE_GUI_ELEMENT_H_
#define _MOLE2D_BASE_GUI_ELEMENT_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2009.11.21
*/

#include "Mole2dCommon.h"
#include "Mole2dGUIElementType.h"
#include "Mole2dEventReceiver.h"

#include "Mole2dRect.h"
#include "Mole2dDimension2d.h"
#include "Mole2dPosition2d.h"

#include <string>
#include <list>

//namespace mole2d
//{
//namespace graphics
//{

class CMolBaseFrame;

/** 
 * GUI成员基础类，其它GUI对象都将由此派生
 */
class MOLEXPORT CMolBaseGUIElement : public CMolEventReceiver
{
public:
	/// 构造函数
	CMolBaseGUIElement();
	/// 带参数的构造函数
	CMolBaseGUIElement(MOLGUI_ELEMENT_TYPE type,CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,CMolRect<int> rect);
	/// 析构函数
	virtual ~CMolBaseGUIElement();

	/// 得到渲染设备
	inline CMolBaseFrame* GetDriver(void)
	{
		return m_Driver;
	}
	/// 设置渲染设备
	inline void SetDriver(CMolBaseFrame *driver)
	{
		m_Driver = driver;
	}
	/// 得到当前控件的父控件
	inline CMolBaseGUIElement* GetParent() const
	{
		return m_Parent;
	}
	/// 设置当前控件的父控件
	inline void SetParent(CMolBaseGUIElement* parent)
	{
		m_Parent = parent;
	}
	/// 返回当前控件的显示范围
	inline CMolRect<int>& GetAbsoluteRect(void)
	{
		return m_AbsoluteRect;
	}
	/// 设置当前控件的显示范围
	inline void SetAbsoluteRect(CMolRect<int>& rect)
	{
		m_AbsoluteRect = rect;
	}
	/// 得到当前控件的相对偏移
	inline CMolDimension2d<int>& GetRelativeRect(void)
	{
		return m_RelativeRect;
	}
	/// 设置当前控件的相对偏移
	inline void SetRelativeRect(CMolDimension2d<int>& rect)
	{
		m_RelativeRect = rect;
	}
	/// 得到当前控件的裁剪区域
	inline CMolRect<int>& GetClippingRect(void)
	{
		return m_ClippingRect;
	}
	/// 设置当前控件的裁剪区域
	inline void SetClippingRect(CMolRect<int>& rect)
	{
		m_ClippingRect = rect;
	}
	/// 得到当前控件的高宽
	inline CMolDimension2d<int>& GetControlWidthAndHeight(void)
	{
		return m_ControlWidthAndHeight;
	}
	/// 设置当前控件的高宽
	inline void SetControlWidthAndHeight(CMolDimension2d<int>& size)
	{
		m_ControlWidthAndHeight = size;
	}
	/// 设置当前控件是否显示
	inline void SetVisible(bool visible)
	{
		m_IsVisible = visible;
	}
	/// 得到当前控件是否显示
	inline bool isVisible() const
	{
		return m_IsVisible;
	}
	/// 设置当前控件是否得到焦点
	virtual void SetFocus(bool focus)
	{
		m_IsFocused = focus;
	}
	/// 得到当前控件是否得到焦点
	inline bool GetFocus(void)
	{
		return m_IsFocused;
	}
	/// 设置是否可以移动控件
	inline void SetMoving(bool moving)
	{
		m_IsMoved = moving;
	}
	/// 得到是否可以移动控件
	inline bool isMoving(void)
	{
		return m_IsMoved;
	}
	/// 设置当前控件是否可用
	virtual void SetEnabled(bool enabled)
	{
		m_IsEnabled = enabled;
	}
	/// 得到当前控件是否可用
	inline bool IsEnabled(void)
	{
		return m_IsEnabled;
	}
	/// 设置控件使用的图片
	inline void SetBgImage(HTEXTURE tex)
	{
		m_bgImage = tex;
	}
	/// 得到控件使用的图片
	inline HTEXTURE GetBgImage(void)
	{
		return m_bgImage;
	}
	/// 设置成员的名称
	inline void SetCaption(std::string caption)
	{
		m_Caption = caption;
	}
	/// 得到成员的名称
	inline std::string GetCaption(void)
	{
		return m_Caption;
	}
	/// 设置成员的提示信息
	inline void SetTipText(std::string tip)
	{
		m_TipText = tip;
	}
	/// 得到成员的提示信息
	inline std::string GetTipText()
	{
		return m_TipText;
	}
	/// 设置当前成员的ID
	inline void SetID(int id)
	{
		m_ID = id;
	}
	/// 得到当前成员的ID
	inline int GetID(void)
	{
		return m_ID;
	}
	/// 得到当前成员的类型
	inline MOLGUI_ELEMENT_TYPE GetType(void)
	{
		return m_Type;
	}
	/// 设置当前成员的类型
	inline void SetType(MOLGUI_ELEMENT_TYPE type)
	{
		m_Type = type;
	}
	/// 设置是否支持tab按键
	inline void SetUseTab(bool isuse)
	{
		m_IsTab = isuse;
	}
	/// 检测是否支持tab按键
	inline bool IsTab(void)
	{
		return m_IsTab;
	}
	/// 检测当前控件是否有子控件
	inline bool IsChildrens(void)
	{
		return m_Childrens.empty() ? false : true;
	}
	/// 得到当前控件的子控件列表
	inline std::list<CMolBaseGUIElement*>& GetChildrens(void)
	{
		return m_Childrens;
	}
	/// 设置是否显示轮廓文字
	inline void SetUseFigure(bool isfigure)
	{
		m_IsFigure = isfigure;
	}
	/// 得到是否显示轮廓文字
	inline bool IsUseFigure(void)
	{
		return m_IsFigure;
	}

	/// 将指定控件放在控件整个控件最上面
	bool bringToFront(CMolBaseGUIElement* element);
	/// 根据控件ID查找控件是否在这个控件中
	CMolBaseGUIElement* FindControlById(int id);
	/// 根据指定控件查找下一个激活控件
	CMolBaseGUIElement* FindNextFocusControl(CMolBaseGUIElement *ctl);
	/// 根据鼠标位置查找是否有控件存在
	CMolBaseGUIElement* FindControlByPosition(CMolPosition2d<int> pos);

	/// 清除当前控件中所有的子控件
	void DeleteAllControls(void);
	/// 添加一个控件到这个控件中
	void AddChildren(CMolBaseGUIElement *control);
	/// 删除指定的控件
	void DeleteChildren(CMolBaseGUIElement *control);

	/// 移动控件到指定的位置
	virtual void Move(CMolPosition2d<int> pos);
	/// 画控件
	virtual void Draw()
	{
		if(!m_IsVisible || m_Childrens.empty())
			return;

		std::list<CMolBaseGUIElement*>::iterator iter = m_Childrens.begin();
		for(;iter != m_Childrens.end();++iter)
		{
			if((*iter) && (*iter)->isVisible()) (*iter)->Draw();
		}
	}
	/// 处理画之前更新
	virtual bool OnProcessPostUpdate()
	{
		if(!m_IsVisible || m_Childrens.empty())
			return false;

		std::list<CMolBaseGUIElement*>::iterator iter = m_Childrens.begin();
		for(;iter != m_Childrens.end();++iter)
		{
			if((*iter) && (*iter)->isVisible()) 
			{
				//if((*iter)->OnProcessPostUpdate()) return true;
				(*iter)->OnProcessPostUpdate();
			}
		}

		return true;
	}
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event)
	{
		return m_Parent ? m_Parent->OnProcessEvent(event) : false;
	}
	/// 处理丢失焦点的事件
	virtual void OnProcessLostFocusEvent(const CMolEvent& event)
	{

	}
	/// 处理鼠标离开游戏主窗口事件
	virtual void OnProcessMouseLeaveFrame(const CMolEvent& event)
	{
	
	}

protected:
	/// 检查鼠标是否在图像区域范围内
	bool CheckMouseInImage(CMolPosition2d<s32> pos);

protected:
	std::list<CMolBaseGUIElement*> m_Childrens;         /**< 当前控件的子控件 */

	CMolBaseGUIElement *m_Parent;                       /**< 当前结点的父结点 */

	CMolRect<s32> m_AbsoluteRect;                       /**< 绝对位置 */
	CMolDimension2d<s32> m_ControlWidthAndHeight;       /**< 控件的显示高宽 */
	CMolDimension2d<s32> m_RelativeRect;                /**< 相对于父控件的偏移 */
	CMolRect<s32> m_ClippingRect;                       /**< 当前控件的裁剪区域 */
	HTEXTURE m_bgImage;                                 /**< 控件使用的图片 */

	bool m_IsVisible;                                   /**< 是否可见 */
	bool m_IsEnabled;                                   /**< 是否可用 */
	bool m_IsMoved;                                     /**< 是否可以移动控件 */
	bool m_IsFocused;                                   /**< 当前控件是否得到焦点 */
	bool m_IsFigure;                                    /**< 是否显示轮廓字体 */
	bool m_IsTab;                                       /**< 是否支持tab按键 */

	std::string m_Caption;                              /**< 成员的名称 */
	std::string m_TipText;                              /**< 成员的提示信息 */

	s32  m_ID;                                          /**< 成员的ID */

	CMolBaseFrame *m_Driver;                            /**< 画图设备 */
	
	MOLGUI_ELEMENT_TYPE  m_Type;                        /**< 成员类型 */
};

//}
//}

#endif
