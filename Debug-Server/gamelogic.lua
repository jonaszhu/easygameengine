m_carddata = {1,2,3,4,5,6,7,8,9,10,11,12,13,
              17,18,19,20,21,22,23,24,25,26,27,28,29,
              33,34,35,36,37,38,39,40,41,42,43,44,45,
              49,50,51,52,53,54,55,56,57,58,59,60,61,78,79};

m_playerCardData = {};
m_playerCardData[1] = {};
m_playerCardData[2] = {};
m_playerCardData[3] = {};
m_shengyuCardData = {};                         -- 剩下的三张牌
m_curOutCardDate = {};                          -- 当前用户出牌数据
m_curOutCardPlayer = -1;                        -- 当前出牌用户
m_startOutCardPlayer = -1;                      -- 最开始出牌用户
m_jiaofencard = 0;                              -- 用于叫分的牌
m_startJiaoFenPlayer = -1;                      -- 一局游戏开始的叫分玩家
m_curJiaoFenPlayer = -1;                        -- 当前叫分的玩家
m_jiaofenResult = 0;                            -- 当前叫分结果
m_oldjiaofenresult = {};                        -- 当前用户叫分值 

m_outlineplayercount = 0;                       -- 掉线玩家个数
m_outlineplayers = {};                          -- 掉线玩家列表

m_PlayerMaster = -1;                            -- 地主 

m_sucplayer = -1;                               -- 游戏的胜利者 

-- 
-- 重新设置游戏数据
--
function ResetGameData()
	for i = 1 , 3 do
		for j = 1,table.getn(m_playerCardData[i]) do
			m_playerCardData[i][j] = nil;
		end
		
		m_shengyuCardData[i] = nil;
	end
	
	m_playerCardData = {};
	m_playerCardData[1] = {};
	m_playerCardData[2] = {};
	m_playerCardData[3] = {};	
	
	for i = 1 , table.getn(m_curOutCardDate) do
		m_curOutCardDate[i] = nil;
	end
	
	for i = 1 , table.getn(m_outlineplayers) do
		m_outlineplayers[i] = nil;
	end
	
    for i = 1 , table.getn(m_oldjiaofenresult) do m_oldjiaofenresult[i] = nil end  	
	
	m_jiaofencard = 0;         
	m_startJiaoFenPlayer = -1;    
	m_curJiaoFenPlayer = -1;   
	m_jiaofenResult = 0;            
	m_PlayerMaster = -1;    
	m_startOutCardPlayer = -1; 
	m_outlineplayercount = 0;
	m_curOutCardPlayer = -1;
	m_sucplayer = -1;
end

-- 
-- 检测指定的用户ID是否是掉线用户
--
-- @param playerId 要检测的用户ID
--
-- @return 如果指定用户是掉线用户返回真，否则返回假
--
function IsOutLinePlayer(playerId)
	for i = 1 , table.getn(m_outlineplayers) do
		if m_outlineplayers[i] == playerId then 
			return true;
		end
	end
	
	return false;
end

-- 
-- 结束游戏
--
-- @param room 要检测的房间
-- @param player 要检测输赢的文件的索引
--
function EndGame(room,player)
	if room == nil then return end
	
	room:StopTimer(IDD_TIMER_PLAYER_TUOGUAN);
	room:StopTimer(IDD_TIMER_OUTCARD);
	room:StopTimer(IDD_TIMER_JIAOFEN);
	room:StopTimer(IDD_TIMER_START_GAME);	
	
	m_sucplayer = player;
	local out = CMolMessageOut(IDD_MESSAGE_ROOM);
	out:writeShort(IDD_MESSAGE_GAME_OVER);
	
	if m_sucplayer == m_PlayerMaster then
		out:writeShort(1);             -- 地主赢
	else
		out:writeShort(0);             -- 地主输
	end
	
	room:SendAllPlayerMsg(out);

	--NormalRoom:PrintDebugInfo("一局游戏已经结束。\n");	
	
	-- 设置房间状态为游戏结束状态
	room:SetRoomState(ROOMSTATE_WAITING);
	room:SetAllPlayerState(PLAYERSTATE_NORAML);
	room:SetMaster(-1);
	
	-- 清除掉线玩家
	for i = 1 , table.getn(m_outlineplayers) do
		room:ClearPlayerById(m_outlineplayers[i]);
	end		
end
          
-- 将当前牌数据全部打乱
function GetCardData()           
    local pcarddata = m_carddata; 
   
    math.randomseed(os.time());
    
    for i = 0 , 300 do
        local first = math.random(1,54);
        local second = math.random(1,54);
        
        if first ~= second then
            local temp = pcarddata[second];
            pcarddata[second] = pcarddata[first];
            pcarddata[first] = temp;
        end
    end
	
	-- 随机得到叫分的牌
	m_jiaofencard = pcarddata[math.random(1,50)];
    
    for i = 1 , 17 do
        m_playerCardData[1][i] = pcarddata[i];
        m_playerCardData[2][i] = pcarddata[17+i];
        m_playerCardData[3][i] = pcarddata[34+i];
    end
	
	m_shengyuCardData[1] = pcarddata[52];
	m_shengyuCardData[2] = pcarddata[53];
	m_shengyuCardData[3] = pcarddata[54];
end  

