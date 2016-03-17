use AttendanceTracker;
drop table if exists login;
create table login
(
   loginId INT(11) primary key auto_increment,
   username VARCHAR(32),
   password VARCHAR(255),
   privilegeLevel ENUM('Employee', 'Manager', 'Human Resources')
);
