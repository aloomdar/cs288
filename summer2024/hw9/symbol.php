<?php
require 'vendor/autoload.php';
$client = new MongoDB\Client();
$db = $client->stocks;
$collection = $db->info;

$result = $collection->find([], ['sort' => ['Symbol' => 1]]);

?>
<!DOCTYPE html>
<html>

<body>
    <center>
    <table border="1">
        <tr>
            <th><a href="symbol.php">Symbol</a></th>
            <th><a href="name.php">Name</a></th>
            <th><a href="price.php">Price (Intraday)</a></th>
            <th><a href="change.php">Change</a></th>
            <th><a href="volume.php">Volume (Millions)</a></th>
        </tr>
        <?php
        foreach ($result as $doc) {
            echo "<tr>";
            foreach ($doc as $key => $value) {
                if ($key != "_id") {
                    echo "<td> {$value} </td>";
                }
            }
            echo "<tr>";
        }
        ?>
    </table>
    <h2><a href="31609560_Problem1.php">Go Back</a></h2>
    </center>
</html>
