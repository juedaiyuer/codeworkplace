<?php
/**
 * 生成接口数据，提供ajax获取内容
 * 获取排行榜内容
*/
// 引入链接数据库操作文件
require_once('../db.php');
// 引入生成接口数据文件
require_once('../response.php');
class Ajax {

	/**
	* 获取热门排行
	*/
	public static function hot() {
		try {
			// 根据内容id获取排行语句
			$sql = "select * from hit order by count desc limit 6";
			$connect = Db::getInstance()->connect();
			$hitSelect = mysql_query($sql, $connect);
			$hitIds = $newsMap = array();
			while($row = mysql_fetch_assoc($hitSelect)) {
				$hitIds[] = $row['news_id'];
			}
			
			$newsSql = "select * from news where id in (" . implode(',',$hitIds) .") and image != ''"; 
			$newsSelect = mysql_query($newsSql, $connect);
			$newsList = array();
			while($row = mysql_fetch_assoc($newsSelect)) {
				$newsList[$row['id']] = $row;
			}
			// 组装新数据
			foreach($hitIds as $hitId) {
				if(!isset($newsList[$hitId])) {
					continue;
				}
				$newsMap[] = $newsList[$hitId];
			}
			//var_dump($newsMap);exit;
			
		} catch(Exception $e) {
			return Response::show(400, '数据获取有误');
		}
		
		if($newsMap) {
			return Response::show(200, '热门排行数据返回成功', $newsMap);
		} else {
			return Response::show(200, '数据返回成功', $newsMap);
		}
		
	}
}
Ajax::hot();
