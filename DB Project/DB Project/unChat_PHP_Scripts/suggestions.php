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
	$match_count = $_POST["match_count"];
	$suggested1 = $_POST["suggestedUser1"];
	$suggested2 = $_POST["suggestedUser2"];
	
	$sql = "INSERT INTO SUGGESTIONS(USERNAME1,USERNAME2,MATCH_COUNT,SUGGESTED_USER1,SUGGESTED_USER2) VALUES ('$username1','$username2','$match_count',
	'$suggested1','$suggested2')";
	
	$result = mysqli_query( $conn,$sql );
	if($result) {
		echo "registered successfully";
	}
	else {
		echo "some error occured";
	}
?>