<?php

class loginDB
{
	private $db;
	private $ini;

	public function __construct($inifile)
	{
		$this->ini = parse_ini_file($inifile, true);
		$host = $this->ini['loginDB']['host'];
		$user = $this->ini['loginDB']['user'];
		$password = $this->ini['loginDB']['password'];
		$database = $this->ini['loginDB']['database'];

		$this->db = new mysqli($host,$user,$password,$database);

		if ($this->db->connect_errno > 0)
		{
			echo __FILE__.":".__LINE__.": failed to connect to database, re: ".$this->db->connect_error.PHP_EOL;
			exit(0);
		}
	}

	public function __destruct()
	{
		$this->db->close();
	}

	/**
	private function saltPassword($password)
	{
		$salt = $this->ini['loginDB']['salt'];
		return substr(sha1($password.$salt),10,-10);
	}	
**/
	/**
	public function addNewUser($username,$password,$roles)
	{
		if ($this->checkIfUserExists($username) == true)
		{
			echo "cannot create new user $username, this user already exists!".PHP_EOL;
			return;
		}
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($this->saltPassword($password));
		$roles = $this->db->real_escape_string($roles);	
		$query = "insert into login (username,password,roles) values('$username','$password','$roles');";
		$results = $this->db->query($query);
		if ($this->db->errno > 0)
		{
			echo "DB error: ".$this->db->error.PHP_EOL;
			return;
		}
	}

**/



	/**
	public function ViewHistoryleavetaken ($username, $password)
	{
		
			$query = "select fname,lname,leaveTaken_dates,leavetaken_type from employees where username ='$username';";
			$results = $this->db->query($query);

			if($results->num_rows > 0)
			{
				while($row = $results->fetch_assoc())
				{
					echo " First name : " . $row["fname"] . " Last name : " . $row["lname"] . " leave taken dates : " . $row["leaveTaken_dates"] . " leave taken type : " . $row["leavetaken_type"].PHP_EOL;
				}

			}

			else
			{
				echo "0 results found.".PHP_EOL;
			}
		
	}

**/


	public function ViewRemainderSickDays ($username, $password)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($password);

		if(!$this->validateUser($username, $password))
		{
			echo "Incorrect password".PHP_EOL;
			$response = array(
				"message"=>"Incorrect",
				"result"=>"false"
			);
			return $response;
		}

