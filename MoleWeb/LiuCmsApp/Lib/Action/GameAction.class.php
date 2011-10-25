<?php
class GameAction extends BaseAction{
	public function index(){
		$Game = D("Game");

		if($_GET['Id']){
			$cont = $Game->order('Id desc')->select();
			
			for($i = 0;$i < count($cont);$i++){
				if($cont[$i]['Id'] == $_GET['Id']){
					$show = $cont[$i]['content'];
				}
			}
		}else{
			$cont = $Game->order('Id desc')->select();
			
			if($cont){
				$show = $cont[0]['content'];;
			}
		}

		$this->assign('gameDec',$show);
		$this->assign("categroy",$cont);
		$this->assign("title","游戏介绍");
		$this->display("Public:game");
	}
}
?>