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
	
end
