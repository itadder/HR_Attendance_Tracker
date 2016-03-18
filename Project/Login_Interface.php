#!/usr/bin/php
<?php

require_once("logindb.php.inc");

function print_help()
{
  echo "usage: ".PHP_EOL;
  echo __FILE__." -u <username> -p <password> -l <privilegeLevel> -c <command arguments...>".PHP_EOL;
}

if ($argc < 2)
{
   print_help();
   exit(0);
}
$cArgs = array();
for ($i = 0; $i < $argc;$i++)
{
  if (($argv[$i] === "-h") ||
      ($argv[$i] === "--help"))
  {
      print_help();
      exit(0);
  }
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
  
  if ($argv[$i] === '-l')
  {
    $privilegeLevel = $argv[$i + 1];
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

if (!isset($privilegeLevel))
{
   echo "no privilege level specified".PHP_EOL;
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
  case 'updatePW':
   $login = new loginDB("logindb.ini");
   $login->updateUserPassword($username,$password,$cArgs[0]);
   break;
  case 'validatePW':
   $login = new loginDB("logindb.ini");
   if ($login->validateUser($username,$password))
   {
      echo "password validated!!!".PHP_EOL;
   }
   else
   {
      echo "password does not validate!".PHP_EOL;
   }

   break;
  case 'addNewUser':
   $login = new loginDB("logindb.ini");
   $login->addNewUser($username,$password,$privilegeLevel,$cArgs[0]);
    break;

case 'runprogram':
  $login = new loginDB("logindb.ini");
  if ($login->validateUser($username,$password))
   {
      echo "Hello $username!!!".PHP_EOL;
   }
   else
   {
      echo "password does not validate!".PHP_EOL;
   }
  break;

}

?>
