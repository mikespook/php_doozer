#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_doozer.h"
#include "msg.pb-c.h"

#define DOOZER_VERSION "0.1"
#define DOOZER_CLASS_NAME "Doozer"

/* True global resources - no need for thread safety here */
static int le_doozer;
static zend_class_entry *doozer_ce_ptr;

/* {{{ doozer_functions[]
*/
const zend_function_entry doozer_functions[] = {
    PHP_FE(doozer_info, NULL)
    PHP_FE_END	/* Must be the last line in doozer_functions[] */
};
/* }}} */

/* {{{ doozer_module_entry
*/
zend_module_entry doozer_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "doozer",
    doozer_functions,
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
