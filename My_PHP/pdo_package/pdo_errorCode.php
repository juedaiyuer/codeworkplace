<?php 
header('content-type:text/html;charset=utf-8');
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	$sql='delete from user12 where id=1';
	$res=$pdo->exec($sql);
	//echo $res.'条记录被影响';
	//var_dump($res);
	if($res===false){
		//$pdo->errorCode():SQLSTATE的值
		echo $pdo->errorCode();
		echo '<hr/>';
		//$pdo->errorInfo():返回的错误信息的数组，数组中包含3个单元
		//0=>SQLSTATE,1=>CODE,2=>INFO
		$errInfo=$pdo->errorInfo();
		print_r($errInfo);
	}
//	echo '<hr/>';
//	echo $pdo->lastInsertId();
}catch(PDOException $e){
	echo $e->getMessage();
}