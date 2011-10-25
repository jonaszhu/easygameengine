<?php
class NewsModel extends Model{
	protected $_validate=array(
		array('title','require','新闻标题必填！',0,'',3),
		array('content','require','新闻内容必填！',1,'',3),
	);
	protected $_auto = array(
		array('postdate','time',1,'function'),
	);
}
?>
