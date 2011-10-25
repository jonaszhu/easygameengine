<?php
class RoomAction extends BaseAction{
	function _initialize(){
		$map['uid'] = $_SESSION[C('USER_AUTH_KEY')];
		$map['gtype'] = "2";
		$comp = D("Member")->where($map)->select();
		if(!$comp) $this->error("对不起，您没有权限！");
	}
	public function index(){
		$Room = D("Room");
		import("ORG.Util.Page");
		if($_POST['keyword']){
			$kmap = $_POST['keyword'];
			$map['name'] = array('like','%'.$kmap.'%');
		}elseif($_GET['keyword']){
			$kmap = $_GET['keyword'];
			$map['name'] = array('like','%'.$kmap.'%');
		}
		$count = $Room->where($map)->count();
		$Page = new Page($count,20);
		$Page -> parameter .= "keyword=".urlencode($kmap)."&";
		$show = $Page->show();
		$user = $Room->where($map)->order('Id desc')->limit($Page->firstRow.','.$Page->listRows)->select();
		
		for($i = 0;$i < count($user);$i++)
		{
			$comp = D("Game")->getById($user[$i]['gameId']);	
			$user[$i]['gametype'] = $comp['name'];
		}		
		
		$this->assign('pages',$show);
		$this->assign("user",$user);
		$this->display("Public:room");
	}
	public function add(){
		$game = D("Game")->order('Id desc')->select();

		$this->assign("rtype",$game);		
		$this->assign("dsp","add");
		$this->display("Public:room");
	}	
	public function adds(){
		$Room = D("Room");
		if($Room->Create()){
			if($Room->add()){
				$this->assign("jumpUrl","__URL__/index");
				$this->success("添加成功！");
			}else{
				$this->error("添加失败！");
			}
		}else{
			$this->error($Room->getError());
		}
	}	
	public function edit(){
		if($_GET['Id']){
			$userInfo = D("Room")->getById($_GET['Id']);
			$game = D("Game")->order('Id desc')->select();

			$this->assign("rtype",$game);				
			$this->assign($userInfo);
			$this->assign("dsp","edit");
			$this->display("Public:Room");	
		}else{
			$this->assign("jumpUrl","__URL__");
			$this->error("数据不存在！");
		}
	}	
	public function edits(){
		$data = $_POST;
		if(D("Room")->save($data)){
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