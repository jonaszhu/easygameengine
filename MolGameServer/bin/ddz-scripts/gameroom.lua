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
	
end
