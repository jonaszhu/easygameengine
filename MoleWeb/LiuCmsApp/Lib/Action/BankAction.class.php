<?php
class BankAction extends BaseAction{
	public function index(){
		Load('extend');		
		$this->assign("title","用户充值");
		$this->display("Public:Bank");
	}
}
?>