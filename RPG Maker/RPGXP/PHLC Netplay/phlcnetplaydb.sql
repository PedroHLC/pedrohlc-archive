-- =======================================================================|
-- PHLC-Neplays' Database
-- 28/07/2011
-- Gerado pelo Navcat e modificado para funcionar em qualquer lugar.
-- Atenção: Não utilize esse arquivo como uma atualização.
-- =======================================================================|

SET FOREIGN_KEY_CHECKS=0;

CREATE DATABASE IF NOT EXISTS `phlcdb` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;
USE `phlcdb`;

DROP TABLE IF EXISTS `chars`;
DROP TABLE IF EXISTS `users`;

CREATE TABLE `chars` (
  `char_id` int(5) NOT NULL AUTO_INCREMENT,
  `char_num` int(1) NOT NULL,
  `char_owner` int(5) NOT NULL,
  `char_nick` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `char_genre` int(1) NOT NULL DEFAULT '0',
  `char_class` int(2) NOT NULL,
  `char_exp` int(8) DEFAULT '0',
  `char_money` int(8) DEFAULT '0',
  `char_hp` int(4) DEFAULT '740',
  `char_maxhpp` int(4) DEFAULT '0',
  `char_sp` int(4) DEFAULT '530',
  `char_maxspp` int(4) unsigned DEFAULT '0',
  `char_evap` int(4) DEFAULT '0',
  `char_pdefp` int(4) DEFAULT '0',
  `char_mdefp` int(4) DEFAULT '0',
  `char_agip` int(4) DEFAULT '0',
  `char_atkp` int(4) DEFAULT '0',
  `char_strp` int(4) DEFAULT '0',
  `char_dexp` int(4) DEFAULT '0',
  `char_intp` int(4) DEFAULT '0',
  `char_mapi` int(2) DEFAULT '1',
  `char_posx` int(4) DEFAULT '20',
  `char_posy` int(4) DEFAULT '15',
  `char_posd` int(1) DEFAULT '2',
  `char_guild` int(5) DEFAULT '-1',
  `char_equiped` longtext COLLATE utf8_unicode_ci,
  `char_ivent` longtext COLLATE utf8_unicode_ci,
  `char_skills` longtext COLLATE utf8_unicode_ci,
  PRIMARY KEY (`char_id`,`char_nick`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

CREATE TABLE `users` (
  `login_id` int(4) NOT NULL AUTO_INCREMENT,
  `login_name` varchar(33) COLLATE utf8_unicode_ci NOT NULL,
  `login_pass` varchar(33) COLLATE utf8_unicode_ci NOT NULL,
  `email` varchar(128) COLLATE utf8_unicode_ci DEFAULT '',
  `email_authed` bit(1) DEFAULT b'0',
  `email_authcode` varchar(32) COLLATE utf8_unicode_ci DEFAULT NULL,
  `logged_in` bit(1) DEFAULT b'0',
  `type` int(1) DEFAULT '0',
  PRIMARY KEY (`login_id`,`login_name`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;