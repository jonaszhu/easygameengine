#ifndef _GUI_RADIO_BUTTON_H_
#define _GUI_RADIO_BUTTON_H_

#include "Mole2dBaseGUIElement.h"

/** 
 * ѡ��ť״̬
 */
enum CMolRButtonState
{
	STATE_NORMAL = 0,                // ѡ����״̬
	STATE_SELECTED                   // ������״̬
};

class MOLEXPORT CMolGUIRadioButton : public CMolBaseGUIElement
{
public:
	/// ���캯��
	CMolGUIRadioButton();
	/// �������Ĺ��캯��
	CMolGUIRadioButton(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,std::string caption,CMolRect<int> rect);
	virtual ~CMolGUIRadioButton();

	/// ���ð�ť״̬
	inline void SetButtonState(CMolRButtonState state) { m_BtnState = state; }
	/// �õ���ť״̬
	inline CMolRButtonState GetButtonState(void) { return m_BtnState; }

	/// ���ؼ�
	virtual void Draw();
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// ����ʧ������¼�
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	CMolRButtonState m_BtnState;                          /**< ��ť״̬ */
};

#endif
