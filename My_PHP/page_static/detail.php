<?php
/**
 * 处理cms详情页业务逻辑
*/
//header("content-type:text/htm;charset=utf-8");
// 引入数据库链接操作
require_once('./db.php');
$id = isset($_GET['id']) ? intval($_GET['id']) : 0;
$id = max(0, $id);
if(!$id) {
	// TODO
	// 信息提示  跳转到首页等操作
	return require_once('./index.html');
}

/* 一、 smarty中存在缓存技术 1、缓存，它是临时性的 2、页面静态化是永久性的
 * 
 * 二、引入smarty基本
 * 
 * require_once('./smarty/libs/Smarty.class.php');
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

require_once './smarty/libs/Smarty.class.php';
$smarty = new Smarty();
$smarty->template_dir = "./template"; //设置模板目录
$smarty->compile_dir = "./template_c"; //设置编译目录
$smarty->cache_dir = "./smarty_cache"; //缓存文件夹
$sql = "select * from news where `id` = " . $id . " and `status` = 1";
try{
	$db = Db::getInstance()->connect();
	$result = mysql_query($sql, $db);
	$new = mysql_fetch_assoc($result);
}catch(Exception $e) {
	// TODO
}
$smarty->assign('new', $new);
$contect = $smarty->fetch("detail.html");
file_put_contents('detail/'.$id.'.html', $contect);

