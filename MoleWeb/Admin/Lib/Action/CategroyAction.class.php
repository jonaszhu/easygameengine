<?php
class CategroyAction extends BaseAction{
	function _initialize(){
		$map['uid'] = $_SESSION[C('USER_AUTH_KEY')];
		$map['gtype'] = "2";
		$comp = D("Member")->where($map)->select();
		if(!$comp) $this->error("对不起，您没有权限！");
	}
	public function index(){
		$Categroy = D("Categroy");
		import("ORG.Util.Page");
		if($_POST['keyword']){
			$kmap = $_POST['keyword'];
			$map['name'] = array('like','%'.$kmap.'%');
		}elseif($_GET['keyword']){
			$kmap = $_GET['keyword'];
			$map['name'] = array('like','%'.$kmap.'%');
		}
		$count = $Categroy->where($map)->count();
		$Page = new Page($count,20);
		$Page -> parameter .= "keyword=".urlencode($kmap)."&";
		$show = $Page->show();
		$cats = $Categroy->where($map)->order("cid desc")->limit($Page->firstRow.','.$Page->listRows)->select();
		$this->assign('pages',$show);
		$this->assign('cats',$cats);
		$this->display("Public:categroy");
	}
	public function add(){
		$this->assign("dsp","add");
		$this->display("Public:categroy");
	}
	public function adds(){
		$Categroy = D("Categroy");
		if($Categroy->Create()){
			if($Categroy->add()){
				$this->assign("jumpUrl","__URL__");
				$this->success("添加成功！");
			}else{
				$this->error("添加失败！");
			}
		}else{
			$this->error($Categroy->getError());
		}
	}
	public function edit(){
		if($_GET['cid']){
			$cats = D("Categroy")->getByCid($_GET['cid']);
			$this->assign($cats);
			$this->assign("dsp","edit");
			$this->display("Public:categroy");	
		}else{
			$this->assign("jumpUrl","__URL__");
			$this->error("数据不存在！");
		}
	}
	public function edits(){
		$data = $_POST;
		if(D("Categroy")->save($data)){
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
