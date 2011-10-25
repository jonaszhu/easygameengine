chesspan = {};                    -- 用于保存当前棋盘
chesslist = {};                   -- 用于保存棋盘上的所有棋子
m_chespanisCreated = false;       -- 确保棋牌只初始一次
m_curActivePlayer = -1;           -- 当前下子玩家
totalrow = 15;                    -- 棋盘有多少行
totallist = 15;                   -- 棋盘有多少列
chesswidth = 34;                  -- 棋子宽度
chessheight = 34;                 -- 棋子高度

IDD_TIMER_XIAZI = 1000;              -- 下子定时器ID

m_curChessPosX = -1;
m_curChessPosY = -1;  

-- 
-- 初始化指定行指定列的棋盘
--
-- @param row,list 要初始的棋盘的行列数
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
-- 重新设置整个棋盘
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
-- 检测棋牌是否已经被占满
--
-- @return 如果棋牌已经被占满的话，返回真，否则返回假
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
-- 检测鼠标是否点中了某个棋子
--
-- @param posx,posy 鼠标的坐标
-- @param result 要设置的结果
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
-- 检测指定位置的子是否获胜
--
-- @param direction 要检测的方向: 1 - 垂直；2 - 水平；3 - 左斜；4 - 右斜
-- @param posx,posy 要检测获胜的子
-- @param result 要检测的结果
--
-- @return 如果这列数据有连续5个子出现返回真，否则返回假
--
function CheackIsWin(direction,posx,posy,result)    
    local index = 1;
    if direction == 1 then     -- 垂直
        local temp = {};
        for i = 1 , totalrow do
            if chesslist[i][posy] == result then
                temp[index] = i;
                index = index + 1;
            end
        end
                
        return IsWuLianZhu(direction,temp);
    elseif direction == 2 then   -- 水平
        local temp = {};
        for i = 1 , totallist do
            if chesslist[posx][i] == result then
                temp[index] = i;
                index = index + 1;
            end
        end
                
        return IsWuLianZhu(direction,temp);    
    elseif direction == 3 then   -- 左斜
        local temp = {};
   
        -- 先取右上部分的   
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
        
        -- 再取左下部分的
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
    elseif direction == 4 then   -- 右斜
        local temp = {};
   
        -- 先取左上部分的   
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
        
        -- 再取右下部分的
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

-- 检测一列数据是否有连续五颗子出现
-- 
-- @param direction 要检测的方向: 1 - 垂直；2 - 水平；3 - 左斜；4 - 右斜
-- @param chessdata 要检测的棋子数据
--
-- @return 如果这列数据有连续5个子出现返回真，否则返回假
--
function IsWuLianZhu(direction,chessdata)
    if chessdata == nil then return false end
    
    local chesscount = table.getn(chessdata);
    local lxcount = 1;         -- 连续出现的次数
    
    if direction == 1 then       -- 垂直
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
           direction == 4 then        -- 水平
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
-- 检测游戏是否结束
--
-- @param room 要检测的房间
-- @param posx,posy,result 用户的点子
--
function IsGameEnd(room,posx,posy,result)
	if room == nil then return end;
	
	-- 判断是否结束
	local result = ProcessMouse(posx,posy,chesslist[posx][posy]);
	if result > 0 then
		
		if result > 1 then           
			-- 统计最后游戏结果
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
		
		-- 发送游戏结束消息
		local out = CMolMessageOut(IDD_MESSAGE_ROOM);
		out:writeShort(IDD_MESSAGE_GAME_END);
		
		room:SendTableMsg(-1,out);
		room:SendLookOnMes(-1,out);
	end
end
