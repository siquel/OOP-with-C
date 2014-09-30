#include "class.h"
#include <stdlib.h>
#include <assert.h>
#include "string.h"


void* construct(const void* type, ...) {
	const struct t_class *c = (const struct t_class*)type;
	void* p = calloc(1, c->size);
	assert(p);
	*(const struct t_class **) p = c;

	if (c->ctor) {
		va_list ap;
		va_start(ap, type);
		p = c->ctor(p, &ap);
		va_end(ap);
	}

	return p;
}

void deconstruct(void* type)
{
	const struct t_class **c = (const struct t_class**)type;
	if (type && *c && (*c)->dtor)
		type = (*c)->dtor(type);
	free(type);
}



int main(void) {
	void* a = construct(string, "aaa");
	char const* v = string_get_text(a);
	return 0;
}