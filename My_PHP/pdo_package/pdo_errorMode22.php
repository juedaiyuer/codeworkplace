<?php 
/*
 PDO::ERRMODE_SLIENT:默认模式，静默模式
 PDO::ERRMODE_WARNING:警告模式
 PDO::ERRMODE_EXCEPTION:异常模式
 */
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$sql='SELECT * FROM noneTable';
	$pdo->query($sql);
	echo $pdo->errorCode();
	echo '<br/>';
	print_r($pdo->errorInfo());
}catch(PDOException $e){
	echo $e->getMessage();
}