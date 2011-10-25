<?php
class NavigationModel extends Model{
	protected $_validate=array(
		array('name','require','名称必填！',0,'',3),
		array('url','require','链接必填！',0,'',3),
		array('url','url','链接URL格式错误！',2,'',3),
	);
}
?>