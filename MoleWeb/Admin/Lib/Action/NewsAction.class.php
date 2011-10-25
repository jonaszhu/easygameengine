<?php
class NewsAction extends BaseAction{
	function _initialize(){
		$map['uid'] = $_SESSION[C('USER_AUTH_KEY')];
		$map['gtype'] = "2";
		$comp = D("Member")->where($map)->select();
		if(!$comp) $this->error("对不起，您没有权限！");
	}
	public function index(){
		$News = D("News");
		import("ORG.Util.Page");
		if($_POST['keyword']){
			$kmap = $_POST['keyword'];
			$map['title'] = array('like','%'.$kmap.'%');
		}elseif($_GET['keyword']){
			$kmap = $_GET['keyword'];
			$map['title'] = array('like','%'.$kmap.'%');
		}
		$count = $News->where($map)->count();
		$Page = new Page($count,20);
		$Page -> parameter .= "keyword=".urlencode($kmap)."&";
		$show = $Page->show();
		$news = $News->where($map)->order('nid desc')->limit($Page->firstRow.','.$Page->listRows)->select();
		$this->assign('pages',$show);
		$this->assign("news",$news);
		$this->display("Public:news");
	}
	public function add(){
		$this->assign('uid',Session::get(C('USER_AUTH_KEY')));
		$this->assign("dsp","add");
		$this->display("Public:news");
	}
	public function adds(){
		$News = D("News");
		if($News->Create()){
			if($News->add()){
				$this->assign("jumpUrl","__URL__");
				$this->success("发布成功！");
			}else{
				$this->error("发布失败！");
			}
		}else{
			$this->error($News->getError());
		}
	}
	public function edit(){
		if($_GET['nid']){
			$news = D("News")->getByNid($_GET['nid']);
			$this->assign($news);
			$this->assign("dsp","edit");
			$this->display("Public:news");
		}else{
			$this->assign("jumpUrl","__URL__");
			$this->error("数据不存在！");
		}
	}
	public function edits(){
		$data = $_POST;
		$data['postdate'] = strtotime($_POST['postdate']);
		if(D("News")->save($data)){
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
