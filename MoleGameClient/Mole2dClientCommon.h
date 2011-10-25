#ifndef _MOLE2D_COMMON_H_INCLUDE_
#define _MOLE2D_COMMON_H_INCLUDE_

/** 
 * 服务器参数结构
 */
struct SerParamStru
{
	char IPAddress[128];                 // IP地址
	char Password[128];                  // 进入密码
	int  Port;                           // 端口
};

#define IDD_CLIENT_CONFIG_FILE "clientconfig.ini"              // 客户端配置文件
#define IDD_CLIENT_CAPTION  "Mole开放游戏平台"

#define IDM_BTN_SERVER_LOGIN             WM_USER+100           // 用户登录服务器
#define IDM_GAMEFRAME_MESSAGE            WM_USER+101           // 游戏客户端发送的消息
#define IDD_CLOSE_GAME_FRAME             WM_USER+102           // 关闭游戏窗口
#define IDD_EXIT_GAME                    WM_USER+103           // 退出游戏
#define IDD_REENTER_GAME                 WM_USER+104           // 重新进入游戏
#define IDD_SHOW_CONN_TIP                WM_USER+105           // 显示连接提示

#define IDD_MAINFRAME_HOMEPAGE            601                   // 首页
#define IDD_MAINFRAME_LASTPAGE            602                   // 上一页
#define IDD_MAINFRAME_NEXTPAGE            603                   // 下一页
#define IDD_MAINFRAME_TAILPAGE            604                   // 尾页
#define IDD_MAINFRAME_AUTOJOIN            605                   // 自动加入

//计算数组维数
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))

#endif
