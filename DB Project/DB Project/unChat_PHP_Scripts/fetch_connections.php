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
		
		$result = array();
		$result['data'] = array();
	    $sql = "SELECT username1,username2 FROM CONNECTIONS WHERE username1 = '$username' OR username2 = '$username'";
	    $responce = mysqli_query($conn,$sql);
       		
		while($row = mysqli_fetch_array($responce))
		{
			if($username == $row['0'])
			{
			  $index['users']   = $row['1'];   
			}
			else if($username == $row['1'])
			{
			   $index['users']   = $row['0'];   
			}
			array_push($result['data'], $index);
		}
			
			$result["success"]="1";
			echo json_encode($result);
	mysqli_close($conn);
?>