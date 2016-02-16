<?php 
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	//exec():执行一条sql语句并返回其受影响的记录的条数,如果没有受影响的记录，他返回0
	//exec对于select没有作用
	$sql=<<<EOF
		CREATE TABLE IF NOT EXISTS user(
		id INT UNSIGNED AUTO_INCREMENT KEY,
		username VARCHAR(20) NOT NULL UNIQUE,
		password CHAR(32) NOT NULL,
		email VARCHAR(30) NOT NULL
		);
EOF;
	$res=$pdo->exec($sql);
	var_dump($res);	
	$sql='INSERT user(username,password,email) VALUES("king","'.md5('king').'","imooc@qq.com")';
	//echo $sql;
	$res=$pdo->exec($sql); //返回受影响的条数
	echo $res;
}catch(PDOException $e){
	echo $e->getMessage();
}
