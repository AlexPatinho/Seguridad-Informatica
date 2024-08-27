<?php

$host_db = 'localhost:3306/phishing';
$user_db = 'root';
$pass_db = '';
$db_name = 'phishing';
$tbl_name = 'login';


$connection = new mysqli($host_db, $user_db, $pass_db, $db_name);

if ($connection->connect_error){
    die("La conexión a la base de datos falló: " . $connection->connect_error);
}else{
    echo "Conexión exitosa";
}

//Prueba de insersion
// $sql = "INSERT INTO login (username, password) VALUES ('edsongay', '1234')";
// $result = $connection->query($sql);

?>

