<?php
class GameModel extends Model{
	protected $_validate=array(
		array('Id','require','��ϷID���',0,'',3),
		array('Id','','��ϷID�Ѵ��ڣ�',2,'unique',1), 
		array('name','require','��Ϸ���Ʊ��',0,'',3),
		array('name','','��Ϸ�����Ѵ��ڣ�',2,'unique',1), 	
		array('Type','require','��Ϸ���ͱ��',0,'',3),
	);
}
?>