CREATE TABLE IF NOT EXISTS userAccount(
id TINYINT UNSIGNED AUTO_INCREMENT KEY,
username VARCHAR(20) NOT NULL UNIQUE,
money DECIMAL(10,2)
)ENGINE=INNODB;

INSERT userAccount(username,money) VALUES('imooc',10000),('king',5000);

DELIMITER //
CREATE PROCEDURE test1()
BEGIN
	SELECT * FROM user;
	SELECT * FROM userAccount;
END 
//
DELIMITER ;

CREATE TABLE test2(

);


