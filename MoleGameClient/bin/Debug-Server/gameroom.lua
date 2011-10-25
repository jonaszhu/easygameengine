dofile("defines.lua");
dofile("gamelogic.lua");

--
-- 用于处理用户进入房间的消息
-- room 用户进入的游戏房间
-- playerId 用户在房间中的ID
--
function OnProcessEnterRoomMsg(room , playerId)

end

-- 
-- 用于处理用户离开房间的消息
-- room 用户离开的游戏房间
-- playerId 用户在房间中的ID
--
function OnProcessLeaveRoomMsg(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
    local pPlayer = toHelper.toPlayer(NormalRoom:GetPlayer(playerId));
    if pPlayer == nil then return end
	
	-- 如果用户不是旁观用户，并且房间处于游戏中的话，那么就先结束游戏
	if pPlayer:IsLookOn() == false and NormalRoom:GetRoomState() == ROOMSTATE_GAMING then
		NormalRoom:GameEnd();
	end
end

--
-- 用于处理用户准备消息
-- room 用户进入的游戏房间
-- playerId 用户在房间中的ID
--
function OnProcessPlayerReadyMes(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	NormalRoom:PrintDebugInfo("玩家:"..tostring(playerId).."准备好游戏了。");
	
    -- 如果用户有两个用户准备就可以开始游戏
    if NormalRoom:GetPlayerCount(PLAYERSTATE_READY) == 2 then
        -- 设置房间状态为游戏中状态
        NormalRoom:SetRoomState(ROOMSTATE_GAMING);
        NormalRoom:SetAllPlayerState(PLAYERSTATE_GAMING);
		
		NormalRoom:GameStart();
		
		m_curActivePlayer = NormalRoom:GetCurrentPlayer();
		
        -- 如果棋牌是第一次使用就先建立,否则直接使用
        if m_chespanisCreated == false then
            InitChessPan(totalrow,totallist);
            m_chespanisCreated = true;
        else
            ResetChessPan();
        end		
    
        -- 开始游戏，向玩家发送开始游戏玩家
        local out = CMolMessageOut(IDD_MESSAGE_ROOM);
        out:writeShort(IDD_MESSAGE_GAME_START);
        out:writeShort(m_curActivePlayer);   
		
        NormalRoom:SendTableMsg(-1,out);
		NormalRoom:SendLookOnMes(-1,out);
		
		-- 开启下子定时器
		IDD_TIMER_XIAZI = NormalRoom:StartTimer(30000);
    end	
end

--
-- 用于处理用户游戏中消息
-- room 用户进入的游戏房间
-- playerId 用户在房间中的ID
-- mes 要处理的用户消息
--
function OnProcessPlayerGamingMes(room , playerId , mes)
 
end

-- 
-- 用于处理用户断开连接消息
-- room 用户进入的游戏房间
-- playerId 用户在房间中的ID
--
function OnProcessDisconnectNetMes(room , playerId)

end

-- 
-- 用于处理用户断线重回连接消息
-- room 用户进入的游戏房间
-- playerId 用户在房间中的ID
--
function OnProcessDisconnectBackNetMes(room , playerId)
 
end

--
-- 用于处理用户房间定时器消息
-- room 要处理的游戏房间
-- timerId 要处理的定时器ID
--
function OnProcessTimerMsg(room , timerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	if timerId == IDD_TIMER_XIAZI then
		NormalRoom:PrintDebugInfo("玩家:"..tostring(m_curActivePlayer).."开始下子了。");
		--NormalRoom:StopTimer(IDD_TIMER_XIAZI);
		
		-- 首先检查这个玩家是否是机器人，如果是机器人的话，就帮它下
		local pPlayer = toHelper.toPlayer(NormalRoom:GetPlayer(m_curActivePlayer));
		if pPlayer == nil then return end
		
		if pPlayer:GetType() == PLAYERTYPE_ROBOT then
			math.randomseed(os.time())
			
			local out = CMolMessageOut(IDD_MESSAGE_ROOM);
			out:writeShort(IDD_MESSAGE_GAMING_DIANZI);
			out:writeShort(m_curActivePlayer);  
			out:writeByte(math.random() * totalrow + 1);
			out:writeByte(math.random() * totallist + 1);

			NormalRoom:SendTableMsg(-1,out);
			NormalRoom:SendLookOnMes(-1,out);			

			if m_curActivePlayer == 0 then 
				m_curActivePlayer = 1;
			elseif m_curActivePlayer == 1 then 
				m_curActivePlayer = 0;
			end				
		end
	end
end
