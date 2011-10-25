<?php
class ToolboxAction extends BaseAction{
	function _initialize(){
		$map['uid'] = $_SESSION[C('USER_AUTH_KEY')];
		$map['gtype'] = "2";
		$comp = D("Member")->where($map)->select();
		if(!$comp) $this->error("对不起，您没有权限！");
	}
	public function index(){
		$this->display("Public:toolbox");
	}
	public function modify(){
		$userInfo = D("Member")->getByUid(Session::get(C('USER_AUTH_KEY')));
		$this->assign($userInfo);
		$this->assign("dsp","modify");
		$this->display("Public:tools");
	}
	public function modifys(){
		$data = $_POST;
		
		if($data['opassword'] && $data['uid']){
			$map['password'] = md5($data['opassword']);
			$map['uid'] = $data['uid'];
			$Member = D("Member");
			$checkuser = $Member->where($map)->count();
			if(!$checkuser){
				$this->assign("toolmsg","ture");
				$this->error("密码错误！");
			}elseif($data['npassword']){
				$data['password'] = md5($data['npassword']);
			}
			if($Member->save($data)){
				$this->assign("toolmsg","ture");
				$this->success("修改成功！");
			}else{
				$this->assign("toolmsg","ture");
				$this->error("资料无改变或修改失败！");		
			}
		}else{
			$this->assign("toolmsg","ture");
			$this->error("请输入当前密码！");	
		}
	}
	public function cache(){
		$this->assign("dsp","cache");
		$this->display("Public:tools");
	}
	public function clear(){
		$id = $_REQUEST['id'];
		$file['cache'] = array("Admin/Runtime/Cache","LiuCmsApp/Runtime/Cache");
		$file['data'] = array("Admin/Runtime/Data/_fields","LiuCmsApp/Runtime/Data/_fields");
		$file['temp'] = array("Admin/Runtime/Temp","LiuCmsApp/Runtime/Temp");
		$file['logs'] = array("Admin/Runtime/Logs","LiuCmsApp/Runtime/Logs");
		$file['runtime'] = array("Admin/Runtime/~runtime.php","LiuCmsApp/Runtime/~runtime.php");
		$file['app'] = array("Admin/Runtime/~app.php","LiuCmsApp/Runtime/~app.php");
		$dir = array();
		foreach($id as $key){
			$dir = array_merge($dir,$file[$key]);
		}
		foreach($dir as $key){
			$this->removeDir($key);
		}
		$this->assign("toolmsg","ture");
		$this->success("缓存已更新！");
	}
	function removeDir($dirName){ 
    	if(!is_dir($dirName)) return @unlink($dirName); 
    	$handle = @opendir($dirName); 
    	while(($file = @readdir($handle)) !== false){ 
        	if($file != '.' && $file != '..'){ 
            	$dir = $dirName . '/' . $file;
				is_dir($dir) ? removeDir($dir) : @unlink($dir);
        	} 
    	} 
    	closedir($handle); 
		return true;
	}
	public function slide(){
		$act = $_GET['act'];
		switch($act){
			case "add": 
				$this->assign("dsp","addslide");
				$this->display("Public:tools");
				break;
			case "edit":
				if(!$sid = $_GET['sid']) $this->error("数据丢失！");	
				$slide = D("Slide")->getBySid($sid);
				$this->assign($slide);
				$this->assign("dsp","editslide");
				$this->display("Public:tools");
				break;
			case "delete":
				$this->_batch("Slide");
				break;
			default:
				Load("extend");
				$slide = D("Slide")->order("sid desc")->select();
				$this->assign("slide",$slide);
				$this->assign("dsp","slide");
				$this->display("Public:tools");
		}
	}
	public function addslide(){
		$data = $_POST;
		$Slide = D("Slide");
		if(!empty($_FILES['attachment']['name'])){
			$data['attachment'] = $this->_upload("Slide",false,778,300,true);
		}else{
			$this->error("请选择需上传的图片！");
		}
		$data['postdate'] = time(); 
		if($Slide->Create()){
			if($Slide->add($data)){
				$this->assign("jumpUrl","__URL__/slide");
				$this->success("发布成功！");
			}else{
				$this->error("发布失败！");
			}
		}else{
			$this->error($Slide->getError());
		}
	}
	public function editslide(){
		$data = $_POST;
		if(!empty($_FILES['attachment']['name'])) $data['attachment'] = $this->_upload("Slide",false,778,300,true);
		$data['postdate'] = strtotime($_POST['postdate']);
		if(D("Slide")->save($data)){
			$this->success("修改成功！");
		}else{
			$this->error("资料无改变或修改失败！");		
		}
	}
	public function navigation(){
		$act = $_GET['act'];
		switch($act){
			case "add": 
				$Navigation = D("Navigation");
				if($Navigation->Create()){
					if($Navigation->add()){
						$this->success("发布成功！");
					}else{
						$this->error("发布失败！");
					}
				}else{
					$this->error($Navigation->getError());
				}
				break;
			case "edit":
				$data = $_POST;
				if(D("Navigation")->save($data)){
					$this->success("修改成功！");
				}else{
					$this->error("资料无改变或修改失败！");		
				}
				break;
			case "delete":
				$this->_batch("Navigation");
				break;
			default:
				$navigation = D("Navigation")->order("orders")->select();
				$this->assign("navigation",$navigation);
				$this->assign("dsp","navigation");
				$this->display("Public:tools");
		}
	}
}
?>