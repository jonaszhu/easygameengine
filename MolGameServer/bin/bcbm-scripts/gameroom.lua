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
end

-- 
-- 用于处理用户离开房间的消息
-- room 用户离开的游戏房间
-- playerId 用户在房间中的ID
--
function OnProcessLeaveRoomMsg(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end

end

--
-- 用于处理用户准备消息
-- room 用户进入的游戏房间
-- playerId 用户在房间中的ID
--
function OnProcessPlayerReadyMes(room , playerId)
    local NormalRoom = toHelper.toRoom(room);
    if NormalRoom == nil then return end

	if isStartGame == false then
		isStartGame = true;

		-- 开始游戏
		NormalRoom:StartTimer(IDD_TIMER_START_GAME,10);
	end	
	
	-- 发送用户等待状态
	local out = CMolMessageOut(IDD_MESSAGE_ROOM);
	out:writeShort(IDD_MESSAGE_ROOM_WAITING);

	NormalRoom:SendTableMsg(playerId,out);
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

	if timerId == IDD_TIMER_START_GAME and curtime <= 0 then
		NormalRoom:GameStart();
		NormalRoom:StopTimer(IDD_TIMER_START_GAME);
		
		NormalRoom:StartTimer(IDD_TIMER_GET_RESULT,30);
	elseif timerId == IDD_TIMER_GET_RESULT and curtime <= 0 then
		local biaozhi = math.random(24);
		
		NormalRoom:PrintDebugInfo("是否执行2");
		
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_ROOM_GETRESULT);
		out:writeByte(biaozhi);

		NormalRoom:SendTableMsg(-1,out);		
	end
end
