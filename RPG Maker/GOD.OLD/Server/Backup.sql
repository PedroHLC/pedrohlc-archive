SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for char1
-- ----------------------------
CREATE TABLE `char1` (
  `id` int(255) unsigned NOT NULL auto_increment,
  `owner` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `char_exp` int(255) NOT NULL default '1',
  `raça_id` int(255) NOT NULL default '1',
  `genero_id` int(255) NOT NULL default '1',
  `class_id` int(255) NOT NULL default '1',
  `graphic_name` varchar(255) NOT NULL default '147-Storekeeper01',
  `gold` int(255) NOT NULL default '0',
  `energia_nuclear` int(255) NOT NULL default '0',
  `enirgia_oni` int(255) NOT NULL default '0',
  `hp` int(255) NOT NULL default '1',
  `maxhp` int(255) NOT NULL default '2',
  `sp` int(255) NOT NULL default '1',
  `maxsp` int(255) NOT NULL default '2',
  `states` varchar(255) NOT NULL default '[]',
  `eva` int(255) NOT NULL default '1',
  `pdef` int(255) NOT NULL default '1',
  `mdef` int(255) NOT NULL default '1',
  `agi` int(255) NOT NULL default '1',
  `atk` int(255) NOT NULL default '1',
  `str` int(255) NOT NULL default '1',
  `dex` int(255) NOT NULL default '1',
  `inte` int(255) NOT NULL default '1',
  `equiped` varchar(255) NOT NULL default '[0,0,0,0,0]' COMMENT 'Itens equipados',
  `weapons` varchar(255) NOT NULL default '[]',
  `armors` varchar(255) NOT NULL default '[]',
  `items` varchar(255) NOT NULL default '[]',
  `skills` varchar(255) NOT NULL default '[]',
  `skill_key` varchar(255) NOT NULL default '0',
  `map_id` int(255) NOT NULL default '12',
  `map_x` int(255) NOT NULL default '10',
  `map_y` int(255) NOT NULL default '8',
  `map_direction` int(255) NOT NULL default '2',
  `move_speed` int(255) NOT NULL default '4',
  `move_frequency` int(255) NOT NULL default '6',
  `walk_anime` varchar(255) NOT NULL default 'true',
  `step_anime` varchar(255) NOT NULL default 'false',
  `always_on_top` varchar(255) NOT NULL default 'false',
  `upp` int(255) NOT NULL default '2',
  `char_guild` varchar(255) NOT NULL default '',
  `player_job` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for char2
-- ----------------------------
CREATE TABLE `char2` (
  `id` int(255) unsigned NOT NULL auto_increment,
  `owner` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `char_exp` int(255) NOT NULL default '1',
  `raça_id` int(255) NOT NULL default '1',
  `genero_id` int(255) NOT NULL default '1',
  `class_id` int(255) NOT NULL default '1',
  `graphic_name` varchar(255) NOT NULL default '147-Storekeeper01',
  `gold` int(255) NOT NULL default '0',
  `energia_nuclear` int(255) NOT NULL default '0',
  `energia_oni` int(255) NOT NULL default '0',
  `hp` int(255) NOT NULL default '1',
  `maxhp` int(255) NOT NULL default '2',
  `sp` int(255) NOT NULL default '1',
  `maxsp` int(255) NOT NULL default '2',
  `states` varchar(255) NOT NULL default '[]',
  `eva` int(255) NOT NULL default '1',
  `pdef` int(255) NOT NULL default '1',
  `mdef` int(255) NOT NULL default '1',
  `agi` int(255) NOT NULL default '1',
  `atk` int(255) NOT NULL default '1',
  `str` int(255) NOT NULL default '1',
  `dex` int(255) NOT NULL default '1',
  `inte` int(255) NOT NULL default '1',
  `equiped` varchar(255) NOT NULL default '[0,0,0,0,0]' COMMENT 'Itens equipados',
  `weapons` varchar(255) NOT NULL default '[]',
  `armors` varchar(255) NOT NULL default '[]',
  `items` varchar(255) NOT NULL default '[]',
  `skills` varchar(255) NOT NULL default '[]',
  `skill_key` varchar(255) NOT NULL default '0',
  `map_id` int(255) NOT NULL default '12',
  `map_x` int(255) NOT NULL default '10',
  `map_y` int(255) NOT NULL default '8',
  `map_direction` int(255) NOT NULL default '2',
  `move_speed` int(255) NOT NULL default '4',
  `move_frequency` int(255) NOT NULL default '6',
  `walk_anime` varchar(255) NOT NULL default 'true',
  `step_anime` varchar(255) NOT NULL default 'false',
  `always_on_top` varchar(255) NOT NULL default 'false',
  `upp` int(255) NOT NULL default '2',
  `char_guild` varchar(255) NOT NULL default '',
  `player_job` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for char3
-- ----------------------------
CREATE TABLE `char3` (
  `id` int(255) unsigned NOT NULL auto_increment,
  `owner` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `char_exp` int(255) NOT NULL default '1',
  `raça_id` int(255) NOT NULL default '1',
  `genero_id` int(255) NOT NULL default '1',
  `class_id` int(255) NOT NULL default '1',
  `graphic_name` varchar(255) NOT NULL default '147-Storekeeper01',
  `gold` int(255) NOT NULL default '0',
  `energia_nuclear` int(255) NOT NULL default '0',
  `energia_oni` int(255) NOT NULL default '0',
  `hp` int(255) NOT NULL default '1',
  `maxhp` int(255) NOT NULL default '2',
  `sp` int(255) NOT NULL default '1',
  `maxsp` int(255) NOT NULL default '2',
  `states` varchar(255) NOT NULL default '[]',
  `eva` int(255) NOT NULL default '1',
  `pdef` int(255) NOT NULL default '1',
  `mdef` int(255) NOT NULL default '1',
  `agi` int(255) NOT NULL default '1',
  `atk` int(255) NOT NULL default '1',
  `str` int(255) NOT NULL default '1',
  `dex` int(255) NOT NULL default '1',
  `inte` int(255) NOT NULL default '1',
  `equiped` varchar(255) NOT NULL default '[0,0,0,0,0]' COMMENT 'Itens equipados',
  `weapons` varchar(255) NOT NULL default '[]',
  `armors` varchar(255) NOT NULL default '[]',
  `items` varchar(255) NOT NULL default '[]',
  `skills` varchar(255) NOT NULL default '[]',
  `skill_key` varchar(255) NOT NULL default '0',
  `map_id` int(255) NOT NULL default '12',
  `map_x` int(255) NOT NULL default '10',
  `map_y` int(255) NOT NULL default '8',
  `map_direction` int(255) NOT NULL default '2',
  `move_speed` int(255) NOT NULL default '4',
  `move_frequency` int(255) NOT NULL default '6',
  `walk_anime` varchar(255) NOT NULL default 'true',
  `step_anime` varchar(255) NOT NULL default 'false',
  `always_on_top` varchar(255) NOT NULL default 'false',
  `upp` int(255) NOT NULL default '2',
  `char_guild` varchar(255) NOT NULL default '',
  `player_job` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for char4
-- ----------------------------
CREATE TABLE `char4` (
  `id` int(255) unsigned NOT NULL auto_increment,
  `owner` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `char_exp` int(255) NOT NULL default '1',
  `raça_id` int(255) NOT NULL default '1',
  `genero_id` int(255) NOT NULL default '1',
  `class_id` int(255) NOT NULL default '1',
  `graphic_name` varchar(255) NOT NULL default '147-Storekeeper01',
  `gold` int(255) NOT NULL default '0',
  `energia_nuclear` int(255) NOT NULL default '0',
  `energia_oni` int(255) NOT NULL default '0',
  `hp` int(255) NOT NULL default '1',
  `maxhp` int(255) NOT NULL default '2',
  `sp` int(255) NOT NULL default '1',
  `maxsp` int(255) NOT NULL default '2',
  `states` varchar(255) NOT NULL default '[]',
  `eva` int(255) NOT NULL default '1',
  `pdef` int(255) NOT NULL default '1',
  `mdef` int(255) NOT NULL default '1',
  `agi` int(255) NOT NULL default '1',
  `atk` int(255) NOT NULL default '1',
  `str` int(255) NOT NULL default '1',
  `dex` int(255) NOT NULL default '1',
  `inte` int(255) NOT NULL default '1',
  `equiped` varchar(255) NOT NULL default '[0,0,0,0,0]' COMMENT 'Itens equipados',
  `weapons` varchar(255) NOT NULL default '[]',
  `armors` varchar(255) NOT NULL default '[]',
  `items` varchar(255) NOT NULL default '[]',
  `skills` varchar(255) NOT NULL default '[]',
  `skill_key` varchar(255) NOT NULL default '0',
  `map_id` int(255) NOT NULL default '12',
  `map_x` int(255) NOT NULL default '10',
  `map_y` int(255) NOT NULL default '8',
  `map_direction` int(255) NOT NULL default '2',
  `move_speed` int(255) NOT NULL default '4',
  `move_frequency` int(255) NOT NULL default '6',
  `walk_anime` varchar(255) NOT NULL default 'true',
  `step_anime` varchar(255) NOT NULL default 'false',
  `always_on_top` varchar(255) NOT NULL default 'false',
  `upp` int(255) NOT NULL default '2',
  `char_guild` varchar(255) NOT NULL default '',
  `player_job` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for guilds
-- ----------------------------
CREATE TABLE `guilds` (
  `id` int(255) NOT NULL auto_increment,
  `name` varchar(255) NOT NULL,
  `members` varchar(255) NOT NULL default '',
  `master_char` varchar(255) NOT NULL,
  `master_owner` varchar(255) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for partys
-- ----------------------------
CREATE TABLE `partys` (
  `id` int(255) NOT NULL auto_increment,
  `name` varchar(255) NOT NULL,
  `members` varchar(255) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for users
-- ----------------------------
CREATE TABLE `users` (
  `id` int(255) NOT NULL auto_increment,
  `rank_pos` int(255) unsigned NOT NULL default '0',
  `name` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `loggedin` int(255) unsigned NOT NULL default '0',
  `banned` int(255) unsigned NOT NULL default '0',
  `net_group` varchar(255) NOT NULL default 'Standart',
  `cash` int(255) NOT NULL default '0',
  `bank_weapons` varchar(255) NOT NULL default '[]',
  `bank_gold` int(255) NOT NULL default '0',
  `bank_energia_nuclear` int(255) NOT NULL default '0',
  `bank_energia_oni` int(255) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
