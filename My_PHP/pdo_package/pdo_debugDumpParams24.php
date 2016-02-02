<?php 

try{
	
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	$sql='INSERT user(username,password,email) VALUES(?,?,?)';
	$stmt=$pdo->prepare($sql);
	$stmt->bindParam(1, $username,PDO::PARAM_STR);
	$stmt->bindParam(2,$password,PDO::PARAM_STR);
	$stmt->bindParam(3,$email,PDO::PARAM_STR);
	$username='testParam';
	$password='testParam';
	$email='testParam@imooc.com';
	$stmt->execute();
	$stmt->debugDumpParams();
}catch(PDOException $e){
	echo $e->getMessage();
}
