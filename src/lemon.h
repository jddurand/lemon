#ifndef LEMON_LEMON_H
#define LEMON_LEMON_H

#include <stddef.h>
#include <stdint.h>
#include <lemon_export.h>

#include "ltype.h"
#include "lframe.h"
#include "lfunction.h"

#define LEMON_NAME_MAX 256

struct lobject;

struct lemon {
	long l_random;

	void *l_arena;
	void *l_input;
	void *l_lexer;
	void *l_scope;
	void *l_global;
	void *l_generator;
	void *l_allocator;
	void *l_collector;
	void *l_machine;

	void *l_try_enclosing;
	void *l_loop_enclosing;
	void *l_stmt_enclosing;
	void *l_space_enclosing; /* variable space (function and module) */

	/*
	 * lobject->l_method -> ltype hashtable
	 */
	void *l_types_slots;
	unsigned long l_types_count;
	unsigned long l_types_length;

	/*
	 * use lobject->method and ltype->method to identify lobject's type
	 */
	struct ltype *l_type_type;
	struct ltype *l_karg_type;
	struct ltype *l_varg_type;
	struct ltype *l_vkarg_type;
	struct ltype *l_table_type;
	struct ltype *l_super_type;
	struct ltype *l_class_type;
	struct ltype *l_frame_type;
	struct ltype *l_array_type;
	struct ltype *l_number_type;
	struct ltype *l_string_type;
	struct ltype *l_module_type;
	struct ltype *l_integer_type;
	struct ltype *l_boolean_type;
	struct ltype *l_function_type;
	struct ltype *l_instance_type;
	struct ltype *l_iterator_type;
	struct ltype *l_coroutine_type;
	struct ltype *l_exception_type;
	struct ltype *l_dictionary_type;
	struct ltype *l_continuation_type;

	struct lobject *l_nil;
	struct lobject *l_true;
	struct lobject *l_false;
	struct lobject *l_sentinel;

	struct lobject *l_modules;

	struct lobject *l_base_error;
	struct lobject *l_type_error;
	struct lobject *l_item_error;
	struct lobject *l_memory_error;
	struct lobject *l_runtime_error;
	struct lobject *l_argument_error;
	struct lobject *l_attribute_error;
	struct lobject *l_arithmetic_error;
	struct lobject *l_not_callable_error;
	struct lobject *l_not_iterable_error;
	struct lobject *l_not_implemented_error;

	/*
	 * this is an memory_error instance
	 */
	struct lobject *l_out_of_memory;

	struct lobject *l_empty_string;
	struct lobject *l_space_string;
	struct lobject *l_add_string;
	struct lobject *l_sub_string;
	struct lobject *l_mul_string;
	struct lobject *l_div_string;
	struct lobject *l_mod_string;
	struct lobject *l_call_string;
	struct lobject *l_get_item_string;
	struct lobject *l_set_item_string;
	struct lobject *l_get_attr_string;
	struct lobject *l_set_attr_string;
	struct lobject *l_del_attr_string;
	struct lobject *l_init_string;
	struct lobject *l_string_string;
	struct lobject *l_array_string;
	struct lobject *l_next_string;
	struct lobject *l_iterator_string;
};

