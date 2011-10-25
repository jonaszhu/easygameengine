#ifndef _MOLE2D_GUI_STATIC_H_
#define _MOLE2D_GUI_STATIC_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.2.3
*/

#include "Mole2dBaseGUIElement.h"
#include "Mole2dBaseFont.h"

//namespace mole2d
//{
//namespace graphics
//{

class MOLEXPORT CMolGUIStatic : public CMolBaseGUIElement
{
public:
	/// 构造函数
	CMolGUIStatic();
	/// 带参数的构造函数
	CMolGUIStatic(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
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
	void SetText(std::string t);
	/// 得到要显示的文字
	inline std::string GetText(void)
	{
		return m_Text;
	}
	/// 设置文字显示的颜色
	inline void SetColor(CMolColor color)
	{
		pColor = m_Color = color;
	}
	/// 得到文字显示的颜色
	inline CMolColor GetColor(void)
	{
		return m_Color;
	}
	/// 设置对齐方式
	inline void SetSnapStyle(SnapStyle style)
	{
		m_SnapStyle = style;
		m_oldSnapStyle = style;
	}
	/// 得到对齐方式
	inline SnapStyle GetSnapStyle(void)
	{
		return m_SnapStyle;
	}
	/// 设置是否为超链接
	inline void SetIsHyperlink(bool ishl)
	{
		m_Ishyperlink = ishl;
	}
	/// 得到是否为超链接
	inline bool IsHyperlink(void)
	{
		return m_Ishyperlink;
	}
	/// 如果是超链接,设置选择后的颜色
	inline void SetHLSelColor(CMolColor col)
	{
		m_SelColor = col;
	}
	/// 如果是超链接，返回选择后的颜色
	inline CMolColor GetHLSelColor(void)
	{
		return m_SelColor;
	}
	/// 设置超级链接网址
	inline void SetHLAddress(std::string ar)
	{
		m_address = ar;
	}
	/// 得到超级链接网址
	inline std::string GetHLAddress(void)
	{
		return m_address;
	}
	/// 设置字体轮廓显示颜色
	inline void SetFigureColor(CMolColor col)
	{
		m_figureColor = col;	
	}
	/// 得到字体轮廓显示颜色
	inline CMolColor GetFigureColor(void)
	{
		return m_figureColor;
	}
	/// 设置是否闪烁文字
	inline void SetUseFlicker(bool isFlicker)
	{
		m_isFlicker = isFlicker;
		pColor = m_Color;
	}
	/// 得到是否山所文字
	inline bool IsFlicker(void)
	{
		return m_isFlicker;
	}

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
	SnapStyle m_SnapStyle,m_oldSnapStyle;           /**< 文字的对齐方式 */
	CMolColor m_Color,m_SelColor,pColor;            /**< 文字显示的颜色 */
	CMolColor m_figureColor;                        /**< 文字轮廓显示的颜色 */
	bool m_Ishyperlink;                             /**< 是否是超链接 */
	bool m_isSelected;                              /**< 鼠标是否选中文字 */
	bool m_isFlicker;                                /**< 是否闪烁文字 */
	DWORD m_CurTime;                                 /**< 用于控制文字闪烁 */
	std::string m_address;                          /**< 点击超链接后要打开的网站网址 */
};

//}
//}

#endif
