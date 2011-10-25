<?php
class MessageAction extends BaseAction{
	function _initialize(){
		$map['uid'] = $_SESSION[C('USER_AUTH_KEY')];
		$map['gtype'] = "2";
		$comp = D("Member")->where($map)->select();
		if(!$comp) $this->error("对不起，您没有权限！");
	}
	public function index(){
		$message = D("Message")->order("mid desc")->select();
		$this->assign("message",$message);
		$this->display("Public:message");
	}
	public function view(){
		if(!$_GET['mid']){
			$this->assign("jumpUrl","__URL__");
			$this->error("数据不存在！");
		}
		$message = D("Message")->getByMid($_GET['mid']);
		$this->assign($message);
		$this->assign("dsp","view");
		$this->display("Public:message");
	}
	public function reply(){
		$data = $_POST;
		$data['postdate'] = strtotime($_POST['postdate']);
		$data['replydate'] = strtotime($_POST['replydate']);
		if(D("Message")->save($data)){
			$this->success("回复或修改成功！");
		}else{
			$this->error("留言无改变或回复失败！");		
		}
	}
	public function batch(){
		$this->_batch();
	} 
}
?>