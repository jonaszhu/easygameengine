#ifndef _MOLE2D_GUI_MANAGER_H_
#define _MOLE2D_GUI_MANAGER_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2009.11.21
*/

#include "Mole2dBaseGUIContainer.h"

namespace mole2d
{
//namespace graphics
//{

class MOLEXPORT CMolGUIManager : public CMolBaseGUIContainer
{
public:
	/// ���캯��
	CMolGUIManager();
	/// �������Ĺ��캯��
	CMolGUIManager(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		s32 id,CMolRect<s32> rect);
	/// ��������
	virtual ~CMolGUIManager();

	/// ����ָ���ؼ�����ʾ״̬
	void ShowControlById(int id,bool isShow);
	/// ����ָ���ؼ���ʹ��״̬
	void EnableControlById(int id,bool isEnable);

	/// ���ؼ�
	virtual void Draw();

protected:
	/// ����һ���¼���ϵͳ��
	virtual bool postEventFromUser(const CMolEvent& event);

protected:
	CMolBaseGUIElement *m_Focus;                     /**< ��ǰ����ؼ� */
	CMolBaseGUIElement *m_Active;                    /**< ��ǰ����ؼ� */
};

//}
}

#endif