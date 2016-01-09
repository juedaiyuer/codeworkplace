<?php
/**
* 利用PHP正则表达式来处理伪静态
* 以http://static.com/newsList.php?type=2&category_id=1 =>  http://static.com/newsList.php/2/1.shtml
*/
//echo 12;
var_dump($_SERVER);

if(isset($_SERVER['PATH_INFO'])) {
	// 解析 /2/1.shtml 匹配pathinfo值，如果没匹配到则数据不合法，若匹配到做相应处理
	if(preg_match("/^\/(\d+)\/(\d+)(\.shtml)$/", $_SERVER['PATH_INFO'], $pathInfo)) {
		//var_dump($pathInfo);
		$type = $pathInfo[1]; // 类型值
		$categoryId = $pathInfo[2]; // 所在栏目值
		// 引入数据库链接类
		require_once('./db.php'); 
		$sql = "select * from news where `category_id` = ".$categoryId." and `type` = ".$type." order by id desc";
		try{
			$db = Db::getInstance()->connect();
			$result = mysql_query($sql, $db);
			$newsList = array();
			while($row = mysql_fetch_assoc($result)) {
				$newsList[] = $row;
			}
			var_dump($newsList);
			exit;
		}catch(Exception $e) {
			// TODO
		}
	} else {
		// TODO
		die('url error!');
	}
} else {
	// TODO
	// 错误提示，然后跳转到首页处理
	die('地址有误');
}