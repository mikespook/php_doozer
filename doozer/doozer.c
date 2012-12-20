#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "zend_exceptions.h"
#include "php_doozer.h"

#include <sys/time.h>
#include <string.h>

#include "msg.pb-c.h"
#include "client.h"

#define DZ_VERSION_NAME "DZ_VERSION"
#define DZ_VERSION "0.1"
#define DZ_CLASS_NAME "Doozer"
#define DZ_EXCEPTION_CLASS_NAME "DoozerException"
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

#define GET_FD(this, fd) {\
    zval *z_fd_p = zend_read_property(Z_OBJCE_P(this), \
            this, ZEND_STRL(DZ_PP_FD), ZEND_ACC_PROTECTED TSRMLS_CC); \
    fd = Z_LVAL_P(z_fd_p); \
}

#define ERR_CHECK_THROW(rt, msg) {\
    if (rt == DOOZER_ERR) { \
        zend_throw_exception(doozer_exception_ce_p, \
                msg, doozer_last_errno() TSRMLS_CC); \
        return; \
    } \ 
}

#define ERR_CHECK_RETURN(rt, msg) {\
    if (rt == DOOZER_ERR) { \
        zend_throw_exception(doozer_exception_ce_p, \
                msg, doozer_last_errno() TSRMLS_CC); \
        RETURN_FALSE; \
    } \ 
}

#define GET_REV(argc, num, rev, fd, rt) { \
    if ((argc != num) || (rev <= 0)) { \
        rt = doozer_rev(fd, &rev); \
        ERR_CHECK_RETURN(rt, "Get revision error"); \
    } \
}

/* True global resources - no need for thread safety here */
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

/* {{{ proto void Doozer::connect([string $addr][,int port[, array $params]]) */
PHP_METHOD(doozer, connect) {
    char * addr = NULL;
    long lport=0;
    int port, addrlen, argc = ZEND_NUM_ARGS();
    zval *params = NULL, *this = getThis(), **z_sndto_pp, **z_rcvto_pp;
    struct timeval *tv_sndto_p = NULL, *tv_rcvto_p = NULL, tv_sndto, tv_rcvto;

    if (zend_parse_parameters(argc TSRMLS_CC, "|s!l!a", &addr,
                &addrlen, &lport, &params) == FAILURE) {
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
    ERR_CHECK_RETURN(fd, "Can not connect to Doozer server");
    zend_update_property_long(Z_OBJCE_P(this), this, DZ_PP_FD,
            strlen(DZ_PP_FD), fd TSRMLS_CC);
}/* }}}*/

/* {{{ proto void Doozer::close() */
PHP_METHOD(doozer, close) {
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
        RETURN_FALSE;
    }
    zval *this = getThis();
    int fd;
    GET_FD(this, fd)
        doozer_close(fd);
}/* }}} */ 

/* {{{ proto int Doozer::getRev() */
PHP_METHOD(doozer, getRev) {
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
        RETURN_FALSE;
    }
    zval *this = getThis();
    int fd;
    GET_FD(this, fd);
    int64_t rev;
    int rt = doozer_rev(fd, &rev);
    ERR_CHECK_RETURN(rt, "Get revision error");
    RETURN_LONG(rev);
}/* }}} */ 

/* {{{ proto int Doozer::set(string $path, string $value, int $rev=0) */
PHP_METHOD(doozer, set) {
    char *path = NULL;
    zval *val;
    int pathlen, argc = ZEND_NUM_ARGS();
    int64_t rev = 0;
    if (zend_parse_parameters(argc TSRMLS_CC, "sz|l", 
                &path, &pathlen, &val, &rev) == FAILURE) {
        RETURN_FALSE;
    }
    zval *this = getThis();
    int fd, rt;
    GET_FD(this, fd);
    GET_REV(argc, 3, rev, fd, rt);
    convert_to_string_ex(&val);
    rt = doozer_set(fd, path, (uint8_t *)Z_STRVAL_P(val), Z_STRLEN_P(val), &rev);
    ERR_CHECK_RETURN(rt, "Set value error");
    RETURN_LONG(rev);
}/* }}} */

