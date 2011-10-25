chesspan = {};                    -- ���ڱ��浱ǰ����
chesslist = {};                   -- ���ڱ��������ϵ���������
m_chespanisCreated = false;       -- ȷ������ֻ��ʼһ��
m_curActivePlayer = -1;           -- ��ǰ�������
totalrow = 15;                    -- �����ж�����
totallist = 15;                   -- �����ж�����
chesswidth = 34;                  -- ���ӿ��
chessheight = 34;                 -- ���Ӹ߶�

IDD_TIMER_XIAZI = 1000;              -- ���Ӷ�ʱ��ID

m_curChessPosX = -1;
m_curChessPosY = -1;  

-- 
-- ��ʼ��ָ����ָ���е�����
--
-- @param row,list Ҫ��ʼ�����̵�������
--
function InitChessPan(row,list)  
   for i = 1 , row do
      chesspan[i] = {};
      chesslist[i] = {};
      starty = (i-1)*chessheight + 37;  
      for j = 1 , list do
        startx = (j-1)*chesswidth + 17;         
        chesspan[i][j] = CMolRect_int_(startx+2,starty+2,startx+chesswidth-2,starty+chessheight-2);
        chesslist[i][j] = 0;
      end
   end
end

-- 
-- ����������������
--
function ResetChessPan()
   for i = 1 , totalrow do
      for j = 1 , totallist do
        chesslist[i][j] = 0;
      end
   end
   
	m_curChessPosX = -1;
	m_curChessPosY = -1;    
end

--
-- ��������Ƿ��Ѿ���ռ��
--
-- @return ��������Ѿ���ռ���Ļ��������棬���򷵻ؼ�
--
function IsFullChess()  
   for i = 1 , totalrow do
      for j = 1 , totallist do
         if chesslist[i][j] == 0 then
			return false;
		 end
      end
   end	
   
   return true;
end

-- 
-- �������Ƿ������ĳ������
--
-- @param posx,posy ��������
-- @param result Ҫ���õĽ��
--
function ProcessMouse(posx,posy,result)          
	if CheackIsWin(1,posx,posy,result) then                
		return 3;
	end
	if CheackIsWin(2,posx,posy,result) then                
		return 4;
	end
	if CheackIsWin(3,posx,posy,result) then                
		return 5;
	end
	if CheackIsWin(4,posx,posy,result) then                
		return 6;
	end
	if IsFullChess() == true then
		return 2;
	end
   
    return 0;
end

-- 
-- ���ָ��λ�õ����Ƿ��ʤ
--
-- @param direction Ҫ���ķ���: 1 - ��ֱ��2 - ˮƽ��3 - ��б��4 - ��б
-- @param posx,posy Ҫ����ʤ����
-- @param result Ҫ���Ľ��
--
-- @return �����������������5���ӳ��ַ����棬���򷵻ؼ�
--
function CheackIsWin(direction,posx,posy,result)    
    local index = 1;
    if direction == 1 then     -- ��ֱ
        local temp = {};
        for i = 1 , totalrow do
            if chesslist[i][posy] == result then
                temp[index] = i;
                index = index + 1;
            end
        end
                
        return IsWuLianZhu(direction,temp);
    elseif direction == 2 then   -- ˮƽ
        local temp = {};
        for i = 1 , totallist do
            if chesslist[posx][i] == result then
                temp[index] = i;
                index = index + 1;
            end
        end
                
        return IsWuLianZhu(direction,temp);    
    elseif direction == 3 then   -- ��б
        local temp = {};
   
        -- ��ȡ���ϲ��ֵ�   
        tempx = posx;
        tempy = posy;
        while tempx <= totalrow and tempy >= 1 do
            if chesslist[tempx][tempy] == result then
                if temp[index] ~= tempy then temp[index] = tempy; end
                index = index + 1;
            end
            
            tempx = tempx + 1;
            tempy = tempy - 1;
        end        
        
        -- ��ȡ���²��ֵ�
        tempx = posx;
        tempy = posy;
        index = 1;
        while tempx >= 1 and tempy <= totallist do
            if chesslist[tempx][tempy] == result then
                if temp[index] ~= tempy then temp[index] = tempy; end
                index = index + 1;
            end
            
            tempx = tempx - 1;
            tempy = tempy + 1;
        end
        
        table.sort(temp);
               
        return IsWuLianZhu(direction,temp);     
    elseif direction == 4 then   -- ��б
        local temp = {};
   
        -- ��ȡ���ϲ��ֵ�   
        tempx = posx;
        tempy = posy;
        while tempx >= 1 and tempy >= 1 do
            if chesslist[tempx][tempy] == result then
                if temp[index] ~= tempy then temp[index] = tempy; end
                index = index + 1;
            end
            
            tempx = tempx - 1;
            tempy = tempy - 1;
        end        
        
        -- ��ȡ���²��ֵ�
        tempx = posx;
        tempy = posy;
        index = 1;
        while tempx <= totalrow and tempy <= totallist do
            if chesslist[tempx][tempy] == result then
                if temp[index] ~= tempy then temp[index] = tempy; end
                index = index + 1;
            end
            
            tempx = tempx + 1;
            tempy = tempy + 1;
        end
        
        table.sort(temp);
               
        return IsWuLianZhu(direction,temp);                   
    end
