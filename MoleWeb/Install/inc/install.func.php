<?php
if(!defined('LIUCMS_INSTALL')) exit('Access Denied');
function tpl($file){
	$file = "tpl/".$file.".html";
	return $file;
}
function str_parcate($cate, &$str_parcate, $startID = 0){
	if(!$cate[$startID]['cup']) return;
	foreach ($cate as $key => $value){
		if($value['cup'] == $startID){
			$str_parcate .= $value['cid'].',';
			str_parcate($cate, $str_parcate, $value['cid']);
		}
	}
}

function str_subcate($cate, &$str_subcate, $startID = 0){
	foreach($cate as $key => $value){
		if($value['cup'] == $startID){
			$str_subcate .= $value['cid'].',';
			str_subcate($cate, $str_subcate, $value['cid']);
		}
	}
}
function addS(&$array){
	if (is_array($array)){
		foreach ($array as $key => $value)
		{
			 addS($array[$key]);
		}
	}elseif(is_string($array)){
		$array = addslashes($array);
	}
}
function result($result = 1, $output = 1){
	if($result){
		$text = ' ... <span class="blue">OK</span>';
		if(!$output){
			return $text;
		}
		echo $text;
	}else{
		$text = ' ... <span class="red">Failed</span>';
		if(!$output){
			return $text;
		}
		echo $text;
	}
}
function createtable($sql, $db_charset){
	$db_charset = (strpos($db_charset, '-') === FALSE) ? $db_charset : str_replace('-', '', $db_charset);
	$type = strtoupper(preg_replace("/^\s*CREATE TABLE\s+.+\s+\(.+?\).*(ENGINE|TYPE)\s*=\s*([a-z]+?).*$/isU", "\\2", $sql));
	$type = in_array($type, array("MYISAM", "HEAP")) ? $type : "MYISAM";
	return preg_replace("/^\s*(CREATE TABLE\s+.+\s+\(.+?\)).*$/isU", "\\1", $sql).
		(mysql_get_server_info() > "4.1" ? " ENGINE=$type DEFAULT CHARSET=$db_charset" : " TYPE=$type");
}
function getip(){
	if(isset ($_SERVER['HTTP_X_FORWARDED_FOR'])){
		$onlineip = $_SERVER['HTTP_X_FORWARDED_FOR'];
	}elseif(isset ($_SERVER['HTTP_CLIENT_IP'])){
		$onlineip = $_SERVER['HTTP_CLIENT_IP'];
	}else{
		$onlineip = $_SERVER['REMOTE_ADDR'];
	}
	$onlineip = preg_match('/[\d\.]{7,15}/', addslashes($onlineip), $onlineipmatches);
	return $onlineipmatches[0] ? $onlineipmatches[0] : 'unknown';
}
function writable($var){
	$writeable = FALSE;
	$var = LIUCMS_ROOT.$var;
	if(!is_dir($var)){
		@mkdir($var, 0777);
	}
	if(is_dir($var)){
		$var .= '/temp.txt';
		if(($fp = @fopen($var, 'w')) && (fwrite($fp, 'LIUCMS'))){
			fclose($fp);
			@unlink($var);
			$writeable = TRUE;
		}
	}
	return $writeable;
}
function PWriteFile($filename, $content, $mode = 'ab'){
	if(strpos($filename, '..') !== FALSE){
		return FALSE;
	}
	$path = dirname($filename);
	if(!is_dir($path)){
		if(!mkdir($path, 0777)){
			return FALSE;
		}
	}
	$fp = @ fopen($filename, $mode);
	if($fp){
		flock($fp, LOCK_EX);
		fwrite($fp, $content);
		fclose($fp);
		@ chmod($filename, 0777);
		return TRUE;
	}
	return FALSE;
}
function random($length, $isNum = FALSE){
	$random = '';
	$str = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
	$num = '0123456789';
	if($isNum){
		$sequece = 'num';
	}else{
		$sequece = 'str';
	}
	$max = strlen($$sequece) - 1;
	for($i = 0; $i < $length; $i++){
		$random .= ${$sequece}{mt_rand(0, $max)};
	}
	return $random;
}
function clear(){
	$file['cache'] = array(LIUCMS_ROOT."Admin/Runtime/Cache",LIUCMS_ROOT."LiuCmsApp/Runtime/Cache");
	$file['data'] = array(LIUCMS_ROOT."Admin/Runtime/Data/_fields",LIUCMS_ROOT."LiuCmsApp/Runtime/Data/_fields");
	$file['temp'] = array(LIUCMS_ROOT."Admin/Runtime/Temp",LIUCMS_ROOT."LiuCmsApp/Runtime/Temp");
	$file['logs'] = array(LIUCMS_ROOT."Admin/Runtime/Logs",LIUCMS_ROOT."LiuCmsApp/Runtime/Logs");
	$file['runtime'] = array(LIUCMS_ROOT."Admin/Runtime/~runtime.php",LIUCMS_ROOT."LiuCmsApp/Runtime/~runtime.php");
	$file['app'] = array(LIUCMS_ROOT.LIUCMS_ROOT."Admin/Runtime/~app.php",LIUCMS_ROOT."LiuCmsApp/Runtime/~app.php");
	$dir = array_merge($file['cache'],$file['data'],$file['temp'],$file['logs'],$file['runtime'],$file['app']);
	foreach($dir as $key){
		removeDir($key);
	}
}
function removeDir($dirName){ 
   	if(!is_dir($dirName)) return @unlink($dirName); 
   	$handle = @opendir($dirName); 
   	while(($file = @readdir($handle)) !== false){ 
       	if($file != '.' && $file != '..'){ 
           	$dir = $dirName . '/' . $file;
			is_dir($dir) ? removeDir($dir) : @unlink($dir);
       	} 
   	} 
   	closedir($handle); 
	return true;
}
?>