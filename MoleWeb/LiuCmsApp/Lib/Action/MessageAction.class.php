<?php
class MessageAction extends BaseAction{
	public function _empty(){
		$Message = D("Message");
		import("ORG.Util.Page");
		$count = $Message->count();
		$Page = new Page($count,10);
		$show = $Page->show();
		$message = D("Message")->order("postdate desc")->limit($Page->firstRow.','.$Page->listRows)->select();
		$this->assign('pages',$show);
		$this->assign("message",$message);
		$this->assign("title","客服中心");
		$this->display("Public:message");
	}
	public function submitmsg(){
		Load('extend');
		if($_SESSION['verify']!=md5($_POST['verify'])){
			$this->error('验证码错误！');
		}elseif(strlen_utf8($_POST['content']) > 200 || strlen_utf8($_POST['content']) < 10){
			$this->error("留言内容不能少于10字，不能超过200字！");
		}else{
			$data = $_POST;
			$Message = D("Message");
			$data['clientip'] = get_client_ip();
			$data['postdate'] = time();
			if($Message->Create()){
				if($Message->add($data)){
					$this->assign("jumpUrl","__URL__");
					$this->success("留言成功！");
				}else{
					$this->error("留言失败！");
				}
			}else{
				$this->error($Message->getError());
			}
		}
	}
}
?>