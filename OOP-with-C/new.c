#include "new.h"
#include "class.h"
#include <stdlib.h>
#include <assert.h>

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

int equals(const void* a, const void* b) {
	const struct t_class* const *c = a;
	// is null? has class? has equals?
	assert(a && *c && (*c)->eq);
	return (*c)->eq(a, b);
}