#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_doozer.h"

#define DOOZER_VERSION "0.1"
#define DOOZER_CLASS_NAME "Doozer"
#define DZ_PP_FD "_fd"

/* True global resources - no need for thread safety here */
static int le_doozer;
static zend_class_entry *doozer_ce_ptr;

/* {{{ proto Doozer::__construct(string $addr, int port, array $params) */
ZEND_METHOD(doozer, __construct) {

}/* }}} */

/* {{{ proto Doozer::__destruct() */
ZEND_METHOD(doozer, __destruct) {
    
}/* }}} */

/* {{{ proto Doozer::close() */
ZEND_METHOD(doozer, close) {

}/* }}} */ 

/* {{{ proto Doozer::getRev() */
ZEND_METHOD(doozer, getRev) {

}/* }}} */ 

/* {{{ proto Doozer::set(string $path, string $value, int $rev=0) */
ZEND_METHOD(doozer, set) {

}/* }}} */

/* {{{ proto Doozer::get(string $path, int $rev=0) */
ZEND_METHOD(doozer, get) {

}/* }}} */

/* {{{ proto Doozer::delete(string $path, int $rev=0) */
ZEND_METHOD(doozer, delete) {

}/* }}} */

/* {{{ proto Doozer::getDir(string $path, int $rev=0, int $offset=0) */
ZEND_METHOD(doozer, getDir) {

}/* }}} */

/* {{{ proto Doozer::getStat(string $path, int $rev=0) */
ZEND_METHOD(doozer, getStat) {

}/* }}} */

/* {{{ proto Doozer::access(strilng $path) */
ZEND_METHOD(doozer, access) {

}/* }}} */

/* {{{ proto Doozer::walk(strinlg $path, int $rev=0, int $offset=0) */
ZEND_METHOD(doozer, walk) {

}/* }}} */

/* {{{ proto Doozer::getHosts() */
ZEND_METHOD(doozer, getHosts) {

}/* }}} */

/* {{{ proto Doozer::wait(string $path, int $rev=0) */
ZEND_METHOD(doozer, wait) {

}/* }}} */



/* {{{ doozer_methods[]
*/
const zend_function_entry doozer_methods[] = {
    ZEND_ME(doozer, __construct, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(doozer, __destruct, NULL, ZEND_ACC_PUBLIC) 
    ZEND_ME(doozer, close, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(doozer, getRev, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(doozer, set, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(doozer, get, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(doozer, delete, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(doozer, getDir, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(doozer, getStat, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(doozer, access, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(doozer, walk, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(doozer, getHosts, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(doozer, wait, NULL, ZEND_ACC_PUBLIC)
    PHP_FE(doozer_info, NULL)
    PHP_FE_END
};
/* }}} */

/* {{{ doozer_module_entry
*/
zend_module_entry doozer_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "doozer",
    doozer_methods,
    PHP_MINIT(doozer),
    PHP_MSHUTDOWN(doozer),
    PHP_RINIT(doozer),		/* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(doozer),	/* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(doozer),
#if ZEND_MODULE_API_NO >= 20010901
    DOOZER_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DOOZER
ZEND_GET_MODULE(doozer)
#endif

    /* {{{ PHP_MINIT_FUNCTION
    */
PHP_MINIT_FUNCTION(doozer)
{
    zend_class_entry doozer_ce;
    INIT_CLASS_ENTRY(doozer_ce, DOOZER_CLASS_NAME, NULL);
    doozer_ce_ptr = zend_register_internal_class(&doozer_ce);
    zend_declare_property_string(doozer_ce_ptr,
                          "addr", strlen("addr"),
                          "127.0.0.1", ZEND_ACC_PUBLIC);
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
*/
PHP_MSHUTDOWN_FUNCTION(doozer)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION
*/
PHP_RINIT_FUNCTION(doozer)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION
*/
PHP_RSHUTDOWN_FUNCTION(doozer)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
*/
PHP_MINFO_FUNCTION(doozer)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "doozer support", "enabled");
    php_info_print_table_end();
}
/* }}} */


/* {{{ proto string doozer_info()
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(doozer_info)
{
    array_init(return_value);
    add_assoc_string(return_value, "version", DOOZER_VERSION, strlen(DOOZER_VERSION));
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
