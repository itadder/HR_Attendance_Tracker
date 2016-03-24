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

	public function checkIfUserExists($username)
   	{
		$username = $this->db->real_escape_string($username);
		$query = "select username from login where username = '$username';";
        	$results = $this->db->query($query);
		$row = $results->fetch_assoc();
		
		if ($row['username'] === $username)
        	{
			return true;
		}
        	
		return false;
   	}


	public function validateUser($username, $password)
	{
		$username = $this->db->real_escape_string($username);
		$password = $this->db->real_escape_string($this->saltPassword($password));
		$query = "select username, password from login where username = '$username';";
		$results = $this->db->query($query);
		$row = $results->fetch_assoc();

		if ($row['password'] === $password)
		{
			return true;
		}
		
		return false;
	}

 	public function checkIFAdmin($username)
   	{
		$username = $this->db->real_escape_string($username);		
		$query = "select roles from login where username = '$username';";
        	$results = $this->db->query($query);
		$row = $results->fetch_assoc();
		
		if ($row['roles'] === 'admin')
		{
			echo "".PHP_EOL;
			echo "Admin Logged on ".PHP_EOL;
			echo "".PHP_EOL;
			return true;
		}
		echo "false".PHP_EOL;
		return false;
   	}

	 public function checkIfManager($username)
        {
                $username = $this->db->real_escape_string($username);
                $query = "select roles from login where username = '$username';";
                $results = $this->db->query($query);
                $row = $results->fetch_assoc();

                if ($row['roles'] === 'manager')
                {
                        echo "".PHP_EOL;
                        echo "Manager Access granted! Your command has been processed...  ".PHP_EOL;
                        echo "".PHP_EOL;
                        return true;
                }
                echo "false".PHP_EOL;
                return false;
        }

	

	private function saltPassword($password)
   	{
		$salt = $this->ini['loginDB']['salt'];
		return substr(sha1($password.$salt),10,-10);
   	}	
	
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

	
	

	

public function ViewHistoryleavetaken ($username, $password)
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
	}
	



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
			$Sickdaysquery = "select username,fname,lname,leaveTaken_dates,leavetaken_type from employees where leavetaken_type ='Sick';";
                       $Sickdaycount="select COUNT(leavetaken_type) from employees where leavetaken_type='Sick'";
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
			$vacationdaysquery = "select username,fname,lname,leaveTaken_dates,leavetaken_type from employees where leavetaken_type ='Personal';";
                       $vacationdaycount="select COUNT(leavetaken_type) from employees where leavetaken_type='personal'";
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
	
     public function requestTimeOff ($username, $password)
	{
		$username = $this->db->real_escape_string($username);
                $password = $this->db->real_escape_string($password);
                $fname = $this->db->real_escape_string($fname);
                $lname = $this->db->real_escape_string($lname);
                $leakveTakendates = $this->db->real_escape_string($leaveTaken_dates);
                $leavetaken_type = $this->db->real_escape_string($leave_type);
                $requestTime_off = $this->db->real_escape_string($requestTime_off);
                

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
			 $query = "insert into `employees`(username,fname,lname,leaveTaken_dates,leavetaken_type,requestTime_off,requestTime_off_status) VALUES( $username,'$fname','$lname','$leaveTaken_dates','$leavetaken_type',$requestTime_off)";
               		 $results = $this->db->query($query);

                        if($results->rows > 0)
                        {
                                while($row = $results->fetch_assoc())
                                {
                                        echo " User Name : " . $row["username"] ." Requested Time off : ".$row[" requestTime_off "] . " leave taken dates : " . $row["leavetaken_dates"] . " leave taken type : " . $row["leavetaken_type"] . "Request time off" . $row["requestTime_off"] . "requestTime off Status" . $row["requestTime_off_status"].PHP_EOL;
                                }

			}
			else
			{
				echo "0 results found.".PHP_EOL;
			}
		}
	}

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
			 
			$query = "insert into `employees`(username,fname,lname,leaveTaken_dates,leavetaken_type,requestTime_off,requestTime_off_status) VALUES( $username,'$fname','$lname','$leaveTaken_dates','sick');";
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
	
public function set_vacation_days_allowed ($username, $password, $set_vacation_days_allowed)
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
			 $query = "UPDATE login SET allowedsickdays = '$set_vacation_days_allowed;";
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
	
public function set_sick_days_allowed ($username, $password, $set_allowedsickdays)
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
			 $query = "update login set allowedsickdays = '$set_allowedsickdays;";
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
}



?>
