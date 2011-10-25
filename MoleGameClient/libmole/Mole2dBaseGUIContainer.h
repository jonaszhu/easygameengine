#ifndef _MOLE2D_BASE_GUI_CONTAINER_H_
#define _MOLE2D_BASE_GUI_CONTAINER_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2009.12.1
*/

#include "Mole2dBaseGUIElement.h"

#include "tinyxml/tinyxml.h"

#include <vector>
#include <string>

//namespace mole2d
//{
//namespace graphics
//{

class CMolGUIButton;
class CMolGUIProcessBar;
class CMolGUIImage;
class CMolGUIStatic;
class CMolGUIEditorBox;
class CMolGUIVideo;
class CMolGUIGameCard;
class CMolGUIGameClock;
class CMolGUIGameAnimator;
class CMolGUIInfoScroller;
class CMolGUITextarea;
class CMolGUIScrollBar;
class CMolGUIChatMessage;
class CMolGUIImageListBox;
class CMolGUIMultiButton;
class CMolGUIMultiListBox;
class CMolGUIBiqoQing;
class CMolGUIMoveAnimator;
class CMolGUIDragControl;
class CMolGUIRoomList;
class CMolGUIGameList;
class CMolGUIRadioButton;
class CMolGUIFlash;

class MOLEXPORT CMolBaseGUIContainer : public CMolBaseGUIElement
{
public:
	/// ���캯��
	CMolBaseGUIContainer();
	/// �������Ĺ��캯��
	CMolBaseGUIContainer(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		s32 id,CMolRect<s32> rect);
	/// ��������
	virtual ~CMolBaseGUIContainer();

	/// �����Ƿ�Ϊģʽ������
	virtual void SetModal(bool modal);
	/// �õ��Ƿ�Ϊģʽ������
	virtual bool IsModal(void) { return isModal; }
	/// �����Ƿ�ģʽ�������´���䰵
	inline void SetBianAn(bool ba) { IsHeiPin = ba; }
	/// �õ��Ƿ�ģʽ�������´���䰵
	inline bool IsBianAn(void) { return IsHeiPin; }
	/// ����ָ���ؼ�����ʾ״̬
	void ShowControlById(int id,bool isShow);
	/// ����ָ���ؼ���ʹ��״̬
	void EnableControlById(int id,bool isEnable);
	/// �õ���ǰ����ؼ�
	inline CMolBaseGUIElement* GetCurFocusControl(void) { return m_Focus; }
	/// ���õ�ǰ����ؼ�
	inline void SetCurFocusControl(CMolBaseGUIElement *ctl);
	/// �õ���ǰ����ؼ�
	inline CMolBaseGUIElement* GetCurActiveControl(void) { return m_Active; }
	/// ���õ�ǰ����ؼ�
	inline void SetCurActiveControl(CMolBaseGUIElement *ctl) { m_Active = ctl; }

	/// ���õ�ǰ����Ƿ���
	inline void SetMousePress(bool p) { isPressed = p; }
	/// �õ���ǰ����Ƿ���
	inline bool GetMousePress(void) { return isPressed; }
	/// ����tab�¼�
	bool OnProcessTabEvent(CMolBaseGUIElement *ctl);

	/// �������ļ��е���GUI����
	virtual bool LoadGUIConfig(const char* filepath);
	/// ����GUI����
	virtual void SaveGUIConfig(std::string filepath);
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// ���ؼ�
	virtual void Draw();
	/// ����ʧ������¼�
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);
	/// ��������뿪��Ϸ�������¼�
	virtual void OnProcessMouseLeaveFrame(const CMolEvent& event);

	/// ���һ����ť
	CMolGUIButton* AddButton(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ��ͼ��ؼ�
	CMolGUIImage* AddImage(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ��flash�ؼ�
	CMolGUIFlash* AddFlash(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ��������
	CMolGUIProcessBar* AddProcessBar(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ����ǩ�ؼ�
	CMolGUIStatic* AddStaticText(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ����Ϣ������
	CMolGUIInfoScroller* AddInfoScroller(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ�������ؼ�
	CMolGUIEditorBox* AddEditorBox(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ����Ƶ��ʾ��ؼ�
	CMolGUIVideo* AddVideoBox(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ���ƿؼ�
	CMolGUIGameCard* AddGameCard(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ����Ϸʱ�ӿؼ�
	CMolGUIGameClock* AddGameClock(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ����Ϸ�����ؼ�
	CMolGUIGameAnimator* AddGameAnimator(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// ���һ���ı���ʾ��
	CMolGUITextarea* AddTextarea(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// ���һ���������ؼ�
	CMolGUIScrollBar* AddScrollBar(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// ���һ��������Ϣ��ʾ��ؼ�
	CMolGUIChatMessage* AddChatMessage(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// ���һ��ͼ���б��ؼ�
	CMolGUIImageListBox* AddImageListBox(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// ���һ����ѡ��ť�ؼ�
	CMolGUIMultiButton* AddMultiButton(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// ���һ�������б��ؼ�
	CMolGUIMultiListBox* AddMultiListBox(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// ���һ������ѡ��ؼ�
	CMolGUIBiqoQing* AddBiaoQingCtrl(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ���ƶ������ؼ�
	CMolGUIMoveAnimator* AddMoveAnimator(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ���϶������ؼ�
	CMolGUIDragControl* AddDragControl(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ�������б�ؼ�
	CMolGUIRoomList* AddRoomListCtl(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ����Ϸ�б�ؼ�
	CMolGUIGameList* AddGameListCtl(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);
	/// ���һ����ѡ��ť�ؼ�
	CMolGUIRadioButton* AddRadioButton(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent=NULL);	
	/// ���һ��������
	CMolBaseGUIContainer* AddContainer(s32 id,std::string caption,CMolRect<s32> rect,CMolBaseGUIElement* parent,bool isVisible=false);

protected:
	/// ����һ���¼���ϵͳ��
	virtual bool postEventFromUser(const CMolEvent& event);
	/// ����ָ�������������ӽ��
	bool LoadControlsFromTheNode(CMolBaseGUIContainer *pRoot,TiXmlElement *pNode);
	/// ���ڷֽ�ָ���ַ���Ϊ��ͬ�Ĳ���
	int ParseStringToParameter(std::string str,std::string chr=";");

protected:
	bool isModal;                  /**< �Ƿ�ģʽ������ */
	bool IsHeiPin;                 /**< �Ƿ���ģʽ�������´��ڱ䰵 */

	CMolBaseGUIElement *m_Focus;                     /**< ��ǰ����ؼ� */
	CMolBaseGUIElement *m_Active;                    /**< ��ǰ����ؼ� */
	CMolBaseGUIElement *m_CurScrollBar;              /**< �Թ������������⴦���Ա��������κεط����ܲ��������� */	

	std::vector<std::string>  m_Parameters;                        /**< Ҫ�ֽ�Ĳ��� */

	CMolGUIRoomList            *m_MainRoomList;                               /**< �����б� */

private:
	bool isPressed;                /**< ����Ƿ��� */
	CMolPosition2d<s32> m_OldPosition;            /**< �ϵ����λ�� */
};

//}
//}

#endif