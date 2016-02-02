<?php 
try{
	$dsn='imooc';
	$username='root';
	$passwd='root';
	$pdo=new PDO($dsn,$username,$passwd);
	var_dump($pdo);
}catch(PDOException $e){
	echo $e->getMessage();
}