chesspan = {};                    -- ���ڱ��浱ǰ����
chesslist = {};                   -- ���ڱ��������ϵ���������
totalrow = 15;                    -- �����ж�����
totallist = 15;                    -- �����ж�����
chesswidth = 36;                  -- ���ӿ��
chessheight = 36;                 -- ���Ӹ߶�

GAMESTATE_WAITING = 0;            -- �ȴ���ʼ��Ϸ
GAMESTATE_GAMING = 1;             -- ��Ϸ��
GAMESTATE_END = 2;                -- ��ͣ��Ϸ
      
m_gamestate = GAMESTATE_WAITING;   
m_texChess1 = 0;    -- �����õ���ͼƬ
m_texChess2 = 0;
m_texPlayerType1=0;
m_texPlayerType2=0;
m_texChessSel = 0;
m_chesstexWidth = 36;
m_chesstexHeight = 36;         

m_curChessPosX = -1;
m_curChessPosY = -1;  

m_playerId = 0;                   -- �������Ϸ�е�ID
m_playerRoomIndex = -1;           -- ����ڷ����е�ID
m_RoomId = -1;                    -- ������ڷ���ID      

-- 
-- ��ʼ��ָ����ָ���е�����
--
-- @param row,list Ҫ��ʼ�����̵�������
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
-- ��������ѡ��ͼƬ
--
function LoadChessSelImage()
    if chessselimage then return end
    
    -- ��������ѡ��ͼƬ
    local myImage = engine.__CMolBaseGUIContainer__:AddImage(0,"ѡ��ͼƬ",CMolRect_int_(0,0,chesswidth-2,chessheight-2));
    chessselimage = toHelper.toMolGUIImage(myImage);
    if chessselimage then
       chessselimage:SetImagePath("��ϷͼƬ\\chesssel.png"); 
       chessselimage:SetVisible(false);
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
	m_gamestate = GAMESTATE_WAITING;  	
end

-- 
-- �������λ����ʾ����ѡ��ͼƬ
--
-- @param posx,posy ��������
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
-- �������Ƿ������ĳ������
--
-- @param posx,posy ��������
-- @param result Ҫ���õĽ��
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
            if chessdata[i]+1 == chessdata[i+1] then
                lxcount = lxcount + 1;
            end
        end
        
        if lxcount >= 5 then return true end
    elseif direction == 2 or 
           direction == 3 or 
           direction == 4 then        -- ˮƽ
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
-- ����������ʾ��ʾ������
--
-- @param caption ������ʾҪ��ʾ������
--
function SetConnectionTip(caption)
    pConnTipCtrl = toHelper.toMolGUIStatic(engine.__CMolBaseGUIContainer__:FindControlById(IDD_CONNFRAME_TIP));
    
    if pConnTipCtrl then 
        pConnTipCtrl:SetText(caption);
    end
end
