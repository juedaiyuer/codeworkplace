<?php 
header('content-type:text/html;charset=utf-8');
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	$sql='INSERT user(username,password,email) VALUES("king11","'.md5('king11').'","imooc11@qq.com")';
	$stmt=$pdo->query($sql);
	var_dump($stmt);
}catch(PDOException $e){
	echo $e->getMessage();
}