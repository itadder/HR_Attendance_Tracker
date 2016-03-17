Drop database if exists AttendanceTracker;
create database AttendanceTracker;
use  AttendanceTracker;
drop table if exists `employees`;

create table `employees` (
	employeeID int(10) primary key not null auto_increment,
	fname varchar(255),
	lname varchar(255),
	role enum('Employee','Manager','HR'),
	leaveTaken_dates varchar(10),
	leavetaken_type enum('personal','vacation','sick')
);

insert into `employees` (
	fname,
	lname,
	role,
	leaveTaken_dates,
	leavetaken_type)
values (
	"Bob",
	"smith",
	"Employee",
	"12/20/2015",
	"personal"
);

