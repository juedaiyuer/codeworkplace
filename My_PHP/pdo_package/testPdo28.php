<?php 
header('content-type:text/html;charset=utf-8');
//1.通过PDO连接数据库
$pStartTime=microtime(true);
$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
$sql='INSERT test2 VALUES(:id)';
$stmt=$pdo->prepare($sql);
for($i=1;$i<=500;$i++){
	$id=1;
	$stmt->bindParam(':id', $id,PDO::PARAM_INT);
	$stmt->execute();
}
$pEndTime=microtime(true);
$res1=$pEndTime-$pStartTime;
unset($pdo);//$pdo=null;
//2.通过MySQL连接数据库
$mStartTime=microtime(true);
mysql_connect('localhost','root','root');
mysql_select_db('imooc');
for($i=1;$i<=500;$i++){
	$sql='INSERT test2 VALUES(2)';
	mysql_query($sql);
}
mysql_close();
$mEndTime=microtime(true);
$res2=$mEndTime-$mStartTime;
echo $res1,'<br/>',$res2;
echo '<hr/>';
if($res1>$res2){
	echo 'PDO插入500条记录的是MySQL'.round($res1/$res2).'倍';
}else{
	echo 'MySQL插入500条记录的是PDO的'.round($res2/$res1).'倍';
}


