<?php
class IndexAction extends BaseAction{
    public function index(){
		$userInfo = D("Member")->where("uid = ".Session::get(C('USER_AUTH_KEY')))->find();
		$siteCount['usercount'] = D("Member")->count();
		$siteCount['newscount'] = D("News")->count();
		$siteCount['pagescount'] = D("Pages")->count();
		$siteCount['catscount'] = D("Categroy")->count();
		$siteCount['msgcount'] = D("Message")->count();
		$array['osinfo'] = PHP_OS;
		$array['osinfo'] .= @ini_get('safe_mode') ? ' Safe Mode' : NULL;
		$array['serverinfo'] = $_SERVER["SERVER_SOFTWARE"];
		$sqlinfo = M()->query("SELECT VERSION()");
		$array['sqlinfo'] = $sqlinfo[0]['VERSION()'];
		$array['serverip'] = $_SERVER['SERVER_NAME'].' [ '.gethostbyname($_SERVER['SERVER_NAME']).' ]';
		$array['servertime'] = date("Y年n月j日 H:i:s");
		if(@ini_get('file_uploads')) {
			$upload = ini_get('upload_max_filesize');
		} else {
			$upload = '<font color="red">'.不支持上传.'</font>';
		}
		$array['upload'] = $upload;
		$this->assign('latestversion','<script language="javascript" src="http://fengziliu.com/liucms/vs.php?version='.C("LIUCMS_VERSION").'"></script>');
		$this->assign('userInfo',$userInfo);
		$this->assign('siteCount',$siteCount);
		$this->assign($array);
		$this->display("Public:index");
    }
}
?>