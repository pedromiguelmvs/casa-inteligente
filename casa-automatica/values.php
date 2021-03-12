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

        $stmt4 = $pdo->prepare('SELECT recurso FROM recursos WHERE id = :id');
        $stmt4->bindValue(":id", 'ldr');
        $stmt4->execute();

        while($user = $stmt4->fetch()){
            echo $user['recurso'];
        }

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