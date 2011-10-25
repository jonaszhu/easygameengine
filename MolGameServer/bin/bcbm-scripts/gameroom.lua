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
end

-- 
-- ���ڴ����û��뿪�������Ϣ
-- room �û��뿪����Ϸ����
-- playerId �û��ڷ����е�ID
--
function OnProcessLeaveRoomMsg(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end

end

--
-- ���ڴ����û�׼����Ϣ
-- room �û��������Ϸ����
-- playerId �û��ڷ����е�ID
--
function OnProcessPlayerReadyMes(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end

	if isStartGame == false then
		isStartGame = true;

		-- ��ʼ��Ϸ
		NormalRoom:StartTimer(IDD_TIMER_START_GAME,10);
	end	
	
	-- �����û��ȴ�״̬
	local out = CMolMessageOut(IDD_MESSAGE_ROOM);
	out:writeShort(IDD_MESSAGE_ROOM_WAITING);

	NormalRoom:SendTableMsg(playerId,out);
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

	if timerId == IDD_TIMER_START_GAME and curtime <= 0 then
		NormalRoom:GameStart();
		NormalRoom:StopTimer(IDD_TIMER_START_GAME);
		
		NormalRoom:StartTimer(IDD_TIMER_GET_RESULT,30);
	elseif timerId == IDD_TIMER_GET_RESULT and curtime <= 0 then
		local biaozhi = math.random(24);
		
		NormalRoom:PrintDebugInfo("�Ƿ�ִ��2");
		
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_ROOM_GETRESULT);
		out:writeByte(biaozhi);

		NormalRoom:SendTableMsg(-1,out);		
	end
end
