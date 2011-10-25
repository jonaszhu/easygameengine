--
-- 处理用户进入房间消息
--
function OnProcessEnterRoomMsg(nChairID,msg)
	engine:SystemLog(INFO,tostring(nChairID).."进入房间了！");
end

--
-- 处理用户离开房间消息
--
function OnProcessLeaveRoomMsg(nChairID,msg)
	engine:SystemLog(INFO,tostring(nChairID).."离开房间了！");
end

--
-- 处理用户断开连接消息
--
function OnProcessDisconnectNetMes(nChairID,msg)

end

--
-- 处理用户断线重连消息
--
function OnProcessDisconnectBackNetMes(nChairID,msg)
	engine:SystemLog(INFO,tostring(nChairID).."断线回到游戏！");
end

--
-- 处理用户准备开始消息
--
function OnProcessPlayerReadyMes(nChairID)
	engine:SystemLog(INFO,tostring(nChairID).."准备好了游戏！");
end

--
-- 处理用户房间消息
--
function OnProcessPlayerGameRoomMsg(msg)

end