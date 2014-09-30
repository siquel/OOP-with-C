#include "string.h"
#include <stdlib.h>
#include <string.h>
#include "class.h"
#include <assert.h>

// string class information
static const struct t_class _string = {
	sizeof(struct string),
	string_new,
	string_free,
	string_equals
};
// abstract datatype of string
const void* string = &_string;

// reassign _internal_string so we can work with private members
struct _internal_string {
	const  char* text;
	unsigned int length;
};

// string constructor
static void* string_new(void* self, va_list* args) {
	struct string* string = (struct string*)self;
	struct _internal_string* internals = malloc(sizeof(struct _internal_string));

	assert(internals);

	const char* text = va_arg(*args, const char*);

	internals->text = (char*)malloc(strlen(text) + 1);
	internals->length = strlen(text); // no need to take care of \0

	strcpy((char*)internals->text, text);

	string->internals = internals;
	return string;
}
// string destructor
static void* string_free(void* self) {
	struct string* string = (struct string*)self;
	struct _internal_string* internals = (struct _internal_string*) string->internals;
	free((char*)internals->text);
	internals->text = 0;
	internals->length = 0;
	
	free(internals);
	internals = 0;
	return string;
}

static int string_equals(const void* _self, const void* _b) {
	const struct string *self = _self;
	const struct string *b = _b;
	// same pointers?
	if (self == b)
		return 1;

	if (!b || b->c != string)
		return 0;
	return strcmp(((struct _internal_string*) (self->internals))->text, ((struct _internal_string*) (b->internals))->text) == 0 ? 1 : 0;
}

unsigned int string_length(void* self) {
	struct string* string = (struct string*)self;
	if (string->internals != 0) {
		const struct _internal_string* privates = string->internals;
		return privates->length;
	}
	return 0;
}
char const* string_get_text(void* self) {
	struct string* string = self;
	const struct _internal_string* _internal = string->internals;
	const char* const c = _internal->text;
	return c;
}

static struct _internal_string* string_get_internals(void* self) {
	struct string* s = self;
	return s->internals;
}

void string_set_text(void* self, char* text) {
	struct _internal_string* internal = string_get_internals(self);
	// TODO: add buffer 
	free(internal->text);
	internal->text = malloc(strlen(text) + 1);
	strcpy(internal->text, text);
	internal->length = strlen(text);
}

void string_concatc(void* self, char* text) {
	if (strlen(text) == 0) return;
	
	struct _internal_string *string = string_get_internals(self);
	// TODO: add buffer 
	size_t l = strlen(text);
	string->text = (char*)realloc(string->text, string->length + l + 1); // remember to add \0
	strcpy(string->text + string->length, text, l);
	string->length += l;
}

void string_concats(void* self, void* other) {
	string_concatc(self, string_get_internals(other)->text);
}


