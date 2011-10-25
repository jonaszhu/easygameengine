<?php
class IndexAction extends BaseAction{
    public function index(){
		Load('extend');
		$this->slide();
        $this->display("Public:index");
    }
	protected function slide(){
		$slide = D("Slide")->select();
		$this->assign("slide",$slide);
	}
}
?>