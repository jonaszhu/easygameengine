<?php
if (!defined('THINK_PATH')) exit();
$lc_version = require './version.inc.php';
$config	= require './config.inc.php';
$adm_config = array(
	//'配置项'=>'配置值'
	'USER_AUTH_GATEWAY'	=>'/Public/login',
);
return array_merge($lc_version,$config,$adm_config);
?>