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
	
	$sql4 = "DELETE FROM SUGGESTIONS WHERE (USERNAME1 = '$username1' AND USERNAME2 = '$username2') OR  (USERNAME1 = '$username2' AND USERNAME2 = '$username1') ";
	$result4 = mysqli_query($conn,$sql4);
	    
	 if($result4)
	    echo "deleted";
	
	mysqli_close($conn);
?>