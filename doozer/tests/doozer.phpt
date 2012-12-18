--TEST--
Check for doozer methods
--SKIPIF--
<?php if (!extension_loaded("doozer")) print "skip"; ?>
--FILE--
<?php 
if (!class_exists("Doozer")) {
    exit();
}
$doozer = new Doozer();
$doozer->connect('127.0.0.1', 8046, array(DZ_SEND_TIMEOUT => 3000, DZ_RECEIVE_TIMEOUT => 3000));
$doozer->close();
$doozer->connect('127.0.0.1', 8046);
$doozer->close();
$doozer->connect('127.0.0.1');
$doozer->close();
$doozer->connect();
$doozer->close();
?>
--EXPECT--
