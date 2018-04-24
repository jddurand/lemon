#ifndef LEMON_LIB_OS_H
#define LEMON_LIB_OS_H

#include <lemon_export.h>
#include "lobject.h"

#ifdef __cplusplus
extern "C" {
#endif

LEMON_EXPORT
struct lobject *
os_module(struct lemon *lemon);

#ifdef __cplusplus
}
#endif

#endif /* LEMON_LIB_OS_H */
