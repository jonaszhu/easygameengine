dofile("游戏脚本\\common.lua");
dofile("游戏脚本\\defines.lua");
dofile("游戏脚本\\networklogic.lua");
--加载五子棋逻辑
dofile("游戏脚本\\wuziqilogic.lua");

--
-- 显示棋盘中所有的棋子
--
function DrawChessPan()
   for i = 1 , totalrow do
      for j = 1 , totallist do
        if chesslist[i][j] == 1 then
			engine:Draw2DImage(m_texChess1,
							 chesspan[i][j],
							 CMolRect_int_(0,0,m_chesstexWidth,m_chesstexHeight));
		elseif chesslist[i][j] == 2 then
			engine:Draw2DImage(m_texChess2,
							 chesspan[i][j],
							 CMolRect_int_(0,0,m_chesstexWidth,m_chesstexHeight));
		end
      end
   end
   
   if (m_curChessPosX > 0 and m_curChessPosX <= totalrow) and 
	  (m_curChessPosY > 0 and m_curChessPosY <= totallist) then
		engine:Draw2DImage(m_texChessSel,
						 chesspan[m_curChessPosX][m_curChessPosY],
						 CMolRect_int_(0,0,m_chesstexWidth+2,m_chesstexHeight+2)); 
   end
end

--
-- 渲染游戏场景
--
function DrawScene()
	-- 显示背景图
	if m_bgTex ~= 0 then
		engine:Draw2DImage(m_bgTex,CMolPosition2d_int_(0,0));
	end

	-- 显示当前桌子数
	local mySelf = toHelper.toPlayer(engine:GetUserData(engine:GetMeChairID()));
	if mySelf ~= nil then
		engine:DrawString("- 第 "..tostring(mySelf:GetRoomId()+1).." 桌",
						  CMolRect_int_(370,39,600,60),
						  CMolColor(255,255,255,255));
	end
	
	-- 显示棋牌
	DrawChessPan();
							  
	for i = 1 , IDD_GAME_PLAYER_COUNT do
		local pPlayer = toHelper.toPlayer(engine:GetUserInfo(i-1));
		if pPlayer ~= nil then
			engine:DrawStringf(pPlayer:GetName(),
			                  CMolRect_int_(playerInfo[i].NamePos[1],playerInfo[i].NamePos[2],playerInfo[i].NamePos[1]+200,playerInfo[i].NamePos[2]+40),
							  CMolColor(255,255,255,255));
			engine:DrawStringf(tostring(pPlayer:GetMoney()),
			                  CMolRect_int_(playerInfo[i].NamePos[1],playerInfo[i].NamePos[2]+31,playerInfo[i].NamePos[1]+200,playerInfo[i].NamePos[2]+80),
							  CMolColor(255,255,255,255));	

			if m_texPlayerType1 ~= 0 and m_texPlayerType2 ~= 0 then
				if pPlayer:GetRoomIndex() == 0 then
					engine:Draw2DImage(m_texPlayerType2,CMolPosition2d_int_(playerInfo[i].typePos[1],playerInfo[i].typePos[2]));
				else 
					engine:Draw2DImage(m_texPlayerType1,CMolPosition2d_int_(playerInfo[i].typePos[1],playerInfo[i].typePos[2]));
				end
			end

			-- 显示用户头像
			if playerInfo[i].Logotex == -1 then
				playerInfo[i].Logotex = engine:LoadTexture(engine:GetProgressDirection().."\\Avatars\\"..pPlayer:GetUserAvatar());
			else
				local texWidth = engine:GetTextureWidth(playerInfo[i].Logotex,true);
				local texHeight = engine:GetTextureHeight(playerInfo[i].Logotex,true);
				
				engine:Draw2DImage(playerInfo[i].Logotex,
								 CMolRect_int_(playerInfo[i].LogoPos[1],playerInfo[i].LogoPos[2],playerInfo[i].LogoPos[1]+IDD_LOGO_WIDTH,playerInfo[i].LogoPos[2]+IDD_LOGO_HEIGHT),
								 CMolRect_int_(0,0,texWidth,texHeight));
			end
			
			-- 写用户准备情况
			if pPlayer:GetState() == PLAYERSTATE_READY then
				engine:DrawStringf("已准备",
								  CMolRect_int_(playerInfo[i].ReadyPos[1],playerInfo[i].ReadyPos[2],playerInfo[i].ReadyPos[1]+200,playerInfo[i].ReadyPos[2]+40),
								  CMolColor(255,255,0,0));
			end
			
			-- 显示用户定时器
			local curTime = engine:GetUserTimer(i-1);
			if curTime > 0 then
				engine:DrawStringf(tostring(curTime),
								  CMolRect_int_(playerInfo[i].TimerPos[1],playerInfo[i].TimerPos[2],playerInfo[i].TimerPos[1]+200,playerInfo[i].TimerPos[2]+40),
								  CMolColor(255,255,255,255));
			end
		else 
			playerInfo[i].Logotex = -1;
		end
	end
	
   --[[for i = 1 , totalrow do		
      for j = 1 , totallist do
        engine:Draw2dLine(CMolPosition2d_int_(0,68+i*36),CMolPosition2d_int_(800,68+i*36),CMolColor(255,255,0,0));
		engine:Draw2dLine(CMolPosition2d_int_(28+j*36,71),CMolPosition2d_int_(28+j*36,800),CMolColor(255,255,0,0));
      end
   end	]]--
