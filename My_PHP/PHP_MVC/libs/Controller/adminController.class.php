<?php
	class adminController{

		public $auth;

		public function __construct(){
			session_start();
			if(!(isset($_SESSION['auth']))&&(PC::$method!='login')){
				$this->showmessage('请登录后在操作！', 'admin.php?controller=admin&method=login');
			}else{
				$this->auth = isset($_SESSION['auth'])?$_SESSION['auth']:array();
			}
		}

		public function index(){
			$newsobj = M('news');
			$newsnum = $newsobj->count();
			VIEW::assign(array('newsnum'=>$newsnum));
			VIEW::display('admin/index.html');
		}
		public function login(){
			if(!isset($_POST['submit'])){
				VIEW::display('admin/login.html');
			}else{
				$this->checklogin();
			}
		}

		public function logout(){
			unset($_SESSION['auth']);
				$this->showmessage('退出成功！', 'admin.php?controller=admin&method=login');
		}

		public function newsadd(){
			if(!isset($_POST['submit'])){
				$data = $this->getnewsinfo();
				VIEW::assign(array('data'=>$data));
				VIEW::display('admin/newsadd.html');
			}else{
				$this->newssubmit();
			}
		}

		public function newslist(){
			$data = $this->getnewslist();
			VIEW::assign(array('data'=>$data));
			VIEW::display('admin/newslist.html');
		}

		public function newsdel(){
			if($_GET['id']){
				$this->delnews();
				$this->showmessage('删除新闻成功！', 'admin.php?controller=admin&method=newslist');
			}
		}

		private function checklogin(){
			if(empty($_POST['username'])||empty($_POST['password'])){
				$this->showmessage('登录失败！', 'admin.php?controller=admin&method=login');
			}
			$username = daddslashes($_POST['username']);
			$password = daddslashes($_POST['password']);
			$authobj = M('auth');
			if($auth = $authobj->checkauth($username, $password)){
				$_SESSION['auth'] = $auth;
				$this->showmessage('登录成功！', 'admin.php?controller=admin&method=index');
			}else{
				$this->showmessage('登录失败！', 'admin.php?controller=admin&method=login');
			}
		}

		private function getnewsinfo(){
			if(isset($_GET['id'])){
				$id = intval($_GET['id']);
				$newsobj = M('news');
				return $newsobj->findOne_by_id($id);
			}else{
				return array();
			}
		}

		private function getnewslist(){
			$newsobj = M('news');
			return $newsobj->findAll_orderby_dateline();
		}

		private function delnews(){
			$newsobj = M('news');
			return $newsobj->del_by_id($_GET['id']);
		}

		private function newssubmit(){
			extract($_POST);				
			if(empty($title)||empty($content)){
				$this->showmessage('请把新闻标题、内容填写完整再提交！', 'admin.php?controller=admin&method=newsadd');
			}
			$title = daddslashes($title);
			$content = daddslashes($content);
			$author = daddslashes($author);
			$from = daddslashes($from);
			$newsobj = M('news');
			$data = array(
				'title'=>$title,
				'content'=>$content,
				'author'=>$author,
				'from'=>$from,
				'dateline'=>time()
			);
			if($_POST['id']!=''){
				$newsobj ->update($data, intval($_POST['id']));
				$this->showmessage('修改成功！', 'admin.php?controller=admin&method=newslist');
			}else{
				$newsobj ->insert($data);
				$this->showmessage('添加成功！', 'admin.php?controller=admin&method=newslist');
			}
		}

		private function showmessage($info, $url){
			echo "<script>alert('$info');window.location.href='$url'</script>";
			exit;
		}
	}
?>