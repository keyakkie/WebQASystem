--- login as administrator
GRANT ALL PRIVILEGES ON WebQADB.* TO WebQAUser@localhost IDENTIFIED BY 'password';
create database WebQADB;
use WebQADB
create table vote(
	fname varchar(16),
	gname varchar(16),
	affiliation varchar(16),
	attribute varchar(16),
	opinion varchar(16),
	focus varchar(16)
);

