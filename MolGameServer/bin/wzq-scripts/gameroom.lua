dofile("defines.lua");
dofile("gamelogic.lua");

--
-- ���ڴ����Թ��û����뷿�����Ϣ
-- room �û��������Ϸ����
-- playerId �û��ڷ����е�ID
--
function OnProcessEnterRoomMsg(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	-- ����û����Թ�״̬���ͷ����û�״̬
	NormalRoom:PrintDebugInfo("���:"..tostring(playerId).."�Թ۽��뷿���ˡ�");	
	local out = CMolMessageOut(IDD_MESSAGE_ROOM);
	out:writeShort(IDD_MESSAGE_LOOKON_ENTER_ROOM);
	out:writeShort(m_curActivePlayer);

	-- ������������
    for i = 1 , totalrow do
	  for j = 1 , totallist do
		out:writeByte(chesslist[i][j]);
	  end
	end	
	NormalRoom:SendLookOnMes(playerId,out);
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
	
	-- ����û������Թ��û������ҷ��䴦����Ϸ�еĻ�����ô���Ƚ�����Ϸ,ǿ�˵��˻ᱻ�۷�
	if NormalRoom:GetRoomState() == ROOMSTATE_GAMING then
		pPlayer:SetMoney(pPlayer:GetMoney()-10);
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
	
	--NormalRoom:PrintDebugInfo("���:"..tostring(playerId).."׼������Ϸ�ˡ�");
	
    -- ����û��������û�׼���Ϳ��Կ�ʼ��Ϸ
    if NormalRoom:GetPlayerCount(PLAYERSTATE_READY) == 2 then
		NormalRoom:GameStart();
		
		math.randomseed(os.time())		
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
		NormalRoom:StartTimer(IDD_TIMER_XIAZI,10);
    end	
end

--
-- ���ڴ����û���������Ϣ
-- room �û��������Ϸ����
-- playerId �û��ڷ����е�ID
-- mes Ҫ������û���Ϣ
--
function OnProcessPlayerRoomMes(room , playerId , mes)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end

	local myMsg = toHelper.toMessageIn(mes);
	local myMsgSubId = myMsg:readShort();
	
	if myMsgSubId == IDD_MESSAGE_GAMING_DIANZI then              -- �û�����
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

			-- �������Ӷ�ʱ��
			NormalRoom:StartTimer(IDD_TIMER_XIAZI,10);		

			-- �����Ϸ�Ƿ����
			IsGameEnd(NormalRoom,chessposx,chessposy,chesslist[chessposx][chessposy]);			
		end
	elseif myMsgSubId == IDD_MESSAGE_GAMING_RENSHU then        -- �û�����
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
		
		-- ������Ϸ������Ϣ
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAME_END);
		
		NormalRoom:SendTableMsg(-1,out);
		NormalRoom:SendLookOnMes(-1,out);	
	elseif myMsgSubId == IDD_MESSAGE_GAMING_CHAT then          -- �û�������Ϣ
        local playerId = myMsg:readShort();
        local chat = myMsg:readString();	
	
		-- ����������Ϣ���������
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAMING_CHAT);
		out:writeShort(playerId);
		out:writeString(chat:c_str());

		NormalRoom:SendTableMsg(-1,out);
		NormalRoom:SendLookOnMes(-1,out);	
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUOQI then          -- �û����
        local playerId = myMsg:readShort();
		
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAMING_HUOQI);
		out:writeShort(playerId);
		
		NormalRoom:SendTableMsg(-1,out);
    elseif myMsgSubId == IDD_MESSAGE_GAMING_HUOQI_CONCEL then    -- ���˲�ͬ�����
        local playerId = myMsg:readShort();
        
        local out = CMolMessageOut(IDD_MESSAGE_ROOM);
        out:writeShort(IDD_MESSAGE_GAMING_HUOQI_CONCEL);
        out:writeShort(playerId);

		NormalRoom:SendTableMsg(-1,out);
    elseif myMsgSubId == IDD_MESSAGE_GAMING_HUOQI_OK then        -- ��͵õ�ͬ��
        -- ƽ��
		NormalRoom:GameEnd();
		NormalRoom:StopTimer(IDD_TIMER_XIAZI);
		
		-- ������Ϸ������Ϣ
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAME_END);
		out.writeLong(0);
		out.writeLong(0);
		
		NormalRoom:SendTableMsg(-1,out);
		NormalRoom:SendLookOnMes(-1,out);	
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUIQI then           -- �������
        local playerId = myMsg:readShort();
		
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAMING_HUIQI);
		out:writeShort(playerId);
		
		NormalRoom:SendTableMsg(-1,out);
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUIQI_OK then        -- �û�ȷ������
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
		
		-- �������Ӷ�ʱ��
		NormalRoom:StartTimer(IDD_TIMER_XIAZI,10);		
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUIQI_CONCEL then        -- �û���ͬ�����
		
	end
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
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	-- ����û����½��뷿��
	NormalRoom:PrintDebugInfo("���:"..tostring(playerId).."���½��뷿���ˡ�");	
	local out = CMolMessageOut(IDD_MESSAGE_ROOM);
	out:writeShort(IDD_MESSAGE_DISCONN_BACK);
	out:writeShort(m_curActivePlayer);

	-- ������������
    for i = 1 , totalrow do
	  for j = 1 , totallist do
		out:writeByte(chesslist[i][j]);
	  end
	end	
	
	NormalRoom:SendTableMsg(playerId,out);
end

--
-- ���ڴ����û����䶨ʱ����Ϣ
-- room Ҫ�������Ϸ����
-- timerId Ҫ����Ķ�ʱ��ID
-- curtime ��ǰʱ��
--
function OnProcessTimerMsg(room , timerId , curtime)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end
	
	if timerId == IDD_TIMER_XIAZI and curtime <= 0 then
		--NormalRoom:PrintDebugInfo("���:"..tostring(m_curActivePlayer).."��ʼ�����ˡ�");
		--NormalRoom:StopTimer(IDD_TIMER_XIAZI);
		
		-- ���ȼ���������Ƿ��ǻ����ˣ�����ǻ����˵Ļ����Ͱ�����,�����û�Ҳ��Ҫ�йܵ�������
		local pPlayer = toHelper.toPlayer(NormalRoom:GetPlayer(m_curActivePlayer));
		if pPlayer == nil then return end
		
		if pPlayer:GetType() == PLAYERTYPE_ROBOT or pPlayer:GetState() == PLAYERSTATE_LOSTLINE then	
			-- ѡ����еĵط�����
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

			-- �����Ϸ�Ƿ����
			IsGameEnd(NormalRoom,chessX,chessY,chesslist[chessX][chessY]);
		end
	end
end
