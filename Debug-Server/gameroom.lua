dofile("defines.lua");
dofile("gamelogic.lua");

--
-- 用于处理用户进入房间的消息
-- room 用户进入的游戏房间
-- playerId 用户在房间中的ID
--
function OnProcessEnterRoomMsg(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
    
    -- 如果房间状态处于游戏状态，用户就不能进入房间
    if NormalRoom:GetRoomState() == ROOMSTATE_GAMING then
        return;
    end    
	
	-- 设置玩家状态为等待状态
    local player = NormalRoom:GetPlayer(playerId);
    if player == nil then return end
    
    local out = CMolMessageOut(IDD_MESSAGE_ROOM);
    out:writeShort(IDD_MESSAGE_ROOM_ENTER);
	out:writeShort(playerId);
	out:writeString(NormalRoom:GetName());
	out:writeShort(NormalRoom:GetPlayerCount());
	
	for i = 1 , NormalRoom:GetPlayerCount() do
		local pPlayer = NormalRoom:GetPlayer(i-1);
		if pPlayer then
			out:writeLong(pPlayer:GetID());
			out:writeShort(i-1);
			out:writeShort(NormalRoom:GetID());
			
			if NormalRoom:GetPlayer(i-1):GetState() == PLAYERSTATE_READY then
				out:writeShort(1);
			else
				out:writeShort(0);			
			end
		end
	end
   
    --NormalRoom:PrintDebugInfo("玩家:"..tostring(playerId).."进入房间了。"..tostring(NormalRoom:GetID()).."\n");
    
    -- 告诉所有玩家当前用户进入房间
    NormalRoom:SendAllPlayerMsg(out);
end

-- 
-- 用于处理用户离开房间的消息
-- room 用户离开的游戏房间
-- playerId 用户在房间中的ID
--
function OnProcessLeaveRoomMsg(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	-- 首先检查当前房间是否在游戏中，如果不在先向房间中其它玩家广播这个消息，然后从房间中删除这个玩家
    if NormalRoom:GetRoomState() == ROOMSTATE_GAMING then
        return;
    end   
	
	--NormalRoom:PrintDebugInfo("有用户退出房间:"..tostring(NormalRoom:GetID()));
end

--
-- 用于处理用户准备消息
-- room 用户进入的游戏房间
-- playerId 用户在房间中的ID
--
function OnProcessPlayerReadyMes(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
    
    -- 如果房间状态处于游戏状态，用户就不能准备成功
    if NormalRoom:GetRoomState() == ROOMSTATE_GAMING then
        return;
    end
    
    local player = NormalRoom:GetPlayer(playerId);
    if player == nil then return end
    
    player:SetState(PLAYERSTATE_READY);
    
    -- 设置房间状态为等待状态
    NormalRoom:SetRoomState(ROOMSTATE_WAITING);
    
    --NormalRoom:PrintDebugInfo("房间:"..tostring(NormalRoom:GetID()).."玩家"..tostring(playerId).."有人已经准备好游戏了。\n");
    
    -- 如果房间没有设置房主，就先设置房主
    if NormalRoom:GetMaster() == -1 then
        NormalRoom:SetMaster(playerId);
    end
	
	-- 向房间中所有用户广播这个用户已经准备好了
    local out = CMolMessageOut(IDD_MESSAGE_ROOM);
    out:writeShort(IDD_MESSAGE_PLAYER_READYED);
	out:writeShort(playerId);
	out:writeShort(NormalRoom:GetPlayerCount());
	
	for i = 1 , NormalRoom:GetPlayerCount() do
		local pPlayer = NormalRoom:GetPlayer(i-1);
		if pPlayer then	
			out:writeLong(pPlayer:GetID());
			out:writeShort(i-1);
			out:writeShort(NormalRoom:GetID());
			
			if pPlayer:GetState() == PLAYERSTATE_READY then
				out:writeShort(1);
			else
				out:writeShort(0);			
			end
		end
	end

    NormalRoom:SendAllPlayerMsg(out);
	
	--NormalRoom:PrintDebugInfo("此局玩家:"..tostring(NormalRoom:GetMaster()).."是房主,房间人数:"..tostring(NormalRoom:GetPlayerCount(PLAYERSTATE_READY)).."\n");
    
    -- 但三个用户都准备好后，开始游戏
    if NormalRoom:GetPlayerCount(PLAYERSTATE_READY) == 3 then		
        IDD_TIMER_START_GAME = NormalRoom:StartTimer(1000);
    end
end

--
-- 用于处理用户游戏中消息
-- room 用户进入的游戏房间
-- playerId 用户在房间中的ID
-- mes 要处理的用户消息
--
function OnProcessPlayerGamingMes(room , playerId , mes)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
    
    local msgin = toHelper.toMessageIn(mes);
    if msgin == nil then return end
    
    local msgId = msgin:readShort();
    
    if msgId == IDD_MESSAGE_GAMING_JIAOFEN then                        -- 用户叫分
		local userJiaofen = msgin:readShort();
		
		--NormalRoom:PrintDebugInfo("用户:"..tostring(playerId).."叫"..tostring(userJiaofen).."分。\n");
		
		-- 如果玩家直接叫3分,那么直接开始游戏
		if userJiaofen == 3 then
			m_PlayerMaster = playerId;
			NormalRoom:SetCurrentPlayer(playerId);
			NormalRoom:StopTimer(IDD_TIMER_JIAOFEN);  
			
			m_playerCardData[playerId+1][18] = m_shengyuCardData[1];
			m_playerCardData[playerId+1][19] = m_shengyuCardData[2];
			m_playerCardData[playerId+1][20] = m_shengyuCardData[3];
			
			-- 谁先叫分，谁先出牌
			local out = CMolMessageOut(IDD_MESSAGE_ROOM);
			out:writeShort(IDD_MESSAGE_OUTCARD);
			out:writeShort(m_PlayerMaster);
			out:writeShort(playerId);
			out:writeShort(userJiaofen);
			
			NormalRoom:SendAllPlayerMsg(out);
			
			m_curOutCardPlayer = playerId;
			NormalRoom:StopTimer(IDD_TIMER_OUTCARD);
			IDD_TIMER_OUTCARD = NormalRoom:StartTimer(30000); 
			m_startJiaoFenPlayer = -1;	
			m_curJiaoFenPlayer = -1;
			return;
		end
		
		if userJiaofen > m_jiaofenResult then
			m_jiaofenResult = userJiaofen;
			m_oldjiaofenresult[table.getn(m_oldjiaofenresult)+1] = m_jiaofenResult;
			m_curJiaoFenPlayer = playerId;
		end
		
		local nextplayer = NormalRoom:GetCurNextPlayer();	
	
		if m_startJiaoFenPlayer ~= nextplayer then
			local out = CMolMessageOut(IDD_MESSAGE_ROOM);
			out:writeShort(IDD_MESSAGE_GAMING_JIAOFEN);
			out:writeShort(playerId);
			out:writeShort(userJiaofen);
			out:writeShort(nextplayer);
			
			NormalRoom:SendAllPlayerMsg(out);
			
			NormalRoom:StopTimer(IDD_TIMER_JIAOFEN);  
			IDD_TIMER_JIAOFEN = NormalRoom:StartTimer(30000); 
		else
			-- 如果一圈转完以后，还是无人叫分，那么重新发牌
			if m_jiaofenResult == 0 then
				NormalRoom:StopTimer(IDD_TIMER_JIAOFEN);  
				--NormalRoom:StartTimer(IDD_TIMER_JIAOFEN,30000); 
				
				IDD_TIMER_START_GAME = NormalRoom:StartTimer(1000);
			else
				m_PlayerMaster = m_curJiaoFenPlayer;
				NormalRoom:SetCurrentPlayer(m_curJiaoFenPlayer);
				NormalRoom:StopTimer(IDD_TIMER_JIAOFEN);  
				
				m_playerCardData[m_curJiaoFenPlayer+1][18] = m_shengyuCardData[1];
				m_playerCardData[m_curJiaoFenPlayer+1][19] = m_shengyuCardData[2];
				m_playerCardData[m_curJiaoFenPlayer+1][20] = m_shengyuCardData[3];
				
				local out = CMolMessageOut(IDD_MESSAGE_ROOM);
				out:writeShort(IDD_MESSAGE_OUTCARD);
				out:writeShort(m_PlayerMaster);
				out:writeShort(m_curJiaoFenPlayer);
				out:writeShort(m_jiaofenResult);
				
				NormalRoom:SendAllPlayerMsg(out);
				
				m_curOutCardPlayer = m_curJiaoFenPlayer;
				NormalRoom:StopTimer(IDD_TIMER_OUTCARD);
				IDD_TIMER_OUTCARD = NormalRoom:StartTimer(30000); 
				m_startJiaoFenPlayer = -1;
				m_curJiaoFenPlayer = -1;
			end
		end
	elseif msgId == IDD_MESSAGE_OUTCARD then                                  -- 用户出牌
		NormalRoom:StopTimer(IDD_TIMER_OUTCARD);
		local cardcount = msgin:readShort();
		
		-- 首先清空上一次的出牌数据
		for i = 1 , table.getn(m_curOutCardDate) do
			m_curOutCardDate[i] = nil;
		end
	
		for i = 1,cardcount do
			m_curOutCardDate[i] = msgin:readShort();
		end
		
		-- 从玩家牌数据中清除玩家出牌
		GetCardDataByPlayer(playerId+1,m_curOutCardDate);
		
		local nextplayer = NormalRoom:GetCurNextPlayer();		
		--NormalRoom:PrintDebugInfo("当前出牌用户:"..tostring(playerId).."当前用户:"..tostring(NormalRoom:GetCurrentPlayer()).."下一个出牌用户:"..tostring(nextplayer).."。\n");
		
		-- 如果出牌用户已经掉线的话，就托管这个用户
		if IsOutLinePlayer(nextplayer) then
			IDD_TIMER_PLAYER_TUOGUAN = NormalRoom:StartTimer(10000); 
		end
		
		-- 将牌数据发送给其它玩家
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_OUTCARD_DATA);
		out:writeShort(playerId);
		out:writeShort(nextplayer);
		out:writeShort(cardcount);
		
		for i = 1,cardcount do
			out:writeShort(m_curOutCardDate[i]);
		end
		
		NormalRoom:SendAllPlayerMsg(out);
		
		m_curOutCardPlayer = playerId;		
		m_startOutCardPlayer = m_curOutCardPlayer;

		IDD_TIMER_OUTCARD = NormalRoom:StartTimer(30000); 

		--NormalRoom:PrintDebugInfo("开始出牌玩家:"..tostring(m_startOutCardPlayer).."当前出牌玩家:"..tostring(m_curOutCardPlayer));	

		-- 然后检查是否牌已经出完，如果出完，看是地主赢还是农民赢
		if table.getn(m_playerCardData[playerId+1]) <= 0 then
			NormalRoom:StopTimer(IDD_TIMER_OUTCARD);
			
			-- 可以结束游戏了
			EndGame(NormalRoom,playerId);
		end		
	elseif msgId == IDD_MESSAGE_PASS_OUT_CARD then                            -- 用户过牌
		NormalRoom:StopTimer(IDD_TIMER_OUTCARD);	
	
		local nextplayer = NormalRoom:GetCurNextPlayer();	
	
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_PASS_OUT_CARD);
		out:writeShort(playerId);
		out:writeShort(nextplayer);
		
		NormalRoom:SendAllPlayerMsg(out);	
		
		--m_curOutCardPlayer = playerId;		
		if m_startOutCardPlayer == nextplayer then
			--NormalRoom:PrintDebugInfo("在这里清除原来出的扑克。");
			m_startOutCardPlayer = m_curOutCardPlayer;
			-- 首先清空上一次的出牌数据
			for i = 1 , table.getn(m_curOutCardDate) do
				m_curOutCardDate[i] = nil;
			end
		end	
			
		-- 如果出牌用户已经掉线的话，就托管这个用户
		if IsOutLinePlayer(nextplayer) then		
			IDD_TIMER_PLAYER_TUOGUAN = NormalRoom:StartTimer(10000); 
		else				
			IDD_TIMER_OUTCARD = NormalRoom:StartTimer(30000);
		end
		
		--NormalRoom:PrintDebugInfo("过牌后开始出牌玩家:"..tostring(m_startOutCardPlayer).."当前出牌玩家:"..tostring(m_curOutCardPlayer));	
	elseif msgId == IDD_MESSAGE_CHAT then                                       -- 用户聊天消息
		local chatcon = msgin:readString();
		
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_CHAT);
		out:writeShort(playerId);
		out:writeString(chatcon:c_str());
		
		NormalRoom:SendAllPlayerMsg(out);
	elseif msgId == IDD_MESSAGE_CHAT_BIAOQING then                                       -- 用户聊天表情消息
		local chatcon = msgin:readString();
		
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_CHAT_BIAOQING);
		out:writeShort(playerId);
		out:writeString(chatcon:c_str());
		
		NormalRoom:SendAllPlayerMsg(out);
	elseif msgId == IDD_MESSAGE_GAME_START then                             -- 游戏开始
        -- 开始游戏，向玩家发送开始游戏玩家
        local out = CMolMessageOut(IDD_MESSAGE_ROOM);
        out:writeShort(IDD_MESSAGE_GAME_START);
        out:writeShort(NormalRoom:GetCurrentPlayer());
        
        NormalRoom:SendAllPlayerMsg(out);         
        
		IDD_TIMER_JIAOFEN = NormalRoom:StartTimer(30000); 	
	end
