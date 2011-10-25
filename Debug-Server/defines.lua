--------------------------------------------框架消息---------------------------------------------------------------------

IDD_MESSAGE_ROOM                = 200;         -- 房间消息
IDD_MESSAGE_READY_START         = 201;         -- 玩家准备开始游戏
IDD_MESSAGE_GAME_START          = 202;         -- 游戏开始
IDD_MESSAGE_ROOM_ENTER          = 203;         -- 进入房间
IDD_MESSAGE_ROOM_LEAVE          = 204;         -- 离开房间
IDD_MESSAGE_PLAYER_READYED      = 205;         -- 玩家已经准备完毕

IDD_MESSAGE_GAMING              = 800;         -- 用户游戏中
IDD_MESSAGE_LEAVE_ROOM          = 702;         -- 离开游戏房间
IDD_MESSAGE_REENTER_ROOM        = 703;         -- 用户掉线后重新回到游戏房间
IDD_MESSAGE_CHANGER_ROOM        = 704;         -- 换游戏房间
IDD_MESSAGE_FALLLINE_ROOM       = 705;         -- 用户从游戏房间中掉线

---------------------------------------------游戏逻辑消息--------------------------------------------------------------------
IDD_MESSAGE_GAMING_JIAOFEN      = 1000;        -- 用户叫分
IDD_MESSAGE_OUTCARD             = 1001;        -- 用户出牌
IDD_MESSAGE_OUTCARD_DATA        = 1002;        -- 用户出牌数据
IDD_MESSAGE_PASS_OUT_CARD       = 1003;        -- 用户过牌
IDD_MESSAGE_GAME_OVER           = 1004;        -- 游戏结束
IDD_MESSAGE_CHAT                = 1005;        -- 游戏房间聊天消息
IDD_MESSAGE_CHAT_BIAOQING       = 1006;        -- 游戏房间聊天表情消息

---------------------------------------------游戏定时器----------------------------------------------------------------------

IDD_TIMER_START_GAME            = 100;         -- 游戏开始定时器
IDD_TIMER_JIAOFEN               = 101;         -- 用户叫分定时器
IDD_TIMER_OUTCARD               = 102;         -- 用户出牌定时器
IDD_TIMER_PLAYER_TUOGUAN        = 103;         -- 玩家掉线托管定时器
