
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_doozer.h"
#include "doozer_exception.h"

zend_class_entry *doozer_exception_ce;

static function_entry doozer_exception_methods[] = {
    PHP_ME(Doozer, close, NULL, ZEND_ACC_PUBLIC)

}


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
