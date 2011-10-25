dofile("��Ϸ�ű�\\common.lua");
dofile("��Ϸ�ű�\\defines.lua");
dofile("��Ϸ�ű�\\networklogic.lua");
--�����������߼�
dofile("��Ϸ�ű�\\wuziqilogic.lua");

--
-- ��ʾ���������е�����
--
function DrawChessPan()
   for i = 1 , totalrow do
      for j = 1 , totallist do
        if chesslist[i][j] == 1 then
			engine:Draw2DImage(m_texChess1,
							 chesspan[i][j],
							 CMolRect_int_(0,0,m_chesstexWidth,m_chesstexHeight));
		elseif chesslist[i][j] == 2 then
			engine:Draw2DImage(m_texChess2,
							 chesspan[i][j],
							 CMolRect_int_(0,0,m_chesstexWidth,m_chesstexHeight));
		end
      end
   end
   
   if (m_curChessPosX > 0 and m_curChessPosX <= totalrow) and 
	  (m_curChessPosY > 0 and m_curChessPosY <= totallist) then
		engine:Draw2DImage(m_texChessSel,
						 chesspan[m_curChessPosX][m_curChessPosY],
						 CMolRect_int_(0,0,m_chesstexWidth+2,m_chesstexHeight+2)); 
   end
end

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
		engine:DrawString("- �� "..tostring(mySelf:GetRoomId()+1).." ��",
						  CMolRect_int_(370,39,600,60),
						  CMolColor(255,255,255,255));
	end
	
	-- ��ʾ����
	DrawChessPan();
							  
	for i = 1 , IDD_GAME_PLAYER_COUNT do
		local pPlayer = toHelper.toPlayer(engine:GetUserInfo(i-1));
		if pPlayer ~= nil then
			engine:DrawStringf(pPlayer:GetName(),
			                  CMolRect_int_(playerInfo[i].NamePos[1],playerInfo[i].NamePos[2],playerInfo[i].NamePos[1]+200,playerInfo[i].NamePos[2]+40),
							  CMolColor(255,255,255,255));
			engine:DrawStringf(tostring(pPlayer:GetMoney()),
			                  CMolRect_int_(playerInfo[i].NamePos[1],playerInfo[i].NamePos[2]+31,playerInfo[i].NamePos[1]+200,playerInfo[i].NamePos[2]+80),
							  CMolColor(255,255,255,255));	

			if m_texPlayerType1 ~= 0 and m_texPlayerType2 ~= 0 then
				if pPlayer:GetRoomIndex() == 0 then
					engine:Draw2DImage(m_texPlayerType2,CMolPosition2d_int_(playerInfo[i].typePos[1],playerInfo[i].typePos[2]));
				else 
					engine:Draw2DImage(m_texPlayerType1,CMolPosition2d_int_(playerInfo[i].typePos[1],playerInfo[i].typePos[2]));
				end
			end

			-- ��ʾ�û�ͷ��
			if playerInfo[i].Logotex == -1 then
				playerInfo[i].Logotex = engine:LoadTexture(engine:GetProgressDirection().."\\Avatars\\"..pPlayer:GetUserAvatar());
			else
				local texWidth = engine:GetTextureWidth(playerInfo[i].Logotex,true);
				local texHeight = engine:GetTextureHeight(playerInfo[i].Logotex,true);
				
				engine:Draw2DImage(playerInfo[i].Logotex,
								 CMolRect_int_(playerInfo[i].LogoPos[1],playerInfo[i].LogoPos[2],playerInfo[i].LogoPos[1]+IDD_LOGO_WIDTH,playerInfo[i].LogoPos[2]+IDD_LOGO_HEIGHT),
								 CMolRect_int_(0,0,texWidth,texHeight));
			end
			
			-- д�û�׼�����
			if pPlayer:GetState() == PLAYERSTATE_READY then
				engine:DrawStringf("��׼��",
								  CMolRect_int_(playerInfo[i].ReadyPos[1],playerInfo[i].ReadyPos[2],playerInfo[i].ReadyPos[1]+200,playerInfo[i].ReadyPos[2]+40),
								  CMolColor(255,255,0,0));
			end
			
			-- ��ʾ�û���ʱ��
			local curTime = engine:GetUserTimer(i-1);
			if curTime > 0 then
				engine:DrawStringf(tostring(curTime),
								  CMolRect_int_(playerInfo[i].TimerPos[1],playerInfo[i].TimerPos[2],playerInfo[i].TimerPos[1]+200,playerInfo[i].TimerPos[2]+40),
								  CMolColor(255,255,255,255));
			end
		else 
			playerInfo[i].Logotex = -1;
		end
	end
	
   --[[for i = 1 , totalrow do		
      for j = 1 , totallist do
        engine:Draw2dLine(CMolPosition2d_int_(0,68+i*36),CMolPosition2d_int_(800,68+i*36),CMolColor(255,255,0,0));
		engine:Draw2dLine(CMolPosition2d_int_(28+j*36,71),CMolPosition2d_int_(28+j*36,800),CMolColor(255,255,0,0));
      end
   end	]]--
