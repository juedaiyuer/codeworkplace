<?php 
//通过参数形式连接数据库
try{
	$dsn='mysql:host=localhost;dbname=imooc';
	$username='root';
	$passwd='root';
	$pdo=new PDO($dsn, $username, $passwd);
	var_dump($pdo);
}catch(PDOException $e){
	echo $e->getMessage();
}