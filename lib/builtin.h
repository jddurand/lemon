#ifndef LEMON_BUILTIN_H
#define LEMON_BUILTIN_H

struct lemon;
struct lobject;

#include <lemon_export.h>

#ifdef __cplusplus
extern "C" {
#endif

LEMON_EXPORT
void
builtin_init(struct lemon *lemon);

struct lobject *
builtin_map(struct lemon *lemon,
            struct lobject *self,
            int argc, struct lobject *argv[]);

#ifdef __cplusplus
}
#endif

#endif /* LEMON_BUILTIN_H */
