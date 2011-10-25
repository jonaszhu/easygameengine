#ifndef _MOLE2D_GUI_STATIC_H_
#define _MOLE2D_GUI_STATIC_H_

/** 
* Mole2d ͼ������
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
	/// ���캯��
	CMolGUIStatic();
	/// �������Ĺ��캯��
	CMolGUIStatic(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,std::string caption,CMolRect<int> rect);

	/// ���û����ֵ�����
	inline void SetFont(CMolGUIBaseFont *font)
	{
		m_Font = font;
	}
	/// �õ������ֵ�����
	inline CMolGUIBaseFont* GetFont(void)
	{
		return m_Font;
	}
	/// �������ִ�С
	inline void SetSize(int s)
	{
		m_Size = s;
	}
	/// �õ����ִ�С
	inline int GetSize(void)
	{
		return m_Size;
	}
	/// ����Ҫ��ʾ������
	void SetText(std::string t);
	/// �õ�Ҫ��ʾ������
	inline std::string GetText(void)
	{
		return m_Text;
	}
	/// ����������ʾ����ɫ
	inline void SetColor(CMolColor color)
	{
		pColor = m_Color = color;
	}
	/// �õ�������ʾ����ɫ
	inline CMolColor GetColor(void)
	{
		return m_Color;
	}
	/// ���ö��뷽ʽ
	inline void SetSnapStyle(SnapStyle style)
	{
		m_SnapStyle = style;
		m_oldSnapStyle = style;
	}
	/// �õ����뷽ʽ
	inline SnapStyle GetSnapStyle(void)
	{
		return m_SnapStyle;
	}
	/// �����Ƿ�Ϊ������
	inline void SetIsHyperlink(bool ishl)
	{
		m_Ishyperlink = ishl;
	}
	/// �õ��Ƿ�Ϊ������
	inline bool IsHyperlink(void)
	{
		return m_Ishyperlink;
	}
	/// ����ǳ�����,����ѡ������ɫ
	inline void SetHLSelColor(CMolColor col)
	{
		m_SelColor = col;
	}
	/// ����ǳ����ӣ�����ѡ������ɫ
	inline CMolColor GetHLSelColor(void)
	{
		return m_SelColor;
	}
	/// ���ó���������ַ
	inline void SetHLAddress(std::string ar)
	{
		m_address = ar;
	}
	/// �õ�����������ַ
	inline std::string GetHLAddress(void)
	{
		return m_address;
	}
	/// ��������������ʾ��ɫ
	inline void SetFigureColor(CMolColor col)
	{
		m_figureColor = col;	
	}
	/// �õ�����������ʾ��ɫ
	inline CMolColor GetFigureColor(void)
	{
		return m_figureColor;
	}
	/// �����Ƿ���˸����
	inline void SetUseFlicker(bool isFlicker)
	{
		m_isFlicker = isFlicker;
		pColor = m_Color;
	}
	/// �õ��Ƿ�ɽ������
	inline bool IsFlicker(void)
	{
		return m_isFlicker;
	}

	/// ���ؼ�
	virtual void Draw();
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// ����ʧ������¼�
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	CMolGUIBaseFont *m_Font;                        /**< Ҫ�����ֵ����� */
	int m_Size;                                     /**< ���ֵ���ʾ��С */
	std::string m_Text;                             /**< Ҫ��ʾ������ */
	SnapStyle m_SnapStyle,m_oldSnapStyle;           /**< ���ֵĶ��뷽ʽ */
	CMolColor m_Color,m_SelColor,pColor;            /**< ������ʾ����ɫ */
	CMolColor m_figureColor;                        /**< ����������ʾ����ɫ */
	bool m_Ishyperlink;                             /**< �Ƿ��ǳ����� */
	bool m_isSelected;                              /**< ����Ƿ�ѡ������ */
	bool m_isFlicker;                                /**< �Ƿ���˸���� */
	DWORD m_CurTime;                                 /**< ���ڿ���������˸ */
	std::string m_address;                          /**< ��������Ӻ�Ҫ�򿪵���վ��ַ */
};

//}
//}

#endif
