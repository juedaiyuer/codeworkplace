<?php 
header('content-type:text/html;charset=utf-8');
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	//exec():执行一条sql语句并返回其受影响的记录的条数,如果没有受影响的记录，他返回0
	//exec对于select没有作用
//	$sql=<<<EOF
//	INSERT user(username,password,email) VALUES("king1","king1","imooc1@qq.com"),
//	("king2","king2","imooc1@qq.com"),
//	("king3","king2","imooc1@qq.com")
//	
//EOF;
	//echo $sql;
	$sql='INSERT user(username,password,email) VALUES("king6","king6","imooc6@qq.com")';
	$res=$pdo->exec($sql);
	echo '受影响的记录的条数为：'.$res,'<br/>';
	//$pdo->lastInsertId():得到新插入记录的ID号
	echo '最后插入的ID号为'.$pdo->lastInsertId();
}catch(PDOException $e){
	echo $e->getMessage();
}