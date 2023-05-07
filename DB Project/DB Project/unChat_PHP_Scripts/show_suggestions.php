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
	$username = $_POST["username"];
	
	$sql = "SELECT USERNAME2 FROM SUGGESTIONS WHERE MATCH_COUNT = MAX(MATCH_COUNT) AND USERNAME1 = '$username'";
	$responce = mysqli_query($conn,$sql);
	$row = mysqli_fetch_array($responce);
	
	$result = array();
	$result['data'] = array();
	$sql2 = "SELECT Photo FROM USER WHERE username = '$row[0]'";
	$responce2 = mysqli_query($conn,$sql2);
	$row2 = mysqli_fetch_array($responce2);
	
	$index['username'] = $row['0'];
	$index['image'] = $row2['0'];
	array_push($result['data'], $index);
	
	$result["success"]="1";
	echo json_encode($result);
	mysqli_close($conn);
?>