/* {{{ proto array Doozer::get(string $path, int $rev=0) */
PHP_METHOD(doozer, get) {
    char *path = NULL;
    int pathlen, argc = ZEND_NUM_ARGS();
    int64_t rev = 0;
    if (zend_parse_parameters(argc TSRMLS_CC, "s|l", 
                &path, &pathlen, &rev) == FAILURE) {
        RETURN_FALSE;
    }
    zval *this = getThis();
    int fd, rt;
    GET_FD(this, fd);
    GET_REV(argc, 2, rev, fd, rt);
    uint8_t *val;
    size_t vallen;
    rt = doozer_get(fd, path, rev, &val, &vallen);
    ERR_CHECK_RETURN(rt, "Get value error");
    RETURN_STRINGL(val, vallen, 1);
}/* }}} */

/* {{{ proto void Doozer::delete(string $path, int $rev=0) */
PHP_METHOD(doozer, delete) {
    char *path = NULL;
    int pathlen, argc = ZEND_NUM_ARGS();
    int64_t rev = 0;
    if (zend_parse_parameters(argc TSRMLS_CC, "s|l", 
                &path, &pathlen, &rev) == FAILURE) {
        RETURN_FALSE;
    }
    zval *this = getThis();
    int fd, rt;
    GET_FD(this, fd);
    GET_REV(argc, 2, rev, fd, rt);
    rt = doozer_delete(fd, path, rev);
    ERR_CHECK_RETURN(rt, "Delete value error");
    RETURN_TRUE;
}/* }}} */

/* {{{ proto Doozer::getDir(string $path, int $offset=0, int $rev=0) */
PHP_METHOD(doozer, getDir) {
    char *path = NULL;
    int pathlen, argc = ZEND_NUM_ARGS();
    int64_t rev = 0;
    int32_t offset = 0;
    if (zend_parse_parameters(argc TSRMLS_CC, "s|ll", 
                &path, &pathlen, &offset, &rev) == FAILURE) {
        RETURN_FALSE;
    }
    zval *this = getThis();
    int fd, rt;
    GET_FD(this, fd);
    GET_REV(argc, 3, rev, fd, rt);
    char *val;
    rt = doozer_dir(fd, path, rev, offset, &val);
    ERR_CHECK_RETURN(rt, "Get directory error");
    RETURN_STRING(val, 1);
}/* }}} */

/* {{{ proto Doozer::getStat(string $path, int $rev=0) */
PHP_METHOD(doozer, getStat) {
    char *path = NULL;
    int pathlen, argc = ZEND_NUM_ARGS();
    int64_t rev = 0;
    if (zend_parse_parameters(argc TSRMLS_CC, "s|l", 
                &path, &pathlen, &rev) == FAILURE) {
        RETURN_FALSE;
    }
    zval *this = getThis();
    int fd, rt;
    GET_FD(this, fd); 
    GET_REV(argc, 2, rev, fd, rt);
    int len = 0;
    rt = doozer_stat(fd, path, &rev, &len);
    ERR_CHECK_RETURN(rt, "Stat directory error");
    switch(rev) {
        case DOOZER_STAT_MISSING:
            {
                char *buf;
                buf = emalloc(strlen(path) + 18);
                sprintf(buf, "Path[%s] is missing", path);
                zend_throw_exception(doozer_exception_ce_p, 
                        buf, DOOZER__RESPONSE__ERR__BAD_PATH TSRMLS_CC);
                efree(buf);
            }
            break;
        case DOOZER_STAT_DIR:
            RETURN_LONG(len);
            break;
        default:
            array_init(return_value);
            add_assoc_long(return_value, "len", len);
            add_assoc_long(return_value, "rev", rev); 
    }
}/* }}} */

/* {{{ proto Doozer::access(strilng $token) */
PHP_METHOD(doozer, access) {
    char *token = NULL;
    int tklen, argc = ZEND_NUM_ARGS();
    if (zend_parse_parameters(argc TSRMLS_CC, "s", &token, &tklen) == FAILURE) {
        RETURN_FALSE;
    }
    zval *this = getThis();
    int fd, rt;
    GET_FD(this, fd); 
    rt = doozer_access(fd, token);
    ERR_CHECK_RETURN(rt, "Access error");
    RETURN_TRUE;
}/* }}} */

