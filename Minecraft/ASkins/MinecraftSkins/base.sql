create database mineskins;
use mineskins;
create table players(
	nick varchar(64) not null,
	url varchar(256) not null,
	primary key (nick)
);
insert into players values('pedrohlc', 'http://dl.dropbox.com/u/44637513/MineSkn/EzioAuditore.png');