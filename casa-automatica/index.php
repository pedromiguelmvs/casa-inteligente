<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>Document</title>
</head>
<body>
    <div>
        <label class="label">LED da Piscina</label>
        <form class="form-container" method="POST">        
            <button class="button" type="submit" value=0 name="led_piscina">Desligar</button>
            <button class="button" type="submit" value=1 name="led_piscina">Ligar</button>
        </form>
    </div> 
    <div>
        <label class="label">Buzzer</label>
        <form class="form-container" method="POST">        
            <button class="button" type="submit" value=2 name="buzzer">Desligar</button>
            <button class="button" type="submit" value=3 name="buzzer">Ligar</button>
        </form>
    </div> 
    <div>
        <label class="label">LED do Quarto</label>
        <form class="form-container" method="POST">        
            <button class="button" type="submit" value=4 name="led_quarto">Desligar</button>
            <button class="button" type="submit" value=5 name="led_quarto">Ligar</button>
        </form>
    </div>    
</body>
</html>

<div style="display: none">
<?php 

    /**
     * id 0-1: piscina
     * id 2-3: buzzer
     * id 3-4: led do quarto     
     */

    $username = "root";
    $password = "";

    if (isset($_POST["led_piscina"])) {
        $led = $_POST["led_piscina"];
        $id = 'led_piscina';

        try {
            $pdo = new PDO('mysql:host=localhost;dbname=casa_automatica', $username, $password);
            $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        
            $stmt = $pdo->prepare('UPDATE recursos SET recurso = :led_casa WHERE id = :id');
            $stmt->bindValue(":led_casa", $led);
            $stmt->bindValue(":id", $id);
            $stmt->execute();
        
            echo $stmt->rowCount();
        } catch(PDOException $e) {
            echo 'Error: ' . $e->getMessage();
        }
    }

    if (isset($_POST["buzzer"])) {
        $buzzer = $_POST["buzzer"];
        $id = 'buzzer';

        try {
            $pdo = new PDO('mysql:host=localhost;dbname=casa_automatica', $username, $password);
            $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        
            $stmt = $pdo->prepare('UPDATE recursos SET recurso = :buzzer WHERE id = :id');
            $stmt->bindValue(":buzzer", $buzzer);
            $stmt->bindValue(":id", $id);
            $stmt->execute();
        
            echo $stmt->rowCount();
        } catch(PDOException $e) {
            echo 'Error: ' . $e->getMessage();
        }
    }

    if (isset($_POST["led_quarto"])) {
        $led_quarto = $_POST["led_quarto"];
        $id = 'led_quarto';

        try {
            $pdo = new PDO('mysql:host=localhost;dbname=casa_automatica', $username, $password);
            $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        
            $stmt = $pdo->prepare('UPDATE recursos SET recurso = :led_quarto WHERE id = :id');
            $stmt->bindValue(":led_quarto", $led_quarto);
            $stmt->bindValue(":id", $id);
            $stmt->execute();
        
            echo $stmt->rowCount();
        } catch(PDOException $e) {
            echo 'Error: ' . $e->getMessage();
        }
    }

?>
</div>