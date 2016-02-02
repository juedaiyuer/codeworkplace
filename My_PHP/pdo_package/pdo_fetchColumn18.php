<?php
header('content-type:text/html;charset=utf-8'); 
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	$sql='SELECT username,password,email FROM user';
	$stmt=$pdo->query($sql);
	echo $stmt->fetchColumn(0),'<br/>';
	echo $stmt->fetchColumn(1),'<br/>';
	echo $stmt->fetchColumn(2);
}catch(PDOException $e){
	echo $e->getMessage();
}