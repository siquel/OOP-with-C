#include "string.h"
#include <stdlib.h>
#include <string.h>
#include "class.h"

// string class information
static const struct t_class _string = {
	sizeof(struct string),
	string_new,
	string_free
};
// abstract datatype of string
const void* string = &_string;


// string constructor
static void* string_new(void* self, va_list* args) {
	struct string* string = (struct string*)self;
	const char* text = va_arg(*args, const char*);

	string->text = (char*)malloc(strlen(text) + 1);

	strcpy(string->text, text);
	return string;
}
// string destructor
static void* string_free(void* self) {
	struct string* string = (struct string*)self;
	free(string->text);
	string->text = 0;
	return string;
}

