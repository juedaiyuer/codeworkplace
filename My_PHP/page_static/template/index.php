<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="description" content="首页" />
<title>首页</title>
<link type="text/css" rel="stylesheet" href="/public/css/global.css" />
<script src="/public/js/jquery-1.7.min.js"></script>
<!--[if lt IE 7]>
<script type="text/javascript" src="/public/js/unitpngfix.js"></script>
<![endif]-->
<script>
$(document).ready(function()
{ 
 $(".slvh").each(function(){ 
 var maxwidth=28; 
 if($(this).text().length>maxwidth){ 
 $(this).text($(this).text().substring(0,maxwidth)); 
 $(this).html($(this).html()+' ...'); 
 } }); });
 
$(document).ready(function()
{ 
 $(".ywzsdes").each(function(){ 
 var maxwidth=140; 
 if($(this).text().length>maxwidth){ 
 $(this).text($(this).text().substring(0,maxwidth)); 
 $(this).html($(this).html()+' ...'); 
 } }); }); 

// ajax请求热门排行数据
$.ajax({ 
	type : "GET",
	url: "http://static.com/api/ajax.php",
	dataType : "json",
	success: function(data){
		// 如果数据请求成功
		if(data.code = 200) {
			hotHtml(data.data);
		}
	}
});

// 填充数据到html节点中
var hotHtml = function (data) {
	var html = '';
	for(i=0; i<data.length; i++) {
		html += '<li><a href="#"><img src="'+data[i].image+'" alt="'+data[i].title+'" title="'+data[i].title+'" /></a> <a href="#"><h3 class="slvh">'+data[i].title+'</h3></a> </li>';
	}
	$("#hothtml").html(html);
}
</script>
</head>

<body>
<div class="headbg">
  <div class="header">
    <ul class="logareg">
      <li><a href="#">登录</a></li>
      <li class="lineli">|</li>
      <li><a href="#">注册</a></li>
    </ul>
    <div class="clear"></div>
    <img class="logo" src="/public/images/logo.png" alt="" title="" />
    <ul class="topnav">
      <li class="topseled"><a href="index.html">首页</a></li>
      <li><a href="List.html">业务展示</a></li>
      <li><a href="show.html">驾校服务</a></li>
      <li><a href="buy.html">我要买车</a></li>
      <li><a href="#">汽车美容</a></li>
    </ul>
    <div class="clear"></div>
  </div>
</div>
<div class="bannbg">
  <div class="banner">
    <div class="quicknav"> <span class="quktit">品牌快速导航</span>
      <div class="quklogo"> <a href="#"><img src="/public/images/b1.png" alt="" title="" /></a> <a href="#"><img src="/public/images/b2.png" alt="" title="" /></a> <a href="#"><img src="/public/images/b3.png" alt="" title="" /></a> <a href="#"><img src="/public/images/b4.png" alt="" title="" /></a> <a href="#"><img src="/public/images/b5.png" alt="" title="" /></a> <a href="#"><img src="/public/images/b6.png" alt="" title="" /></a> <a href="#"><img src="/public/images/b7.png" alt="" title="" /></a> </div>
      <span class="qukmore"><a href="#">MORE &gt;&gt;</a></span>
      <div class="clear"></div>
    </div>
    <div class="quilink"> <a class="a1" href="#"></a> <a class="a2" href="#"></a> <a class="a3" href="#"></a> </div>
    <div class="quilink_sec"> <a href="#"></a> </div>
  </div>
