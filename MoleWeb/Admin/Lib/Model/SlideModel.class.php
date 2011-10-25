<?php
class SlideModel extends Model{
	protected $_validate=array(
		array('title','require','标题必填！',0,'',3),
		array('content','require','描述必填！',0,'',3),
		array('url','url','链接URL格式错误！',2,'',3),
	);
	protected $_auto=array(
		array('postdate','time',1,'function'),
	);
}
?>