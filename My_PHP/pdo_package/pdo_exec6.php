<?php 
header('content-type:text/html;charset=utf-8');
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	//$sql='update user set username="king" where id=1';
	//$sql='delete from user12 where id=1';
	$sql='select * from user';
	$res=$pdo->exec($sql);
	//echo $res.'条记录被影响';
	var_dump($res);
//	echo '<hr/>';
//	echo $pdo->lastInsertId();
}catch(PDOException $e){
	echo $e->getMessage();
}