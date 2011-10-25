<?php
if (!defined('THINK_PATH')) exit();
$lc_version = require './version.inc.php';
$config	= require './config.inc.php';
$liucms_config = array(
	//'配置项'=>'配置值'
);
return array_merge($lc_version,$config,$liucms_config);
?>