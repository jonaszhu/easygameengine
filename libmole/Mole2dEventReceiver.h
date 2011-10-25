#ifndef _MOLE2D_EVENT_RECEIVER_H_
#define _MOLE2D_EVENT_RECEIVER_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2009.11.21
*/

#include "Mole2dCommon.h"
#include "Mole2dPosition2d.h"

//namespace mole2d
//{
//namespace graphics
//{

/** 
 * ϵ�yʹ�õ��¼�����
 */
enum MOLEVENT_TYPE
{
	/// GUI�¼�
	MOLET_GUI_EVENT = 0,
	/// ��������¼�
	MOLET_MOUSE_INPUT_EVENT,
	/// �����¼�
	MOLET_KEY_INPUT_EVENT,
	/// IME�����¼�
	MOLET_IME_EVENT,
	/// ��Ϸ�����¼�
	MOLET_GAME_UPDATE_EVENT,
	/// ��Ϸ��Ƶ�¼�
	MOLET_GAME_VIDEO_EVENT,
	/// �����¼�
	MOLET_GAME_ANIMATOR_EVENT,
	/// �����¼�
	MOLET_USER_EVENT
};

/** 
 * ��������¼����е����¼�
 */
enum MOLMOUSE_INPUT_EVENT
{
	/// ������������
	MOLMIE_LMOUSE_PRESSED_DOWN = 0,
	/// ������˫��
	MOLMIE_LMOUSE_DOUBLE_CLICK,
	/// ����Ҽ�������
	MOLMIE_RMOUSE_PRESSED_DOWN,
	/// ����м�������
	MOLMIE_MMOUSE_PRESSED_DOWN,
	/// ������������
	MOLMIE_LMOUSE_LEFT_UP,
	/// ����Ҽ�������
	MOLMIE_RMOUSE_LEFT_UP,
	/// ����м�������
	MOLMIE_MMOUSE_LEFT_UP,
	/// ����ƶ�
	MOLMIE_MOUSE_MOVED,
	/// �������ƶ�
	MOLMIE_MOUSE_WHEEL,
	/// �¼�����
	MOLMIE_COUNT
};

/** 
 * ��Ϸ�������¼�
 */
enum MOLGAME_UPDATE_EVENT
{
	/// ��Ϸ�������
	MOLGAME_UPDATE_COMPLETE = 0,
	/// ��Ϸ���³���
	MOLGAME_UPDATE_ERROR,    
	/// �õ���Ϸ�����б�
	MOLGAME_UPDATE_GET_LIST,
	/// ��Ϸ������
	MOLGAME_UPDATE_PROCESS,
	/// �ļ����صĸ��½���
	MOLGAME_UPDATE_PROCESS_VALUE,
	/// ��ѹ��Դ
	MOLGAME_UPDATE_UNZIP,
	/// �¼�����
	MOLGAME_UPDATE_COUNT
};

class CMolBaseGUIElement;

/** 
 * GUI�¼����������¼�
 */
enum MOLGUI_EVENT_TYPE
{
	/// GUI����ʧȥ����
	MOLGET_ELEMENT_FOCUS_LOST = 0,
	/// GUI����õ�����
	MOLGET_ELEMENT_FOCUSED,
	/// �����GUI������
	MOLGET_ELEMENT_HOVERED,
	/// ����뿪GUI����
	MOLGET_ELEMENT_LEFT,
	/// �ر�GUI����
	MOLGET_ELEMENT_CLOSED,
	/// ��ť�����
	MOLGET_BUTTON_CLICKED,
	/// GUI���󱻸ı�
	MOLGET_ELEMENT_CHANGED,
	/// GUI�����б�ѡ���¼�
	MOLGET_ELEMENT_SELECTED,
	/// GUI�����б�˫��ѡ���¼�
	MOLGET_ELEMENT_DCSELECTED,
	/// GUI�����ж�����������¼�
	MOLGET_ELEMENT_ANIMATOR_FINISH,
	/// �¼�����
	MOLGET_COUNT
};

/** 
 * IME �¼�
 */
enum MOLIME_EVENT_TYPE
{
	/// ����Ӣ���ַ�
	MOLIME_IME_ENGLISH = 0,
	/// ���������ַ�
	MOLIME_IME_CHINESE,
	/// �¼�����
	MOLIME_IME_COUNT
};

/** 
* �����¼�
*/
enum MOLANIM_EVENT_TYPE
{
	/// ����������¼�
	MOLANIM_LMOUSE_CLICK = 0,
	/// ������˫���¼�
	MOLANIM_LMOUSE_DOUBLE_CLICK,
	/// ����Ҽ�����¼�
	MOLANIM_RMOUSE_CLICK,
	/// �¼�����
	MOLANIM_COUNT
};

/** 
 * �¼��ṹ
 */
struct CMolEvent
{
	/** 
	 * GUI�¼��ṹ
	 */
	struct CMolGuiEvent
	{
		// ���õ�GUI�ؼ�
		CMolBaseGUIElement *Caller;

		// �����õ�GUI�ؼ�
		CMolBaseGUIElement *Element;

		// GUI�¼�����
		MOLGUI_EVENT_TYPE EventType;
	};

	/** 
	 * ����¼��ṹ
	 */
	struct CMolMouseEvent
	{
		// ���X
		s32 X;
		// ���Y
		s32 Y;
		// ����
		f32 Wheel;

		// ����¼�����
		MOLMOUSE_INPUT_EVENT EventType;
	};

	/** 
	 * �����¼��ṹ
	 */
	struct CMolKeyEvent
	{
		// ����ֵ
		char Char;

		// ��������
		int Key;

		// �����Ϊ�棬��ô�����Ѿ�����
		bool isPressedDown;

		// ���Shift�Ѿ�����Ϊ��
		bool isShift;

		// ���ctrl�Ѿ�����Ϊ��
		bool isControl;
	};

	/** 
	 * IME�¼��ṹ
	 */
	struct CMolImeEvent
	{
		// �洢������ַ���
		char inputStr[1024];

		// IME�¼�����
		MOLIME_EVENT_TYPE EventType;
	};

	/** 
	* �����¼��ṹ
	*/
	struct CMolAnimEvent
	{
		// �洢����������
		char animName[1024];

		// �����¼�����
		MOLANIM_EVENT_TYPE EventType;
	};

	/** 
	 * ��Ϸ�����¼��ṹ
	 */
	struct CMolUpdateEvent
	{
		int fileCount;                    // ���ص��ļ�����
		char filename[1024];              // ��ǰ���ص��ļ�
		int process;                      // ���صĽ���

		// �����¼�����
		MOLGAME_UPDATE_EVENT EventType;
	};

	MOLEVENT_TYPE mEventType;             // �¼�����
	int           mControlId;             // �����¼��Ŀؼ�ID

	//union
	//{
		struct CMolGuiEvent mGuiEvent;
		struct CMolMouseEvent mMouseEvent;
		struct CMolKeyEvent mKeyEvent;
		struct CMolImeEvent mImeEvent;
		struct CMolUpdateEvent mUpdateEvnet;
		struct CMolAnimEvent mAnimEvent;
	//};
};

/** 
 * �¼�����ӿ�
 */
class MOLEXPORT CMolEventReceiver
{
public:
	/// ��������
	virtual ~CMolEventReceiver() { }

	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event) = 0;
};

//}
//}

#endif
