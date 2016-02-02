<?php 
header('content-type:text/html;charset=utf-8');
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	$sql='select * from user';
	$stmt=$pdo->prepare($sql);
	$res=$stmt->execute();
//	if($res){
//		while($row=$stmt->fetch(PDO::FETCH_OBJ)){
//			print_r($row);
//			echo '<hr/>';
//		}
//	}
//	$rows=$stmt->fetchAll(PDO::FETCH_ASSOC);
//	print_r($rows);
	echo '<hr/>';
	$stmt->setFetchMode(PDO::FETCH_ASSOC);	
	//var_dump($stmt);
	$rows=$stmt->fetchAll();
	print_r($rows);
}catch(PDOException $e){
	echo $e->getMessage();
}