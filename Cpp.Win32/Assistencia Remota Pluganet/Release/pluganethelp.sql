/*
MySQL Data Transfer
Source Host: localhost
Source Database: pluganethelp
Target Host: localhost
Target Database: pluganethelp
Date: 15/04/2012 10:53:13
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for users
-- ----------------------------
CREATE TABLE `users` (
  `login_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `login_name` varchar(12) COLLATE utf8_bin NOT NULL DEFAULT '',
  `type` tinyint(1) NOT NULL DEFAULT '0',
  `login_pass` varchar(256) COLLATE utf8_bin NOT NULL,
  `email` varchar(60) COLLATE utf8_bin DEFAULT NULL,
  `name` varchar(60) COLLATE utf8_bin NOT NULL DEFAULT '<AUTO>',
  `zip` varchar(8) COLLATE utf8_bin DEFAULT NULL,
  `tickets` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`login_id`,`login_name`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `users` VALUES ('1', 'tdesker', '9', '59f2443a4317918ce29ad28a14e1bdb7', 'bot@pluganet.net', 'Deskhelper test account', null, '0');
INSERT INTO `users` VALUES ('2', 'tclient', '0', '59f2443a4317918ce29ad28a14e1bdb7', 'bot@pluganet.net', 'Client test account', null, '999');
INSERT INTO `users` VALUES ('3', 'tpobre', '0', '59f2443a4317918ce29ad28a14e1bdb7', 'bot@pluganet.net', 'Pobre test account', null, '0');
