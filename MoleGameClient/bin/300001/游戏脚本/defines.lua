-- 网络消息
IDD_MESSAGE_ROOM                = 200;         -- 房间消息
IDD_MESSAGE_READY_START         = 201;         -- 准备开始游戏
IDD_MESSAGE_GAME_START          = 202;         -- 游戏开始
IDD_MESSAGE_GAME_END            = 203;         -- 游戏结束

IDD_MESSAGE_DISCONN_BACK        = 300;

IDD_MESSAGE_CONNECT             = 400;         -- 用户连接消息
IDD_MESSAGE_CONNECT_SUCESS      = 401;         -- 用户连接成功
IDD_MESSAGE_CONNECT_FAIL        = 402;         -- 用户连接失败

IDD_MESSAGE_LOGIN               = 500;         -- 用户登录消息
IDD_MESSAGE_LOGIN_SUCESS        = 501;         -- 用户登录成功
IDD_MESSAGE_LOGIN_FAIL          = 502;         -- 用户登录失败
IDD_MESSAGE_LOGIN_BUSY          = 503;         -- 系统忙,用户登录过于频繁
IDD_MESSAGE_LOGIN_EXIST         = 504;         -- 用户已经在系统中

IDD_MESSAGE_HEART_JITTER        = 600;         -- 心跳消息

IDD_MESSAGE_FRAME               = 700;         -- 游戏框架消息
IDD_MESSAGE_ENTER_ROOM          = 701;         -- 进入房间
IDD_MESSAGE_LEAVE_ROOM          = 702;         -- 离开游戏房间
IDD_MESSAGE_ENTERROOM_FAIL      = 703;         -- 进入游戏房间失败
IDD_MESSAGE_LOOKON_ENTER_ROOM   = 707;         -- 旁观进入游戏房间

IDD_MESSAGE_GAMING              = 800;         -- 游戏中消息
IDD_MESSAGE_GAMING_DIANZI       = 801;         -- 用户点子
IDD_MESSAGE_GAMING_CHAT         = 802;         -- 发送聊天消息
IDD_MESSAGE_GAMING_SHENGLI      = 803;         -- 有玩家获取胜利
IDD_MESSAGE_GAMING_HUOQI        = 804;         -- 请求和棋消息
IDD_MESSAGE_GAMING_HUOQI_OK     = 805;         -- 同意求和消息
IDD_MESSAGE_GAMING_HUOQI_CONCEL = 806;         -- 不同意求和消息
IDD_MESSAGE_GAMING_PINGJU       = 807;         -- 平局
IDD_MESSAGE_GAMING_RENSHU       = 808;         -- 认输
IDD_MESSAGE_GAMING_HUIQI        = 809;         -- 悔棋
IDD_MESSAGE_GAMING_HUIQI_OK     = 810;         -- 悔棋成功
IDD_MESSAGE_GAMING_HUIQI_CONCEL = 811;         -- 悔棋失败

-- 控件消息 
IDD_EXITTIPDIG                  = 10001;       -- 退出提示对话框
IDD_EXITTIPDIG_OK               = 200;         -- 退出提示框确定按钮
IDD_EXITTIPDIG_CONCEL           = 201;         -- 退出提示框取消按钮

IDD_QIUHEDIG                    = 10002;       -- 求和提示对话框
IDD_QIUHEDIG_OK                 = 302;         -- 求和确定按钮
IDD_QIUHEDIG_CONCEL             = 303;         -- 求和取消按钮

IDD_HUIQIDLG                    = 10003;       -- 悔棋提示对话框
IDD_HUIQIDLG_OK                 = 402;         -- 悔棋确定按钮
IDD_HUIQIDLG_CONCEL             = 403;         -- 悔棋取消按钮

IDD_MAINFRAME_START_GAME        = 102;         -- 开始游戏
IDD_MAINFRAME_CLOSE_GAME        = 115;         -- 关闭游戏按钮
IDD_MAINFRAME_CHAT_INPUT        = 111;         -- 聊天信息输入框
IDD_MAINFRAME_CHAT_MESSAGE      = 112;         -- 聊天信息显示框
IDD_MAINFRAME_SENDCHAT_BTN      = 114;         -- 发送聊天信息按钮
IDD_MAINFRAME_HUIQI_BTN         = 100;         -- 悔棋按钮
IDD_MAINFRAME_HUOQI_BTN         = 101;         -- 和棋按钮
IDD_MAINFRAME_RENSHU_BTN        = 103;         -- 认输按钮

IDD_CONNFRAME_TIP               = 300;         -- 连接提示

-- 定时器消息
IDD_TIMER_XIAZI                 = 500;         -- 下子定时器ID