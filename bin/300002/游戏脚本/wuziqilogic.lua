chesspan = {};                    -- 用于保存当前棋盘
chesslist = {};                   -- 用于保存棋盘上的所有棋子
totalrow = 15;                    -- 棋盘有多少行
totallist = 15;                    -- 棋盘有多少列
chesswidth = 36;                  -- 棋子宽度
chessheight = 36;                 -- 棋子高度

GAMESTATE_WAITING = 0;            -- 等待开始游戏
GAMESTATE_GAMING = 1;             -- 游戏中
GAMESTATE_END = 2;                -- 暂停游戏
      
m_gamestate = GAMESTATE_WAITING;   
m_texChess1 = 0;    -- 棋子用到的图片
m_texChess2 = 0;
m_texPlayerType1=0;
m_texPlayerType2=0;
m_texChessSel = 0;
m_chesstexWidth = 36;
m_chesstexHeight = 36;         

m_curChessPosX = -1;
m_curChessPosY = -1;  

m_playerId = 0;                   -- 玩家在游戏中的ID
m_playerRoomIndex = -1;           -- 玩家在房间中的ID
m_RoomId = -1;                    -- 玩家所在房间ID      

-- 
-- 初始化指定行指定列的棋盘
--
-- @param row,list 要初始的棋盘的行列数
--
function InitChessPan(row,list)  
   for i = 1 , row do
      chesspan[i] = {};
      chesslist[i] = {};
      starty = (i-1)*chessheight + 86;  
      for j = 1 , list do
        startx = (j-1)*chesswidth + 46;         
        chesspan[i][j] = CMolRect_int_(startx,starty,startx+chesswidth,starty+chessheight);
        chesslist[i][j] = 0;
      end
   end
end

-- 
-- 导入棋子选择图片
--
function LoadChessSelImage()
    if chessselimage then return end
    
    -- 加载棋子选择图片
    local myImage = engine.__CMolBaseGUIContainer__:AddImage(0,"选择图片",CMolRect_int_(0,0,chesswidth-2,chessheight-2));
    chessselimage = toHelper.toMolGUIImage(myImage);
    if chessselimage then
       chessselimage:SetImagePath("游戏图片\\chesssel.png"); 
       chessselimage:SetVisible(false);
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
	m_gamestate = GAMESTATE_WAITING;  	
end

-- 
-- 根据鼠标位置显示棋子选择图片
--
-- @param posx,posy 鼠标的坐标
--
function ProcessChessSelect(posx,posy)
   for i = 1 , totalrow do
      for j = 1 , totallist do
        if chesspan[i][j]:isPointInside(CMolPosition2d_int_(posx,posy)) and
            chesslist[i][j] == 0 then
			m_curChessPosX = i;
			m_curChessPosY = j; 
            return true;
        end
      end
   end
   
   return false;
end

-- 
-- 检测鼠标是否点中了某个棋子
--
-- @param posx,posy 鼠标的坐标
-- @param result 要设置的结果
--
function ProcessMouse(posx,posy,result)
	if chesslist[posx][posy] == 0 then
		chesslist[posx][posy] = result;
		m_curChessPosX = posx;
		m_curChessPosY = posy;
		return true;
	end
	
	return false;
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
            if chessdata[i]+1 == chessdata[i+1] then
                lxcount = lxcount + 1;
            end
        end
        
        if lxcount >= 5 then return true end
    elseif direction == 2 or 
           direction == 3 or 
           direction == 4 then        -- 水平
        for i = 1 , chesscount-1 do
            if chessdata[i]+1 == chessdata[i+1] then
                lxcount = lxcount + 1;
            end
        end
        
        if lxcount >= 5 then return true end    
    end
    
    return false;
end

--
-- 设置连接提示显示的内容
--
-- @param caption 连接提示要显示的内容
--
function SetConnectionTip(caption)
    pConnTipCtrl = toHelper.toMolGUIStatic(engine.__CMolBaseGUIContainer__:FindControlById(IDD_CONNFRAME_TIP));
    
    if pConnTipCtrl then 
        pConnTipCtrl:SetText(caption);
    end
end
