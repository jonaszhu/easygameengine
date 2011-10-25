<?php
class ProductsAction extends BaseAction{
	public function _empty(){
		$pid = $_GET['pid'];
		if(!$pid){
			if($_GET['cid']) $map['cid'] = $_GET['cid'];
			import("ORG.Util.Page");
			$Products = D("Products");
			$Categroy = D("Categroy");
			$count = $Products->count();
			$Page = new Page($count,12);
			$show = $Page->show();
			$products = $Products->where($map)->order('pid desc')->limit($Page->firstRow.','.$Page->listRows)->select();
			$categroy = $Categroy->select();
			$this->assign('pages',$show);
			$this->assign("products",$products);
			$this->assign("categroy",$categroy);
			$this->assign("title","产品展示");
		}else{
			$this->view($pid);
			$this->assign("dsp","view");
		}
		$this->display("Public:products");
	}
	protected function view($pid){
		$products = D("Products")->getByPid($pid);
		if($products['parameters']){
			$parameters = explode('<br />',$products['parameters']);
			$this->assign("par",$parameters);//使用volist标签 name="parameters"时不能正常输出 
		}
		$this->assign($products);
	}
}
?>