#ifndef _MOLE2D_BASE_GUI_ELEMENT_H_
#define _MOLE2D_BASE_GUI_ELEMENT_H_

/** 
* Mole2d ͼ������
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
 * GUI��Ա�����࣬����GUI���󶼽��ɴ�����
 */
class MOLEXPORT CMolBaseGUIElement : public CMolEventReceiver
{
public:
	/// ���캯��
	CMolBaseGUIElement();
	/// �������Ĺ��캯��
	CMolBaseGUIElement(MOLGUI_ELEMENT_TYPE type,CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,CMolRect<int> rect);
	/// ��������
	virtual ~CMolBaseGUIElement();

	/// �õ���Ⱦ�豸
	inline CMolBaseFrame* GetDriver(void)
	{
		return m_Driver;
	}
	/// ������Ⱦ�豸
	inline void SetDriver(CMolBaseFrame *driver)
	{
		m_Driver = driver;
	}
	/// �õ���ǰ�ؼ��ĸ��ؼ�
	inline CMolBaseGUIElement* GetParent() const
	{
		return m_Parent;
	}
	/// ���õ�ǰ�ؼ��ĸ��ؼ�
	inline void SetParent(CMolBaseGUIElement* parent)
	{
		m_Parent = parent;
	}
	/// ���ص�ǰ�ؼ�����ʾ��Χ
	inline CMolRect<int>& GetAbsoluteRect(void)
	{
		return m_AbsoluteRect;
	}
	/// ���õ�ǰ�ؼ�����ʾ��Χ
	inline void SetAbsoluteRect(CMolRect<int>& rect)
	{
		m_AbsoluteRect = rect;
	}
	/// �õ���ǰ�ؼ������ƫ��
	inline CMolDimension2d<int>& GetRelativeRect(void)
	{
		return m_RelativeRect;
	}
	/// ���õ�ǰ�ؼ������ƫ��
	inline void SetRelativeRect(CMolDimension2d<int>& rect)
	{
		m_RelativeRect = rect;
	}
	/// �õ���ǰ�ؼ��Ĳü�����
	inline CMolRect<int>& GetClippingRect(void)
	{
		return m_ClippingRect;
	}
	/// ���õ�ǰ�ؼ��Ĳü�����
	inline void SetClippingRect(CMolRect<int>& rect)
	{
		m_ClippingRect = rect;
	}
	/// �õ���ǰ�ؼ��ĸ߿�
	inline CMolDimension2d<int>& GetControlWidthAndHeight(void)
	{
		return m_ControlWidthAndHeight;
	}
	/// ���õ�ǰ�ؼ��ĸ߿�
	inline void SetControlWidthAndHeight(CMolDimension2d<int>& size)
	{
		m_ControlWidthAndHeight = size;
	}
	/// ���õ�ǰ�ؼ��Ƿ���ʾ
	inline void SetVisible(bool visible)
	{
		m_IsVisible = visible;
	}
	/// �õ���ǰ�ؼ��Ƿ���ʾ
	inline bool isVisible() const
	{
		return m_IsVisible;
	}
	/// ���õ�ǰ�ؼ��Ƿ�õ�����
	virtual void SetFocus(bool focus)
	{
		m_IsFocused = focus;
	}
	/// �õ���ǰ�ؼ��Ƿ�õ�����
	inline bool GetFocus(void)
	{
		return m_IsFocused;
	}
	/// �����Ƿ�����ƶ��ؼ�
	inline void SetMoving(bool moving)
	{
		m_IsMoved = moving;
	}
	/// �õ��Ƿ�����ƶ��ؼ�
	inline bool isMoving(void)
	{
		return m_IsMoved;
	}
	/// ���õ�ǰ�ؼ��Ƿ����
	virtual void SetEnabled(bool enabled)
	{
		m_IsEnabled = enabled;
	}
	/// �õ���ǰ�ؼ��Ƿ����
	inline bool IsEnabled(void)
	{
		return m_IsEnabled;
	}
	/// ���ÿؼ�ʹ�õ�ͼƬ
	inline void SetBgImage(HTEXTURE tex)
	{
		m_bgImage = tex;
	}
	/// �õ��ؼ�ʹ�õ�ͼƬ
	inline HTEXTURE GetBgImage(void)
	{
		return m_bgImage;
	}
	/// ���ó�Ա������
	inline void SetCaption(std::string caption)
	{
		m_Caption = caption;
	}
	/// �õ���Ա������
	inline std::string GetCaption(void)
	{
		return m_Caption;
	}
	/// ���ó�Ա����ʾ��Ϣ
	inline void SetTipText(std::string tip)
	{
		m_TipText = tip;
	}
	/// �õ���Ա����ʾ��Ϣ
	inline std::string GetTipText()
	{
		return m_TipText;
	}
	/// ���õ�ǰ��Ա��ID
	inline void SetID(int id)
	{
		m_ID = id;
	}
	/// �õ���ǰ��Ա��ID
	inline int GetID(void)
	{
		return m_ID;
	}
	/// �õ���ǰ��Ա������
	inline MOLGUI_ELEMENT_TYPE GetType(void)
	{
		return m_Type;
	}
	/// ���õ�ǰ��Ա������
	inline void SetType(MOLGUI_ELEMENT_TYPE type)
	{
		m_Type = type;
	}
	/// �����Ƿ�֧��tab����
	inline void SetUseTab(bool isuse)
	{
		m_IsTab = isuse;
	}
	/// ����Ƿ�֧��tab����
	inline bool IsTab(void)
	{
		return m_IsTab;
	}
	/// ��⵱ǰ�ؼ��Ƿ����ӿؼ�
	inline bool IsChildrens(void)
	{
		return m_Childrens.empty() ? false : true;
	}
	/// �õ���ǰ�ؼ����ӿؼ��б�
	inline std::list<CMolBaseGUIElement*>& GetChildrens(void)
	{
		return m_Childrens;
	}
	/// �����Ƿ���ʾ��������
	inline void SetUseFigure(bool isfigure)
	{
		m_IsFigure = isfigure;
	}
	/// �õ��Ƿ���ʾ��������
	inline bool IsUseFigure(void)
	{
		return m_IsFigure;
	}

