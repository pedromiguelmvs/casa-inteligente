<?php 
    $username = "id16184140_root";
    $password = "a=U9n*mi>ND/iSJQS";

    try {
        $pdo = new PDO('mysql:host=localhost;dbname=id16184140_casa_automatica', $username, $password);
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    
        $stmt = $pdo->prepare('SELECT recurso FROM recursos WHERE id = :id');
        $stmt->bindValue(":id", 'led_piscina');
        $stmt->execute();

        while($user = $stmt->fetch()){
            echo $user['recurso'];
        }        
                
    } catch(PDOException $e) {
        echo 'Error: ' . $e->getMessage();
    }
?>