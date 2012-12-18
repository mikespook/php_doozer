PHP_ARG_ENABLE(doozer, for doozer support,
[  --enable-doozer              Enable doozer support])

PHP_ARG_WITH(protobufc, for protobuf-c support,
[  --with-protobufc[=DIR]        Include protobuf-c support])


if test "$PHP_DOOZER" != "no"; then
    if test -r $PHP_PROTOBUFC/include/google/protobuf-c/protobuf-c.h; then
        PROTOBUF_DIR=$PHP_PROTOBUFC
    else
        AC_MSG_CHECKING(for protobuf-c in default path)
        for i in /usr/local /usr; do
            if test -r $i/include/google/protobuf-c/protobuf-c.h; then
                PROTOBUF_DIR=$i
                AC_MSG_RESULT(found in $i)
                break
            fi
        done
    fi

    if test -z "$PROTOBUF_DIR"; then
        AC_MSG_RESULT(not found)
        AC_MSG_ERROR(Please reinstall the protobuf-c distribution - protobuf-c.h should be in <protobuf-dir>/include/google/protobuf-c/)
    fi

    PHP_ADD_INCLUDE($PROTOBUF_DIR/include)
    PHP_EVAL_LIBLINE($PROTOBUF_DIR, DOOZER_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(protobufc, $PROTOBUF_DIR/$PHP_LIBDIR, DOOZER_SHARED_LIBADD)
    PHP_NEW_EXTENSION(doozer, msg.pb-c.c client.c doozer.c, $ext_shared)
    CFLAGS="$CFLAGS -Wall -g"
fi
