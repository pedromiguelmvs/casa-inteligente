<?php 
    $username = "root";
    $password = "";

    try {
        $pdo = new PDO('mysql:host=localhost;dbname=casa_automatica', $username, $password);
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    
        $stmt = $pdo->prepare('SELECT recurso FROM recursos WHERE id = :id');
        $stmt->bindValue(":id", 'led_piscina');
        $stmt->execute();

        while($user = $stmt->fetch()){
            echo $user['recurso'];
        }

        $stmt2 = $pdo->prepare('SELECT recurso FROM recursos WHERE id = :id');
        $stmt2->bindValue(":id", 'buzzer');
        $stmt2->execute();

        while($user = $stmt2->fetch()){
            echo $user['recurso'];
        }

        $stmt3 = $pdo->prepare('SELECT recurso FROM recursos WHERE id = :id');
        $stmt3->bindValue(":id", 'led_quarto');
        $stmt3->execute();

        while($user = $stmt3->fetch()){
            echo $user['recurso'];
        }
                
    } catch(PDOException $e) {
        echo 'Error: ' . $e->getMessage();
    }
?>