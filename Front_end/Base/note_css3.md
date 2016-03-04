#CSS个人笔记#
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

渐变类型 (渐变方向,颜色值(start),...,颜色值(end))

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