/* {{{ proto Doozer::getHosts(int $rev=0) */

PHP_METHOD(doozer, getHosts) {
    int64_t rev = 0, noderev = 0;
    int argc = ZEND_NUM_ARGS();
    if (zend_parse_parameters(argc TSRMLS_CC, "|l", &rev) == FAILURE) {
        RETURN_FALSE;
    }
    zval *this = getThis();
    int fd, rt;
    int32_t len = 0;    
    char *subpath;
    GET_FD(this, fd);
    GET_REV(argc, 1, rev, fd, rt);
    // /ctl/node/*
    noderev = rev;
    rt = doozer_stat(fd, "/ctl/node", &noderev, &len);
    ERR_CHECK_RETURN(rt, "Stat /ctl/node error");
    array_init(return_value);
    int i;
    for(i = 0; i < len; i ++) {
        rt = doozer_dir(fd, "/ctl/node", rev, i, &subpath);
        ERR_CHECK_RETURN(rt, "Get directory error");
        char buf[14 + strlen(subpath)];
        sprintf(buf, "/ctl/node/%s/addr", subpath);
        uint8_t *val;
        size_t vallen;
        rt = doozer_get(fd, buf, rev, &val, &vallen);
        ERR_CHECK_RETURN(rt, "Get error");
        // add to return_value
        int j;
        uint8_t *end;
        for(j = 0; j < vallen; j ++) {
            end = val + j;
            if(end[0] == ':') {
                end[0] = '\0';
                break;
            }
        }
        unsigned port = atoi(end + 1);
        zval *arr;
        ALLOC_INIT_ZVAL(arr);
        array_init(arr);
        add_assoc_stringl(arr, "addr", val, strlen(val), 1);
        add_assoc_long(arr, "port", port);
        add_next_index_zval(return_value, arr);
    }
}/* }}} */

/* {{{ proto Doozer::walk(string $path, int $rev=0) */
void _visit_file(int fd, char *path, int64_t rev, zval **array) {
    uint8_t *val;
    size_t vallen;
    int rt = doozer_get(fd, path, rev, &val, &vallen);
    ERR_CHECK_THROW(rt, "Visit file error");
    add_assoc_stringl(*array, path, val, vallen, 1);
}

void _visit_dir(int fd, char *path, int64_t rev, int32_t offset, zval ** array) {
    char *val;
    int rt = doozer_dir(fd, path, rev, offset, &val);
    ERR_CHECK_THROW(rt, "Get directory error");
    int buflen;
    char *format;
    if (strcmp(path, "/") == 0) {
        buflen = 1 + strlen(val);
        format = "%s%s";
    } else {
        buflen = 1 + strlen(val) + strlen(path);
        format = "%s/%s"; 
    }
    char buf[buflen];
    sprintf(buf, format, path, val);
    _step(fd, buf, rev, array);
}

void _step(int fd, char *path, int64_t rev, zval **array) {
    int len = 0;
    int64_t noderev = rev;
    int rt = doozer_stat(fd, path, &noderev, &len);
    ERR_CHECK_THROW(rt, "Stat directory error");
    switch(noderev) {
        case DOOZER_STAT_MISSING:
            {
                char *buf;
                buf = emalloc(strlen(path) + 18);
                sprintf(buf, "Path[%s] is missing", path);
                zend_throw_exception(doozer_exception_ce_p, 
                        buf, DOOZER__RESPONSE__ERR__BAD_PATH TSRMLS_CC);
                efree(buf);
            }
            break;
        case DOOZER_STAT_DIR:
            {
                int i;
                for(i = 0; i < len; i ++) {
                    _visit_dir(fd, path, rev, i, array);
                }
            }
            break;
        default:
            _visit_file(fd, path, rev, array);
            break;
    }
}

