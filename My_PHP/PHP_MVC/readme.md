1.使用操作MySQL的方法仍然是mysql,方法比较古老.

2.insert函数
   
  正常的SQL插入语句
  
  INSERT INTO tb_name(字段1,字段2...) VALUES (value1,value2...)

  传递数组,key-value 形式避免插入SQL语句的出错

  
3.update函数

  正常的SQL更新语句
  
  UPDATE 表名 set 字段 = 字段值 where ...


4.工厂模式
  
  class factory{
    
    static function create($type){
      return new $type;
    }
  }

  $obj=factory::create('mysql');

  统一管理对象的实例化,便于扩展维护

  DB.class.php

  视图引擎的类封装 (VIEW.class.php)

  
5.微型框架
  1.函数库
  2.类库(a.视图引擎库  b.DB引擎库  c.核心库(工厂类))
  3.require文件清单
  4.启动引擎程序
  




