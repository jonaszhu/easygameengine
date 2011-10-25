<?php
class PagesModel extends Model{
	protected $_validate=array(
		array('title','require','标题必填！',0,'',3),
		array('content','require','内容必填！',1,'',3),
	);
	protected $_auto = array(
		array('postdate','time',1,'function'),
	);
}
?>