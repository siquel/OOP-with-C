#ifndef STRING_H
#define STRING_H

#include <stdarg.h>

extern const void* string;

struct string {
	// inheritance
	const void* c;
	char* text;
};


static void* string_new(void* self, va_list *args);
static void* string_free(void* self);

#endif