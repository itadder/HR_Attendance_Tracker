use AttendanceTracker;
drop table if exists login;
create table login(
   LoginID int(10) primary key not null auto_increment,
   username VARCHAR(32),
   password VARCHAR(255),
   roles ENUM('Employee', 'Manager', 'Human Resources','Admin'),
   allowedvacationdays int DEFAULT 15,
   allowedsickdays int DEFAULT 7 
);

