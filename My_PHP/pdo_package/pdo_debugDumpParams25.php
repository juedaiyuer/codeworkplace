<?php 
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	$sql='SELECT * FROM user WHERE username=:username AND password=:password';
	$stmt=$pdo->prepare($sql);
	$stmt->bindParam(':username', $username,PDO::PARAM_STR);
	$stmt->bindParam(':password',$password,PDO::PARAM_STR);
	$username='testParam';
	$password='testParam';
	$stmt->execute();
	$stmt->debugDumpParams();
}catch(PDOException $e){
	echo $e->getMessage();
}
