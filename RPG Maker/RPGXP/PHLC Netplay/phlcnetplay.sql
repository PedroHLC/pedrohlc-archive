/*
MySQL Data Transfer
Source Host: localhost
Source Database: phlcnetplay
Target Host: localhost
Target Database: phlcnetplay
Date: 12/02/2011 11:52:03
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for chars
-- ----------------------------
CREATE TABLE `chars` (
  `id` int(255) NOT NULL AUTO_INCREMENT,
  `acc_char_id` int(11) NOT NULL DEFAULT '0',
  `owner` varchar(255) NOT NULL,
  `nick` varchar(255) NOT NULL,
  `class_id` int(11) NOT NULL DEFAULT '0',
  `exp` int(255) NOT NULL DEFAULT '0',
  `maxhp` int(255) NOT NULL DEFAULT '0',
  `maxmp` int(255) NOT NULL DEFAULT '0',
  `status_id` int(11) NOT NULL DEFAULT '0',
  `map_x` int(255) NOT NULL DEFAULT '0',
  `map_y` int(255) NOT NULL DEFAULT '0',
  `map_id` int(255) NOT NULL DEFAULT '0',
  `itens` varchar(255) NOT NULL DEFAULT '[]',
  `weapons` varchar(255) NOT NULL DEFAULT '[]',
  `armors` varchar(255) NOT NULL DEFAULT '[]',
  `genre` int(11) NOT NULL DEFAULT '0',
  `head` int(11) NOT NULL DEFAULT '0',
  `body` int(11) NOT NULL DEFAULT '0',
  `hair` int(11) NOT NULL DEFAULT '0',
  `eyes` int(11) NOT NULL DEFAULT '0',
  `hair_color` int(11) NOT NULL DEFAULT '0',
  `eyes_color` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for users
-- ----------------------------
CREATE TABLE `users` (
  `id` int(255) NOT NULL AUTO_INCREMENT,
  `login` varchar(255) NOT NULL,
  `pass` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL DEFAULT 'noemail',
  `acc_type` int(11) NOT NULL DEFAULT '0',
  `genre` int(11) NOT NULL DEFAULT '0',
  `loggedin` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `chars` VALUES ('1', '0', 'pedrohlc', '[ADM]PedroHLC', '0', '0', '0', '0', '0', '0', '0', '0', '[]', '[]', '[]', '0', '0', '0', '0', '0', '0', '0');
