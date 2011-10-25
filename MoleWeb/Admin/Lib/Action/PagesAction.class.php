<?php
class PagesAction extends BaseAction{
	function _initialize(){
		$map['uid'] = $_SESSION[C('USER_AUTH_KEY')];
		$map['gtype'] = "2";
		$comp = D("Member")->where($map)->select();
		if(!$comp) $this->error("对不起，您没有权限！");
	}
	public function index(){
		$Pages = D("Pages");
		import("ORG.Util.Page");
		if($_POST['keyword']){
			$kmap = $_POST['keyword'];
			$map['title'] = array('like','%'.$kmap.'%');
		}elseif($_GET['keyword']){
			$kmap = $_GET['keyword'];
			$map['title'] = array('like','%'.$kmap.'%');
		}
		$count = $Pages->where($map)->count();
		$Page = new Page($count,20);
		$Page -> parameter .= "keyword=".urlencode($kmap)."&";
		$show = $Page->show();
		$pages = $Pages->where($map)->order('pgid desc')->limit($Page->firstRow.','.$Page->listRows)->select();
		$this->assign('pages',$show);
		$this->assign("pgs",$pages);
		$this->display("Public:pages");
	}
	public function add(){
		$this->assign('uid',Session::get(C('USER_AUTH_KEY')));
		$this->assign("dsp","add");
		$this->display("Public:pages");
	}
	public function adds(){
		$Pages = D("Pages");
		if($Pages->Create()){
			if($Pages->add()){
				$this->assign("jumpUrl","__URL__");
				$this->success("发布成功！");
			}else{
				$this->error("发布失败！");
			}
		}else{
			$this->error($Pages->getError());
		}
	}
	public function edit(){
		if($_GET['pgid']){
			$pgs = D("Pages")->getByPgid($_GET['pgid']);
			$this->assign($pgs);
			$this->assign("dsp","edit");
			$this->display("Public:pages");
		}else{
			$this->assign("jumpUrl","__URL__");
			$this->error("数据不存在！");
		}
	}
	public function edits(){
		$data = $_POST;
		$data['postdate'] = strtotime($_POST['postdate']);
		if(D("Pages")->save($data)){
			$this->success("修改成功！");
		}else{
			$this->error("资料无改变或修改失败！");		
		}
	}
	public function batch(){
		$this->_batch();
	} 
}
?>