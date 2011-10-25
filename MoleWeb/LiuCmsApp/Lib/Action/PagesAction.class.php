<?php
class PagesAction extends BaseAction{
	public function _empty(){
		$pgid = $_GET['pgid'];
		if(!$pgid) $pgid = 1;
		$pages = D("Pages")->getByPgid($pgid);
		$this->assign($pages);
		$this->display("Public:pages");
	}
}
?>