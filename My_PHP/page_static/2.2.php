<?php
// 打开输出控制缓冲 
ob_start();
echo 1;
// 获取缓冲区中的内容
$str = ob_get_contents();
// 将缓冲区中的内容写入文件
// 主要是为了让学员看看是否能获取到缓冲区中的内容 ,目前缓冲区数据为1
file_put_contents('cache/1.txt', $str); // 查看文件中是否存在1

// 清空（擦掉）输出缓冲区
// ob_clean();
// 当使用了ob_clean函数之后浏览器就不会输出1了，但如果我们 echo $str依然可以输出1的内容
// 也就是说缓冲区的内容并没有完全清空。
echo $str; // 1
ob_end_clean(); // 函数会销毁输出缓冲区 ， 那么所有的内容都不会输出，这里主要是为了让学员明白ob_clean和ob_end_clean函数之间的区别


echo '测试ob_get_clean函数功能';
// 我们再来看看下述函数ob_get_clean
$str2 = ob_get_clean(); // 这个函数作用：ob_get_contents 和 ob_end_clean组合功能
echo $str2;
file_put_contents('cache/2.txt', $str2);

// 最后讲解下ob_get_flush函数功能



/**
 * 总结PHP如何生成页面静态化
*/
// 利用PHP内置的OB函数以及结合PHP内置file_put_contents函数来处理页面静态化操作
// OB是操作缓冲区的 file_put_contents是用来处理讲内容写入文件的   


// 以上两个原理大家一定要清楚和明白，这样才有利于我们的学习






