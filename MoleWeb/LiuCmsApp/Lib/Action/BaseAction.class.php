<?php
class BaseAction extends Action{
	function _initialize(){
		$sinfo = D("Options")->findall();
		foreach($sinfo as $key){
			$this->assign($key['types'],$key['values']);
		}
		$navigation = D("Navigation")->order("orders")->select();
		$this->assign("navigation",$navigation);
	}
	public function verify(){ 
		$type = isset($_GET['type'])?$_GET['type']:'gif'; 
        import("ORG.Util.Image"); 
        Image::buildImageVerify(4,1,$type,'','24px'); 
    }
}
?>