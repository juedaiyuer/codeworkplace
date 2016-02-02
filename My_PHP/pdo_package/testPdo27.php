<?php 
header('content-type:text/html;charset=utf-8');
//1.通过PDO连接数据库
$pStartTime=microtime(true);
for($i=1;$i<=100;$i++){
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
}
$pEndTime=microtime(true);
$res1=$pEndTime-$pStartTime;

//2.通过MySQL连接数据库
$mStartTime=microtime(true);
for($i=1;$i<=100;$i++){
	mysql_connect('localhost','root','root');
	mysql_select_db('imooc');
}
$mEndTime=microtime(true);
$res2=$mEndTime-$mStartTime;
echo $res1,'<br/>',$res2;
echo '<hr/>';
if($res1>$res2){
	echo 'PDO连接数据库MySQL的'.round($res1/$res2).'倍';
}else{
	echo 'MySQL连接数据库PDO的'.round($res2/$res1).'倍';
}