	/// ��ָ���ؼ����ڿؼ������ؼ�������
	bool bringToFront(CMolBaseGUIElement* element);
	/// ���ݿؼ�ID���ҿؼ��Ƿ�������ؼ���
	CMolBaseGUIElement* FindControlById(int id);
	/// ����ָ���ؼ�������һ������ؼ�
	CMolBaseGUIElement* FindNextFocusControl(CMolBaseGUIElement *ctl);
	/// �������λ�ò����Ƿ��пؼ�����
	CMolBaseGUIElement* FindControlByPosition(CMolPosition2d<int> pos);

	/// �����ǰ�ؼ������е��ӿؼ�
	void DeleteAllControls(void);
	/// ���һ���ؼ�������ؼ���
	void AddChildren(CMolBaseGUIElement *control);
	/// ɾ��ָ���Ŀؼ�
	void DeleteChildren(CMolBaseGUIElement *control);

	/// �ƶ��ؼ���ָ����λ��
	virtual void Move(CMolPosition2d<int> pos);
	/// ���ؼ�
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
	/// ����֮ǰ����
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
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event)
	{
		return m_Parent ? m_Parent->OnProcessEvent(event) : false;
	}
	/// ����ʧ������¼�
	virtual void OnProcessLostFocusEvent(const CMolEvent& event)
	{

	}
	/// ��������뿪��Ϸ�������¼�
	virtual void OnProcessMouseLeaveFrame(const CMolEvent& event)
	{
	
	}

protected:
	/// �������Ƿ���ͼ������Χ��
	bool CheckMouseInImage(CMolPosition2d<s32> pos);

protected:
	std::list<CMolBaseGUIElement*> m_Childrens;         /**< ��ǰ�ؼ����ӿؼ� */

	CMolBaseGUIElement *m_Parent;                       /**< ��ǰ���ĸ���� */

	CMolRect<s32> m_AbsoluteRect;                       /**< ����λ�� */
	CMolDimension2d<s32> m_ControlWidthAndHeight;       /**< �ؼ�����ʾ�߿� */
	CMolDimension2d<s32> m_RelativeRect;                /**< ����ڸ��ؼ���ƫ�� */
	CMolRect<s32> m_ClippingRect;                       /**< ��ǰ�ؼ��Ĳü����� */
	HTEXTURE m_bgImage;                                 /**< �ؼ�ʹ�õ�ͼƬ */

	bool m_IsVisible;                                   /**< �Ƿ�ɼ� */
	bool m_IsEnabled;                                   /**< �Ƿ���� */
	bool m_IsMoved;                                     /**< �Ƿ�����ƶ��ؼ� */
	bool m_IsFocused;                                   /**< ��ǰ�ؼ��Ƿ�õ����� */
	bool m_IsFigure;                                    /**< �Ƿ���ʾ�������� */
	bool m_IsTab;                                       /**< �Ƿ�֧��tab���� */

	std::string m_Caption;                              /**< ��Ա������ */
	std::string m_TipText;                              /**< ��Ա����ʾ��Ϣ */

	s32  m_ID;                                          /**< ��Ա��ID */

	CMolBaseFrame *m_Driver;                            /**< ��ͼ�豸 */
	
	MOLGUI_ELEMENT_TYPE  m_Type;                        /**< ��Ա���� */
};

//}
//}

#endif
