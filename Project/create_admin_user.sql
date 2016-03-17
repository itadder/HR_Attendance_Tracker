drop user 'root'@'localhost';
create user 'root'@'localhost' identified by "asdfasdf";
grant all privileges on *.* to 'root'@'localhost';
flush privileges;