</div>
<div class="container">
  <div class="conlinone">
    <div class="zncompan">
      <h1>最新资讯</h1>
      <ul>
	  <?php foreach($newsList as $key => $news) {?>
        <li><a href="detail/<?php echo $news['id']?>.html"><?php echo $news['title']?></a></li>
	  <?php }?>
      </ul>
      <span class="qukmore_sec"><a href="#">More &gt;&gt;</a></span> </div>
    <div class="zncompan">
      <h1>二手车</h1>
      <ul>
        <li><a href="#">富安达运输有限公司</a></li>
        <li><a href="#">福特嘉年华两厢</a></li>
        <li><a href="#">广州星海益达运输有限责任公司</a></li>
        <li><a href="#">宝马530豪华配置带天窗530S宝马530豪华配置带天窗530S</a></li>
      </ul>
      <span class="qukmore_sec"><a href="#">More &gt;&gt;</a></span> </div>
    <div class="zncompan_thr">
      <h1>业务展示</h1>
      <div class="ywzs"> <img src="/public/images/abimg.jpg" alt="" title="" />
        <p class="ywzsdes">汽车服务网站平台提供各种汽车保养和维修套餐及服务网站汽车服务网站平台提供各种汽车保养和维修套餐及服务网站会员可通过平台定制自己需要的服务。同时，网站平台定期推出各种优惠活动，敬请广大用户关会员可通过平台定制自己需要的服务。同时，网站平台定期推出各种优惠活的服务。同时，网站平台定期推出各种优惠活动，敬请广大用户关注的服务。同时，网站平台定期推出各种优惠活动，敬请广大用户关注动，敬请广大用户关注</p>
        <span class="qukmore_sec"><a href="#">More &gt;&gt;</a></span> </div>
    </div>
    <div class="clear"></div>
  </div>
  <div class="copyrights">Collect from <a href="http://www.cssmoban.com/"  title="网站模板">网站模板</a></div>
  <div class="conlintwo">
    <div class="contwotit">
      <h3>热门排行 </h3>
    </div>
    <div class="contwonr" >
      <ul id="hothtml">
        <!--<li>
		  <a href="#"><img src="/public/images/pro1.jpg" alt="" title="" /></a> <a href="#">
          <h3 class="slvh">2013款正品美国龟牌极限镀膜蜡T-32 汽车蜡新车腊镀膜</h3>
          </a> 
		</li>-->
      </ul>
    </div>
  </div>
  <div class="conlinthre">
    <div class="friendlink">
      <ul>
        <li><a href="#"><img src="/public/images/fridlingk1.jpg" alt="" title="" />苏州新海宜通信科技</a></li>
        <li><a href="#"><img src="/public/images/fridlingk2.jpg" alt="" title="" />中大集团</a></li>
        <li><a href="#"><img src="/public/images/fridlingk3.jpg" alt="" title="" />壳牌喜力爱车保养中心</a></li>
      </ul>
      <span class="qukmore_four"><a href="#">MORE &gt;&gt;</a></span> </div>
  </div>
</div>
<div class="footbg">
  <div class="footer">
    <div class="foot_l">
      <div class="menu_foot">
        <p>关于我们</p>
        <ul>
          <li><a href="#">关于汽车服务</a></li>
          <li><a href="#">关于我们</a></li>
          <li><a href="#">平台介绍</a></li>
          <li><a href="#">平台宗旨</a></li>
        </ul>
      </div>
      <div class="menu_foot">
        <p>关于我们</p>
        <ul>
          <li><a href="#">关于汽车服务</a></li>
          <li><a href="#">关于我们</a></li>
          <li><a href="#">平台介绍</a></li>
          <li><a href="#">平台宗旨</a></li>
        </ul>
      </div>
      <div class="clear"></div>
      <div class="copyright">Copyright &copy; 2014.Company name All rights reserved.<a target="_blank" href="http://www.cssmoban.com/">&#x7F51;&#x9875;&#x6A21;&#x677F;</a> - More Templates <a href="http://www.cssmoban.com/" target="_blank" title="模板之家">模板之家</a> </div>
    </div>
    <div class="foot_r">
      <div class="title">关于我们</div>
      <div class="detail">汽车服务网站平台提供各种汽车保养和维修套餐及服务网站汽车服务网站平台提供各种汽车保养和维修套餐及服务网站会员可通过平台定制自己需要的服务。同时，网站平台定期推出各种优惠活动...</div>
    </div>
  </div>
</div>

</body>
</html>
