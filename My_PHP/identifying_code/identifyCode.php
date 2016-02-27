<?php
/**
1. imagecolorallocate为一幅图像分配颜色,通用方法
2. imagestring — 水平地画一行字符串
3. imagesetpixel — 画一个单一像素,增加点元素的干扰
4.imageline — 画一条线段,增加线元素的干扰
*/
	session_start();  //必须位于脚本的顶部

	$image =  imagecreatetruecolor(100, 30);
	$bgcolor = imagecolorallocate($image, 255, 255, 255);
	imagefill($image, 0, 0, $bgcolor);

	$captch_code = '';

/**
// 实现了简单的四位数字验证码功能
	for ($i=0; $i <4 ; $i++) { 
		$fontsize = 6;
		$fontcolor = imagecolorallocate($image, rand(0,120), rand(0,120), rand(0,120));
		$fontcontent = rand(0,9);

		$captch_code.=$fontcontent;

		$x = ($i*100/4) + rand(5,10);
		$y = rand(5,10);

		imagestring($image, $fontsize, $x, $y, $fontcontent, $fontcolor);
	}
*/

	for ($i=0; $i <4 ; $i++) { 
		$fontsize = 6;
		$fontcolor = imagecolorallocate($image, rand(0,120), rand(0,120), rand(0,120));

		$data = 'abcdefghigklmnopqrstuvwxyz123456789';
		$fontcontent = substr($data, rand(0,strlen($data)),1);

		$captch_code.=$fontcontent;

		$x = ($i*100/4) + rand(5,10);
		$y = rand(5,10);

		imagestring($image, $fontsize, $x, $y, $fontcontent, $fontcolor);
	}

	$_SESSION['authcode'] = $captch_code;

	for($i=0;$i<200;$i++){
		$pointcolor = imagecolorallocate($image, rand(50,200), rand(50,200), rand(50,200));
		imagesetpixel($image, rand(1,99), rand(1,29), $pointcolor);

	}

	for ($i=0; $i <3 ; $i++) { 
		$linecolor = imagecolorallocate($image, rand(80,220), rand(80,220), rand(80,220));
		imageline($image, rand(1,99), rand(1,29), rand(1,99), rand(1,29), $linecolor);
	}

header('content-type:image/png');
imagepng($image);
imagedestroy($image);
?>