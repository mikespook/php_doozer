PHP Doozer extension
==========

A [Doozer](https://github.com/ha/doozerd) extension for PHP

Dependencies
============

[PHP 5.3.0 and above](http://www.php.net)

[Protobuf-C](http://code.google.com/p/protobuf-c/)

Usage
=====

```php
$doozer = new Doozer();
$doozer->connect('127.0.0.1', 8046, array(DZ_SEND_TIMEOUT => 3000, DZ_RECEIVE_TIMEOUT => 3000));
$rev = $doozer->getRev();
try {
    echo $doozer->get('/');
} catch(DoozerException $e) {
    echo "Can not call get() with a dir.\n";
}
echo $doozer->set('/test', 'foobar');
echo $doozer->get('/test');
echo $doozer->delete('/test');
echo $doozer->getDir('/');
var_dump($doozer->getStat('/ctl/cal/0'));
var_dump($doozer->getStat('/ctl'));
try {
    echo $doozer->getStat('/not/exists');
} catch(DoozerException $e) {
    echo "The path is not exist.\n"
}
echo $doozer->access('foobar');
var_dump($doozer->getHosts());
var_dump($doozer->walk('/'));
$doozer->close();
```

Authors
=======
Xing Xing <mikespook@gmail.com>

Open Source - MIT Software License
==================================
Copyright (c) 2012 Xing Xing

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
