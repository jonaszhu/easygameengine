--
-- �����û����뷿����Ϣ
--
function OnProcessEnterRoomMsg(nChairID,msg)
	engine:SystemLog(INFO,tostring(nChairID).."���뷿���ˣ�");
end

--
-- �����û��뿪������Ϣ
--
function OnProcessLeaveRoomMsg(nChairID,msg)
	engine:SystemLog(INFO,tostring(nChairID).."�뿪�����ˣ�");
end

--
-- �����û��Ͽ�������Ϣ
--
function OnProcessDisconnectNetMes(nChairID,msg)

end

--
-- �����û�����������Ϣ
--
function OnProcessDisconnectBackNetMes(nChairID,msg)
	engine:SystemLog(INFO,tostring(nChairID).."���߻ص���Ϸ��");
end

--
-- �����û�׼����ʼ��Ϣ
--
function OnProcessPlayerReadyMes(nChairID)
	engine:SystemLog(INFO,tostring(nChairID).."׼��������Ϸ��");
end

--
-- �����û�������Ϣ
--
function OnProcessPlayerGameRoomMsg(msg)

end