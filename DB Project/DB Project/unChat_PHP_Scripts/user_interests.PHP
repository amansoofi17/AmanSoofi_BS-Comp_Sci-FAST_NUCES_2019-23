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
    $category = $_POST["category"];
	

		
	// FETCH INTEREST ID	
		$sql2 = "SELECT INTEREST_ID FROM INTERESTS WHERE CATEGORY_NAME = '$category'";
		$responce = mysqli_query($conn,$sql2);
	    $row =  mysqli_fetch_array($responce);
	//echo $row[0];
	$sql = "INSERT INTO USER_INTERESTS (username,INTEREST_ID) VALUES ('$username','$row[0]')";
	$result = mysqli_query($conn,$sql);
	if($result) {
		echo "inserted successfully";
	}
	else {
		echo "some error occured";
	}
	
	mysqli_close($conn);
 ?>