PHP_METHOD(doozer, walk) {
    char *path = NULL;
    int pathlen, argc = ZEND_NUM_ARGS();
    int64_t rev = 0;
    if (zend_parse_parameters(argc TSRMLS_CC, "s|l", 
                &path, &pathlen, &rev) == FAILURE) {
        RETURN_FALSE;
    }
    zval *this = getThis();
    int fd, rt;
    GET_FD(this, fd);
    GET_REV(argc, 2, rev, fd, rt);
    array_init(return_value);
    _step(fd, path, rev, &return_value);
}/* }}} */

/* {{{ proto Doozer::wait(string $path, int $rev=0) */
PHP_METHOD(doozer, wait) {
    char *path = NULL;
    int pathlen, argc = ZEND_NUM_ARGS();
    int64_t rev = 0;
    if (zend_parse_parameters(argc TSRMLS_CC, "s|l", &path, &pathlen, &rev) == FAILURE) {
        RETURN_FALSE;
    }
    zval *this = getThis();
    int fd, rt;
    GET_FD(this, fd);
    GET_REV(argc, 2, rev, fd, rt);
    char *resppath;    
    uint8_t *body;
    size_t bodylen;
    int32_t flag;
    rt = doozer_wait(fd, path, &rev, &resppath, &body, &bodylen, &flag);
    ERR_CHECK_RETURN(rt, "Wait error");
    array_init(return_value);
    add_assoc_stringl(return_value, "path", resppath, strlen(resppath), 1);
    add_assoc_stringl(return_value, "value", (char *)body, bodylen, 1);
    flag = ((flag & ( DOOZER_DEL | DOOZER_SET ) & DOOZER_DEL) == 0) ?
        DOOZER_SET : DOOZER_DEL;
    add_assoc_long(return_value, "flag", flag);
}/* }}} */

/* {{{ doozer_get_exception_base */
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
}/* }}} */

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
        PHP_ME(doozer, getHosts, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(doozer, walk, NULL, ZEND_ACC_PUBLIC) 
        PHP_ME(doozer, wait, NULL, ZEND_ACC_PUBLIC)
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
    DZ_VERSION,
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
    // constants
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
    REGISTER_STRING_CONSTANT(DZ_VERSION_NAME,
            DZ_VERSION, CONST_CS | CONST_PERSISTENT);

    // errno constants
    REGISTER_LONG_CONSTANT("DZ_ERR_OTHER",
            DOOZER__RESPONSE__ERR__OTHER, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("DZ_ERR_TAG_IN_USE",
            DOOZER__RESPONSE__ERR__TAG_IN_USE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("DZ_ERR_UNKNOWN_VERB",
            DOOZER__RESPONSE__ERR__UNKNOWN_VERB, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("DZ_ERR_READONLY",
            DOOZER__RESPONSE__ERR__READONLY, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("DZ_ERR_TOO_LATE",
            DOOZER__RESPONSE__ERR__TOO_LATE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("DZ_ERR_REV_MISMATCH",
            DOOZER__RESPONSE__ERR__REV_MISMATCH, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("DZ_ERR_BAD_PATH",
            DOOZER__RESPONSE__ERR__BAD_PATH, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("DZ_ERR_MISSING_ARG",
            DOOZER__RESPONSE__ERR__MISSING_ARG, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("DZ_ERR_RANGE",
            DOOZER__RESPONSE__ERR__RANGE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("DZ_ERR_NOTDIR",
            DOOZER__RESPONSE__ERR__NOTDIR, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("DZ_ERR_ISDIR",
            DOOZER__RESPONSE__ERR__ISDIR, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("DZ_ERR_NOENT",
            DOOZER__RESPONSE__ERR__NOENT, CONST_CS | CONST_PERSISTENT);

    // class Doozer
    zend_class_entry doozer_ce;
    INIT_CLASS_ENTRY(doozer_ce, DZ_CLASS_NAME, doozer_methods);
    doozer_ce_p = zend_register_internal_class(&doozer_ce);
    zend_declare_property_null(doozer_ce_p, DZ_PP_FD, 
            sizeof(DZ_PP_FD), ZEND_ACC_PROTECTED TSRMLS_CC);

    // class DoozerException
    zend_class_entry doozer_exception_ce;
    INIT_CLASS_ENTRY(doozer_exception_ce, DZ_EXCEPTION_CLASS_NAME,
            NULL);
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

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
