<?php
header('content-type:text/html;charset=utf-8'); 
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	$sql='SELECT username,password,email FROM user';
	$stmt=$pdo->prepare($sql);
	$stmt->execute();
	echo '结果集中的列数一共有：'.$stmt->columnCount();
	echo '<hr/>';
	print_r($stmt->getColumnMeta(0));
	echo '<hr/>';
	$stmt->bindColumn(1, $username);
	$stmt->bindColumn(2,$password);
	$stmt->bindColumn(3, $email);
	while($stmt->fetch(PDO::FETCH_BOUND)){
		echo '用户名：'.$username.'-密码：'.$password.'-邮箱：'.$email.'<hr/>';
	}
}catch(PDOException $e){
	echo $e->getMessage();
}