<?php 
header('content-type:text/html;charset=utf-8');
try{
	$dsn='mysql:host=localhost;dbname=imooc';
	$username='root';
	$passwd='root';
	$options=array(PDO::ATTR_AUTOCOMMIT,0);
	$pdo=new PDO($dsn, $username, $passwd, $options);
	var_dump($pdo->inTransaction());
	//开启事务
	$pdo->beginTransaction();
	var_dump($pdo->inTransaction());
	//$sql='UPDATE userAccount SET money=money-2000 WHERE username="imooc"';
	$sql='UPDATE userAccount SET money=money-2000 WHERE username="imooc"';
	
	$res1=$pdo->exec($sql);
	if($res1==0){
		throw new PDOException('imooc 转账失败');
	}
	$res2=$pdo->exec('UPDATE userAccount SET money=money+2000 WHERE username="king1"');
	if($res2==0){
		throw new PDOException('king 接收失败');
	}
	//提交事务
	$pdo->commit();
}catch(PDOException $e){
	//回滚事务
	$pdo->rollBack();
	echo $e->getMessage();
}