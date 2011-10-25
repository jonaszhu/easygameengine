SET FOREIGN_KEY_CHECKS=0;

DROP TABLE IF EXISTS `mol_categroy`;
CREATE TABLE `mol_categroy` (
  `cid` int(11) NOT NULL auto_increment,
  `name` varchar(50) NOT NULL,
  `parentid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`cid`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

DROP TABLE IF EXISTS `mol_member`;
CREATE TABLE `mol_member` (
  `uid` int(11) NOT NULL auto_increment,
  `gtype` int(1) default NULL,  
  `username` varchar(20) NOT NULL,
  `password` varchar(50) NOT NULL,
  `email` varchar(50) NOT NULL,
  `sex` int(1) NOT NULL,
  `realname` varchar(100) NOT NULL,
  `homeplace` varchar(100) NOT NULL,
  `telephone` varchar(100) NOT NULL,
  `QQ` varchar(100) NOT NULL,  
  `createtime` int(11) NOT NULL,
  `lastlogintime` int(11) default NULL,
  PRIMARY KEY  (`uid`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

DROP TABLE IF EXISTS `mol_message`;
CREATE TABLE `mol_message` (
  `mid` int(11) NOT NULL auto_increment,
  `types` tinyint(2) NOT NULL,
  `name` varchar(20) NOT NULL,
  `content` text NOT NULL,
  `phone` varchar(20) default NULL,
  `email` varchar(30) NOT NULL,
  `qq` varchar(30) default NULL,
  `clientip` varchar(50) NOT NULL,
  `reply` text,
  `postdate` int(11) NOT NULL,
  `replydate` int(11) default NULL,
  PRIMARY KEY  (`mid`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

DROP TABLE IF EXISTS `mol_navigation`;
CREATE TABLE `mol_navigation` (
  `ngid` int(11) NOT NULL auto_increment,
  `name` varchar(20) NOT NULL,
  `url` varchar(100) NOT NULL,
  `orders` int(11) NOT NULL,
  PRIMARY KEY  (`ngid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=6 ;
INSERT INTO `mol_navigation` (`ngid`, `name`, `url`, `orders`) VALUES
(1, '新闻中心', '{siteurl}/index.php/News', 1),
(2, '游戏介绍', '{siteurl}/index.php/Game', 2),
(3, '用户管理', '{siteurl}/index.php/Member', 3),
(4, '账号充值', '{siteurl}/index.php/bank', 4),
(5, '游戏下载', '{siteurl}/index.php/Pages/pgid/1', 5),
(6, '玩家排行', '{siteurl}/index.php/ranklist', 6),
(7, '客服中心', '{siteurl}/index.php/Message', 7);

DROP TABLE IF EXISTS `mol_news`;
CREATE TABLE `mol_news` (
  `nid` int(11) NOT NULL auto_increment,
  `uid` int(11) NOT NULL,
  `title` varchar(50) NOT NULL,
  `content` text NOT NULL,
  `postdate` int(11) NOT NULL,
  PRIMARY KEY  (`nid`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

DROP TABLE IF EXISTS `mol_options`;
CREATE TABLE `mol_options` (
  `types` varchar(50) NOT NULL,
  `values` text NOT NULL,
  PRIMARY KEY  (`types`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
INSERT INTO `mol_options` (`types`, `values`) VALUES
('company', 'company'),
('companyaddress', 'company address'),
('description', 'description'),
('email', 'akinggw@126.com'),
('factoryaddress', 'factory address'),
('fax', 'fax'),
('icp', 'icp'),
('keywords', 'keywords'),
('linkman', 'Fengzi'),
('phone', 'phone'),
('seotitle', '休闲游戏平台'),
('sitename', 'Mole2d'),
('siteurl', 'www.mole2d.com');

DROP TABLE IF EXISTS `mol_pages`;
CREATE TABLE `mol_pages` (
  `pgid` int(11) NOT NULL auto_increment,
  `uid` int(11) NOT NULL,
  `title` varchar(50) NOT NULL,
  `content` text NOT NULL,
  `description` varchar(300) default NULL,
  `keywords` varchar(100) default NULL,
  `postdate` int(11) NOT NULL,
  PRIMARY KEY  (`pgid`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;
INSERT INTO `mol_pages` (`pgid`, `uid`, `title`, `content`, `description`, `keywords`, `postdate`) VALUES
(1, 1, '游戏下载', '', '', '', 1268293327),
(2, 1, '游戏协议', '', '', '', 1268293327);

DROP TABLE IF EXISTS `mol_slide`;
CREATE TABLE `mol_slide` (
  `sid` int(11) NOT NULL auto_increment,
  `title` varchar(50) NOT NULL,
  `content` varchar(200) NOT NULL,
  `attachment` varchar(100) NOT NULL,
  `url` varchar(100) NOT NULL,
  `postdate` int(11) NOT NULL,
  PRIMARY KEY  (`sid`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;
INSERT INTO `mol_slide` (`sid`, `title`, `content`, `attachment`, `url`, `postdate`) VALUES

DROP TABLE IF EXISTS `mol_game`;
CREATE TABLE `mol_game` (
  `Id` int(6) unsigned NOT NULL auto_increment,
  `name` varchar(100) NOT NULL,
  `Type` int(1) NOT NULL,
  `content` text NOT NULL,
  PRIMARY KEY  (`Id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=300003 ;
INSERT INTO `mol_game` VALUES (300001, '斗地主', 0, '');
INSERT INTO `mol_game` VALUES (300002, '五子棋', 0, '');

DROP TABLE IF EXISTS `mol_room`;
CREATE TABLE `mol_room` (
  `Id` int(6) unsigned NOT NULL auto_increment,
  `gameId` int(6) NOT NULL,
  `name` varchar(100) NOT NULL,
  PRIMARY KEY  (`Id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3;
INSERT INTO `mol_room` VALUES (1, 300001, '斗地主普通房间');
INSERT INTO `mol_room` VALUES (2, 300002, '五子棋普通房间');

DROP TABLE IF EXISTS `mol_userdata`;
CREATE TABLE `mol_userdata` (
  `UserId` int(6) NOT NULL,
  `Money` bigint(15) NOT NULL default '0',
  `Level` int(6) NOT NULL default '0',
  `Experience` int(6) NOT NULL default '0',
  `UserAvatar` varchar(100) NOT NULL,
  `TotalBureau` int(6) NOT NULL default '0',
  `SBureau` int(6) NOT NULL default '0',
  `FailBureau` int(6) NOT NULL default '0',
  `SuccessRate` float NOT NULL default '0',
  `RunawayRate` float NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=3;