end

-- 
-- 用于处理用户断开连接消息
-- room 用户进入的游戏房间
-- playerId 用户在房间中的ID
--
function OnProcessDisconnectNetMes(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
    -- 如果房间状态不处于游戏状态，就不处理游戏
    if NormalRoom:GetRoomState() ~= ROOMSTATE_GAMING then
        return;
    end
	
	m_outlineplayercount = m_outlineplayercount + 1;
	m_outlineplayers[m_outlineplayercount] = playerId;	
	
	-- 如果房间中有两个掉线，游戏结束
	if m_outlineplayercount >= 2 then
		for i = 1 , 3 do
			if IsOutLinePlayer(i) == false then
				EndGame(NormalRoom,i);
				break;
			end
		end	
	end
end

-- 
-- 用于处理用户断线重回连接消息
-- room 用户进入的游戏房间
-- playerId 用户在房间中的ID
--
function OnProcessDisconnectBackNetMes(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	--NormalRoom:PrintDebugInfo("玩家:"..tostring(playerId).."已经掉线重回了。\n");
	
	m_outlineplayercount = m_outlineplayercount - 1;
	for i = 1 , table.getn(m_outlineplayers) do
		if m_outlineplayers[i] == playerId then
			m_outlineplayers[i] = nil;
			break;
		end
	end
	
	-- 如果游戏还处于进行状态下
	if NormalRoom:GetRoomState() == ROOMSTATE_GAMING then
		local pPlayer = NormalRoom:GetPlayer(playerId);
		if pPlayer == nil then return end
		
		m_outlineplayercount = 0;
		for i = 1 , table.getn(m_outlineplayers) do
			m_outlineplayers[i] = nil;
		end
		
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_REENTER_ROOM);	
		out:writeShort(1);                           -- 向掉线用户重新发送游戏信息
		out:writeLong(pPlayer:GetID());
		out:writeShort(NormalRoom:GetID());
		out:writeShort(playerId);
		out:writeShort(m_curOutCardPlayer);
		out:writeShort(NormalRoom:GetCurrentPlayer());
		out:writeShort(m_curJiaoFenPlayer);
		out:writeShort(m_PlayerMaster);	

		if m_curJiaoFenPlayer >= 0 and m_curJiaoFenPlayer < 3 then	
			out:writeShort(NormalRoom:GetCurTime(IDD_TIMER_JIAOFEN));    -- 发送当前叫分定时器时间		
			
			-- 发送用户已经叫过的的分数
			out:writeShort(table.getn(m_oldjiaofenresult));
			for i = 1 , table.getn(m_oldjiaofenresult) do
				out:writeShort(m_oldjiaofenresult[i]);
			end
		else
			out:writeShort(NormalRoom:GetCurTime(IDD_TIMER_OUTCARD));    -- 发送当前出牌定时器时间
		end
		
		out:writeShort(table.getn(m_playerCardData[playerId+1]));
		
		for i = 1 , table.getn(m_playerCardData[playerId+1]) do
			out:writeByte(m_playerCardData[playerId+1][i]);
		end
		
		out:writeByte(m_shengyuCardData[1]);
		out:writeByte(m_shengyuCardData[2]);
		out:writeByte(m_shengyuCardData[3]);
		
		-- 如果有用户出牌的话，发送出牌数据
		out:writeShort(table.getn(m_curOutCardDate));	
		if table.getn(m_curOutCardDate) > 0 and 
			m_curOutCardPlayer ~= -1 then						
			for i = 1,table.getn(m_curOutCardDate) do
				out:writeShort(m_curOutCardDate[i]);
			end			
		end	

		-- 发送其它两家玩家的剩余牌
		out:writeShort(NormalRoom:GetPlayerCount()-1);
		for index = 1 , NormalRoom:GetPlayerCount() do
			if (index-1) ~= playerId then
				out:writeShort(index-1);
				out:writeShort(table.getn(m_playerCardData[index]));
				for i = 1 , table.getn(m_playerCardData[index]) do
					out:writeByte(m_playerCardData[index][i]);
				end				
			end
		end

		NormalRoom:SendPlayerMsg(playerId,out);  
		
		-- 向房间其它用户发送玩家返回房间信息
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_REENTER_ROOM);	
		out:writeShort(2);                           
		out:writeShort(playerId);

		NormalRoom:SendOtherPlayerMsg(playerId,out);  	
	else
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAME_OVER);
		out:writeShort(m_sucplayer);
		
		NormalRoom:SendPlayerMsg(playerId,out); 
	end
