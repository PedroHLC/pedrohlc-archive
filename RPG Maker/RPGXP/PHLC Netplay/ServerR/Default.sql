/*
Navicat MySQL Data Transfer

Source Server         : PedroHLC
Source Server Version : 50153
Source Host           : localhost:3306
Source Database       : phlcnetplay

Target Server Type    : MYSQL
Target Server Version : 50153
File Encoding         : 65001

Date: 2011-01-02 13:28:18
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `users`
-- ----------------------------
DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `id` int(255) NOT NULL AUTO_INCREMENT,
  `login` varchar(255) NOT NULL,
  `pass` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL DEFAULT 'noemail',
  `type` int(11) NOT NULL DEFAULT '0',
  `genre` int(11) NOT NULL DEFAULT '0',
  `loggedin` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of users
-- ----------------------------
