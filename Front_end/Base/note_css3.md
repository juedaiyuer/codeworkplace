#CSS个人笔记#

1. src [十天精通CSS3](http://www.imooc.com/learn/33)


##圆角效果##
1.背景图片,元素拼凑  
2.border-radius(css3效果)  

	border-radius:10px //所有角都使用半径为10px的圆角
	border-radius:5px 4px 3px 2px;//左上角,右上角,右下角,左下角
*实心圆*
	div{
		height:100px;/*与width设置一致*/
		width:100px;
		background:#9da;
		border-radius:50px;/*四个圆角值都设置为宽度或高度值的一半*/
		} 
*实心上半圆*
	div{
		height:50px;/*是width的一半*/
		width:100px;
		background:#9da;
		border-radius:50px 50px 0 0;/*半径至少设置为height的值*/
		}	

##阴影##

box-shadow: X轴偏移量 Y轴偏移量 [阴影模糊半径] [阴影扩展半径] [阴影颜色] [投影方式];  
阴影模糊半径：此参数可选，其值只能是为正值，如果其值为0时，表示阴影不具有模糊效果，其值越大阴影的边缘就越模糊  
阴影扩展半径：此参数可选，其值可以是正负值，如果值为正，则整个阴影都延展扩大，反之值为负值时，则缩小  
inset 参数设置内部阴影  

*边框应用图片*
	border-image:url() (切割图片的宽度) (round,repeat,stretch)

##RGBA##
rgba(r,g,b,透明度);  

##渐变##
*渐变类型*
linear(线性渐变) radial(径向渐变)

linear-gradient
渐变类型 (渐变方向,颜色值(start),...,颜色值(end))

[CSS3 经典教程系列：CSS3 线性渐变（linear-gradient）](http://www.cnblogs.com/lhb25/archive/2013/01/30/css3-linear-gradient.html)

##文字和字体##

*文本溢出的表现*
	//省略标记效果
	text-overflow:ellipsis; 
	overflow:hidden;//溢出效果隐藏 
	white-space:nowrap; //强制文本在一行内显示

	word-wrap:normal|break-word //表示控制连续文本换行,表示内容将在边界内换行,属性不常用,浏览器默认值即可

**嵌入字体**

	@font-face {
		font-family : 字体名称;
		src : 字体文件在服务器上的相对或绝对路径;
	}

**文本阴影**

	text-shadow: X-Offset Y-Offset blur color;

##背景样式##
	/**
	1.元素背景图片的原始起始位置
	2.如果背景不是no-repeat,这个属性无效	
	*/
	background-origin ： border-box | padding-box | content-box;

	//适当裁剪
	background-clip ： border-box | padding-box | content-box | no-clip
	
	//背景图片大小
	background-size: auto | <长度值> | <百分比> | cover | contain

##CSS选择器##
**结构性伪选择器**
1. 根选择器 :root
2. 否定选择器 :not
3. :empty 没有内容的元素
4. #(url):target
5. :first-child父元素的第一个子元素   
   :last-child   
	ul>li:last-child{background:blue}  
   :nth-child(){}  
   :nth-last-child(){} 最后的子元素算起  
   :first-of-type() 定位父元素下的某类型的第一个子元素 :last-of-type()  
   :nth-of-type(n) :nth-last-of-type(n)  
   :only-child()  
   :only-of-type()  
6. :enabled选择器 可用选择器 :disabled选择器  
   :checked 选中状态  
   ::selection 用来匹配突出显示的文本(鼠标选择的文本)  
   Firefox增加前缀 -moz-  
   :read-only 指定处于只读状态的元素,该元素要设置readonly='readonly'  
   :read-write 

##旋转##

1. rotate() 旋转
2. skew() 扭曲
3. scale() 缩放
4. translate() 位移
5.  matrix() 
6.  transfrom-origin() 定位图形的原点
7. transition 过渡属性
8. keyframes 关键帧
   animation-name属性 调用@keyframes定义好的动画  
   animation-duration 动画持续时间  
   animation-timing-function 动画播放方式  
   animation-delay 设置动画开始播放的时间  
   animation-iteration-count 定义动画播放的次数 infinite 无限次播放  
   animation-direction 动画播放方向 normal向前播放 alternate 偶次向前,奇次向反  
   animation-play-state 控制元素动画的播放状态 running paused  
   animation-fill-mode 设置动画时间外属性  

##布局样式##

>CSS Multi Column Layout Module
1. columns: col_width col_num 多列布局
2. column-width:auto | length
3. column-count:auto | num
4. column-gap:normal | length  normal(font-size 默认是1em,间隔就是font-size的数值)
5. column-rule,边框宽度,边框样式,边框颜色   
   边框样式:none、hidden、dotted、dashed、solid、double、groove、ridge、inset、outset  
6. box-sizing:content-box | border-box | inherit  
   
**伸缩布局(CSS3新特性)**
1. 创建一个flex容器
	.flexcontainer{ display: -webkit-flex; display: flex; }
2. Flex项目列显示
	.flexcontainer{ display: -webkit-flex; display: flex; -webkit-flex-direction: column; flex-direction: column; }


##媒体类型##
>解决不同终端显示问题
>CSS3的Media Queries模块让一个页面适应不同的终端(或屏幕尺寸)

1. 最大宽度 max-width
2. 最小宽度 min-width
3. 设备屏幕的输出宽度 Device Width

**Responsive**

1. 自动缩放属性 resize
2. 外轮廓属性 outline





