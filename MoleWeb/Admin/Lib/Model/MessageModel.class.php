<?php
class MessageModel extends Model{
	protected $_validate=array(
		array('name','require','姓名必填！',0,'',3),
		array('content','require','留言内容必填！',1,'',3),
		array('email','require','Email必填！',1,'',3),
		array('email','email','Email格式错误！',2,'',3),
	);
}
?>