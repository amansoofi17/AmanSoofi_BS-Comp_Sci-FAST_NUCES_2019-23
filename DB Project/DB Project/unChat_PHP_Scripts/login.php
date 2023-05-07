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
		$password = $_POST["password"];

		$sql = "SELECT * FROM USER WHERE username = '$username' AND password = '$password'";
		$result = mysqli_query($con,$sql);
		
		if($result->num_rows > 0){
			echo "logged in successfully" ;
		}else{
  			 echo "user not found";
}
?>