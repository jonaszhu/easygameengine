<?php
class ThemeAction extends BaseAction{
	function _initialize(){
		$map['uid'] = $_SESSION[C('USER_AUTH_KEY')];
		$map['gtype'] = "2";
		$comp = D("Member")->where($map)->select();
		if(!$comp) $this->error("�Բ�����û��Ȩ�ޣ�");
	}
	public function index(){
		$this->display("Public:theme");
	}
}
?>