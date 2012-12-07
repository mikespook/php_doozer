PHP_ARG_ENABLE(doozer, for doozer support,
[  --enable-doozer            Enable doozer support])

if test "$PHP_DOOZER" != "no"; then
dnl TODO: check the protobuf library & headers
PHP_NEW_EXTENSION(doozer, doozer.c doozer_exception.c, $ext_shared)
fi