end

--
-- �û�������Ϸ���õ�����Դ
-- 
function LoadGameResources()
	engine:LoadGUIConfig("��Ϸ����\\gamemainframe.gui");
	
	m_texChess1 = engine:LoadTexture("��ϷͼƬ\\chess1.png");
	m_texChess2 = engine:LoadTexture("��ϷͼƬ\\chess2.png");
	m_texChessSel = engine:LoadTexture("��ϷͼƬ\\chesssel.png");
	m_bgTex = engine:LoadTexture("��ϷͼƬ\\bg.png");
	m_texPlayerType1 = engine:LoadTexture("��ϷͼƬ\\heifang.png");
	m_texPlayerType2 = engine:LoadTexture("��ϷͼƬ\\baifang.png");
	
    -- ��ʼ����
    InitChessPan(totalrow,totallist);	
end

-- 
-- ���ڴ�����Ϸ���¼�
-- event ��ϵͳ�д�������Ҫ�������Ϸ�¼�����Щ�¼�������������꣬GUI�������¼�
--
function OnProcessGameEvent(event)
	local myevent = toHelper.toMolEvent(event);
	
	if myevent.mEventType == MOLET_GUI_EVENT then                      -- GUI�¼�
		-- ����û������Թ�״̬��ֱ�ӷ���
		if engine:IsLookonMode() == true then return end;
		
		if myevent.mGuiEvent.EventType == MOLGET_BUTTON_CLICKED then
			local ctrlId = myevent.mGuiEvent.Caller:GetID();			
			if ctrlId == IDD_MAINFRAME_START_GAME then           -- ׼����Ϸ
                -- ���������������׼����Ϣ
                local out = CMolMessageOut(IDD_MESSAGE_FRAME);
                out:writeShort(IDD_MESSAGE_READY_START);
                engine:Send(out);
				
				engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_START_GAME,false);
            elseif ctrlId == IDD_MAINFRAME_RENSHU_BTN then       -- ����
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_RENSHU);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_RENSHU_BTN,false);	
            elseif ctrlId == IDD_MAINFRAME_HUOQI_BTN then        -- �������
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_HUOQI);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUOQI_BTN,false);	
            elseif ctrlId == IDD_QIUHEDIG_OK then                -- ��Ϸ������ʾ��ȷ����ť
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_HUOQI_OK);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:ShowControlById(IDD_QIUHEDIG,false);  
            elseif ctrlId == IDD_QIUHEDIG_CONCEL then            -- ��Ϸ������ʾ��ȡ����ť
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_HUOQI_CONCEL);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:ShowControlById(IDD_QIUHEDIG,false);  	
			elseif ctrlId == IDD_MAINFRAME_HUIQI_BTN then        -- �������
				-- �����ʱ�򣬱��뵱ǰ��Ҳ����Լ�
				
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_HUIQI);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:ShowControlById(IDD_MAINFRAME_HUIQI_BTN,false);  
			elseif ctrlId == IDD_HUIQIDLG_OK then                -- ȷ������
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_HUIQI_OK);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:ShowControlById(IDD_HUIQIDLG,false);  
			elseif ctrlId == IDD_HUIQIDLG_CONCEL then            -- ��ͬ�����	
                local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                out:writeShort(IDD_MESSAGE_GAMING_HUIQI_CONCEL);
                out:writeShort(engine:GetMeChairID());
                
                engine:Send(out);
                
                engine.__CMolBaseGUIContainer__:ShowControlById(IDD_HUIQIDLG,false);  
            elseif ctrlId == IDD_MAINFRAME_SENDCHAT_BTN then     -- ����������Ϣ
                local myCtrl = engine.__CMolBaseGUIContainer__:FindControlById(IDD_MAINFRAME_CHAT_INPUT);
                local myEditor = toHelper.toMolGUIEditorBox(myCtrl);
                
                if myEditor and myEditor:GetText() ~= "" then                  
                    -- ����������Ϣ���������
                    local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                    out:writeShort(IDD_MESSAGE_GAMING_CHAT);
                    out:writeShort(m_playerRoomIndex);
                    out:writeString(myEditor:GetText());
                    engine:Send(out);
                    
                    myEditor:SetText("");
                end	

				engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_SENDCHAT_BTN,false);		
			end
		end
    elseif myevent.mEventType == MOLET_MOUSE_INPUT_EVENT then          -- ����¼�
		-- ����û������Թ�״̬��ֱ�ӷ���
		if engine:IsLookonMode() == true then return end;
		
        if myevent.mMouseEvent.EventType == MOLMIE_LMOUSE_PRESSED_DOWN then
            local MouseposX = myevent.mMouseEvent.X;
            local MouseposY = myevent.mMouseEvent.Y;
            
			-- ��������Ϸ��״̬�����ҵ�ǰ��������Լ�
            if m_gamestate == GAMESTATE_GAMING and m_playerRoomIndex == engine:GetMeChairID() then
                if ProcessChessSelect(MouseposX,MouseposY) then 
					-- ���ŵ�������
					engine:EffectPlay("��Ϸ����\\dianzi1.wav");	
					
					chesslist[m_curChessPosX][m_curChessPosY] = m_playerRoomIndex+1;
				
                    -- ��������������ҵ�����Ϣ
                    local out = CMolMessageOut(IDD_MESSAGE_ROOM);
                    out:writeShort(IDD_MESSAGE_GAMING_DIANZI);
                    out:writeShort(m_playerRoomIndex);
                    out:writeByte(m_curChessPosX);
                    out:writeByte(m_curChessPosY);
                    engine:Send(out);    

					if m_playerRoomIndex == 0 then 
						m_playerRoomIndex = 1;
					elseif m_playerRoomIndex == 1 then 
						m_playerRoomIndex = 0;
					end		

					-- �رն�ʱ��
					engine:KillGameTimer(IDD_TIMER_XIAZI);
					engine:SetGameTimer(engine:SwitchViewChairID(m_playerRoomIndex),IDD_TIMER_XIAZI,10);
                end
            end
        elseif myevent.mMouseEvent.EventType == MOLMIE_MOUSE_MOVED then
            local MouseposX = myevent.mMouseEvent.X;
            local MouseposY = myevent.mMouseEvent.Y;
            
            if m_gamestate == GAMESTATE_GAMING and m_playerRoomIndex == engine:GetMeChairID() then
                -- ����Ϸ״̬�¸������λ����ʾѡ��ͼƬ
                ProcessChessSelect(MouseposX,MouseposY);
            end
        end
	elseif myevent.mEventType == MOLET_KEY_INPUT_EVENT then                   -- �����¼�

	end	
