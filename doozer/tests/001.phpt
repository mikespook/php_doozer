--TEST--
Check for doozer presence
--SKIPIF--
<?php if (!extension_loaded("doozer")) print "skip"; ?>
--FILE--
<?php 
echo doozer_info();
?>
--EXPECT--
Version: 0.1
