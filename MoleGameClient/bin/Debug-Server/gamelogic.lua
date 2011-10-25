chesspan = {};                    -- ���ڱ��浱ǰ����
chesslist = {};                   -- ���ڱ��������ϵ���������
m_chespanisCreated = false;       -- ȷ������ֻ��ʼһ��
m_curActivePlayer = -1;           -- ��ǰ�������
totalrow = 15;                    -- �����ж�����
totallist = 15;                   -- �����ж�����
chesswidth = 34;                  -- ���ӿ��
chessheight = 34;                 -- ���Ӹ߶�

IDD_TIMER_XIAZI = 0;              -- ���Ӷ�ʱ��ID

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
end

-- 
-- �������Ƿ������ĳ������
--
-- @param posx,posy ��������
-- @param result Ҫ���õĽ��
--
function ProcessMouse(posx,posy,result)
   for i = 1 , totalrow do
      for j = 1 , totallist do
        if chesspan[i][j]:isPointInside(CMolPosition2d_int_(posx,posy)) and
            chesslist[i][j] == 0 then
            chesslist[i][j] = result;
            
            if CheackIsWin(1,i,j,result) then                
                return 3;
            end
            if CheackIsWin(2,i,j,result) then                
                return 4;
            end
            if CheackIsWin(3,i,j,result) then                
                return 5;
            end
            if CheackIsWin(4,i,j,result) then                
                return 6;
            end
            return 1;
        end
      end
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
