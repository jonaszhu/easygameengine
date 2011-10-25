dofile("defines.lua");
dofile("gamelogic.lua");

--
-- ���ڴ����û����뷿�����Ϣ
-- room �û��������Ϸ����
-- playerId �û��ڷ����е�ID
--
function OnProcessEnterRoomMsg(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
    
    -- �������״̬������Ϸ״̬���û��Ͳ��ܽ��뷿��
    if NormalRoom:GetRoomState() == ROOMSTATE_GAMING then
        return;
    end    
	
	-- �������״̬Ϊ�ȴ�״̬
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
   
    --NormalRoom:PrintDebugInfo("���:"..tostring(playerId).."���뷿���ˡ�"..tostring(NormalRoom:GetID()).."\n");
    
    -- ����������ҵ�ǰ�û����뷿��
    NormalRoom:SendAllPlayerMsg(out);
end

-- 
-- ���ڴ����û��뿪�������Ϣ
-- room �û��뿪����Ϸ����
-- playerId �û��ڷ����е�ID
--
function OnProcessLeaveRoomMsg(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	-- ���ȼ�鵱ǰ�����Ƿ�����Ϸ�У�����������򷿼���������ҹ㲥�����Ϣ��Ȼ��ӷ�����ɾ��������
    if NormalRoom:GetRoomState() == ROOMSTATE_GAMING then
        return;
    end   
	
	--NormalRoom:PrintDebugInfo("���û��˳�����:"..tostring(NormalRoom:GetID()));
end

--
-- ���ڴ����û�׼����Ϣ
-- room �û��������Ϸ����
-- playerId �û��ڷ����е�ID
--
function OnProcessPlayerReadyMes(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
    
    -- �������״̬������Ϸ״̬���û��Ͳ���׼���ɹ�
    if NormalRoom:GetRoomState() == ROOMSTATE_GAMING then
        return;
    end
    
    local player = NormalRoom:GetPlayer(playerId);
    if player == nil then return end
    
    player:SetState(PLAYERSTATE_READY);
    
    -- ���÷���״̬Ϊ�ȴ�״̬
    NormalRoom:SetRoomState(ROOMSTATE_WAITING);
    
    --NormalRoom:PrintDebugInfo("����:"..tostring(NormalRoom:GetID()).."���"..tostring(playerId).."�����Ѿ�׼������Ϸ�ˡ�\n");
    
    -- �������û�����÷������������÷���
    if NormalRoom:GetMaster() == -1 then
        NormalRoom:SetMaster(playerId);
    end
	
	-- �򷿼��������û��㲥����û��Ѿ�׼������
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
	
	--NormalRoom:PrintDebugInfo("�˾����:"..tostring(NormalRoom:GetMaster()).."�Ƿ���,��������:"..tostring(NormalRoom:GetPlayerCount(PLAYERSTATE_READY)).."\n");
    
    -- �������û���׼���ú󣬿�ʼ��Ϸ
    if NormalRoom:GetPlayerCount(PLAYERSTATE_READY) == 3 then		
        IDD_TIMER_START_GAME = NormalRoom:StartTimer(1000);
    end
end

--
-- ���ڴ����û���Ϸ����Ϣ
-- room �û��������Ϸ����
-- playerId �û��ڷ����е�ID
-- mes Ҫ������û���Ϣ
--
function OnProcessPlayerGamingMes(room , playerId , mes)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
    
    local msgin = toHelper.toMessageIn(mes);
    if msgin == nil then return end
    
    local msgId = msgin:readShort();
    
    if msgId == IDD_MESSAGE_GAMING_JIAOFEN then                        -- �û��з�
		local userJiaofen = msgin:readShort();
		
		--NormalRoom:PrintDebugInfo("�û�:"..tostring(playerId).."��"..tostring(userJiaofen).."�֡�\n");
		
		-- ������ֱ�ӽ�3��,��ôֱ�ӿ�ʼ��Ϸ
		if userJiaofen == 3 then
			m_PlayerMaster = playerId;
			NormalRoom:SetCurrentPlayer(playerId);
			NormalRoom:StopTimer(IDD_TIMER_JIAOFEN);  
			
			m_playerCardData[playerId+1][18] = m_shengyuCardData[1];
			m_playerCardData[playerId+1][19] = m_shengyuCardData[2];
			m_playerCardData[playerId+1][20] = m_shengyuCardData[3];
			
			-- ˭�Ƚз֣�˭�ȳ���
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
			-- ���һȦת���Ժ󣬻������˽з֣���ô���·���
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
	elseif msgId == IDD_MESSAGE_OUTCARD then                                  -- �û�����
		NormalRoom:StopTimer(IDD_TIMER_OUTCARD);
		local cardcount = msgin:readShort();
		
		-- ���������һ�εĳ�������
		for i = 1 , table.getn(m_curOutCardDate) do
			m_curOutCardDate[i] = nil;
		end
	
		for i = 1,cardcount do
			m_curOutCardDate[i] = msgin:readShort();
		end
		
		-- ������������������ҳ���
		GetCardDataByPlayer(playerId+1,m_curOutCardDate);
		
		local nextplayer = NormalRoom:GetCurNextPlayer();		
		--NormalRoom:PrintDebugInfo("��ǰ�����û�:"..tostring(playerId).."��ǰ�û�:"..tostring(NormalRoom:GetCurrentPlayer()).."��һ�������û�:"..tostring(nextplayer).."��\n");
		
		-- ��������û��Ѿ����ߵĻ������й�����û�
		if IsOutLinePlayer(nextplayer) then
			IDD_TIMER_PLAYER_TUOGUAN = NormalRoom:StartTimer(10000); 
		end
		
		-- �������ݷ��͸��������
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

		--NormalRoom:PrintDebugInfo("��ʼ�������:"..tostring(m_startOutCardPlayer).."��ǰ�������:"..tostring(m_curOutCardPlayer));	

		-- Ȼ�����Ƿ����Ѿ����꣬������꣬���ǵ���Ӯ����ũ��Ӯ
		if table.getn(m_playerCardData[playerId+1]) <= 0 then
			NormalRoom:StopTimer(IDD_TIMER_OUTCARD);
			
			-- ���Խ�����Ϸ��
			EndGame(NormalRoom,playerId);
		end		
	elseif msgId == IDD_MESSAGE_PASS_OUT_CARD then                            -- �û�����
		NormalRoom:StopTimer(IDD_TIMER_OUTCARD);	
	
		local nextplayer = NormalRoom:GetCurNextPlayer();	
	
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_PASS_OUT_CARD);
		out:writeShort(playerId);
		out:writeShort(nextplayer);
		
		NormalRoom:SendAllPlayerMsg(out);	
		
		--m_curOutCardPlayer = playerId;		
		if m_startOutCardPlayer == nextplayer then
			--NormalRoom:PrintDebugInfo("���������ԭ�������˿ˡ�");
			m_startOutCardPlayer = m_curOutCardPlayer;
			-- ���������һ�εĳ�������
			for i = 1 , table.getn(m_curOutCardDate) do
				m_curOutCardDate[i] = nil;
			end
		end	
			
		-- ��������û��Ѿ����ߵĻ������й�����û�
		if IsOutLinePlayer(nextplayer) then		
			IDD_TIMER_PLAYER_TUOGUAN = NormalRoom:StartTimer(10000); 
		else				
			IDD_TIMER_OUTCARD = NormalRoom:StartTimer(30000);
		end
		
		--NormalRoom:PrintDebugInfo("���ƺ�ʼ�������:"..tostring(m_startOutCardPlayer).."��ǰ�������:"..tostring(m_curOutCardPlayer));	
	elseif msgId == IDD_MESSAGE_CHAT then                                       -- �û�������Ϣ
		local chatcon = msgin:readString();
		
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_CHAT);
		out:writeShort(playerId);
		out:writeString(chatcon:c_str());
		
		NormalRoom:SendAllPlayerMsg(out);
	elseif msgId == IDD_MESSAGE_CHAT_BIAOQING then                                       -- �û����������Ϣ
		local chatcon = msgin:readString();
		
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_CHAT_BIAOQING);
		out:writeShort(playerId);
		out:writeString(chatcon:c_str());
		
		NormalRoom:SendAllPlayerMsg(out);
	elseif msgId == IDD_MESSAGE_GAME_START then                             -- ��Ϸ��ʼ
        -- ��ʼ��Ϸ������ҷ��Ϳ�ʼ��Ϸ���
        local out = CMolMessageOut(IDD_MESSAGE_ROOM);
        out:writeShort(IDD_MESSAGE_GAME_START);
        out:writeShort(NormalRoom:GetCurrentPlayer());
        
        NormalRoom:SendAllPlayerMsg(out);         
        
		IDD_TIMER_JIAOFEN = NormalRoom:StartTimer(30000); 	
	end
