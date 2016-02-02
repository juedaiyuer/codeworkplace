<?php 
header('content-type:text/html;charset=utf-8');
try{
	$dsn='mysql:host=localhost;dbname=imooc';
	$username='root';
	$passwd='root';
	$pdo=new PDO($dsn, $username, $passwd);
	$attrArr=array(
		'AUTOCOMMIT','ERRMODE','CASE','PERSISTENT','TIMEOUT','ORACLE_NULLS',
			'SERVER_INFO','SERVER_VERSION','CLIENT_VERSION','CONNECTION_STATUS'
	);
	foreach($attrArr as $attr){
		echo "PDO::ATTR_$attr: ";
		echo $pdo->getAttribute(constant("PDO::ATTR_$attr")),'<br/>';
	}
}catch(PDOException $e){
	echo $e->getMessage();
}