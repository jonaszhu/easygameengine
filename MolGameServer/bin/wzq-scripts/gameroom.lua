dofile("defines.lua");
dofile("gamelogic.lua");

--
-- 用于处理旁观用户进入房间的消息
-- room 用户进入的游戏房间
-- playerId 用户在房间中的ID
--
function OnProcessEnterRoomMsg(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	-- 如果用户是旁观状态，就发送用户状态
	NormalRoom:PrintDebugInfo("玩家:"..tostring(playerId).."旁观进入房间了。");	
	local out = CMolMessageOut(IDD_MESSAGE_ROOM);
	out:writeShort(IDD_MESSAGE_LOOKON_ENTER_ROOM);
	out:writeShort(m_curActivePlayer);

	-- 发送棋牌数据
    for i = 1 , totalrow do
	  for j = 1 , totallist do
		out:writeByte(chesslist[i][j]);
	  end
	end	
	NormalRoom:SendLookOnMes(playerId,out);
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
	
	-- 如果用户不是旁观用户，并且房间处于游戏中的话，那么就先结束游戏,强退的人会被扣分
	if NormalRoom:GetRoomState() == ROOMSTATE_GAMING then
		pPlayer:SetMoney(pPlayer:GetMoney()-10);
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
	
	--NormalRoom:PrintDebugInfo("玩家:"..tostring(playerId).."准备好游戏了。");
	
    -- 如果用户有两个用户准备就可以开始游戏
    if NormalRoom:GetPlayerCount(PLAYERSTATE_READY) == 2 then
		NormalRoom:GameStart();
		
		math.randomseed(os.time())		
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
		NormalRoom:StartTimer(IDD_TIMER_XIAZI,10);
    end	
end

--
-- 用于处理用户房间中消息
-- room 用户进入的游戏房间
-- playerId 用户在房间中的ID
-- mes 要处理的用户消息
--
function OnProcessPlayerRoomMes(room , playerId , mes)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end

	local myMsg = toHelper.toMessageIn(mes);
	local myMsgSubId = myMsg:readShort();
	
	if myMsgSubId == IDD_MESSAGE_GAMING_DIANZI then              -- 用户点子
		local pPlayerId = myMsg:readShort();
		local chessposx = myMsg:readByte();
		local chessposy = myMsg:readByte();	
	
		if pPlayerId == m_curActivePlayer then
			NormalRoom:StopTimer(IDD_TIMER_XIAZI);
			
			local out = CMolMessageOut(IDD_MESSAGE_ROOM);
			out:writeShort(IDD_MESSAGE_GAMING_DIANZI);
			out:writeShort(m_curActivePlayer);  
			out:writeByte(chessposx);
			out:writeByte(chessposy);
			
			chesslist[chessposx][chessposy] = m_curActivePlayer+1;
			m_curChessPosX = chessposx;
			m_curChessPosY = chessposy;			

			NormalRoom:SendTableMsg(-1,out);
			NormalRoom:SendLookOnMes(-1,out);

			if m_curActivePlayer == 0 then 
				m_curActivePlayer = 1;
			elseif m_curActivePlayer == 1 then 
				m_curActivePlayer = 0;
			end		

			-- 开启下子定时器
			NormalRoom:StartTimer(IDD_TIMER_XIAZI,10);		

			-- 检测游戏是否结束
			IsGameEnd(NormalRoom,chessposx,chessposy,chesslist[chessposx][chessposy]);			
		end
	elseif myMsgSubId == IDD_MESSAGE_GAMING_RENSHU then        -- 用户认输
		local pPlayerId = myMsg:readShort();
	
		if pPlayerId == 0 then 
			local pPlayer = toHelper.toPlayer(NormalRoom:GetPlayer(0));
			if pPlayer ~= nil then 
				pPlayer:SetMoney(pPlayer:GetMoney()+10);
			end
			pPlayer = toHelper.toPlayer(NormalRoom:GetPlayer(1));
			if pPlayer ~= nil then 
				pPlayer:SetMoney(pPlayer:GetMoney()-10);
			end	
		elseif pPlayerId == 1 then 
			local pPlayer = toHelper.toPlayer(NormalRoom:GetPlayer(0));
			if pPlayer ~= nil then 
				pPlayer:SetMoney(pPlayer:GetMoney()-10);
			end
			pPlayer = toHelper.toPlayer(NormalRoom:GetPlayer(1));
			if pPlayer ~= nil then 
				pPlayer:SetMoney(pPlayer:GetMoney()+10);
			end	
		end
		
		NormalRoom:GameEnd();
		NormalRoom:StopTimer(IDD_TIMER_XIAZI);
		
		-- 发送游戏结束消息
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAME_END);
		
		NormalRoom:SendTableMsg(-1,out);
		NormalRoom:SendLookOnMes(-1,out);	
	elseif myMsgSubId == IDD_MESSAGE_GAMING_CHAT then          -- 用户聊天信息
        local playerId = myMsg:readShort();
        local chat = myMsg:readString();	
	
		-- 发送聊天消息到其他玩家
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAMING_CHAT);
		out:writeShort(playerId);
		out:writeString(chat:c_str());

		NormalRoom:SendTableMsg(-1,out);
		NormalRoom:SendLookOnMes(-1,out);	
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUOQI then          -- 用户求和
        local playerId = myMsg:readShort();
		
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAMING_HUOQI);
		out:writeShort(playerId);
		
		NormalRoom:SendTableMsg(-1,out);
    elseif myMsgSubId == IDD_MESSAGE_GAMING_HUOQI_CONCEL then    -- 有人不同意求和
        local playerId = myMsg:readShort();
        
        local out = CMolMessageOut(IDD_MESSAGE_ROOM);
        out:writeShort(IDD_MESSAGE_GAMING_HUOQI_CONCEL);
        out:writeShort(playerId);

		NormalRoom:SendTableMsg(-1,out);
    elseif myMsgSubId == IDD_MESSAGE_GAMING_HUOQI_OK then        -- 求和得到同意
        -- 平局
		NormalRoom:GameEnd();
		NormalRoom:StopTimer(IDD_TIMER_XIAZI);
		
		-- 发送游戏结束消息
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAME_END);
		out.writeLong(0);
		out.writeLong(0);
		
		NormalRoom:SendTableMsg(-1,out);
		NormalRoom:SendLookOnMes(-1,out);	
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUIQI then           -- 请求悔棋
        local playerId = myMsg:readShort();
		
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAMING_HUIQI);
		out:writeShort(playerId);
		
		NormalRoom:SendTableMsg(-1,out);
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUIQI_OK then        -- 用户确定悔棋
		NormalRoom:StopTimer(IDD_TIMER_XIAZI);
		
		chesslist[m_curChessPosX][m_curChessPosY] = 0;
		
		if m_curActivePlayer == 0 then 
			m_curActivePlayer = 1;
		elseif m_curActivePlayer == 1 then 
			m_curActivePlayer = 0;
		end	
		
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAMING_HUIQI_OK);
		out:writeByte(m_curChessPosX);
		out:writeByte(m_curChessPosY);
		
		NormalRoom:SendTableMsg(-1,out);
		
		-- 开启下子定时器
		NormalRoom:StartTimer(IDD_TIMER_XIAZI,10);		
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUIQI_CONCEL then        -- 用户不同意悔棋
		
	end
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
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	-- 如果用户重新进入房间
	NormalRoom:PrintDebugInfo("玩家:"..tostring(playerId).."重新进入房间了。");	
	local out = CMolMessageOut(IDD_MESSAGE_ROOM);
	out:writeShort(IDD_MESSAGE_DISCONN_BACK);
	out:writeShort(m_curActivePlayer);

	-- 发送棋牌数据
    for i = 1 , totalrow do
	  for j = 1 , totallist do
		out:writeByte(chesslist[i][j]);
	  end
	end	
	
	NormalRoom:SendTableMsg(playerId,out);