end

--
-- 用户加载游戏中用到的资源
-- 
function LoadGameResources()
	engine:LoadGUIConfig("游戏界面\\gamemainframe.gui");
	
	m_texChess1 = engine:LoadTexture("游戏图片\\chess1.png");
	m_texChess2 = engine:LoadTexture("游戏图片\\chess2.png");
	m_texChessSel = engine:LoadTexture("游戏图片\\chesssel.png");
	m_bgTex = engine:LoadTexture("游戏图片\\bg.png");
	m_texPlayerType1 = engine:LoadTexture("游戏图片\\heifang.png");
	m_texPlayerType2 = engine:LoadTexture("游戏图片\\baifang.png");
	
    -- 初始棋盘
    InitChessPan(totalrow,totallist);	
end

-- 
-- 用于处理游戏中事件
-- event 从系统中传过来的要处理的游戏事件，这些事件包括按键，鼠标，GUI和其它事件
--
function OnProcessGameEvent(event)
	local myevent = toHelper.toMolEvent(event);
	
	if myevent.mEventType == MOLET_GUI_EVENT then                      -- GUI事件
		-- 如果用户处于旁观状态，直接返回
		if engine:IsLookonMode() == true then return end;
		
		if myevent.mGuiEvent.EventType == MOLGET_BUTTON_CLICKED then
			local ctrlId = myevent.mGuiEvent.Caller:GetID();			
			if ctrlId == IDD_MAINFRAME_START_GAME then           -- 准备游戏
                -- 给服务器发送玩家准备消息
                local out = CMolMessageOut(IDD_MESSAGE_FRAME);
                out:writeShort(IDD_MESSAGE_READY_START);
                engine:Send(out);
				
				engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_START_GAME,false);
            elseif ctrlId == IDD_MAINFRAME_RENSHU_BTN then       -- 认输
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_RENSHU);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_RENSHU_BTN,false);	
            elseif ctrlId == IDD_MAINFRAME_HUOQI_BTN then        -- 请求和棋
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_HUOQI);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUOQI_BTN,false);	
            elseif ctrlId == IDD_QIUHEDIG_OK then                -- 游戏和棋提示框确定按钮
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_HUOQI_OK);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:ShowControlById(IDD_QIUHEDIG,false);  
            elseif ctrlId == IDD_QIUHEDIG_CONCEL then            -- 游戏和棋提示框取消按钮
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_HUOQI_CONCEL);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:ShowControlById(IDD_QIUHEDIG,false);  	
			elseif ctrlId == IDD_MAINFRAME_HUIQI_BTN then        -- 请求悔棋
				-- 悔棋的时候，必须当前玩家不是自己
				
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_HUIQI);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:ShowControlById(IDD_MAINFRAME_HUIQI_BTN,false);  
			elseif ctrlId == IDD_HUIQIDLG_OK then                -- 确定悔棋
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_HUIQI_OK);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:ShowControlById(IDD_HUIQIDLG,false);  
			elseif ctrlId == IDD_HUIQIDLG_CONCEL then            -- 不同意悔棋	
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_HUIQI_CONCEL);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:ShowControlById(IDD_HUIQIDLG,false);  
            elseif ctrlId == IDD_MAINFRAME_SENDCHAT_BTN then     -- 发送聊天消息
                local myCtrl = engine.__CMolBaseGUIContainer__:FindControlById(IDD_MAINFRAME_CHAT_INPUT);
                local myEditor = toHelper.toMolGUIEditorBox(myCtrl);
                
                if myEditor and myEditor:GetText() ~= "" then                  
                    -- 发送聊天消息到其他玩家
                    local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                    out:writeShort(IDD_MESSAGE_GAMING_CHAT);
                    out:writeShort(m_playerRoomIndex);
                    out:writeString(myEditor:GetText());
                    engine:Send(out);
                    
                    myEditor:SetText("");
                end	

				engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_SENDCHAT_BTN,false);		
			end
		end
    elseif myevent.mEventType == MOLET_MOUSE_INPUT_EVENT then          -- 鼠标事件
		-- 如果用户处于旁观状态，直接返回
		if engine:IsLookonMode() == true then return end;
		
        if myevent.mMouseEvent.EventType == MOLMIE_LMOUSE_PRESSED_DOWN then
            local MouseposX = myevent.mMouseEvent.X;
            local MouseposY = myevent.mMouseEvent.Y;
            
			-- 必须在游戏中状态，而且当前下棋的是自己
            if m_gamestate == GAMESTATE_GAMING and m_playerRoomIndex == engine:GetMeChairID() then
                if ProcessChessSelect(MouseposX,MouseposY) then 
					-- 播放点子声音
					engine:EffectPlay("游戏声音\\dianzi1.wav");	
					
					chesslist[m_curChessPosX][m_curChessPosY] = m_playerRoomIndex+1;
				
                    -- 给服务器发送玩家点子消息
                    local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                    out:writeShort(IDD_MESSAGE_GAMING_DIANZI);
                    out:writeShort(m_playerRoomIndex);
                    out:writeByte(m_curChessPosX);
                    out:writeByte(m_curChessPosY);
                    engine:Send(out);    

					if m_playerRoomIndex == 0 then 
						m_playerRoomIndex = 1;
					elseif m_playerRoomIndex == 1 then 
						m_playerRoomIndex = 0;
					end		

					-- 关闭定时器
					engine:KillGameTimer(IDD_TIMER_XIAZI);
					engine:SetGameTimer(engine:SwitchViewChairID(m_playerRoomIndex),IDD_TIMER_XIAZI,10);
                end
            end
        elseif myevent.mMouseEvent.EventType == MOLMIE_MOUSE_MOVED then
            local MouseposX = myevent.mMouseEvent.X;
            local MouseposY = myevent.mMouseEvent.Y;
            
            if m_gamestate == GAMESTATE_GAMING and m_playerRoomIndex == engine:GetMeChairID() then
                -- 在游戏状态下根据鼠标位置显示选择图片
                ProcessChessSelect(MouseposX,MouseposY);
            end
        end
	elseif myevent.mEventType == MOLET_KEY_INPUT_EVENT then                   -- 按键事件

	end	
