<?php 
header('content-type:text/html;charset=utf-8');
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');	
	$sql="INSERT user(username,password,email) VALUES(:username,:password,:email)";
	$stmt=$pdo->prepare($sql);	
	$stmt->bindParam(":username",$username,PDO::PARAM_STR);
	$stmt->bindParam(":password",$password,PDO::PARAM_STR);
	$stmt->bindParam(":email",$email);
	$username='imooc1';
	$password='imooc1';
	$email='imooc1@imooc.com';
	$stmt->execute();
	$username='MR.KING1';
	$password='MR.KING1';
	$email='MR.KING1@imooc.com';
	$stmt->execute();
	echo $stmt->rowCount();
}catch(PDOException $e){
	echo $e->getMessage();
}
