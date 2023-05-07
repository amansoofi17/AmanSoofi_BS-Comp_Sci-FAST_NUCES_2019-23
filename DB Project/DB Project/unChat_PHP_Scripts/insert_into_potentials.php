<?php 

$servername = "localhost";
$username = "id17671841_unchat123";
$database = "id17671841_unchat";
$password = "m4?ioke|fwD{qn/K";

// Create connection
$conn = new mysqli($servername, $username, $password,$database);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// reciveing the data 
	$username1 = $_POST["username1"];
	$username2 = $_POST["username2"];
	
	
	
	$sql = "UPDATE SUGGESTIONS SET SUGGESTED_USER1 = 'Y' WHERE USERNAME1 = '$username1' AND USERNAME2 = '$username2'";
	$result1 = mysqli_query($conn,$sql);
	
	$sql2 = "INSERT INTO POTENTIAL_USERS(username1,username2) VALUES ('$username1','$username2')";
	$result2 = mysqli_query($conn,$sql2);
	
	
	if($result1 && $result2){echo "success";}
    else{echo "failed";}
	
	
	mysqli_close($conn);
?>