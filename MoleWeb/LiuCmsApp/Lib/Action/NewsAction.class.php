<?php
class NewsAction extends BaseAction{
	public function _empty(){
		$nid = $_GET['nid'];
		if(!$nid){
			import("ORG.Util.Page");
			$News = D("News");
			$count = $News->count();
			$Page = new Page($count,20);
			$show = $Page->show();
			$news = $News->order('nid desc')->limit($Page->firstRow.','.$Page->listRows)->select();
			$this->assign('pages',$show);
			$this->assign("title","新闻中心");
			$this->assign("news",$news);
		}else{
			$this->view($nid);
			$this->assign("dsp","view");
		}
		$this->display("Public:news");
	}
	protected function view($nid){
		$news = D("News")->getByNid($nid);
		$this->assign($news);
	}
}
?>