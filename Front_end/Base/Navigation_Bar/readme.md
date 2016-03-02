1.菜单的构成(无序列表)  
<ul>
<li><a href="#"></a></li>
<li><a href="#"></a></li>
<li><a href="#"></a></li>
<li><a href="#"></a></li>
...
</ul>

2.Vertical_menu 垂直菜单  

3.水平菜单  
  float:left  

4.菜单外观  
通过设置背景,改变外观样式  
通过a:hover,可以为菜单增加交互效果  

如果要给水平菜单增加整体背景，需要进行哪些CSS设置  
菜单<li>浮动后，<li>脱离文档流，导致<ul>将失去高度和宽度；如果需要对<ul>进行整体背景设置，首先要给<ul>定义宽、高  

垂直拉伸效果:  
vertical_stretch_menu  
背景图片沿y轴向上移动30px（水平方向不动）  
background-position:0 -30px;  

伸缩菜单的制作  
高度向上延伸的效果 margin-top:-10px  
水平变化  

