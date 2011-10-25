<?php
class MemberAction extends BaseAction{
	public function index(){
		Load('extend');
		
		$this->assign("title","用户管理");
		
		// 如果用户已经登录成功的话，直接转到用户管理界面
		if(Session::is_set(C('USER_AUTH_KEY'))){
			$this->assign("dsp","change");
			$uid = Session::get(C('USER_AUTH_KEY'));
			$userInfo = D("Member")->getByUid($uid);
			$GameData = D("Userdata")->getByUserid($uid);
			$this->assign($userInfo);		
			$this->assign($GameData);		
			$this->display("Public:Member");
		}
		else{
			$this->display("Public:Member");
		}
	}
	public function userinfo(){
		if(Session::is_set(C('USER_AUTH_KEY'))){
			$this->assign("dsp","change");
			$uid = Session::get(C('USER_AUTH_KEY'));
			$userInfo = D("Member")->getByUid($uid);
			$GameData = D("Userdata")->getByUserid($uid);
			$this->assign($userInfo);		
			$this->assign($GameData);		
			$this->display("Public:Member");
		}
	}
	public function changeinfo(){
		if(Session::is_set(C('USER_AUTH_KEY'))){	
			$this->assign("dsp","change");
			$this->assign("dspT","change");
			$uid = Session::get(C('USER_AUTH_KEY'));
			$userInfo = D("Member")->getByUid($uid);
			$GameData = D("Userdata")->getByUserid($uid);
			$this->assign($userInfo);
			$this->assign($GameData);
			$this->display("Public:Member");
		}
	}	
	public function changed(){
		if(Session::is_set(C('USER_AUTH_KEY'))){
			$map['uid'] = Session::get(C('USER_AUTH_KEY'));
			$data['homeplace'] = $_POST['homeplace'];
			$data['telephone'] = $_POST['telephone'];
			$data['QQ'] = $_POST['QQ'];
			D("Member")->where('uid='.$map["uid"])->data($data)->save();
			
			$mapU['UserId'] = $map['uid'];
			$dataU['UserAvatar'] = $_POST['UserAvatar'];
			D("Userdata")->where('UserId='.$mapU['UserId'])->data($dataU)->save();
				
			$this->assign("jumpUrl","__URL__/index");
			$this->success("资料修改成功！");
		}
	}
	public function changepass(){
		if(Session::is_set(C('USER_AUTH_KEY'))){	
			$this->assign("dsp","change");
			$this->assign("dspT","changepass");
			$this->display("Public:Member");
		}
	}
	public function changepassd(){
		if(Session::is_set(C('USER_AUTH_KEY'))){
			// 如果密码输入为空
			if(!$_POST['password'] || !$_POST['passwordagain']){
				$this->error("密码输入不能为空，请重新输入！");
				return;
			}
			
			// 如果两次密码输入不相同
			if($_POST['password'] != $_POST['passwordagain']){
				$this->error("两次密码输入不相同，请重新输入密码！");
				return;
			}
			
			$map['uid'] = Session::get(C('USER_AUTH_KEY'));
			$data['password'] = md5($_POST['password']);
			if(D("Member")->where('uid'.$map['uid'])->data($data)->save()){
				$this->assign("jumpUrl","__URL__");						
				$this->success("密码修改成功！");
			}else{
				$this->error("密码修改失败！");
			}			
		}
	}
	public function adds(){
		// 如果两次密码输入不相同
		if($_POST['password'] != $_POST['passwordagain']){
			$this->error("两次密码输入不相同，请重新输入密码！");
			return;
		}

		// 如果用户没有同意游戏协议
		if(!$_POST['protocol'])
		{
			$this->error("对不起，您好像没有同意我们的软件使用协议吧！");
			return;
		}
		
		$Member = D("Member");
		if($Member->Create()){
			$Member->password = md5($_POST['password']);
			$Member->gtype = 0;
			$mId = $Member->add();
			if($mId){
				// 如果用户注册成功，为用户初始化用户数据
				$Userdata = D("Userdata");
				
				if($Userdata->Create()){
					$Userdata->UserId = $mId;
					$Userdata->UserAvatar = $_POST['avatar'];
					if($Userdata->add()){						
						$this->assign("jumpUrl","__URL__");						
						$this->success("添加成功！");
					}else{
					   $this->error("添加失败！");
					}
				}else{
					$this->error("添加失败！");
				}
			}else{
				$this->error("添加失败！");
			}
		}else{
			$this->error($Member->getError());
		}
	}	
	public function logins(){
		if($_SESSION['verify']!=md5($_POST['verify'])){
			$this->error('验证码错误！');
		}else{
			$Member = D("Member");
			$map['username'] = $_POST['username'];
			$map['password'] = md5($_POST['password']);
			$checkUser = $Member->where($map)->find();
			if(!$checkUser){
				$this->assign("jumpUrl","__URL__");
				$this->error("用户名或密码不正确!");
			}else{
				Session::set(C('USER_AUTH_KEY'),$checkUser['uid']);
				$Member->where("uid = ".$checkUser['uid'])->setField("lastlogintime",time());
				$this->assign("jumpUrl","__URL__");
				$this->success("登陆成功！");
			}
		}
	}
	public function reg(){
		$this->assign("dsp","register");
		$this->display("Public:Member");
	}
	public function verify(){ 
		$type = isset($_GET['type'])?$_GET['type']:'gif'; 
        import("ORG.Util.Image"); 
        Image::buildImageVerify(4,1,$type,'','20px'); 
    }	
	public function logout(){
		if(Session::is_set(C('USER_AUTH_KEY'))){
			Session::clear();
			$this->assign('jumpUrl',__URL__.'/index');
			$this->success("注销成功！");
		}else{
			$this->assign('jumpUrl',__URL__.'/index');
			$this->error('已经注销！');
		}
		$this->forward();
	}	
}
?>