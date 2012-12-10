
#ifndef PHP_DOOZER_H
#define PHP_DOOZER_H

extern zend_module_entry doozer_module_entry;
#define phpext_doozer_ptr &doozer_module_entry

#ifdef PHP_WIN32
#	define PHP_DOOZER_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_DOOZER_API __attribute__ ((visibility("default")))
#else
#	define PHP_DOOZER_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(doozer);
PHP_MSHUTDOWN_FUNCTION(doozer);
PHP_RINIT_FUNCTION(doozer);
PHP_RSHUTDOWN_FUNCTION(doozer);
PHP_MINFO_FUNCTION(doozer);

PHP_FUNCTION(doozer_info);

ZEND_BEGIN_MODULE_GLOBALS(doozer)
    /* TODO Put connection pool here*/
ZEND_END_MODULE_GLOBALS(doozer)

#ifdef ZTS
#define DOOZER_G(v) TSRMG(doozer_globals_id, zend_doozer_globals *, v)
#else
#define DOOZER_G(v) (doozer_globals.v)
#endif

#endif	/* PHP_DOOZER_H */

