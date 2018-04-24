#ifndef LEMON_LSTRING_H
#define LEMON_LSTRING_H

#include <lemon_export.h>
#include <lobject.h>

struct lstring {
	struct lobject object;

	long length;

	/* lstring is dynamic size */
	char buffer[1];
};

#ifdef __cplusplus
extern "C" {
#endif

LEMON_EXPORT
const char *
lstring_to_cstr(struct lemon *lemon, struct lobject *object);

LEMON_EXPORT
char *
lstring_buffer(struct lemon *lemon, struct lobject *object);

LEMON_EXPORT
long
lstring_length(struct lemon *lemon, struct lobject *object);

LEMON_EXPORT
void *
lstring_create(struct lemon *lemon, const char *buffer, long length);

LEMON_EXPORT
struct ltype *
lstring_type_create(struct lemon *);

#ifdef __cplusplus
}
#endif

#endif /* LEMON_LSTRING_H */
