<?php 
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	$sql='INSERT user(username,password,email) VALUES(:username,:password,:email)';
	$stmt=$pdo->prepare($sql);
	$username='imooc_king22';
	$password='imooc_king22';
	$stmt->bindValue(':username',$username);
	$stmt->bindValue(':password',$password);
	$stmt->bindValue(':email','king@imooc.com');
	$stmt->execute();
	echo $stmt->rowCount();
	$username='imooc_king33';
	$password='imooc_king33';
	$stmt->bindValue(':username',$username);
	$stmt->bindValue(':password',$password);
	$stmt->bindValue(':email','king33@imooc.com');
	$stmt->execute();
	echo $stmt->rowCount();
}catch(PDOException $e){
	echo $e->getMessage();
}