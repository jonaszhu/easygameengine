dofile("游戏脚本\\common.lua");
dofile("游戏脚本\\defines.lua");
dofile("游戏脚本\\networklogic.lua");

--
-- 渲染游戏场景
--
function DrawScene()
	-- 显示背景图
	if m_bgTex ~= 0 then
		engine:Draw2DImage(m_bgTex,CMolPosition2d_int_(0,0));
	end
	
	-- 显示当前桌子数
	local mySelf = toHelper.toPlayer(engine:GetUserData(engine:GetMeChairID()));
	if mySelf ~= nil then
		engine:DrawString("咕噜斗地主 - 第 "..tostring(mySelf:GetRoomId()+1).." 桌",
						  CMolRect_int_(20,7,600,60),
						  CMolColor(255,255,255,255));
	end	
end

--
-- 用户加载游戏中用到的资源
-- 
function LoadGameResources()
	engine:LoadGUIConfig("游戏界面\\gamemainframe.gui");

	m_bgTex = engine:LoadTexture("游戏图片\\bg.png");	
end

-- 
-- 用于处理游戏中事件
-- event 从系统中传过来的要处理的游戏事件，这些事件包括按键，鼠标，GUI和其它事件
--
function OnProcessGameEvent(event)
	local myevent = toHelper.toMolEvent(event);
	
	if myevent.mEventType == MOLET_GUI_EVENT then                      -- GUI事件

    elseif myevent.mEventType == MOLET_MOUSE_INPUT_EVENT then          -- 鼠标事件

	elseif myevent.mEventType == MOLET_KEY_INPUT_EVENT then                   -- 按键事件

	end	
end

--
-- 用于处理游戏中定时器事件
-- IDEvent 要处理的游戏中的定时器ID
--
function OnProcessGameTimer(IDEvent)

end

--
-- 用于处理房间中的网络消息
--
-- @param msg 接收到要处理的网络消息
--
function OnProcessPlayerGameRoomMsg(msg)

end
