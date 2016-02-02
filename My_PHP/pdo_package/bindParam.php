<?php 
function bindParam(&$sql,$location,$var,$type){
	switch($type){
		case 'STRING':
			$var=addslashes($var);
			$var="'".$var."'";
			break;
		case 'INT':
		case 'INTEGER':
			$var=intval($var);
			break;
		case 'BOOL':
			$var=boolval($var);
			break;
	}
	for($i=1,$pos=0;$i<=$location;$i++){
		$pos=strpos($sql,' ?',$pos+1);
	}
	
}
$uid=10086;
$psw='pwfdsd';
$sql="select * from table where uid= ? and password= ?";
bindParam($sql, 1, $uid, 'INT');
bindParam($sql,2,$psw,'STRING');
echo $sql;