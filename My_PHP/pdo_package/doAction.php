<?php 
header('content-type:text/html;charset=utf-8');
$username=$_POST['username'];
$password=$_POST['password'];
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');	
	//echo $pdo->quote($username);
	//$sql="select * from user where username='{$username}' and password='{$password}'";
	//echo $sql;
	//通过quote():返回带引号的字符串，过滤字符串中的特殊字符,特殊字符反斜线引入
	$username=$pdo->quote($username);
	$sql="select * from user where username={$username} and password='{$password}'";
	echo $sql;
	$stmt=$pdo->query($sql);
	//PDOStatement对象的方法：rouCount()：对于select操作返回的结果集中记录的条数，
	//对于INSERT、UPDATE、DELETE返回受影响的记录的条数
	echo $stmt->rowCount();
}catch(PDOException $e){
	echo $e->getMessage();
}