-- 
-- 查找指定的牌在哪家玩家手中，返回这家玩家的索引
--
-- @param card 要查找的牌
--
-- @return 如果存在于当前游戏玩家的手上返回这个玩家在房间中的ID，否则返回-1
--
function GetJiaoPaiPlayer(card)
	for i = 1 , 3 do
		for j = 1,table.getn(m_playerCardData[i]) do
			if m_playerCardData[i][j] == card then
				return i - 1;
			end
		end
	end
	
	return -1;
end

-- 
-- 从指定玩家的牌中获取一张大于指定值的牌
--
-- @param cardlist 玩家的牌队列
-- @param card 要比较的牌
--
-- @return 如果存在这样的牌返回牌值，否则返回-1
--
function GetCardFromPlayer(cardlist,card)
	for i = 1 , table.getn(cardlist) do
		if cardlist[i] > card then
			return cardlist[i];
		end
	end
	
	return -1;
end

--
-- 从指定玩家的牌数据中删除指定的牌数据
--
-- @param index 玩家索引
-- @param carddata 玩家牌数据
--
function GetCardDataByPlayer(index,carddata)
	if index < 1 or index > 3 then return end
	if carddata == nil then return end

	for i = 1 , table.getn(carddata) do
		for j = 1 , table.getn(m_playerCardData[index]) do
			if m_playerCardData[index][j] == carddata[i] then
				table.remove(m_playerCardData[index],j);
				break;
			end
		end
	end
end

--
-- 托管出牌
--
-- @param room 要托管的房间
--
function TuoGuanOutCard(room)
	if room == nil then return end
	
	local nextplayer = room:GetCurrentPlayer();
	local lastnextplayer = room:GetCurNextPlayer();	
	
	-- 我们这里只处理用户出一张牌的情况，其它情况全部过牌
	if table.getn(m_curOutCardDate) > 1 then                        -- 牌数量大于1时直接过牌
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_PASS_OUT_CARD);
		out:writeShort(nextplayer);
		out:writeShort(lastnextplayer);
		
		room:SendAllPlayerMsg(out);	
		
		if m_startOutCardPlayer == lastnextplayer then
			m_startOutCardPlayer = m_curOutCardPlayer;
			-- 首先清空上一次的出牌数据
			for i = 1 , table.getn(m_curOutCardDate) do
				m_curOutCardDate[i] = nil;
			end
		end	
		return;
	elseif table.getn(m_curOutCardDate) == 1 then		            -- 牌数量等于1时，如果玩家手上有相应的牌就出牌，否则过牌
		--local pCard = GetCardFromPlayer(m_playerCardData[nextplayer+1],m_curOutCardDate[1]);
		
		--if pCard == -1 then
			local out = CMolMessageOut(IDD_MESSAGE_ROOM);
			out:writeShort(IDD_MESSAGE_PASS_OUT_CARD);
			out:writeShort(nextplayer);
			out:writeShort(lastnextplayer);
			
			room:SendAllPlayerMsg(out);	
			
			if m_startOutCardPlayer == lastnextplayer then
				m_startOutCardPlayer = m_curOutCardPlayer;
				-- 首先清空上一次的出牌数据
				for i = 1 , table.getn(m_curOutCardDate) do
					m_curOutCardDate[i] = nil;
				end
			end				
			return;		
		--end
	
		-- 首先清空上一次的出牌数据
		--for i = 1 , table.getn(m_curOutCardDate) do
		--	m_curOutCardDate[i] = nil;
		--end

		--m_curOutCardDate[1] = pCard;
	else                                                            -- 当前没有出牌的情况下就随便出一张牌
		-- 首先清空上一次的出牌数据
		for i = 1 , table.getn(m_curOutCardDate) do
			m_curOutCardDate[i] = nil;
		end

		m_curOutCardDate[1] = m_playerCardData[nextplayer+1][1];
	end
	
	-- 从玩家牌数据中清除玩家出牌
	GetCardDataByPlayer(nextplayer+1,m_curOutCardDate);
	
	-- 将牌数据发送给其它玩家
	local out = CMolMessageOut(IDD_MESSAGE_ROOM);
	out:writeShort(IDD_MESSAGE_OUTCARD_DATA);
	out:writeShort(nextplayer);
	out:writeShort(lastnextplayer);
	out:writeShort(1);
	out:writeShort(m_curOutCardDate[1]);
	
	room:SendAllPlayerMsg(out);
	
	m_curOutCardPlayer = nextplayer;	
	m_startOutCardPlayer = m_curOutCardPlayer;

	IDD_TIMER_OUTCARD = room:StartTimer(30000); 

	--room:PrintDebugInfo("玩家:"..tostring(nextplayer).."进行托管"..tostring(table.getn(m_curOutCardDate)).."开始出牌:"..tostring(m_startOutCardPlayer).."当前出牌:"..tostring(m_curOutCardPlayer));

	-- 然后检查是否牌已经出完，如果出完，看是地主赢还是农民赢
	if table.getn(m_playerCardData[nextplayer+1]) <= 0 then
		room:StopTimer(IDD_TIMER_OUTCARD);
		
		-- 可以结束游戏了
		EndGame(room,nextplayer);
	end		
end

--
-- 托管状态下指定玩家出牌
--
-- @param room 玩家所在的房间
-- @param player 要出牌的玩家ID
--
function PlayerSendCard(room,player)
	if room == nil then return end
	if player < 0 or player > 2 then return end
	
	TuoGuanOutCard(room);
	
	--room:PrintDebugInfo("当前出牌玩家:"..tostring(player).."下一个出牌玩家:"..tostring(player));
end

