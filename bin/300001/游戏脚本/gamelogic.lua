dofile("��Ϸ�ű�\\common.lua");
dofile("��Ϸ�ű�\\defines.lua");
dofile("��Ϸ�ű�\\networklogic.lua");

--
-- ��Ⱦ��Ϸ����
--
function DrawScene()
	-- ��ʾ����ͼ
	if m_bgTex ~= 0 then
		engine:Draw2DImage(m_bgTex,CMolPosition2d_int_(0,0));
	end
	
	-- ��ʾ��ǰ������
	local mySelf = toHelper.toPlayer(engine:GetUserData(engine:GetMeChairID()));
	if mySelf ~= nil then
		engine:DrawString("���භ���� - �� "..tostring(mySelf:GetRoomId()+1).." ��",
						  CMolRect_int_(20,7,600,60),
						  CMolColor(255,255,255,255));
	end	
end

--
-- �û�������Ϸ���õ�����Դ
-- 
function LoadGameResources()
	engine:LoadGUIConfig("��Ϸ����\\gamemainframe.gui");

	m_bgTex = engine:LoadTexture("��ϷͼƬ\\bg.png");	
end

-- 
-- ���ڴ�����Ϸ���¼�
-- event ��ϵͳ�д�������Ҫ�������Ϸ�¼�����Щ�¼�������������꣬GUI�������¼�
--
function OnProcessGameEvent(event)
	local myevent = toHelper.toMolEvent(event);
	
	if myevent.mEventType == MOLET_GUI_EVENT then                      -- GUI�¼�

    elseif myevent.mEventType == MOLET_MOUSE_INPUT_EVENT then          -- ����¼�

	elseif myevent.mEventType == MOLET_KEY_INPUT_EVENT then                   -- �����¼�

	end	
end

--
-- ���ڴ�����Ϸ�ж�ʱ���¼�
-- IDEvent Ҫ�������Ϸ�еĶ�ʱ��ID
--
function OnProcessGameTimer(IDEvent)

end

--
-- ���ڴ������е�������Ϣ
--
-- @param msg ���յ�Ҫ�����������Ϣ
--
function OnProcessPlayerGameRoomMsg(msg)

end