#ifdef __cplusplus
extern "C" {
#endif

LEMON_EXPORT
struct lemon *
lemon_create();

LEMON_EXPORT
void
lemon_destroy(struct lemon *lemon);

LEMON_EXPORT
int
lemon_compile(struct lemon *lemon);

LEMON_EXPORT
int
lemon_input_set_file(struct lemon *lemon,
                     const char *filename);

LEMON_EXPORT
int
lemon_input_set_buffer(struct lemon *lemon,
                       const char *filename,
                       char *buffer,
                       int length);

LEMON_EXPORT
void *
lemon_allocator_alloc(struct lemon *lemon, long size);

LEMON_EXPORT
void
lemon_allocator_free(struct lemon *lemon, void *ptr);

LEMON_EXPORT
void *
lemon_allocator_realloc(struct lemon *lemon, void *ptr, long size);

LEMON_EXPORT
void
lemon_mark_types(struct lemon *lemon);

LEMON_EXPORT
void
lemon_mark_errors(struct lemon *lemon);

LEMON_EXPORT
void
lemon_mark_strings(struct lemon *lemon);

LEMON_EXPORT
struct lobject *
lemon_get_type(struct lemon *lemon, lobject_method_t method);

LEMON_EXPORT
int
lemon_add_type(struct lemon *lemon, struct ltype *type);

LEMON_EXPORT
void
lemon_del_type(struct lemon *lemon, struct ltype *type);

LEMON_EXPORT
struct lobject *
lemon_add_global(struct lemon *lemon, const char *name, void *object);

LEMON_EXPORT
void
lemon_machine_reset(struct lemon *lemon);

LEMON_EXPORT
int
lemon_machine_halted(struct lemon *lemon);

LEMON_EXPORT
struct lobject *
lemon_machine_throw(struct lemon *lemon,
                    struct lobject *lobject);

LEMON_EXPORT
int
lemon_machine_get_pc(struct lemon *lemon);

LEMON_EXPORT
void
lemon_machine_set_pc(struct lemon *lemon, int pc);

LEMON_EXPORT
int
lemon_machine_get_fp(struct lemon *lemon);

LEMON_EXPORT
void
lemon_machine_set_fp(struct lemon *lemon, int fp);

LEMON_EXPORT
int
lemon_machine_get_sp(struct lemon *lemon);

LEMON_EXPORT
void
lemon_machine_set_sp(struct lemon *lemon, int sp);

/*
 * first function frame's ra (machine->frame[1]->ra)
 */
LEMON_EXPORT
int
lemon_machine_get_ra(struct lemon *lemon);

LEMON_EXPORT
void
lemon_machine_set_ra(struct lemon *lemon, int ra);

LEMON_EXPORT
struct lobject *
lemon_machine_get_stack(struct lemon *lemon, int sp);

LEMON_EXPORT
struct lobject *
lemon_machine_pop_object(struct lemon *lemon);

LEMON_EXPORT
void
lemon_machine_push_object(struct lemon *lemon,
                          struct lobject *object);

LEMON_EXPORT
struct lframe *
lemon_machine_get_frame(struct lemon *lemon, int fp);

LEMON_EXPORT
void
lemon_machine_set_frame(struct lemon *lemon, int fp, struct lframe *frame);

/*
 * 1. create frame
 * 2. store frame
 * 3. push frame
 *
 * use `lemon_machine_return_frame' when C function return
 */
LEMON_EXPORT
struct lframe *
lemon_machine_push_new_frame(struct lemon *lemon,
                             struct lobject *self,
                             struct lobject *callee,
                             lframe_call_t callback,
                             int nlocals);

/*
 * pop out all top frame with callback
 */
LEMON_EXPORT
struct lobject *
lemon_machine_return_frame(struct lemon *lemon,
                           struct lobject *retval);

LEMON_EXPORT
void
lemon_machine_push_frame(struct lemon *lemon,
                         struct lframe *frame);

LEMON_EXPORT
struct lframe *
lemon_machine_peek_frame(struct lemon *lemon);

LEMON_EXPORT
struct lframe *
lemon_machine_pop_frame(struct lemon *lemon);

LEMON_EXPORT
void
lemon_machine_store_frame(struct lemon *lemon,
                          struct lframe *frame);

LEMON_EXPORT
void
lemon_machine_restore_frame(struct lemon *lemon,
                            struct lframe *frame);

LEMON_EXPORT
struct lframe *
lemon_machine_add_pause(struct lemon *lemon);

LEMON_EXPORT
struct lframe *
lemon_machine_get_pause(struct lemon *lemon);

LEMON_EXPORT
struct lframe *
lemon_machine_set_pause(struct lemon *lemon,
                        struct lframe *frame);

LEMON_EXPORT
void
lemon_machine_del_pause(struct lemon *lemon,
                        struct lframe *frame);

LEMON_EXPORT
struct lobject *
lemon_machine_parse_args(struct lemon *lemon,
                         struct lobject *callee,
                         struct lframe *frame,
                         int define,
                         int nvalues, /* number of optional parameters */
                         int nparams, /* number of parameters */
                         struct lobject *params[], /* parameters name */
                         int argc,
                         struct lobject *argv[]);

LEMON_EXPORT
int
lemon_machine_execute(struct lemon *lemon);

LEMON_EXPORT
struct lobject *
lemon_machine_execute_loop(struct lemon *lemon);

LEMON_EXPORT
void
lemon_collector_enable(struct lemon *lemon);

LEMON_EXPORT
void
lemon_collector_disable(struct lemon *lemon);

LEMON_EXPORT
int
lemon_collector_enabled(struct lemon *lemon);

LEMON_EXPORT
void
lemon_collector_trace(struct lemon *lemon,
                      struct lobject *object);

LEMON_EXPORT
void
lemon_collector_untrace(struct lemon *lemon,
                        struct lobject *object);

LEMON_EXPORT
void
lemon_collector_mark(struct lemon *lemon,
                     struct lobject *object);

LEMON_EXPORT
void
lemon_collector_barrier(struct lemon *lemon,
                        struct lobject *a,
                        struct lobject *b);

LEMON_EXPORT
void
lemon_collector_barrierback(struct lemon *lemon,
                            struct lobject *a,
                            struct lobject *b);

#ifdef __cplusplus
}
#endif

#endif /* LEMON_LEMON_H */
