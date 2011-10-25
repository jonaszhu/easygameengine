<?php
class CategroyModel extends Model{
	protected $_validate=array(
		array('name','require','分类名必填！',0,'',3),
	);
}
?>
