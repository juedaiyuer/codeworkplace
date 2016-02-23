1.实际应用的时候，注意文件的权限问题，可能会造成上传失败
move_upload_file(file,newloc)
newloc设定的文件权限

2.path路径的设置

3.singleFileUp文件
  简单的单文件上传代码
 
  doAction.php
  了解了文件上传变量的概念 $_FILES

  比如上传一个图片,打印出来的变量$_FILES是这样的数据

  Array
(
    [myFile] => Array
        (
            [name] => nv.jpg
            [type] => image/jpeg
            [tmp_name] => /tmp/phpFseWLo
            [error] => 0
            [size] => 176943
        )

)


  这里采用了将二维数组转化成一维数组的简化过程

  $fileInfo = $_FILES('myFile')

  测试未成功,原因既然是exit没有注释掉 @@
 
  
  doAction1.php 
  单文件上传,上传同一文件,重名文件覆盖问题
  
  doAction2.php 单文件上传,增加了文件命名功能
  
  采用函数
  md5(uniqid(microtime(true),true))
  
4.单文件函数的封装
  singleFileUp_Function

  函数功能:
  1.目标文件夹不存在,建立文件夹,存储目标文件
  
5.多文件上传函数的封装
  multiFileUp1
  返回的是二维数组,file1,file2...形式

  譬如上传了4个文件,$_FILES接收到的信息如下:

  Array
(
    [myFile1] => Array
        (
            [name] => 2.jpg
            [type] => image/jpeg
            [tmp_name] => /tmp/phpTuoGAU
            [error] => 0
            [size] => 356176
        )

    [myFile2] => Array
        (
            [name] => nv.jpg
            [type] => image/jpeg
            [tmp_name] => /tmp/phpBLeCOg
            [error] => 0
            [size] => 176943
        )

    [myFile3] => Array
        (
            [name] => 2.jpg
            [type] => image/jpeg
            [tmp_name] => /tmp/php1c0B2C
            [error] => 0
            [size] => 356176
        )

    [myFile4] => Array
        (
            [name] => c3f9e551f8908f07b7842f9a1102c4e7.jpg
            [type] => image/jpeg
            [tmp_name] => /tmp/phppBbHgZ
            [error] => 0
            [size] => 26798
        )

)
  
  当上传文件含有非法文件的时候,立即退出执行,仅保留之前运行的数据
  因为函数封装,检查到了错误信息之后,break,exit
  
    
  multiFileUp2
  
  upload2前端代码采用了html5的形式,可以在一个input中选多个文件
  
  input的name形式为myFile[]
  按照类型组合的形式
  
  多文件的$_FILES
  Array
(
    [myFile] => Array
        (
            [name] => Array
                (
                    [0] => nv.jpg
                    [1] => nv.jpg
                    [2] => c3f9e551f8908f07b7842f9a1102c4e7.jpg
                    [3] => nv.jpg
                )

            [type] => Array
                (
                    [0] => image/jpeg
                    [1] => image/jpeg
                    [2] => image/jpeg
                    [3] => image/jpeg
                )

            [tmp_name] => Array
                (
                    [0] => /tmp/phpW4eaBW
                    [1] => /tmp/php2anfU8
                    [2] => /tmp/phpd2todl
                    [3] => /tmp/phpvNtywx
                )

            [error] => Array
                (
                    [0] => 0
                    [1] => 0
                    [2] => 0
                    [3] => 0
                )

            [size] => Array
                (
                    [0] => 176943
                    [1] => 176943
                    [2] => 26798
                    [3] => 176943
                )

        )

) 

  getFiles函数得到多文件的信息

  Array
(
    [0] => Array
        (
            [name] => 2.jpg
            [type] => image/jpeg
            [tmp_name] => /tmp/phpzZXPPU
            [error] => 0
            [size] => 356176
        )

    [1] => Array
        (
            [name] => nv.jpg
            [type] => image/jpeg
            [tmp_name] => /tmp/phpuCYHU2
            [error] => 0
            [size] => 176943
        )

    [2] => Array
        (
            [name] => nv.jpg
            [type] => image/jpeg
            [tmp_name] => /tmp/phpRm4FZa
            [error] => 0
            [size] => 176943
        )

    [3] => Array
        (
            [name] => c3f9e551f8908f07b7842f9a1102c4e7.jpg
            [type] => image/jpeg
            [tmp_name] => /tmp/phpNY2H4i
            [error] => 0
            [size] => 26798
        )

)

  错误信息采用了数组res['mes']的形式输出,不再是一有错误就break,exit的形式来处理
  res['dest'] 输出文件路径和文件名
  array_filter($uploadFiles) 可以过滤掉空值
  array_values() 数组重新赋值

  但是上面的过滤空值,可以返回给用户第几个文件的信息吗?

6.面向对象的封装
  
  OOP 面向对象的方法
  



  
