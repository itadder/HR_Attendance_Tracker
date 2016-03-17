<?php


class loginDB
{
   private $db;
   private $ini;
   public function __construct($iniFile)
   {
	$this->ini = parse_ini_file($iniFile,true);
	$host = $this->ini['loginDB']['host'];
	$user = $this->ini['loginDB']['user'];
	$password = $this->ini['loginDB']['password'];
	$database = $this->ini['loginDB']['database'];
	$this->db = new mysqli($host,$user,$password,$database);
	if ($this->db->connect_errno > 0)
	{
		echo __FILE__.":".__LINE__.": failed to connect to db, re: ".$this->db->connect_error.PHP_EOL;
		exit(0);
	}
   }

   public function __destruct()
   {
	$this->db->close();
   }

   public function updateUserPassword($username,$oldPassword,$newPassword)
   {
   	if (!$this->validateUser($username,$oldPassword))
        {
		echo "cannot update Password, validation failed".PHP_EOL;
		$response = array(
			"message"=>"cannot update password, validation failed",
			"result"=>"false");
		return $response;
        }
	$username = $this->db->real_escape_string($username);
	$password = $this->db->real_escape_string($this->saltPassword($newPassword));
	$query = "update login set password = '$password' where username ='$username');";
	$results = $this->db->query($query);
	if ($this->db->errno > 0)
        {
		echo "DB error: ".$this->db->error.PHP_EOL;
		return false;
        }
	return true;
   }
   public function checkUserPrivilegeLevel($username)
   {}
   public function disableUserAccount($username)
   {}
   public function enableUserAccount($username)
   {}

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

   public function validateUser($username,$password)
   {
	$username = $this->db->real_escape_string($username);
	$password = $this->db->real_escape_string($this->saltPassword($password));
	$query = "select username,password from login where username = '$username';";
        $results = $this->db->query($query);
	$row = $results->fetch_assoc();
	if ($row['password'] === $password)
	{
		return true;
	}
	return false;
   }

   private function saltPassword($password)
   {
	$salt = $this->ini['loginDB']['salt'];
	return substr(sha1($password.$salt),10,-10);
   }

   public function addNewUser($username, $password,$privilegeLevel)
   {
	if ($this->checkIfUserExists($username) == true)
        {
		echo "cannot create new user $username, this user already exists!".PHP_EOL;
		return;
	}
	$username = $this->db->real_escape_string($username);
	$password = $this->db->real_escape_string($this->saltPassword($password));
	$privilegeLevel = $this->db->real_escape_string($privilegeLevel);
	$query = "insert into login (username,password,privilegeLevel) values('$username','$password','$privilegeLevel');";
	$results = $this->db->query($query);
	if ($this->db->errno > 0)
        {
		echo "DB error: ".$this->db->error.PHP_EOL;
		return;
        }
   }
}


?>