end

--
-- 用于处理用户房间定时器消息
-- room 要处理的游戏房间
-- timerId 要处理的定时器ID
--
function OnProcessTimerMsg(room , timerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
    
    if timerId == IDD_TIMER_START_GAME then                               -- 游戏开始定时器
        -- 设置房间状态为游戏中状态
        NormalRoom:SetRoomState(ROOMSTATE_GAMING);
        NormalRoom:SetAllPlayerState(PLAYERSTATE_GAMING);
          
		-- 首先重置牌数据
		ResetGameData();
		
        -- 得到牌数据
        GetCardData(); 
		
		-- 设置当前游戏开始玩家
		m_startJiaoFenPlayer = GetJiaoPaiPlayer(m_jiaofencard);
		if m_startJiaoFenPlayer ~= -1 then
			m_curJiaoFenPlayer = m_startJiaoFenPlayer;
			NormalRoom:SetCurrentPlayer(m_startJiaoFenPlayer);
		end
        
        -- 向玩家发送牌数据
		if NormalRoom:GetPlayerCount() <= 3 then		
			for index = 1 , NormalRoom:GetPlayerCount() do   
				local pPlayer = NormalRoom:GetPlayer(index-1);
				if pPlayer then			
					local out = CMolMessageOut(IDD_MESSAGE_ROOM);
					out:writeShort(IDD_MESSAGE_READY_START);			
					out:writeLong(pPlayer:GetID());
					out:writeShort(index-1);
					
					--NormalRoom:PrintDebugInfo("房间:"..tostring(NormalRoom:GetID()).."牌数据:"..tostring(index).." "..tostring(table.getn(m_playerCardData)));
					
					for i = 1 , 17 do
						out:writeByte(m_playerCardData[index][i]);
					end
					
					out:writeByte(m_shengyuCardData[1]);
					out:writeByte(m_shengyuCardData[2]);
					out:writeByte(m_shengyuCardData[3]);

					NormalRoom:SendAllPlayerMsg(out);  
				end
			end
		end
		
		--NormalRoom:PrintDebugInfo("房间:"..tostring(NormalRoom:GetID()).."已经发送完牌数据。\n");
		
		NormalRoom:StopTimer(IDD_TIMER_START_GAME); 	
	elseif timerId == IDD_TIMER_JIAOFEN then                                 -- 用户叫分定时器
		local curplayer = NormalRoom:GetCurrentPlayer();
		
		-- 如果这个叫分用户已经掉线的话，就直接叫三分
		if IsOutLinePlayer(curplayer) then
			m_PlayerMaster = curplayer;
			NormalRoom:SetCurrentPlayer(curplayer);
			
			m_playerCardData[curplayer+1][18] = m_shengyuCardData[1];
			m_playerCardData[curplayer+1][19] = m_shengyuCardData[2];
			m_playerCardData[curplayer+1][20] = m_shengyuCardData[3];
			
			-- 谁先叫分，谁先出牌
			local out = CMolMessageOut(IDD_MESSAGE_ROOM);
			out:writeShort(IDD_MESSAGE_OUTCARD);
			out:writeShort(m_PlayerMaster);
			out:writeShort(curplayer);
			out:writeShort(3);
			
			NormalRoom:SendAllPlayerMsg(out);
			
			m_curOutCardPlayer = curplayer;
			NormalRoom:StopTimer(IDD_TIMER_OUTCARD);
			IDD_TIMER_OUTCARD = NormalRoom:StartTimer(30000); 
			m_startJiaoFenPlayer = -1;	
			m_curJiaoFenPlayer = -1;
			
			NormalRoom:StopTimer(IDD_TIMER_JIAOFEN);  
		end
	elseif timerId == IDD_TIMER_PLAYER_TUOGUAN then                           -- 用户托管定时器
	
		-- 用户托管出牌
		PlayerSendCard(NormalRoom,NormalRoom:GetCurrentPlayer());
		
		NormalRoom:StopTimer(IDD_TIMER_PLAYER_TUOGUAN);
	elseif timerId == IDD_TIMER_OUTCARD then                                  -- 出牌定时器
		local curplayer = NormalRoom:GetCurrentPlayer();
		
		-- 如果这个叫分用户已经掉线的话，就托管用户
		if IsOutLinePlayer(curplayer) then
			TuoGuanOutCard(NormalRoom);
		end

		NormalRoom:StopTimer(IDD_TIMER_OUTCARD);	
	end
end
