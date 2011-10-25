m_carddata = {1,2,3,4,5,6,7,8,9,10,11,12,13,
              17,18,19,20,21,22,23,24,25,26,27,28,29,
              33,34,35,36,37,38,39,40,41,42,43,44,45,
              49,50,51,52,53,54,55,56,57,58,59,60,61,78,79};

m_playerCardData = {};
m_playerCardData[1] = {};
m_playerCardData[2] = {};
m_playerCardData[3] = {};
m_shengyuCardData = {};                         -- ʣ�µ�������
m_curOutCardDate = {};                          -- ��ǰ�û���������
m_curOutCardPlayer = -1;                        -- ��ǰ�����û�
m_startOutCardPlayer = -1;                      -- �ʼ�����û�
m_jiaofencard = 0;                              -- ���ڽзֵ���
m_startJiaoFenPlayer = -1;                      -- һ����Ϸ��ʼ�Ľз����
m_curJiaoFenPlayer = -1;                        -- ��ǰ�зֵ����
m_jiaofenResult = 0;                            -- ��ǰ�зֽ��
m_oldjiaofenresult = {};                        -- ��ǰ�û��з�ֵ 

m_outlineplayercount = 0;                       -- ������Ҹ���
m_outlineplayers = {};                          -- ��������б�

m_PlayerMaster = -1;                            -- ���� 

m_sucplayer = -1;                               -- ��Ϸ��ʤ���� 

-- 
-- ����������Ϸ����
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
-- ���ָ�����û�ID�Ƿ��ǵ����û�
--
-- @param playerId Ҫ�����û�ID
--
-- @return ���ָ���û��ǵ����û������棬���򷵻ؼ�
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
-- ������Ϸ
--
-- @param room Ҫ���ķ���
-- @param player Ҫ�����Ӯ���ļ�������
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
		out:writeShort(1);             -- ����Ӯ
	else
		out:writeShort(0);             -- ������
	end
	
	room:SendAllPlayerMsg(out);

	--NormalRoom:PrintDebugInfo("һ����Ϸ�Ѿ�������\n");	
	
	-- ���÷���״̬Ϊ��Ϸ����״̬
	room:SetRoomState(ROOMSTATE_WAITING);
	room:SetAllPlayerState(PLAYERSTATE_NORAML);
	room:SetMaster(-1);
	
	-- ����������
	for i = 1 , table.getn(m_outlineplayers) do
		room:ClearPlayerById(m_outlineplayers[i]);
	end		
end
          
-- ����ǰ������ȫ������
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
	
	-- ����õ��зֵ���
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
-- ����ָ���������ļ�������У����������ҵ�����
--
-- @param card Ҫ���ҵ���
--
-- @return ��������ڵ�ǰ��Ϸ��ҵ����Ϸ����������ڷ����е�ID�����򷵻�-1
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
-- ��ָ����ҵ����л�ȡһ�Ŵ���ָ��ֵ����
--
-- @param cardlist ��ҵ��ƶ���
-- @param card Ҫ�Ƚϵ���
--
-- @return ��������������Ʒ�����ֵ�����򷵻�-1
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
-- ��ָ����ҵ���������ɾ��ָ����������
--
-- @param index �������
-- @param carddata ���������
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
-- �йܳ���
--
-- @param room Ҫ�йܵķ���
--
function TuoGuanOutCard(room)
	if room == nil then return end
	
	local nextplayer = room:GetCurrentPlayer();
	local lastnextplayer = room:GetCurNextPlayer();	
	
	-- ��������ֻ�����û���һ���Ƶ�������������ȫ������
	if table.getn(m_curOutCardDate) > 1 then                        -- ����������1ʱֱ�ӹ���
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_PASS_OUT_CARD);
		out:writeShort(nextplayer);
		out:writeShort(lastnextplayer);
		
		room:SendAllPlayerMsg(out);	
		
		if m_startOutCardPlayer == lastnextplayer then
			m_startOutCardPlayer = m_curOutCardPlayer;
			-- ���������һ�εĳ�������
			for i = 1 , table.getn(m_curOutCardDate) do
				m_curOutCardDate[i] = nil;
			end
		end	
		return;
	elseif table.getn(m_curOutCardDate) == 1 then		            -- ����������1ʱ����������������Ӧ���ƾͳ��ƣ��������
		--local pCard = GetCardFromPlayer(m_playerCardData[nextplayer+1],m_curOutCardDate[1]);
		
		--if pCard == -1 then
			local out = CMolMessageOut(IDD_MESSAGE_ROOM);
			out:writeShort(IDD_MESSAGE_PASS_OUT_CARD);
			out:writeShort(nextplayer);
			out:writeShort(lastnextplayer);
			
			room:SendAllPlayerMsg(out);	
			
			if m_startOutCardPlayer == lastnextplayer then
				m_startOutCardPlayer = m_curOutCardPlayer;
				-- ���������һ�εĳ�������
				for i = 1 , table.getn(m_curOutCardDate) do
					m_curOutCardDate[i] = nil;
				end
			end				
			return;		
		--end
	
		-- ���������һ�εĳ�������
		--for i = 1 , table.getn(m_curOutCardDate) do
		--	m_curOutCardDate[i] = nil;
		--end

		--m_curOutCardDate[1] = pCard;
	else                                                            -- ��ǰû�г��Ƶ�����¾�����һ����
		-- ���������һ�εĳ�������
		for i = 1 , table.getn(m_curOutCardDate) do
			m_curOutCardDate[i] = nil;
		end

		m_curOutCardDate[1] = m_playerCardData[nextplayer+1][1];
	end
	
	-- ������������������ҳ���
	GetCardDataByPlayer(nextplayer+1,m_curOutCardDate);
	
	-- �������ݷ��͸��������
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

	--room:PrintDebugInfo("���:"..tostring(nextplayer).."�����й�"..tostring(table.getn(m_curOutCardDate)).."��ʼ����:"..tostring(m_startOutCardPlayer).."��ǰ����:"..tostring(m_curOutCardPlayer));

	-- Ȼ�����Ƿ����Ѿ����꣬������꣬���ǵ���Ӯ����ũ��Ӯ
	if table.getn(m_playerCardData[nextplayer+1]) <= 0 then
		room:StopTimer(IDD_TIMER_OUTCARD);
		
		-- ���Խ�����Ϸ��
		EndGame(room,nextplayer);
	end		
end

--
-- �й�״̬��ָ����ҳ���
--
-- @param room ������ڵķ���
-- @param player Ҫ���Ƶ����ID
--
function PlayerSendCard(room,player)
	if room == nil then return end
	if player < 0 or player > 2 then return end
	
	TuoGuanOutCard(room);
	
	--room:PrintDebugInfo("��ǰ�������:"..tostring(player).."��һ���������:"..tostring(player));
end

