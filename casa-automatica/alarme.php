<?php 
    $username = "id16184140_root";
    $password = "a=U9n*mi>ND/iSJQS";

    try {
        $pdo = new PDO('mysql:host=localhost;dbname=id16184140_casa_automatica', $username, $password);
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);        

        $stmt5 = $pdo->prepare('SELECT recurso FROM recursos WHERE id = :id');
        $stmt5->bindValue(":id", 'alarme');
        $stmt5->execute();

        while($user = $stmt5->fetch()){
            echo $user['recurso'];
        }
                
    } catch(PDOException $e) {
        echo 'Error: ' . $e->getMessage();
    }
?>