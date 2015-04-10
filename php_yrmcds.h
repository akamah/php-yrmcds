// (C) 2013 Cybozu.

#pragma once

#ifndef PHP_YRMCDS_H
#define PHP_YRMCDS_H

#include <yrmcds.h>

extern zend_module_entry yrmcds_module_entry;
#define phpext_yrmcds_ptr &yrmcds_module_entry

#ifdef PHP_WIN32
#   define PHP_YRMCDS_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#   define PHP_YRMCDS_API __attribute__ ((visibility("default")))
#else
#   define PHP_YRMCDS_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_YRMCDS_VERSION "1.0.3"
#define PHP_YRMCDS_HASH_KEY "yrmcds:%s"

typedef struct {
    const char* persist_id;
    size_t reference_count;
    yrmcds res;
} php_yrmcds_t;

#define PHP_YRMCDS_FETCH(yrmcdsp,zp)                                    \
    ZEND_FETCH_RESOURCE((yrmcdsp), yrmcds*, &(zp), -1, "yrmcds", le_yrmcds)

ZEND_BEGIN_MODULE_GLOBALS(yrmcds)
    long compression_threshold;
    long default_timeout;
    zend_bool detect_stale_connection;
ZEND_END_MODULE_GLOBALS(yrmcds)

#ifdef ZTS
#define YRMCDS_G(v) TSRMG(yrmcds_globals_id, zend_yrmcds_globals *, v)
#else
#define YRMCDS_G(v) (yrmcds_globals.v)
#endif

#endif  /* PHP_YRMCDS_H */
