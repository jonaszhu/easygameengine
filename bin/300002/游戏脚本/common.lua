engine = CMolBaseFrame:getSingleton();

IDD_GAME_PLAYER_COUNT       =       2                    -- 游戏玩家人数
IDD_LOGO_WIDTH              =       100                  -- 玩家logo的显示高宽
IDD_LOGO_HEIGHT             =       100          
m_bgTex                     =       0         

playerInfo = {};                                         -- 游戏信息
playerInfo[1] = {};
playerInfo[2] = {};
playerInfo[1].NamePos = {804,83};
playerInfo[2].NamePos = {804,221};

playerInfo[1].Logotex = -1;
playerInfo[2].Logotex = -1;

playerInfo[1].typePos = {649,84};
playerInfo[2].typePos = {649,221};

playerInfo[1].LogoPos = {889,73};
playerInfo[2].LogoPos = {889,213};

playerInfo[1].TimerPos = {804,144};
playerInfo[2].TimerPos = {804,281};

playerInfo[1].ReadyPos = {915,113};
playerInfo[2].ReadyPos = {915,251};
