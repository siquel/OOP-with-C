#ifndef STRING_H
#define STRING_H

#include <stdarg.h>

extern const void* string;

// opaque, compiler thinks _internal_string is incomplete type
struct _internal_string;

struct string {
	// inheritance
	const void* c;
	// assigned to _internal_string which is opaque pointer
	const void* internals;
	
};


static void* string_new(void* self, va_list *args);
static void* string_free(void* self);
static int string_equals(const void* self, const void* b);

// methods
unsigned int string_length(void* self);
char const*  string_get_text(void* self);
//void string_set_text(void* self, char* )


#endif