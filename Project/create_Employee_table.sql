use  AttendanceTracker;
drop table if exists employees;

create table employees(
	requestTime_offID int(10) primary key not null auto_increment,
	username varchar(255),
	fname varchar(255),
	lname varchar(255),		
	leaveTaken_dates varchar(10),
	leavetaken_type enum('personal','vacation','sick'),
	requestTime_off varchar(100),
	requestTime_off_status enum ('Approved','Rejected','None') DEFAULT 'None'
);


insert into `employees`(
  username,
  fname,
  lname,
  leaveTaken_dates,
  leavetaken_type,
  requestTime_off,
  requestTime_off_status
  )
values(
  "jgarcia1",
  "Justino",
  "Garcia",
  "12/29/2015",
  "personal",
  "I took time off to go to Linux World",
  "Approved"
);
