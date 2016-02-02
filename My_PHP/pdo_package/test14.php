<?php 
header('content-type:text/html;charset=utf-8');
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');	
	$sql='DELETE FROM user WHERE id<:id';
	$stmt=$pdo->prepare($sql);
	$stmt->bindParam(":id",$id,PDO::PARAM_INT);
	$id=10;
	$stmt->execute();
	echo $stmt->rowCount();
}catch(PDOException $e){
	echo $e->getMessage();
}
