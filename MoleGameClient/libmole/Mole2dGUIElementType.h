#ifndef _MOLE2D_GUI_ELEMENT_TYPE_H_
#define _MOLE2D_GUI_ELEMENT_TYPE_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2009.11.21
*/

/** 
 * 当前系统GUI成员类型
 */
enum MOLGUI_ELEMENT_TYPE
{
	/// 容器
	MOLGUI_CONTAINER = 0,
	/// 按钮
	MOLGUI_BUTTON,
	/// Flash
	MOLGUI_FLASH,
	/// 图像
	MOLGUT_IMAGE,
	/// 进度条
	MOLGUT_PROCESSBAR,
	/// 标签
	MOLGUT_STATIC,
	/// 输入框
	MOLGUT_EDITORBOX,
	/// 视频显示框
	MOLGUI_VIDEOBOX,
	/// 牌控件
	MOLGUI_GAMECARD,
	/// 游戏时钟控件
	MOLGUI_GAMECLOCK,
	/// 游戏动画控件
	MOLGUI_GAMEANIMATOR,
	/// 游戏信息滚动控件
	MOLGUI_INFOSCROLLER,
	/// 文本显示框
	MOLGUI_TEXTAREA,
	/// 滚动条
	MOLGUT_SCROLLBAR,
	/// 聊天信息显示框
	MOLGUI_CHATMESSAGE,
	/// 图片列表框
	MOLGUI_IMAGELISTBOX,
	/// 添加多选按钮
	MOLGUI_MULTIBUTTON,
	/// 添加多项列表框
	MOLGUI_MULTILISTBOX,
	/// 表情选择控件
	MOLGUI_BIAOQING,
	/// 移动动画控件
	MOLGUI_MOVEANIMATOR,
	/// 拖动滑块控件
	MOLGUI_DRAGCONTROL,
	/// 游戏房间列表控件
	MOLGUI_GAMEROOMLIST,
	/// 游戏列表控件
	MOLGUI_GAMELIST,
	/// 单选按钮控件
	MOLGUI_RADIOBUTTON,
	/// 成员计数
	MOLGUI_COUNT
};

#endif
