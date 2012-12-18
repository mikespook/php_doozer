#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_doozer.h"
#include "sys/time.h"
#include "client.h"

#define DOOZER_VERSION "0.1"
#define DOOZER_CLASS_NAME "Doozer"
#define DOOZER_EXCEPTION_CLASS_NAME "DoozerException"
#define DZ_PP_FD "_fd"

#define DZ_SEND_TIMEOUT_NAME "DZ_SEND_TIMEOUT"
#define DZ_RECEIVE_TIMEOUT_NAME "DZ_RECEIVE_TIMEOUT"
#define DZ_PCONNECT_NAME "DZ_PCONNECT"
#define DZ_DEFAULT_ADDR_NAME "DZ_DEFAULT_ADDR"
#define DZ_DEFAULT_PORT_NAME "DZ_DEFAULT_PORT"

#define DZ_SEND_TIMEOUT "SEND_TIMEOUT"
#define DZ_RECEIVE_TIMEOUT "RECEIVE_TIMEOUT"
#define DZ_PCONNECT "PCONNECT"
#define DZ_DEFAULT_ADDR "127.0.0.1"
#define DZ_DEFAULT_PORT 8046

/* True global resources - no need for thread safety here */
static int le_doozer;
static zend_class_entry *doozer_ce_p;
static zend_class_entry *doozer_exception_ce_p;
zend_class_entry *spl_ce_RuntimeException = NULL;

/* {{{ proto Doozer::__construct() */
PHP_METHOD(doozer, __construct) {
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
        RETURN_FALSE;
    }
}/* }}} */

/* {{{ proto Doozer::__destruct() */
PHP_METHOD(doozer, __destruct) {
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
        RETURN_FALSE;
    }  
}/* }}} */

/* {{{ proto Doozer::connect([string $addr][,int port[, array $params]]) */
PHP_METHOD(doozer, connect) {
    char * addr = NULL;
    long lport=0;
    int port, addrlen, argc = ZEND_NUM_ARGS();
    zval *params = NULL, *this = getThis(), **z_sndto_pp, **z_rcvto_pp, **z_pconn_pp;
    struct timeval *tv_sndto_p = NULL, *tv_rcvto_p = NULL, tv_sndto, tv_rcvto;

    if (zend_parse_parameters(argc TSRMLS_CC, "|s!l!a", &addr,
                &addrlen, &lport, &params) == FAILURE) {
        ZVAL_NULL(this);
        RETURN_FALSE;
    }
    port = (int)lport;
    switch(argc) {
        case 0:
            addr = DZ_DEFAULT_ADDR;
        case 1:
            port = DZ_DEFAULT_PORT;
        case 2:
            break;
        case 3:
            // send timeout
            if (zend_hash_find(Z_ARRVAL_P(params), 
                        DZ_SEND_TIMEOUT, sizeof(DZ_SEND_TIMEOUT), 
                        (void **)&z_sndto_pp) == SUCCESS) {
                long timeout = Z_LVAL_PP(z_sndto_pp);
                tv_sndto.tv_sec = timeout ? timeout / 1000 : 0;
                tv_sndto.tv_usec = timeout ? (timeout * 1000) % 1000000 : 0;
                tv_sndto_p = &tv_sndto;
            } 
            // receive timeout
            if (zend_hash_find(Z_ARRVAL_P(params), 
                        DZ_RECEIVE_TIMEOUT, sizeof(DZ_RECEIVE_TIMEOUT), 
                        (void **)&z_rcvto_pp) == SUCCESS) {
                SEPARATE_ZVAL((z_rcvto_pp));
                convert_to_long(*z_rcvto_pp);
                long timeout = Z_LVAL_PP(z_rcvto_pp);
                tv_rcvto.tv_sec = timeout ? timeout / 1000 : 0;
                tv_rcvto.tv_usec = timeout ? (timeout * 1000) % 1000000 : 0;
                tv_rcvto_p = &tv_rcvto;
            }
            break;
    }
    int fd = doozer_connect(addr, port, tv_sndto_p, tv_rcvto_p);
}/* }}}*/

/* {{{ proto Doozer::close() */
PHP_METHOD(doozer, close) {
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
        RETURN_FALSE;
    }  
}/* }}} */ 

