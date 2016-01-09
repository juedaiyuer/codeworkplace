<?php
/**
 * 视图层 
*/


//  以下为测试版本，录制视频的时候会找个好看的模版页面
?>
<html>
<!--引入js-->
<script type="text/javascript" src="http://static.com/demo4/public/js/jquery.js"></script>
<body>
id:<?php echo $new['id']?><br />
标题:<?php echo $new['title']?><br />
<img src="<?php echo $new['image']?>"/><br />
<?php echo $new['description'];?>
<!--以下内容为ajax获取动态数据-->
<div id="ajax">
热门排行:
</div>
<!--ajax获取动态数据-->
</body>

</html>
<script>
$.ajax({ 
	type : "GET",
	url: "http://static.com/demo4/api/ajax.php",
	dataType : "json",
	success: function(data){
		alert(data.message);
	}
});
</script>
