#ifndef LEMON_LARRAY_H
#define LEMON_LARRAY_H

#include <lemon_export.h>
#include <lobject.h>

struct larray {
	struct lobject object;

	int alloc;
	int count;
	struct lobject **items;
};

#ifdef __cplusplus
extern "C" {
#endif

LEMON_EXPORT
struct lobject *
larray_append(struct lemon *lemon,
              struct lobject *self,
              int argc, struct lobject *argv[]);

LEMON_EXPORT
struct lobject *
larray_get_item(struct lemon *lemon,
                struct lobject *self,
                long i);

LEMON_EXPORT
struct lobject *
larray_set_item(struct lemon *lemon,
                struct lobject *self,
                long i,
                struct lobject *value);

LEMON_EXPORT
struct lobject *
larray_del_item(struct lemon *lemon,
                struct lobject *self,
                long i);

LEMON_EXPORT
long
larray_length(struct lemon *lemon, struct lobject *self);

LEMON_EXPORT
void *
larray_create(struct lemon *lemon, int count, struct lobject *items[]);

LEMON_EXPORT
struct ltype *
larray_type_create(struct lemon *lemon);

#ifdef __cplusplus
}
#endif

#endif /* LEMON_LARRAY_H */