end

--
-- ���ڴ�����Ϸ�ж�ʱ���¼�
-- IDEvent Ҫ�������Ϸ�еĶ�ʱ��ID
--
function OnProcessGameTimer(IDEvent)
	if IDEvent == IDD_TIMER_XIAZI then       -- ���Ӷ�ʱ��
		engine.__CMolBaseGUIContainer__:ShowControlById(IDD_QIUHEDIG,false); 
		engine.__CMolBaseGUIContainer__:ShowControlById(IDD_HUIQIDLG,false);  
		
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
		
		-- ��������Ϸ��״̬�����ҵ�ǰ��������Լ�,���Ҳ��ܴ����Թ�״̬
		if m_gamestate == GAMESTATE_GAMING and m_playerRoomIndex == engine:GetMeChairID() and engine:IsLookonMode() == false then
			chesslist[chessX][chessY] = m_playerRoomIndex+1;
			
			m_curChessPosX = chessX;
			m_curChessPosY = chessY; 			
			
			-- ���ŵ�������
			engine:EffectPlay("��Ϸ����\\dianzi1.wav");	
		
			-- ��������������ҵ�����Ϣ
			local out = CMolMessageOut(IDD_MESSAGE_ROOM);
			out:writeShort(IDD_MESSAGE_GAMING_DIANZI);
			out:writeShort(m_playerRoomIndex);
			out:writeByte(chessX);
			out:writeByte(chessY);
			engine:Send(out);    

			if m_playerRoomIndex == 0 then 
				m_playerRoomIndex = 1;
			elseif m_playerRoomIndex == 1 then 
				m_playerRoomIndex = 0;
			end		
		end
	end
end

