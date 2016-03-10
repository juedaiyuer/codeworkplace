#电商数据库#

分类表cate,真实开发为无限级分类  

CREATE DATABASE IF NOT EXISTS `shopImooc`;
USE `shopImooc`;

##管理员表##

    CREATE TABLE `imooc_admin` (
      `id` tinyint(3) unsigned NOT NULL AUTO_INCREMENT KEY,
      `username` varchar(20) NOT NULL UNIQUE,
      `password` char(32) NOT NULL,
      `email` varchar(50) NOT NULL
 
    );

##分类表##

    DROP TABLE IF EXISTS `imooc_cate`;

    CREATE TABLE `imooc_cate` (
      `id` smallint(5) unsigned NOT NULL AUTO_INCREMENT KEY,
      `cName` varchar(50) DEFAULT NULL UNIQUE
    );

##商品表##

    DROP TABLE IF EXISTS `imooc_pro`;

    CREATE TABLE `imooc_pro` (
      `id` int(10) unsigned NOT NULL AUTO_INCREMENT KEY,
      `pName` varchar(255) NOT NULL UNIQUE,
      `pSn` varchar(50) NOT NULL,
      `pNum` int(10) unsigned DEFAULT '1',
      `mPrice` decimal(10,2) NOT NULL,
      `iPrice` decimal(10,2) NOT NULL,
      `pDesc` text,
      `pubTime` int(10) unsigned NOT NULL,
      `isShow` tinyint(1) DEFAULT '1',
      `isHot` tinyint(1) DEFAULT '0',
      `cId` smallint(5) unsigned NOT NULL
    );

##用户表##

	DROP TABLE IF EXISTS `imooc_user`;

	CREATE TABLE `imooc_user` (
	  `id` int(10) unsigned NOT NULL AUTO_INCREMENT KEY,
	  `username` varchar(20) NOT NULL UNIQUE,
	  `password` char(32) NOT NULL,
	  `sex` enum('男','女','保密') NOT NULL DEFAULT '保密',
	  `email` varchar(50) NOT NULL,
	  `face` varchar(50) NOT NULL,
	  `regTime` int(10) unsigned NOT NULL,
	  `activeFlag` tinyint(1) DEFAULT '0'
	);

##相册表##

	DROP TABLE IF EXISTS `imooc_album`;

	CREATE TABLE `imooc_album` (
	  `id` int(10) unsigned NOT NULL AUTO_INCREMENT KEY,
	  `pid` int(10) unsigned NOT NULL,
	  `albumPath` varchar(50) NOT NULL
	);