end

-- ���һ�������Ƿ�����������ӳ���
-- 
-- @param direction Ҫ���ķ���: 1 - ��ֱ��2 - ˮƽ��3 - ��б��4 - ��б
-- @param chessdata Ҫ������������
--
-- @return �����������������5���ӳ��ַ����棬���򷵻ؼ�
--
function IsWuLianZhu(direction,chessdata)
    if chessdata == nil then return false end
    
    local chesscount = table.getn(chessdata);
    local lxcount = 1;         -- �������ֵĴ���
    
    if direction == 1 then       -- ��ֱ
        for i = 1 , chesscount-1 do
            if math.abs(chessdata[i] - chessdata[i+1]) == 1 then
                lxcount = lxcount + 1;
                if lxcount >= 5 then return true end  
            else
                lxcount = 1;
            end
        end
        
        if lxcount >= 5 then return true end
    elseif direction == 2 or 
           direction == 3 or 
           direction == 4 then        -- ˮƽ
        for i = 1 , chesscount-1 do
            if math.abs(chessdata[i] - chessdata[i+1]) == 1 then
                lxcount = lxcount + 1;
                if lxcount >= 5 then return true end  
            else
                lxcount = 1;
            end
        end
        
        if lxcount >= 5 then return true end    
    end
    
    return false;
end

--
-- �����Ϸ�Ƿ����
--
-- @param room Ҫ���ķ���
-- @param posx,posy,result �û��ĵ���
--
function IsGameEnd(room,posx,posy,result)
	if room == nil then return end;
	
	-- �ж��Ƿ����
	local result = ProcessMouse(posx,posy,chesslist[posx][posy]);
	if result > 0 then
		
		if result > 1 then           
			-- ͳ�������Ϸ���
			if chesslist[posx][posy]-1 == 0 then
				local pPlayer = toHelper.toPlayer(room:GetPlayer(0));
				if pPlayer ~= nil then 
					pPlayer:SetMoney(pPlayer:GetMoney()+10);
				end
				pPlayer = toHelper.toPlayer(room:GetPlayer(1));
				if pPlayer ~= nil then 
					pPlayer:SetMoney(pPlayer:GetMoney()-10);
				end					
			elseif chesslist[posx][posy]-1 == 1 then
				local pPlayer = toHelper.toPlayer(room:GetPlayer(0));
				if pPlayer ~= nil then 
					pPlayer:SetMoney(pPlayer:GetMoney()-10);
				end
				pPlayer = toHelper.toPlayer(room:GetPlayer(1));
				if pPlayer ~= nil then 
					pPlayer:SetMoney(pPlayer:GetMoney()+10);
				end	
			end
		end
		
		room:GameEnd();
		room:StopTimer(IDD_TIMER_XIAZI);
		
		-- ������Ϸ������Ϣ
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAME_END);
		
		room:SendTableMsg(-1,out);
		room:SendLookOnMes(-1,out);
	end
end
