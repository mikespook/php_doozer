
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

PHP_FUNCTION(confirm_doozer_compiled);	/* For testing, remove later. */

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(doozer)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(doozer)
*/

/* In every utility function you add that needs to use variables 
   in php_doozer_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as DOOZER_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define DOOZER_G(v) TSRMG(doozer_globals_id, zend_doozer_globals *, v)
#else
#define DOOZER_G(v) (doozer_globals.v)
#endif

#endif	/* PHP_DOOZER_H */

