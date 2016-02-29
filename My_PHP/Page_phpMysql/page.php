<html>
<head>
        <meta http-equiv="Content-type" content="text/html";charset=utf-8>
</head>
<style>
	body{
		font-size:12px;FONT-FAMILY:verdana;width:100%;
	}	

	div.page{
		text-align:center;
	}

	div.content{
		height:350px;
	}

        div.page a{
                <!--去掉标签的下划线 -->
                border:#aaaadd 1px solid;text-decoration:none;padding:2px 5px;margin:2px;
        }

        div.page span.current{
                border:#000099 1px solid;background-color:#000099;padding:4px 6px;margin:2px;color:#fff;
		font-weight:bold;
        }

	div.page span.disable{
		border:#eee 1px solid;padding:2px 5px;margin:2px;color:#ddd;
	}

	div.page form{
		display:inline;
	}
</style>

<body>
<?php
header("Content-type:text/html;charset=utf-8");
/**
1.传入页码
2.根据页码取出数据:php->mysql
3.显示数据+分页条
*/

//数据库的配置需要根据实际情况定义
$page = $_GET['p'];
$host = "localhost";
$username = "root";
$password = "";
$db = "info";
$pageSize = 10;

//显示页码配置
$showPage = 5;

$con = mysql_connect($host,$username,$password);
if(!$con) {
	echo "database connect not success";
	exit;
}else{
echo "数据库连接成功";
echo "<br />";
mysql_select_db($db);
mysql_query("SET NAMES UTF8");

/**
$sql = "SELECT * FROM user";
$result = mysql_query($sql);
if($result){
	while($row = mysql_fetch_assoc($result)){
		print_r($row);
	}
}

*/

//获取分页数据,SELECT * FROM tb_name LIMIT  start_pos  show_number

$num = ($page-1)*10;
$sql = "SELECT * FROM user LIMIT {$num},{$pageSize}";
//echo $sql;
$result = mysql_query($sql);

//处理我们的数据
echo "<div class='content'>";
echo "<table border=1 cellspacing=0 width=40% align=center>";
echo "<tr><td>ID</td><td>username</td></tr>";

while($row = mysql_fetch_assoc($result)){
//输出内容测试代码
//	echo $row['id'].'-'.$row['username'].'<br />';
	echo "<tr>";
	echo "<td>{$row['id']}</td>";
	echo "<td>{$row['username']}</td>";
	echo "</tr>";
}

echo "</table>";
echo "</div>";

}

//释放结果,关闭连接
mysql_free_result($result);

//获取数据总数
$total_num_sql = "SELECT COUNT(*) FROM user ";
$total_num_result = mysql_fetch_array(mysql_query($total_num_sql));
$total = $total_num_result[0];

//显示数据总数的测试代码
//echo $total;

//计算页数
$total_pages = ceil($total/$pageSize);

mysql_close($con);

//显示数据+分页条,div前端美化
$page_banner = "<div class='page'>";

//计算偏移量,显示页码功能设定
$pageoffset = ($showPage-1)/2;


if($page>1){
	$page_banner.= "<a href='".$_SERVER['PHP_SELF']."?p=1 '>首页</a>";
	$page_banner.= "<a href='".$_SERVER['PHP_SELF']."?p=".($page-1). "'><上一页</a>";
}else{
	$page_banner.="<span class='disable'>首页</a></span>";
	$page_banner.="<span class='disable'><上一页</a></span>";
}

$start = 1;
$end = $total_pages;
//总页数大于显示设定页数
if($total_pages>$showPage){
        if($page>$pageoffset+1){
                $page_banner .= "...";
        }
	if($page>$pageoffset){
		$start = $page-$pageoffset;
		$end = $total_pages>$page+$pageoffset?$page+$pageoffset:$total_pages;
	}else{
	//当前页为1,2的情景
		$start = 1;
		$end = $total_pages>$showPage?$showPage:$total_pages;
	}
	if($page+$pageoffset>$total_pages){
	//最后2页的显示处理
		$start = $start-($page+$pageoffset-$end);
	}
}

for($i=$start;$i<=$end;$i++){
	if($page == $i){
	//增加选中样式
		$page_banner.="<span class='current'>{$i}</span>";
	}else{
        	$page_banner.= "<a href='".$_SERVER['PHP_SELF']."?p=".$i. "'>{$i}</a>";
	}	
}

//尾部省略
if($total_pages>$showPage&&$total_pages>$page+$pageoffset){
	$page_banner .= "...";
}


if($page<$total_pages){
	$page_banner.= "<a href='".$_SERVER['PHP_SELF']."?p=".($page+1). "'>下一页></a>";
	$page_banner.= "<a href='".$_SERVER['PHP_SELF']."?p=".($total_pages). "'>尾页</a>";
}else{
	$page_banner.="<span class='disable'>下一页></a></span>";
        $page_banner.="<span class='disable'>尾页</a></span>";
}
$page_banner.= "共{$total_pages}页,";
$page_banner.="<form action='page.php'>";
$page_banner.="到第<input type='text' size='2' name='p'>页";
$page_banner.="<input type='submit' value='确定'>";
$page_banner.="</form></div>";
echo $page_banner;








?>
</body>
</html>
	
