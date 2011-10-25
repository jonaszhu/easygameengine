#ifndef _DEFINES_H_INCLUDE_
#define _DEFINES_H_INCLUDE_

/*********************************************************************************************/
#define IDD_MESSAGE_CONNECTED           100         // 用户连接成功

/*********************************************************************************************/
#define IDD_MESSAGE_ROOM                200         // 游戏房间消息
#define IDD_MESSAGE_READY_START         201         // 玩家准备开始游戏
#define IDD_MESSAGE_GAME_START          202         // 游戏开始
#define IDD_MESSAGE_GAME_END            203         // 游戏结束

/*********************************************************************************************/
#define IDD_MESSAGE_CONNECT             400         // 用户连接消息
#define IDD_MESSAGE_CONNECT_SUCESS      401         // 用户连接成功
#define IDD_MESSAGE_CONNECT_FAIL        402         // 用户连接失败
#define IDD_MESSAGE_CONNECT_EXIST       403         // 用户连接存在

/*********************************************************************************************/
#define IDD_MESSAGE_GAME_LOGIN               500         // 用户登录消息
#define IDD_MESSAGE_GAME_LOGIN_SUCESS        501         // 用户登录成功
#define IDD_MESSAGE_GAME_LOGIN_FAIL          502         // 用户登录失败
#define IDD_MESSAGE_GAME_LOGIN_BUSY          503         // 系统忙,用户登录过于频繁
#define IDD_MESSAGE_GAME_LOGIN_EXIST         504         // 用户已经在系统中
#define IDD_MESSAGE_GAME_LOGIN_FULL          506         // 服务器满

/*********************************************************************************************/
#define IDD_MESSAGE_HEART_JITTER        600         // 心跳

/*********************************************************************************************/
#define IDD_MESSAGE_FRAME               700         // 框架消息
#define IDD_MESSAGE_ENTER_ROOM          701         // 进入游戏房间
#define IDD_MESSAGE_LEAVE_ROOM          702         // 离开游戏房间
#define IDD_MESSAGE_REENTER_ROOM        703         // 用户掉线后重新回到游戏房间
#define IDD_MESSAGE_CHANGER_ROOM        704         // 换游戏房间
#define IDD_MESSAGE_FALLLINE_ROOM       705         // 用户从游戏房间中掉线
#define IDD_MESSAGE_GET_ROOM_LIST       706         // 得到房间列表
#define IDD_MESSAGE_LOOKON_ENTER_ROOM   707         // 旁观进入游戏房间
#define IDD_MESSAGE_GET_ONLINE_PLAYERS  708         // 得到当前所有在线玩家
#define IDD_MESSAGE_LEAVE_SERVER        709         // 离开游戏服务器
#define IDD_MESSAGE_GET_ONLINE_PLAYERS_END 710      // 获取在线玩家结束
#define IDD_MESSAGE_GET_ROOM_LIST_END   711         // 获取房间列表结束

/*********************************************************************************************/
#define IDD_MESSAGE_GAMING              800         // 玩家游戏中消息
#define IDD_MESSAGE_OUT_CARD            801         // 玩家出牌
#define IDD_MESSAGE_PASS_CARD           802         // 玩家过牌

/*********************************************************************************************/
#define IDD_MESSAGE_ENTER_ROOM_FAIL     901         // 进入游戏房间失败
#define IDD_MESSAGE_ENTER_ROOM_SUCC     902         // 进入游戏房间成功
#define IDD_MESSAGE_ENTER_ROOM_LASTMONEY 903        // 金币不能满足房间要求

/*********************************************************************************************/
#define IDD_MESSAGE_GET_PLAYER_MES              2000                   // 取得玩家信息
#define IDD_MESSAGE_GET_SUCCESS                 2001                   // 取得玩家信息成功
#define IDD_MESSAGE_GET_FAIL                    2002                   // 取得玩家信息失败

/*********************************************************************************************/
#define IDD_MESSAGE_REGISTER_GAME               6000                   // 注册游戏
#define IDD_MESSAGE_REGISTER_SUCCESS            6001                   // 注册游戏成功
#define IDD_MESSAGE_REGISTER_FAIL               6002                   // 注册游戏失败
#define IDD_MESSAGE_RE_REGISTER                 6003                   // 重复注册

/*********************************************************************************************/
#define IDD_MESSAGE_UPDATE_GAME_SERVER          7000                   // 更新游戏服务器信息
#define IDD_MESSAGE_UPDATE_GAME_SUCCESS         7001                   // 更新游戏服务器信息成功
#define IDD_MESSAGE_UPDATE_GAME_FAIL            7002                   // 更新游戏服务器信息失败

#endif
