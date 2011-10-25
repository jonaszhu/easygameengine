<?php
class RanklistAction extends BaseAction{
	public function index(){
		Load('extend');
		import("ORG.Util.Page");
		
		$Userdata = D("Userdata");
		
		$count = $Userdata->count();
		$Page = new Page($count,20);
		$show = $Page->show();
		$user = $Userdata->order('Money desc')->limit($Page->firstRow.','.$Page->listRows)->select();
		
		for($i = 0;$i < count($user);$i++){
			$user[$i]['rank'] = $i+1;
			
			$Member = D("Member");
			$mdata = $Member->getByuid($user[$i]['UserId']);
			$user[$i]['rname'] = $mdata['username'];
		}
		
		$this->assign('pages',$show);
		$this->assign("rlist",$user);	
		$this->assign("title","玩家排行");		
        $this->display("Public:Ranklist");
	}
}
?>