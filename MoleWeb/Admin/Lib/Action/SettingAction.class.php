<?php
class SettingAction extends BaseAction{
	function _initialize(){
		$map['uid'] = $_SESSION[C('USER_AUTH_KEY')];
		$map['gtype'] = "2";
		$comp = D("Member")->where($map)->select();
		if(!$comp) $this->error("对不起，您没有权限！");
	}
	public function index(){
		$siteinfo = D("Options")->findall();
		foreach($siteinfo as $key){
			$this->assign($key['types'],$key['values']);
		}
		$this->display("Public:setting");
	}
	public function update(){
		$data = $_POST;
		foreach($data AS $key => $value) {
            $result = D("Options")->query("REPLACE INTO __TABLE__ VALUES ('$key', '$value');");
        }
		$this->assign("jumpUrl","__URL__");
		$this->success("更新成功！");
	}
}
?>