/* {{{ proto Doozer::getRev() */
PHP_METHOD(doozer, getRev) {

}/* }}} */ 

/* {{{ proto Doozer::set(string $path, string $value, int $rev=0) */
PHP_METHOD(doozer, set) {

}/* }}} */

/* {{{ proto Doozer::get(string $path, int $rev=0) */
PHP_METHOD(doozer, get) {

}/* }}} */

/* {{{ proto Doozer::delete(string $path, int $rev=0) */
PHP_METHOD(doozer, delete) {

}/* }}} */

/* {{{ proto Doozer::getDir(string $path, int $rev=0, int $offset=0) */
PHP_METHOD(doozer, getDir) {

}/* }}} */

/* {{{ proto Doozer::getStat(string $path, int $rev=0) */
PHP_METHOD(doozer, getStat) {

}/* }}} */

/* {{{ proto Doozer::access(strilng $path) */
PHP_METHOD(doozer, access) {

}/* }}} */

/* {{{ proto Doozer::walk(strinlg $path, int $rev=0, int $offset=0) */
PHP_METHOD(doozer, walk) {

}/* }}} */

/* {{{ proto Doozer::getHosts() */
PHP_METHOD(doozer, getHosts) {

}/* }}} */

/* {{{ proto Doozer::wait(string $path, int $rev=0) */
PHP_METHOD(doozer, wait) {

}/* }}} */

PHPAPI zend_class_entry *doozer_get_exception_base(int root TSRMLS_DC) {
#if HAVE_SPL
    if (!root) {
        if (!spl_ce_RuntimeException) {
            zend_class_entry **pce;
            if (zend_hash_find(CG(class_table), "runtimeexception",
                        sizeof("RuntimeException"), (void **) &pce) == SUCCESS) {
                spl_ce_RuntimeException = *pce;
                return *pce;
            }
        } else {
            return spl_ce_RuntimeException;
        }
    }
#endif
    return (zend_class_entry *)zend_exception_get_default(TSRMLS_C);
}

/* {{{ doozer_methods[]
*/
const zend_function_entry doozer_methods[] = {
    PHP_ME(doozer, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(doozer, __destruct, NULL, ZEND_ACC_PUBLIC) 
        PHP_ME(doozer, connect, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(doozer, close, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(doozer, getRev, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(doozer, set, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(doozer, get, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(doozer, delete, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(doozer, getDir, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(doozer, getStat, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(doozer, access, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(doozer, walk, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(doozer, getHosts, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(doozer, wait, NULL, ZEND_ACC_PUBLIC)
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
    REGISTER_STRING_CONSTANT(DZ_SEND_TIMEOUT_NAME,
            DZ_SEND_TIMEOUT, CONST_CS | CONST_PERSISTENT);
    REGISTER_STRING_CONSTANT(DZ_RECEIVE_TIMEOUT_NAME,
            DZ_RECEIVE_TIMEOUT, CONST_CS | CONST_PERSISTENT); 
    REGISTER_STRING_CONSTANT(DZ_PCONNECT_NAME,
            DZ_PCONNECT, CONST_CS | CONST_PERSISTENT);  
    REGISTER_STRING_CONSTANT(DZ_DEFAULT_ADDR_NAME,
            DZ_DEFAULT_ADDR, CONST_CS | CONST_PERSISTENT);  
    REGISTER_LONG_CONSTANT(DZ_DEFAULT_PORT_NAME,
            DZ_DEFAULT_PORT, CONST_CS | CONST_PERSISTENT);  

    zend_class_entry doozer_ce;
    INIT_CLASS_ENTRY(doozer_ce, DOOZER_CLASS_NAME, doozer_methods);
    doozer_ce_p = zend_register_internal_class(&doozer_ce);

    zend_class_entry doozer_exception_ce;
    INIT_CLASS_ENTRY(doozer_exception_ce, DOOZER_EXCEPTION_CLASS_NAME, NULL);
    doozer_exception_ce_p = zend_register_internal_class_ex(
            &doozer_exception_ce,
            doozer_get_exception_base(0 TSRMLS_CC),
            NULL TSRMLS_CC
            );
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
