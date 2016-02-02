<?php 
header('content-type:text/html;charset=utf-8');
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	$sql='select * from user where username="king11"';
	//prepare($sql):准备SQL语句
	$stmt=$pdo->prepare($sql);
	//execute():执行预处理语句
	$res=$stmt->execute();
	//var_dump($res);
	//fetch():得到结果集中的一条记录
	$row=$stmt->fetch();
	print_r($row);
	
	//var_dump($stmt);
}catch(PDOException $e){
	echo $e->getMessage();
}