--
-- ���ڴ������е�������Ϣ
--
-- @param msg ���յ�Ҫ�����������Ϣ
--
function OnProcessPlayerGameRoomMsg(msg)
	local myMsg = toHelper.toMolMessageIn(msg);
	local myMsgSubId = myMsg:readShort();
	
	if myMsgSubId == IDD_MESSAGE_GAME_START then              -- ��ʼ��Ϸ
		m_playerRoomIndex = myMsg:readShort();
		
		-- ���³�ʼ����������
		ResetChessPan();
		
		local myTextarea = toHelper.toMolGUITextarea(engine.__CMolBaseGUIContainer__:FindControlById(IDD_MAINFRAME_CHAT_MESSAGE));
		if myTextarea then
			myTextarea:AddString("���:"..tostring(m_playerRoomIndex).." ��ʼ���ӡ�",CMolColor(255,255,0,0));
		end
		
		if engine:IsLookonMode() == false then
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUIQI_BTN,true);
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUOQI_BTN,true);
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_RENSHU_BTN,true);
		end
		
		-- ��������
		engine:EffectPlay("��Ϸ����\\startgame.wav");	
		
		m_gamestate = GAMESTATE_GAMING;  
		engine:SetGameTimer(engine:SwitchViewChairID(m_playerRoomIndex),IDD_TIMER_XIAZI,10);
	elseif myMsgSubId == IDD_MESSAGE_GAMING_DIANZI then              -- �û�����
		local pPlayerId = myMsg:readShort();
		local chessposx = myMsg:readByte();
		local chessposy = myMsg:readByte();
		
		if pPlayerId == m_playerRoomIndex then
			if ProcessMouse(chessposx,chessposy,m_playerRoomIndex+1) then			
				-- ���ŵ�������
				engine:EffectPlay("��Ϸ����\\dianzi1.wav");			
				
				if pPlayerId == 0 then 
					m_playerRoomIndex = 1;
				elseif pPlayerId == 1 then 
					m_playerRoomIndex = 0;
				end
			end
		end
		
		engine:SetGameTimer(engine:SwitchViewChairID(m_playerRoomIndex),IDD_TIMER_XIAZI,10);
	elseif myMsgSubId == IDD_MESSAGE_LOOKON_ENTER_ROOM or myMsgSubId == IDD_MESSAGE_DISCONN_BACK then              -- �Թ�,�����ػ�״̬��
		m_playerRoomIndex = myMsg:readShort();
		m_gamestate = GAMESTATE_GAMING; 
		
		for i = 1 , totalrow do
		  for j = 1 , totallist do
			local chess = myMsg:readByte();
			
			if chess > 0 then
				ProcessMouse(i,j,chess);
			end
		  end
		end		

		engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_START_GAME,false);	
		
		if engine:IsLookonMode() == false then
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUIQI_BTN,true);
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUOQI_BTN,true);
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_RENSHU_BTN,true);
		end
		
		engine:SetGameTimer(engine:SwitchViewChairID(m_playerRoomIndex),IDD_TIMER_XIAZI,10);
	elseif myMsgSubId == IDD_MESSAGE_GAME_END then                        -- ��Ϸ����
		m_gamestate = GAMESTATE_END; 

		if engine:IsLookonMode() == false then		
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUIQI_BTN,false);
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUOQI_BTN,false);
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_RENSHU_BTN,false);	
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_START_GAME,true);
		end
		
		engine:KillGameTimer(IDD_TIMER_XIAZI);
		
		-- ������Ϸ��������
		engine:EffectPlay("��Ϸ����\\win.wav");	
	elseif myMsgSubId == IDD_MESSAGE_GAMING_CHAT then                     -- ������Ϣ
		local playerId = myMsg:readShort();
		local chat = myMsg:readString();
		
		local myTextarea = toHelper.toMolGUITextarea(engine.__CMolBaseGUIContainer__:FindControlById(IDD_MAINFRAME_CHAT_MESSAGE));
		if myTextarea then
			myTextarea:AddString("���:"..tostring(playerId)..chat,CMolColor(255,255,255,255));
		end
		
		if engine:GetMeChairID() == playerId then
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_SENDCHAT_BTN,true);
		end
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUOQI then                    -- �����������
		local playerId = myMsg:readShort();
             
		if playerId ~= engine:GetMeChairID() then                    
			engine:ShowGUIContainer(IDD_QIUHEDIG,"gui\\qiuhuodialog.gui",SANPSTYLE_CENTER);
		end		
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUOQI_CONCEL then             -- ���˲�ͬ�����
		local playerId = myMsg:readShort();		
            
		if playerId == engine:GetMeChairID() then
			engine.__CMolBaseGUIContainer__:EnableControlById(IDD_MAINFRAME_HUOQI_BTN,true);
		end   
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUIQI then                    -- �����������
		local playerId = myMsg:readShort();
             
		if playerId ~= engine:GetMeChairID() then                    
			engine:ShowGUIContainer(IDD_HUIQIDLG,"gui\\huiqidialog.gui",SANPSTYLE_CENTER);
		end	
	elseif myMsgSubId == IDD_MESSAGE_GAMING_HUIQI_OK then                 -- �Ѿ�ͬ�����
		local chessposx = myMsg:readByte();
		local chessposy = myMsg:readByte();
		
		chesslist[chessposx][chessposy] = 0;
		
		if m_playerRoomIndex == 0 then 
			m_playerRoomIndex = 1;
		elseif pPlayerId == 1 then 
			m_playerRoomIndex = 0;
		end
		
		engine:SetGameTimer(engine:SwitchViewChairID(m_playerRoomIndex),IDD_TIMER_XIAZI,10);
	end
end
