<?php

/**
 * Connect to Mongo Labs
 **/
class MongoDBConnect 
{
	public function __construct($uri)
	{
		// Connection Validation
		//	$uri = "mongodb://jgarcia:asdfasdf@ds017582.mlab.com:17582/hrattendancetracker";
		$database = "hrattendancetracker";
		$this->client = new MongoClient($uri);
		try {
			//	$this->client = new MongoClient($uri);
			$db=$this->client->selectDB("hrattendancetracker");

			echo"Connection Sucessfull to Mongo Labs $database Database".PHP_EOL;
		}
		catch (MongoConnectionException $e) {
			die('Error connecting to MongoDB server');}
		catch (MongoConnectionException $e) {
			dir('Error: ' . $e->getMessage());

		}

	}

	


	public function ValidateUser($username, $password)

	{

		$db=$this->client->selectDB("hrattendancetracker");
		$collections = $db->login;
		$query=array('username'=> $username,'password' => $password);	
		//		$count= $collections->findOne($query);
		if ($collections->count($query) > 0) {
			echo "You are successully loggedIn".PHP_EOL;
		}
		//	print_r($doc);

	}

	public function TestCollections()
		{
			$db=$this->client->selectDB("hrattendancetracker");	
		
			$collections = $db->login;	
			$cursor = $collections->find();	
		
			foreach ($cursor as $document) {
				var_dump($document);	
			}
		}

/**
{
    "_id": {
	"$oid": "572e6093ad9557699515b82d"
    },
    "LoginID": "1",
    "username": "jgarcia",
    "password": "asdfasdf",
    "roles": "manager",
    "allowedvacationdays": "11",
    "allowedsickdays": "7"
}
**/

	public function addNewUser($username,$password,$roles)
	{
		$db=$this->client->selectDB("hrattendancetracker");
		$collections = $db->login;
		$collections->insert(array('username'=>$username,'password'=>$password,'roles'=>$roles,'allowedvacationdays'=>11,'allowedsickdays'=>7));



	}


	}

?>