end

--
-- 用于处理游戏中定时器事件
-- IDEvent 要处理的游戏中的定时器ID
--
function OnProcessGameTimer(IDEvent)
	if IDEvent == IDD_TIMER_XIAZI then       -- 下子定时器
		engine.__CMolBaseGUIContainer__:ShowControlById(IDD_QIUHEDIG,false); 
		engine.__CMolBaseGUIContainer__:ShowControlById(IDD_HUIQIDLG,false);  
		
		-- 选择空闲的地方下棋
		local isOk = true;
		local chessX = math.random(totalrow);
		local chessY = math.random(totallist);

		if chesslist[chessX][chessY] ~= 0 then				
			while isOk do
				chessX = math.random(totalrow);
				chessY = math.random(totallist);
				
				if chesslist[chessX][chessY] == 0 then	
					isOk = false;
					break;
				end
			end
		end
		
		-- 必须在游戏中状态，而且当前下棋的是自己,并且不能处于旁观状态
		if m_gamestate == GAMESTATE_GAMING and m_playerRoomIndex == engine:GetMeChairID() and engine:IsLookonMode() == false then
			chesslist[chessX][chessY] = m_playerRoomIndex+1;
			
			m_curChessPosX = chessX;
			m_curChessPosY = chessY; 			
			
			-- 播放点子声音
			engine:EffectPlay("游戏声音\\dianzi1.wav");	
		
			-- 给服务器发送玩家点子消息
			local out = CMolMessageOut(IDD_MESSAGE_ROOM);
			out:writeShort(IDD_MESSAGE_GAMING_DIANZI);
			out:writeShort(m_playerRoomIndex);
			out:writeByte(chessX);
			out:writeByte(chessY);
			engine:Send(out);    

			if m_playerRoomIndex == 0 then 
				m_playerRoomIndex = 1;
			elseif m_playerRoomIndex == 1 then 
				m_playerRoomIndex = 0;
			end		
		end
	end
end

