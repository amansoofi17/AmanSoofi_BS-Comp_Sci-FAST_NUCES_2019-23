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
	$first_name = $_POST["first_name"];
	$last_name = $_POST["last_name"];
	$password =$_POST["password"];
	$email = $_POST["email"];
	$gender = $_POST["gender"];
	$birthdate = $_POST["birthdate"];
	
// set imageData
	 if(isset($_POST['image']))
	{
	$target_dir = "Images/";
	$image = $_POST['image'];
	$imageStore = rand()."_".time().".jpeg";
	$target_dir = $target_dir."/".$imageStore;
	file_put_contents($target_dir, base64_decode($image));
	}
	
	$sql = "INSERT INTO USER(username,first_name,last_name,password,email,gender,birthdate,photo) VALUES ('$username','$first_name','$last_name',
	'$password','$email','$gender','$birthdate','$imageStore')";
	$result = mysqli_query( $conn,$sql );
	if($result) {
		echo "registered successfully";
	}
	else {
		echo "some error occured";
	}
?>