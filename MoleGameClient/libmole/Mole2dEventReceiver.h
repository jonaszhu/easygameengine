#ifndef _MOLE2D_EVENT_RECEIVER_H_
#define _MOLE2D_EVENT_RECEIVER_H_

/** 
* Mole2d 图像引擎
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
 * 系統使用的事件类型
 */
enum MOLEVENT_TYPE
{
	/// GUI事件
	MOLET_GUI_EVENT = 0,
	/// 鼠标输入事件
	MOLET_MOUSE_INPUT_EVENT,
	/// 键盘事件
	MOLET_KEY_INPUT_EVENT,
	/// IME输入事件
	MOLET_IME_EVENT,
	/// 游戏更新事件
	MOLET_GAME_UPDATE_EVENT,
	/// 游戏视频事件
	MOLET_GAME_VIDEO_EVENT,
	/// 动画事件
	MOLET_GAME_ANIMATOR_EVENT,
	/// 其它事件
	MOLET_USER_EVENT
};

/** 
 * 鼠标输入事件所有的子事件
 */
enum MOLMOUSE_INPUT_EVENT
{
	/// 鼠标左键被按下
	MOLMIE_LMOUSE_PRESSED_DOWN = 0,
	/// 鼠标左键双击
	MOLMIE_LMOUSE_DOUBLE_CLICK,
	/// 鼠标右键被按下
	MOLMIE_RMOUSE_PRESSED_DOWN,
	/// 鼠标中键被按下
	MOLMIE_MMOUSE_PRESSED_DOWN,
	/// 鼠标左键被弹起
	MOLMIE_LMOUSE_LEFT_UP,
	/// 鼠标右键被弹起
	MOLMIE_RMOUSE_LEFT_UP,
	/// 鼠标中键被弹起
	MOLMIE_MMOUSE_LEFT_UP,
	/// 鼠标移动
	MOLMIE_MOUSE_MOVED,
	/// 鼠标滚轮移动
	MOLMIE_MOUSE_WHEEL,
	/// 事件计数
	MOLMIE_COUNT
};

/** 
 * 游戏更新子事件
 */
enum MOLGAME_UPDATE_EVENT
{
	/// 游戏更新完成
	MOLGAME_UPDATE_COMPLETE = 0,
	/// 游戏更新出错
	MOLGAME_UPDATE_ERROR,    
	/// 得到游戏更新列表
	MOLGAME_UPDATE_GET_LIST,
	/// 游戏更新中
	MOLGAME_UPDATE_PROCESS,
	/// 文件下载的更新进度
	MOLGAME_UPDATE_PROCESS_VALUE,
	/// 解压资源
	MOLGAME_UPDATE_UNZIP,
	/// 事件计数
	MOLGAME_UPDATE_COUNT
};

class CMolBaseGUIElement;

/** 
 * GUI事件的所有子事件
 */
enum MOLGUI_EVENT_TYPE
{
	/// GUI对象失去焦点
	MOLGET_ELEMENT_FOCUS_LOST = 0,
	/// GUI对象得到焦点
	MOLGET_ELEMENT_FOCUSED,
	/// 鼠标在GUI对象上
	MOLGET_ELEMENT_HOVERED,
	/// 鼠标离开GUI对象
	MOLGET_ELEMENT_LEFT,
	/// 关闭GUI对象
	MOLGET_ELEMENT_CLOSED,
	/// 按钮被点击
	MOLGET_BUTTON_CLICKED,
	/// GUI对象被改变
	MOLGET_ELEMENT_CHANGED,
	/// GUI对象中被选择事件
	MOLGET_ELEMENT_SELECTED,
	/// GUI对象中被双击选中事件
	MOLGET_ELEMENT_DCSELECTED,
	/// GUI对象中动画播放完成事件
	MOLGET_ELEMENT_ANIMATOR_FINISH,
	/// 事件计数
	MOLGET_COUNT
};

/** 
 * IME 事件
 */
enum MOLIME_EVENT_TYPE
{
	/// 输入英文字符
	MOLIME_IME_ENGLISH = 0,
	/// 输入中文字符
	MOLIME_IME_CHINESE,
	/// 事件计数
	MOLIME_IME_COUNT
};

/** 
* 动画事件
*/
enum MOLANIM_EVENT_TYPE
{
	/// 鼠标左键点击事件
	MOLANIM_LMOUSE_CLICK = 0,
	/// 鼠标左键双击事件
	MOLANIM_LMOUSE_DOUBLE_CLICK,
	/// 鼠标右键点击事件
	MOLANIM_RMOUSE_CLICK,
	/// 事件计数
	MOLANIM_COUNT
};

/** 
 * 事件结构
 */
struct CMolEvent
{
	/** 
	 * GUI事件结构
	 */
	struct CMolGuiEvent
	{
		// 调用的GUI控件
		CMolBaseGUIElement *Caller;

		// 被调用的GUI控件
		CMolBaseGUIElement *Element;

		// GUI事件类型
		MOLGUI_EVENT_TYPE EventType;
	};

	/** 
	 * 鼠标事件结构
	 */
	struct CMolMouseEvent
	{
		// 鼠标X
		s32 X;
		// 鼠标Y
		s32 Y;
		// 滚轮
		f32 Wheel;

		// 鼠标事件类型
		MOLMOUSE_INPUT_EVENT EventType;
	};

	/** 
	 * 键盘事件结构
	 */
	struct CMolKeyEvent
	{
		// 按键值
		char Char;

		// 按键类型
		int Key;

		// 如果不为真，那么按键已经弹起
		bool isPressedDown;

		// 如果Shift已经按下为真
		bool isShift;

		// 如果ctrl已经按下为真
		bool isControl;
	};

	/** 
	 * IME事件结构
	 */
	struct CMolImeEvent
	{
		// 存储输入的字符串
		char inputStr[1024];

		// IME事件类型
		MOLIME_EVENT_TYPE EventType;
	};

	/** 
	* 动画事件结构
	*/
	struct CMolAnimEvent
	{
		// 存储动画的名称
		char animName[1024];

		// 动画事件类型
		MOLANIM_EVENT_TYPE EventType;
	};

	/** 
	 * 游戏更新事件结构
	 */
	struct CMolUpdateEvent
	{
		int fileCount;                    // 下载的文件个数
		char filename[1024];              // 当前下载的文件
		int process;                      // 下载的进度

		// 更新事件类型
		MOLGAME_UPDATE_EVENT EventType;
	};

	MOLEVENT_TYPE mEventType;             // 事件类型
	int           mControlId;             // 触动事件的控件ID

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
 * 事件处理接口
 */
class MOLEXPORT CMolEventReceiver
{
public:
	/// 析构函数
	virtual ~CMolEventReceiver() { }

	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event) = 0;
};

//}
//}

#endif