--
-- 用于处理房间中的网络消息
--
-- @param msg 接收到要处理的网络消息
--
function OnProcessPlayerGameRoomMsg(msg)
	local myMsg = toHelper.toMolMessageIn(msg);
	local myMsgSubId = myMsg:readShort();
	
	if myMsgSubId == IDD_MESSAGE_GAME_START then              -- 开始游戏
		m_playerRoomIndex = myMsg:readShort();
		
		-- 重新初始化整个棋盘
		ResetChessPan();
		
		local myTextarea = toHelper.toMolGUITextarea(engine.__CMolBaseGUIContainer__:FindControlById(IDD_MAINFRAME_CHAT_MESSAGE));
		if myTextarea then
			myTextarea:AddString("玩家:"..tostring(m_playerRoomIndex).." 开始下子。",CMolColor(255,255,0,0));
		end
		
		if engine:IsLookonMode() == false then
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUIQI_BTN,true);
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUOQI_BTN,true);
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_RENSHU_BTN,true);
		end
		
		-- 播放声音
		engine:EffectPlay("游戏声音\\startgame.wav");	
		
		m_gamestate = GAMESTATE_GAMING;  
		engine:SetGameTimer(engine:SwitchViewChairID(m_playerRoomIndex),IDD_TIMER_XIAZI,10);
	elseif myMsgSubId == IDD_MESSAGE_GAMING_DIANZI then              -- 用户点子
		local pPlayerId = myMsg:readShort();
		local chessposx = myMsg:readByte();
		local chessposy = myMsg:readByte();
		
		if pPlayerId == m_playerRoomIndex then
			if ProcessMouse(chessposx,chessposy,m_playerRoomIndex+1) then			
				-- 播放点子声音
				engine:EffectPlay("游戏声音\\dianzi1.wav");			
				
				if pPlayerId == 0 then 
					m_playerRoomIndex = 1;
				elseif pPlayerId == 1 then 
					m_playerRoomIndex = 0;
				end
			end
		end
		
		engine:SetGameTimer(engine:SwitchViewChairID(m_playerRoomIndex),IDD_TIMER_XIAZI,10);
	elseif myMsgSubId == IDD_MESSAGE_LOOKON_ENTER_ROOM or myMsgSubId == IDD_MESSAGE_DISCONN_BACK then              -- 旁观,断线重回状态下
		m_playerRoomIndex = myMsg:readShort();
		m_gamestate = GAMESTATE_GAMING; 
		
		for i = 1 , totalrow do
		  for j = 1 , totallist do
			local chess = myMsg:readByte();
			
			if chess > 0 then
				ProcessMouse(i,j,chess);
			end
		  end
		end		

		engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_START_GAME,false);	
		
		if engine:IsLookonMode() == false then
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUIQI_BTN,true);
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUOQI_BTN,true);
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_RENSHU_BTN,true);
		end
		
		engine:SetGameTimer(engine:SwitchViewChairID(m_playerRoomIndex),IDD_TIMER_XIAZI,10);
	elseif myMsgSubId == IDD_MESSAGE_GAME_END then                        -- 游戏结束
		m_gamestate = GAMESTATE_END; 

		if engine:IsLookonMode() == false then		
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUIQI_BTN,false);
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUOQI_BTN,false);
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_RENSHU_BTN,false);	
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_START_GAME,true);
		end
		
		engine:KillGameTimer(IDD_TIMER_XIAZI);
		
		-- 播放游戏结束音乐
		engine:EffectPlay("游戏声音\\win.wav");	
	elseif myMsgSubId == IDD_MESSAGE_GAMING_CHAT then                     -- 聊天消息
		local playerId = myMsg:readShort();
		local chat = myMsg:readString();
		
		local myTextarea = toHelper.toMolGUITextarea(engine.__CMolBaseGUIContainer__:FindControlById(IDD_MAINFRAME_CHAT_MESSAGE));
		if myTextarea then
			myTextarea:AddString("玩家:"..tostring(playerId)..chat,CMolColor(255,255,255,255));
		end
		
		if engine:GetMeChairID() == playerId then
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_SENDCHAT_BTN,true);
		end
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUOQI then                    -- 有人请求和棋
		local playerId = myMsg:readShort();
             
		if playerId ~= engine:GetMeChairID() then                    
			engine:ShowGUIContainer(IDD_QIUHEDIG,"gui\\qiuhuodialog.gui",SANPSTYLE_CENTER);
		end		
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUOQI_CONCEL then             -- 有人不同意和棋
		local playerId = myMsg:readShort();		
            
		if playerId == engine:GetMeChairID() then
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUOQI_BTN,true);
		end   
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUIQI then                    -- 有人请求悔棋
		local playerId = myMsg:readShort();
             
		if playerId ~= engine:GetMeChairID() then                    
			engine:ShowGUIContainer(IDD_HUIQIDLG,"gui\\huiqidialog.gui",SANPSTYLE_CENTER);
		end	
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUIQI_OK then                 -- 已经同意悔棋
		local chessposx = myMsg:readByte();
		local chessposy = myMsg:readByte();
		
		chesslist[chessposx][chessposy] = 0;
		
		if m_playerRoomIndex == 0 then 
			m_playerRoomIndex = 1;
		elseif pPlayerId == 1 then 
			m_playerRoomIndex = 0;
		end
		
		engine:SetGameTimer(engine:SwitchViewChairID(m_playerRoomIndex),IDD_TIMER_XIAZI,10);
	end
end
