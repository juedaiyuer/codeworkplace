<?php
/**
* 数据库链接封装
*/
class Db {
	// 存储类的实例的静态成员变量
	static private $_instance;
	// 数据库链接静态变量
	static private $_connectSource;
	// 链接数据库配置
	private $_dbConfig = array(
		'host' => '127.0.0.1',
		'user' => 'root',
		'password' => '',
		'database' => 'cms',
	);

	private function __construct() {
	}
	
	/**
	 * 实例化
	*/
	static public function getInstance() {
		// 判断是否被实例化
		// 访问实例的公共的静态方法
		if(!(self::$_instance instanceof self)) {
		//本类的属性$_instance是否是本类的实例
		//self指的是本类
			self::$_instance = new self();
		}
		return self::$_instance;
	}

	/**
	* 数据库链接
	*/
	public function connect() {
		if(!self::$_connectSource) {
			// 数据库链接
			self::$_connectSource = @mysql_connect($this->_dbConfig['host'], $this->_dbConfig['user'], $this->_dbConfig['password']);	
			//@符号为阻止警告输出

			if(!self::$_connectSource) {
				// 抛出异常处理
				throw new Exception('mysql connect error ');
			}
			// 选择一款数据库
			mysql_select_db($this->_dbConfig['database'], self::$_connectSource);
			// 设置字符编码
			mysql_query("set names UTF8", self::$_connectSource);
		}
		// 返回资源链接
		return self::$_connectSource;
	}
	
}

//test
/**
$connect = Db::getInstance()->connect();

$sql = "select * from 表名";
$result = mysql_query($sql,$connect);
echo mysql_num_rows($result);
var_dump($result);
*/
