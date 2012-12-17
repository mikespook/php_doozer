--TEST--
Check for doozer presence
--SKIPIF--
<?php if (!extension_loaded("doozer")) print "skip"; ?>
--FILE--
<?php 
if (!class_exists("Doozer")) {
    exit();
}
$doozer = new Doozer('127.0.0.1', 8046, array());

if (!method_exists($doozer, 'getDir')) {
    exit();    
}
$info = doozer_info();
if (isset($info['version'])) {
    echo $info['version'];   
}
?>
--EXPECT--
0.1