end

--
-- 用于处理用户房间定时器消息
-- room 要处理的游戏房间
-- timerId 要处理的定时器ID
-- curtime 当前时间
--
function OnProcessTimerMsg(room , timerId , curtime)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	if timerId == IDD_TIMER_XIAZI and curtime <= 0 then
		--NormalRoom:PrintDebugInfo("玩家:"..tostring(m_curActivePlayer).."开始下子了。");
		--NormalRoom:StopTimer(IDD_TIMER_XIAZI);
		
		-- 首先检查这个玩家是否是机器人，如果是机器人的话，就帮它下,掉线用户也需要托管到他回来
		local pPlayer = toHelper.toPlayer(NormalRoom:GetPlayer(m_curActivePlayer));
		if pPlayer == nil then return end
		
		if pPlayer:GetType() == PLAYERTYPE_ROBOT or pPlayer:GetState() == PLAYERSTATE_LOSTLINE then	
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
			
			local out = CMolMessageOut(IDD_MESSAGE_ROOM);
			out:writeShort(IDD_MESSAGE_GAMING_DIANZI);
			out:writeShort(m_curActivePlayer);  
			out:writeByte(chessX);
			out:writeByte(chessY);
			
			chesslist[chessX][chessY] = m_curActivePlayer+1;
			m_curChessPosX = chessX;
			m_curChessPosY = chessY;

			NormalRoom:SendTableMsg(-1,out);
			NormalRoom:SendLookOnMes(-1,out);	

			if m_curActivePlayer == 0 then 
				m_curActivePlayer = 1;
			elseif m_curActivePlayer == 1 then 
				m_curActivePlayer = 0;
			end	

			-- 检测游戏是否结束
			IsGameEnd(NormalRoom,chessX,chessY,chesslist[chessX][chessY]);
		end
	end
end
