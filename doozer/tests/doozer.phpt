--TEST--
Check for doozer methods
--SKIPIF--
<?php if (!extension_loaded("doozer")) print "skip"; ?>
--FILE--
<?php 
if (!class_exists("Doozer")) {
    exit();
}

function testmsg($str) {
    echo "{$str}\n";
}

$doozer = new Doozer();
$doozer->connect('127.0.0.1', 8046, array(DZ_SEND_TIMEOUT => 3000, DZ_RECEIVE_TIMEOUT => 3000));
$doozer->close();
$doozer->connect('127.0.0.1', 8046);
$doozer->close();
$doozer->connect('127.0.0.1');
$doozer->close();
$doozer->connect();
$rev = $doozer->getRev();

// will throw an exception
try {
    echo $doozer->get('/');
} catch(DoozerException $e) {
    testmsg($e->getCode());
}

if($doozer->set('/test', 'foobar') > $rev) {
    testmsg('set');
}
testmsg($doozer->get('/test'));
if ($doozer->delete('/test')) {
    testmsg('delete');
}

testmsg($doozer->getDir('/'));

$stat = $doozer->getStat('/ctl/cal/0');
testmsg($stat['rev']);
testmsg($stat['len']);
testmsg($doozer->getStat('/ctl'));
try {
    echo $doozer->getStat('/not/exists');
} catch(DoozerException $e) {
    testmsg($e->getCode());
}

testmsg($doozer->access('foobar'));
testmsg($doozer->getHosts());
$doozer->close();
echo 'END';
?>
--EXPECT--
21
set
foobar
delete
ctl
5
16
3
6
1
Array
END
