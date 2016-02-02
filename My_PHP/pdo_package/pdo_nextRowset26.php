<?php 
try{
	$pdo=new PDO('mysql:host=localhost;dbname=imooc','root','root');
	$sql='call test1()';
	$stmt=$pdo->query($sql);
	$rowset=$stmt->fetchAll(PDO::FETCH_ASSOC);
	print_r($rowset);
	echo '<hr color="red"/>';
	$stmt->nextRowset();
	$rowset=$stmt->fetchAll(PDO::FETCH_ASSOC);
	print_r($rowset);
}catch(PDOException $e){
	echo $e->getMessage();
}
