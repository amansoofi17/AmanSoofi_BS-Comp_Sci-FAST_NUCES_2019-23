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
	
	$username = $_POST["username"];

	
	$result = array();
	$result['data'] = array();
	$sql = "SELECT CATEGORY_NAME FROM INTERESTS,USER_INTERESTS 
	         WHERE INTERESTS.INTEREST_ID = USER_INTERESTS.INTEREST_ID AND USER_INTERESTS.username = '$username'";
	$responce = mysqli_query($conn,$sql);
	
	while($row = mysqli_fetch_array($responce))
		{
			$index['CATEGORY_NAME']   = $row['0'];
			array_push($result['data'], $index);
		}
			
			$result["success"]="1";
			echo json_encode($result);
			mysqli_close($conn);

 ?>