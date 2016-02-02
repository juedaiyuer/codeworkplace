<?php 
//通过uri的形式连接数据库
try{
	$dsn='uri:file://G:\phpdev\apache\htdocs\imooc\pdo\dsn.txt';
	$username='root';
	$passwd='root';
	$pdo=new PDO($dsn,$username,$passwd);
	var_dump($pdo);
}catch(PDOException $e){
	echo $e->getMessage();
}