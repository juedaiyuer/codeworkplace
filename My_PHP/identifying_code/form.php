<?php
	header("Content-type:text/html;charset=utf-8");
	if(isset($_REQUEST['authcode'])){
		session_start();

		if (strtolower($_REQUEST['authcode']) == $_SESSION['authcode']) {
			echo '<font color="#0000CC">输入正确</font>';
		}else{
			echo '<font color="#CC0000"><b>输入错误</b></font>';
		}
	}
	exit();
?>

<!DOCTYPE html>
	<html>
		<head>
			<meta charset = 'utf-8' />
			<title>确认验证码</title>
		</head>
		<body>
			<form method = "POST" action =./form.php>
				<p>验证码图片:<img border = "1" src = "./identifyCode.php?r=<?php echo rand();?>" width ="100" height= "30" /></p>
				<p>请输入图片上的内容:<input type = "text" name = "authcode" value = "" /> </p>
				<p><input type = "submit"  value = "提交" style = "padding:6px 20px;"></p>
			</form>	
		</body>
	</html>