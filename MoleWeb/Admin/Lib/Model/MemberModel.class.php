<?php
class MemberModel extends Model{
	protected $_validate=array(
		array('username','require','用户名必填！',0,'',3),
		array('username','','用户已存在！',2,'unique',1), 
		array('password','require','用户密码必填！',1,'',3),
		array('email','require','Email必填！',1,'',3),
		array('email','email','Email格式错误！',2,'',3),
		array('email','','Email已存在！',2,'unique',1), 
	);
	protected $_auto=array(
		array('createtime','time',1,'function'),
	);	
}
?>