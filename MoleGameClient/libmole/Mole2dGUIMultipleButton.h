#ifndef _MOLE2D_GUI_MULTIPLE_BUTTON_H_
#define _MOLE2D_GUI_MULTIPLE_BUTTON_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2009.12.5
*/

#include "Mole2dBaseGUIElement.h"

#include "Mole2dGUIButton.h"

#include <vector>

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIMultiButton : public CMolBaseGUIElement
	{
	public:
		/// ���캯��
		CMolGUIMultiButton();
		/// �������Ĺ��캯��
		CMolGUIMultiButton(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			s32 id,std::string caption,CMolRect<s32> rect);
		/// ��������
		virtual ~CMolGUIMultiButton();

		/// ������ʾ����
		inline void SetDirection(DirectionType dir) { m_DirectionType = dir; }
		/// �õ���ʾ����
		inline DirectionType GetDirection(void) { return m_DirectionType; }
		/// ���һ����ť����ѡ��ť��
		void AddButton(std::string btnpath);
		/// ���ó�ʼѡ��ѡ��
		inline void SetDefSelectedItem(int item) 
		{ 
			m_DefaultSelected = item; 
			m_CurSelected = m_DefaultSelected;
		}
		/// �õ���ʼѡ��ѡ��
		inline int GetDefSelectedItem(void) { return m_DefaultSelected; }
		/// �õ���ǰѡ������
		inline int GetCurSelectedItem(void) { return m_CurSelected; }

		/// ���ؼ�
		virtual void Draw();
		/// ���ڴ�����յ����¼�
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// ����ʧ������¼�
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		/// �õ����а�ť����ʾλ��
		void GetButtonsDisPos(void);
		/// ѡ��ָ���İ�ť
		void SelectButton(CMolGUIButton* btn);

	private:
		std::vector<CMolGUIButton*> m_ButtonList;             /**< ���ڱ������еİ�ť�� */
		DirectionType m_DirectionType;                        /**< ��ѡ��ť�ķ��� */
		int m_DefaultSelected;                                /**< ��ʼѡ��ѡ�� */
		int m_CurSelected;                                    /**< ��ǰѡ���� */
	};

	//}
//}

#endif
