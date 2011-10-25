#ifndef _MOLE2D_GUI_BUTTON_H_
#define _MOLE2D_GUI_BUTTON_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2009.12.5
*/

#include "Mole2dBaseGUIElement.h"

//namespace mole2d
//{
//namespace graphics
//{

class MOLEXPORT CMolGUIButton : public CMolBaseGUIElement
{
public:
	/** 
	 * ��ť״̬
	 */
	enum ButtonState
	{
		STATE_NORMAL = 0,            // ����״̬
		STATE_DOWND,                 // ����״̬
		STATE_HOVERED,               // ��꾭��״̬
		STATE_DISABLED,              // ��ť������״̬
		STATE_NULL
	};

	/** 
	 * ��ť����
	 */
	enum ButtonType
	{
		TYPE_SINGLE = 0,             // ��ѡ��ť
		TYPE_MULTIPLE                // ��ѡ��ť
	};

	/// ���캯��
	CMolGUIButton();
	/// �������Ĺ��캯��
	CMolGUIButton(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		s32 id,std::string caption,CMolRect<s32> rect);

	/// ���ð�ť״̬
	inline void SetState(ButtonState state)
	{
		m_ButtonState = state;
	}
	/// �õ���ť״̬
	inline ButtonState GetState(void)
	{
		return m_ButtonState;
	}
	/// ���õ�ǰ�ؼ��Ƿ����
	virtual void SetEnabled(bool enabled);
	/// ���ð�ť����
	inline void SetType(CMolGUIButton::ButtonType type) { m_ButtoneType = type; }
	/// �õ���ť����
	inline CMolGUIButton::ButtonType GetType(void) { return m_ButtoneType; }
	/// ����Ҫ��ʾ������
	inline void SetText(std::string t) { m_Text = t; }
	/// �õ�Ҫ��ʾ������
	inline std::string GetText(void) { return m_Text; }
	/// ���õ�ǰ��ť�Ƿ�ѡ��
	void SetSelected(bool sel);
	/// �õ���ǰ��ť�Ƿ�ѡ��
	inline bool IsSelected(void) { return m_isSelected; }

	/// ���ؼ�
	virtual void Draw();
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// ����ʧ������¼�
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	/// �������Ƿ���ͼ������Χ��
	bool CheckMouseInImage(CMolPosition2d<s32> pos);

private:
	ButtonState m_ButtonState;          /**< ��ť״̬ */
	ButtonType m_ButtoneType;           /**< ��ť���� */

	bool m_isSelected;                  /**< ��ť�Ƿ�ѡ�У����ڴ����ѡ����� */

	std::string m_Text;                 /**< ��ťҪ��ʾ������ */
};

////}
//}

#endif