		else
		{
			$Sickdaysquery = "select fname,lname from employees,Sick_Days_Off;";
			$Sickdaycount="select COUNT(fk_Employee_ID_Sick_Days_Off) from Sick_Days_Off where fk_Employee_ID_Sick_Days_Off IN (select Employee_ID FROM employees)";
			$Sickdays=$this->db->query($Sickdaycount);
			// echo"$Sickdays".PHP_EOL;
			while($row=$Sickdays->fetch_assoc())
			{
				echo"".$row['COUNT(leavetaken_type)'].PHP_EOL;
				$Sick=$row['COUNT(leavetaken_type)'];


			}
			$Sick_days_allowed_query = "select DEFAULT(allowedSickdays) from login LIMIT 1;";
			$Sick_days_allowed_results=$this->db->query($Sick_days_allowed_query); 

			while($row2=$Sick_days_allowed_results->fetch_assoc())
			{
				echo"".$row2['DEFAULT(allowedSickdays)'].PHP_EOL;
				$Sick2=$row2['DEFAULT(allowedSickdays)'];
			}

			echo "Checking ****$username****Users***Sick days left***".PHP_EOL;
			$remainin= $Sick2 - $Sick;	
			echo"$remainin";


		}
	}



	public function ViewRemaindervacationDays ($username, $password)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($password);

		if(!$this->validateUser($username, $password))
		{
			echo "Incorrect password".PHP_EOL;
			$response = array(
				"message"=>"Incorrect",
				"result"=>"false"
			);
			return $response;
		}

		else
		{
			$vacationdaysquery = "select fname,lname,from employees,Vaction_Time where ;";
			$vacationdaycount="select COUNT(fk_Employee_ID_VactionTime) from Vaction_Time where fk_Employee_ID_VactionTime IN (select Employee_ID FROM employees)";
			$vacationdays=$this->db->query($vacationdaycount);
			// echo"$vacationdays".PHP_EOL;
			while($row=$vacationdays->fetch_assoc())
			{
				echo"".$row['COUNT(leavetaken_type)'].PHP_EOL;
				$vac=$row['COUNT(leavetaken_type)'];


			}
			$vacation_days_allowed_query = "select DEFAULT(allowedvacationdays) from login LIMIT 1;";
			$vacation_days_allowed_results=$this->db->query($vacation_days_allowed_query); 

			while($row2=$vacation_days_allowed_results->fetch_assoc())
			{
				echo"".$row2['DEFAULT(allowedvacationdays)'].PHP_EOL;
				$vac2=$row2['DEFAULT(allowedvacationdays)'];
			}

			echo "Checking ****$username****Users***Personal days left***".PHP_EOL;
			$remainin= $vac2 - $vac;	
			echo"$remainin";


		}
	}
	/**
	public function requestTimeOff ($username, $password, $fname, $lname, $leaveTaken_dates, $leavetaken_type, $requestTime_off)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($password);


		if(!$this->validateUser($username, $password))
		{
			echo "Incorrect password".PHP_EOL;
			$response = array(
				"message"=>"Incorrect",
				"result"=>"false"
			);
			return $response;
		}

		else
		{
			$query = "insert into `employees`(username,fname,lname,leaveTaken_dates,leavetaken_type,requestTime_off,requestTime_off_status) VALUES( '$username','$fname','$lname','$leaveTaken_dates','$leavetaken_type','$requestTime_off','$requestTime_off');";
		return $query ;
			$results = $this->db->query($query);
			echo $results;
			if (!$results) {
				echo "Thier was an error in the query: $query";
				//echo mysqli_error($db);
				die('there was an error in the query');
				echo die(mysqli_error($db));
			}
			//$results = $this->db->die(mysqli_error($db);
			//			//if($results->rows > 0)
			////			{
			////				while($row = $results->fetch_assoc())
			////				{
			//					echo " User Name : " . $row["username"] ." Requested Time off : ".$row[" requestTime_off "] . " leave taken dates : " . $row["leavetaken_dates"] . " leave taken type : " . $row["leavetaken_type"] . "Request time off" . $row["requestTime_off"] . "requestTime off Status" . $row["requestTime_off_status"].PHP_EOL;
			////				}
			//
			//			}
			//			else
			//			{
			//				echo "0 results found.".PHP_EOL;
			//			}
			//		}
		}
	}
	**/
	public function logsickdays ($username, $password)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($password);

		if(!$this->validateUser($username, $password))
		{
			echo "Incorrect password".PHP_EOL;
			$response = array(
				"message"=>"Incorrect",
				"result"=>"false"
			);
			return $response;
		}

		else
		{

			$query = "insert `into Sick_Days_Off`(Sick_Date) VALUES('$Sick_Date') "
			$results = $this->db->query($query);

			if($results->rows > 0)
			{
				while($row = $results->fetch_assoc())
				{

					echo " user name : " . $row["username"] . "leave taken dates : " . $row["leavetaken_dates"] . " leave taken type : " . $row["leavetaken_type"].PHP_EOL;
				}

			}
			else
			{
				echo "0 results found.".PHP_EOL;
			}
		}
	}


	public function viewTeamMemberAttendance ($username, $password)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($password);

		if(!$this->checkIfManager($username, $password))
		{
			echo "Incorrect password".PHP_EOL;
			$response = array(
				"message"=>"Incorrect",
				"result"=>"false"
			);
			return $response;
		}

		else
		{
			$query = "select * from employees;";
			$results = $this->db->query($query);

			if($results->rows > 0)
			{
				while($row = $results->fetch_assoc())
				{
					echo " First name : " . $row["fname"] . " Last name : " . $row["lname"] . " leave taken dates : " . $row["leavetaken_dates"] . " leave taken type : " . $row["leavetaken_type"].PHP_EOL;
				}

			}
			else
			{
				echo "0 results found.".PHP_EOL;
			}
		}
	}


	public function approve_reject_time_off ($username, $password, $updatestatus, $username)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($password);

		if(!$this->checkIfManager($username, $password))
		{
			echo "Incorrect password".PHP_EOL;
			$response = array(
				"message"=>"Incorrect",
				"result"=>"false"
			);
			return $response;
		}

		else
		{
			$query = "UPDATE employees SET requestTime_off_status = '$updatestatus';";
			$results = $this->db->query($query);

			if($results->rows > 0)
			{
				while($row = $results->fetch_assoc())
				{
					echo " First name : " . $row["fname"] . " Last name : " . $row["lname"] . " leave taken status : " . $row["requestTime_off_status enum"].PHP_EOL;
				}

			}
			else
			{
				echo "0 results found.".PHP_EOL;
			}
		}
	}



	public function add_remove_sick_vacation ($username, $password, $updatestatus, $username)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($password);

		if(!$this->checkIfManager($username, $password))
		{
			echo "Incorrect password".PHP_EOL;
			$response = array(
				"message"=>"Incorrect",
				"result"=>"false"
			);
			return $response;
		}

		else
		{
			$query = "UPDATE employees SET requestTime_off_status = '$updatestatus';";
			$results = $this->db->query($query);

			if($results->rows > 0)
			{
				while($row = $results->fetch_assoc())
				{
					echo " First name : " . $row["fname"] . " Last name : " . $row["lname"] . " leave taken status : " . $row["requestTime_off_status enum"].PHP_EOL;
				}

			}
			else
			{
				echo "0 results found.".PHP_EOL;
			}
		}
	}

public function set_vacation_days_allowed ($username, $password, $set_allowedvacationdays)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($password);
                // echo $set_allowedvacationdays.PHP_EOL;
		if(!$this->validateUser($username, $password))
		{
			echo "Incorrect password".PHP_EOL;
			$response = array(
				"message"=>"Incorrect",
				"result"=>"false"
			);
			return $response;
		}

		else     {
			 $query = "update login SET allowedvacationdays = '$set_allowedvacationdays' ;";
		         $results = $this->db->query($query);
			 echo "The allowed vaction days have been updated to " ."$set_allowedvacationdays"." ".PHP_EOL;
		         }


	}


public function set_sick_days_allowed($username, $password, $set_allowedsickdays)
{
	$username = $this->db->real_escape_string($username);
	$password = $this->db->real_escape_string($password);

	if(!$this->validateUser($username, $password))
	{
		echo "Incorrect password".PHP_EOL;
		$response = array(
			"message"=>"Incorrect",
			"result"=>"false"
		);
		return $response;
	}

	else	{
		$query = "update login SET allowedsickdays = '$set_allowedsickdays' ;";
		$results = $this->db->query($query);	
		echo "The allowed sick days have been updated to " ."$set_allowedsickdays"." ".PHP_EOL;

	}		




}


}



?>
