dofile("defines.lua");
dofile("gamelogic.lua");

--
-- ���ڴ����û����뷿�����Ϣ
-- room �û��������Ϸ����
-- playerId �û��ڷ����е�ID
--
function OnProcessEnterRoomMsg(room , playerId)

end

-- 
-- ���ڴ����û��뿪�������Ϣ
-- room �û��뿪����Ϸ����
-- playerId �û��ڷ����е�ID
--
function OnProcessLeaveRoomMsg(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
    local pPlayer = toHelper.toPlayer(NormalRoom:GetPlayer(playerId));
    if pPlayer == nil then return end
	
	-- ����û������Թ��û������ҷ��䴦����Ϸ�еĻ�����ô���Ƚ�����Ϸ
	if pPlayer:IsLookOn() == false and NormalRoom:GetRoomState() == ROOMSTATE_GAMING then
		NormalRoom:GameEnd();
	end
end

--
-- ���ڴ����û�׼����Ϣ
-- room �û��������Ϸ����
-- playerId �û��ڷ����е�ID
--
function OnProcessPlayerReadyMes(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	NormalRoom:PrintDebugInfo("���:"..tostring(playerId).."׼������Ϸ�ˡ�");
	
    -- ����û��������û�׼���Ϳ��Կ�ʼ��Ϸ
    if NormalRoom:GetPlayerCount(PLAYERSTATE_READY) == 2 then
        -- ���÷���״̬Ϊ��Ϸ��״̬
        NormalRoom:SetRoomState(ROOMSTATE_GAMING);
        NormalRoom:SetAllPlayerState(PLAYERSTATE_GAMING);
		
		NormalRoom:GameStart();
		
		m_curActivePlayer = NormalRoom:GetCurrentPlayer();
		
        -- ��������ǵ�һ��ʹ�þ��Ƚ���,����ֱ��ʹ��
        if m_chespanisCreated == false then
            InitChessPan(totalrow,totallist);
            m_chespanisCreated = true;
        else
            ResetChessPan();
        end		
    
        -- ��ʼ��Ϸ������ҷ��Ϳ�ʼ��Ϸ���
        local out = CMolMessageOut(IDD_MESSAGE_ROOM);
        out:writeShort(IDD_MESSAGE_GAME_START);
        out:writeShort(m_curActivePlayer);   
		
        NormalRoom:SendTableMsg(-1,out);
		NormalRoom:SendLookOnMes(-1,out);
		
		-- �������Ӷ�ʱ��
		IDD_TIMER_XIAZI = NormalRoom:StartTimer(30000);
    end	
end

--
-- ���ڴ����û���Ϸ����Ϣ
-- room �û��������Ϸ����
-- playerId �û��ڷ����е�ID
-- mes Ҫ������û���Ϣ
--
function OnProcessPlayerGamingMes(room , playerId , mes)
 
end

-- 
-- ���ڴ����û��Ͽ�������Ϣ
-- room �û��������Ϸ����
-- playerId �û��ڷ����е�ID
--
function OnProcessDisconnectNetMes(room , playerId)

end

-- 
-- ���ڴ����û������ػ�������Ϣ
-- room �û��������Ϸ����
-- playerId �û��ڷ����е�ID
--
function OnProcessDisconnectBackNetMes(room , playerId)
 
end

--
-- ���ڴ����û����䶨ʱ����Ϣ
-- room Ҫ�������Ϸ����
-- timerId Ҫ����Ķ�ʱ��ID
--
function OnProcessTimerMsg(room , timerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	if timerId == IDD_TIMER_XIAZI then
		NormalRoom:PrintDebugInfo("���:"..tostring(m_curActivePlayer).."��ʼ�����ˡ�");
		--NormalRoom:StopTimer(IDD_TIMER_XIAZI);
		
		-- ���ȼ���������Ƿ��ǻ����ˣ�����ǻ����˵Ļ����Ͱ�����
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
