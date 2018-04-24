#ifndef LEMON_LIB_SOCKET_H
#define LEMON_LIB_SOCKET_H

#include <lemon_export.h>

#ifdef __cplusplus
extern "C" {
#endif

LEMON_EXPORT
void
socket_init(struct lemon *lemon);

LEMON_EXPORT
struct lobject *
socket_module(struct lemon *lemon);

#ifdef __cplusplus
}
#endif

#endif /* LEMON_LIB_SOCKET_H */
