<?php
class GameAction extends BaseAction{
	function _initialize(){
		$map['uid'] = $_SESSION[C('USER_AUTH_KEY')];
		$map['gtype'] = "2";
		$comp = D("Member")->where($map)->select();
		if(!$comp) $this->error("对不起，您没有权限！");
	}
	public function index(){
		$Game = D("Game");
		import("ORG.Util.Page");
		if($_POST['keyword']){
			$kmap = $_POST['keyword'];
			$map['name'] = array('like','%'.$kmap.'%');
		}elseif($_GET['keyword']){
			$kmap = $_GET['keyword'];
			$map['name'] = array('like','%'.$kmap.'%');
		}
		$count = $Game->where($map)->count();
		$Page = new Page($count,20);
		$Page -> parameter .= "keyword=".urlencode($kmap)."&";
		$show = $Page->show();
		$user = $Game->where($map)->order('Id desc')->limit($Page->firstRow.','.$Page->listRows)->select();
		$this->assign('pages',$show);
		$this->assign("user",$user);
		$this->display("Public:Game");
	}
	public function add(){
		$this->assign("dsp","add");
		$this->display("Public:Game");
	}
	public function adds(){
		$Game = D("Game");
		if($Game->Create()){
			if($Game->add()){
				$this->assign("jumpUrl","__URL__/index");
				$this->success("添加成功！");
			}else{
				$this->error("添加失败！");
			}
		}else{
			$this->error($Game->getError());
		}
	}
	public function edit(){
		if($_GET['Id']){
			$userInfo = D("Game")->getById($_GET['Id']);
			$this->assign($userInfo);
			$this->assign("dsp","edit");
			$this->display("Public:Game");	
		}else{
			$this->assign("jumpUrl","__URL__");
			$this->error("数据不存在！");
		}
	}
	public function edits(){
		$data = $_POST;
		if(D("Game")->save($data)){
			$this->assign("jumpUrl","__URL__/index");
			$this->success("修改成功！");
		}else{
			$this->error("修改失败！");
		}
	}	
	public function batch(){
		$this->_batch();
	}
}
?>