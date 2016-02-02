<?php 
header('content-type:text/html;charset=utf-8');
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	//$sql='select * from user where id=2';
	$sql='select id,username,email from user';
	//$pdo->query($sql)，执行SQL语句，返回PDOStatement对象
	$stmt=$pdo->query($sql);
	var_dump($stmt);
	echo '<hr/>';
	foreach($stmt as $row){
		//print_r($row);
		echo '编号：'.$row['id'],'<br/>';
		echo '用户名：'.$row['password'],'<br/>';
		echo '邮箱：'.$row['email'],'<br/>';
		echo '<hr/>';
	}
}catch(PDOException $e){
	echo $e->getMessage();
}