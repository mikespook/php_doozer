dnl $Id$
dnl config.m4 for extension doozer

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(doozer, for doozer support,
dnl Make sure that the comment is aligned:
dnl [  --with-doozer             Include doozer support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(doozer, whether to enable doozer support,
dnl Make sure that the comment is aligned:
[  --enable-doozer           Enable doozer support])

if test "$PHP_DOOZER" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-doozer -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/doozer.h"  # you most likely want to change this
  dnl if test -r $PHP_DOOZER/$SEARCH_FOR; then # path given as parameter
  dnl   DOOZER_DIR=$PHP_DOOZER
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for doozer files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       DOOZER_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$DOOZER_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the doozer distribution])
  dnl fi

  dnl # --with-doozer -> add include path
  dnl PHP_ADD_INCLUDE($DOOZER_DIR/include)

  dnl # --with-doozer -> check for lib and symbol presence
  dnl LIBNAME=doozer # you may want to change this
  dnl LIBSYMBOL=doozer # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DOOZER_DIR/lib, DOOZER_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_DOOZERLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong doozer lib version or lib not found])
  dnl ],[
  dnl   -L$DOOZER_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(DOOZER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(doozer, doozer.c, $ext_shared)
fi
