<?php
class GameModel extends Model{
	protected $_validate=array(
		array('Id','require','游戏ID必填！',0,'',3),
		array('Id','','游戏ID已存在！',2,'unique',1), 
		array('name','require','游戏名称必填！',0,'',3),
		array('name','','游戏名称已存在！',2,'unique',1), 	
		array('Type','require','游戏类型必填！',0,'',3),
	);
}
?>