end

-- 
-- ���ڴ����û��Ͽ�������Ϣ
-- room �û��������Ϸ����
-- playerId �û��ڷ����е�ID
--
function OnProcessDisconnectNetMes(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
    -- �������״̬��������Ϸ״̬���Ͳ�������Ϸ
    if NormalRoom:GetRoomState() ~= ROOMSTATE_GAMING then
        return;
    end
	
	m_outlineplayercount = m_outlineplayercount + 1;
	m_outlineplayers[m_outlineplayercount] = playerId;	
	
	-- ������������������ߣ���Ϸ����
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
-- ���ڴ����û������ػ�������Ϣ
-- room �û��������Ϸ����
-- playerId �û��ڷ����е�ID
--
function OnProcessDisconnectBackNetMes(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	--NormalRoom:PrintDebugInfo("���:"..tostring(playerId).."�Ѿ������ػ��ˡ�\n");
	
	m_outlineplayercount = m_outlineplayercount - 1;
	for i = 1 , table.getn(m_outlineplayers) do
		if m_outlineplayers[i] == playerId then
			m_outlineplayers[i] = nil;
			break;
		end
	end
	
	-- �����Ϸ�����ڽ���״̬��
	if NormalRoom:GetRoomState() == ROOMSTATE_GAMING then
		local pPlayer = NormalRoom:GetPlayer(playerId);
		if pPlayer == nil then return end
		
		m_outlineplayercount = 0;
		for i = 1 , table.getn(m_outlineplayers) do
			m_outlineplayers[i] = nil;
		end
		
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_REENTER_ROOM);	
		out:writeShort(1);                           -- ������û����·�����Ϸ��Ϣ
		out:writeLong(pPlayer:GetID());
		out:writeShort(NormalRoom:GetID());
		out:writeShort(playerId);
		out:writeShort(m_curOutCardPlayer);
		out:writeShort(NormalRoom:GetCurrentPlayer());
		out:writeShort(m_curJiaoFenPlayer);
		out:writeShort(m_PlayerMaster);	

		if m_curJiaoFenPlayer >= 0 and m_curJiaoFenPlayer < 3 then	
			out:writeShort(NormalRoom:GetCurTime(IDD_TIMER_JIAOFEN));    -- ���͵�ǰ�зֶ�ʱ��ʱ��		
			
			-- �����û��Ѿ��й��ĵķ���
			out:writeShort(table.getn(m_oldjiaofenresult));
			for i = 1 , table.getn(m_oldjiaofenresult) do
				out:writeShort(m_oldjiaofenresult[i]);
			end
		else
			out:writeShort(NormalRoom:GetCurTime(IDD_TIMER_OUTCARD));    -- ���͵�ǰ���ƶ�ʱ��ʱ��
		end
		
		out:writeShort(table.getn(m_playerCardData[playerId+1]));
		
		for i = 1 , table.getn(m_playerCardData[playerId+1]) do
			out:writeByte(m_playerCardData[playerId+1][i]);
		end
		
		out:writeByte(m_shengyuCardData[1]);
		out:writeByte(m_shengyuCardData[2]);
		out:writeByte(m_shengyuCardData[3]);
		
		-- ������û����ƵĻ������ͳ�������
		out:writeShort(table.getn(m_curOutCardDate));	
		if table.getn(m_curOutCardDate) > 0 and 
			m_curOutCardPlayer ~= -1 then						
			for i = 1,table.getn(m_curOutCardDate) do
				out:writeShort(m_curOutCardDate[i]);
			end			
		end	

		-- ��������������ҵ�ʣ����
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
		
		-- �򷿼������û�������ҷ��ط�����Ϣ
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
-- ���ڴ����û����䶨ʱ����Ϣ
-- room Ҫ�������Ϸ����
-- timerId Ҫ����Ķ�ʱ��ID
--
function OnProcessTimerMsg(room , timerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
    
    if timerId == IDD_TIMER_START_GAME then                               -- ��Ϸ��ʼ��ʱ��
        -- ���÷���״̬Ϊ��Ϸ��״̬
        NormalRoom:SetRoomState(ROOMSTATE_GAMING);
        NormalRoom:SetAllPlayerState(PLAYERSTATE_GAMING);
          
		-- ��������������
		ResetGameData();
		
        -- �õ�������
        GetCardData(); 
		
		-- ���õ�ǰ��Ϸ��ʼ���
		m_startJiaoFenPlayer = GetJiaoPaiPlayer(m_jiaofencard);
		if m_startJiaoFenPlayer ~= -1 then
			m_curJiaoFenPlayer = m_startJiaoFenPlayer;
			NormalRoom:SetCurrentPlayer(m_startJiaoFenPlayer);
		end
        
        -- ����ҷ���������
		if NormalRoom:GetPlayerCount() <= 3 then		
			for index = 1 , NormalRoom:GetPlayerCount() do   
				local pPlayer = NormalRoom:GetPlayer(index-1);
				if pPlayer then			
					local out = CMolMessageOut(IDD_MESSAGE_ROOM);
					out:writeShort(IDD_MESSAGE_READY_START);			
					out:writeLong(pPlayer:GetID());
					out:writeShort(index-1);
					
					--NormalRoom:PrintDebugInfo("����:"..tostring(NormalRoom:GetID()).."������:"..tostring(index).." "..tostring(table.getn(m_playerCardData)));
					
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
		
		--NormalRoom:PrintDebugInfo("����:"..tostring(NormalRoom:GetID()).."�Ѿ������������ݡ�\n");
		
		NormalRoom:StopTimer(IDD_TIMER_START_GAME); 	
	elseif timerId == IDD_TIMER_JIAOFEN then                                 -- �û��зֶ�ʱ��
		local curplayer = NormalRoom:GetCurrentPlayer();
		
		-- �������з��û��Ѿ����ߵĻ�����ֱ�ӽ�����
		if IsOutLinePlayer(curplayer) then
			m_PlayerMaster = curplayer;
			NormalRoom:SetCurrentPlayer(curplayer);
			
			m_playerCardData[curplayer+1][18] = m_shengyuCardData[1];
			m_playerCardData[curplayer+1][19] = m_shengyuCardData[2];
			m_playerCardData[curplayer+1][20] = m_shengyuCardData[3];
			
			-- ˭�Ƚз֣�˭�ȳ���
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
	elseif timerId == IDD_TIMER_PLAYER_TUOGUAN then                           -- �û��йܶ�ʱ��
	
		-- �û��йܳ���
		PlayerSendCard(NormalRoom,NormalRoom:GetCurrentPlayer());
		
		NormalRoom:StopTimer(IDD_TIMER_PLAYER_TUOGUAN);
	elseif timerId == IDD_TIMER_OUTCARD then                                  -- ���ƶ�ʱ��
		local curplayer = NormalRoom:GetCurrentPlayer();
		
		-- �������з��û��Ѿ����ߵĻ������й��û�
		if IsOutLinePlayer(curplayer) then
			TuoGuanOutCard(NormalRoom);
		end

		NormalRoom:StopTimer(IDD_TIMER_OUTCARD);	
	end
end
