#!/usr/bin/php
#
<?php
require_once("MongoDBConnect.php");
$uri = "mongodb://jgarcia:asdfasdf@ds017582.mlab.com:17582/hrattendancetracker";
$login = new MongoDBConnect($uri);
function print_help()
{
	echo "usage: ".PHP_EOL;
	echo __FILE__." -username <username> -p <password> -l <privilegeLevel> -c <command arguments...>".PHP_EOL;
} 
$cArgs = array();
for ($i = 0; $i < $argc;$i++)
{
	if ($argv[$i] === '-u')
	{
		$username = $argv[$i + 1];
		$i++;
		continue;
	}
	if ($argv[$i] === '-p')
	{
		$password = $argv[$i + 1];
		$i++;
		continue;
	}
	if ($argv[$i] == '-r')
	{
		$roles = $argv[$i + 1];
		$i++;
		continue;
	}

	if ($argv[$i] === '-c')
	{
		$command = $argv[$i + 1];
		$i++;
		continue;
	}	      
	$cArgs[] = $argv[$i]; 
}

if (!isset($username))
{
	echo "no username specified".PHP_EOL;
	print_help();
	exit(0);
}

if (!isset($password))
{
	echo "no password specified".PHP_EOL;
	print_help();
	exit(0);
}
if (!isset($command))
{
	   echo "no command specified".PHP_EOL;
	      print_help();
	      exit(0);
}
switch ($command)
{
case 'addNewUser':
	$login->addNewUser($username,$password,$roles,$cArgs[0]);	
	break;

case 'validateUser':
	if ($login->validateUser($username,$password))
	{
		echo "Hello $username!!!".PHP_EOL;
	}
	else
	{
		echo "password does not validate!".PHP_EOL;
	}
	break;
case 'TestCollections':
	$login->TestCollections();
	break;
}

//$login->ValidateUser($username, $password);

?>
