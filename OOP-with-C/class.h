#ifndef CLASS_H
#define CLASS_H

#include <stdarg.h>
#include <stdio.h>

struct t_class {
	size_t size;
	// constructor
	void* (*ctor)(void* self, va_list *args);
	// destructor
	void* (*dtor)(void* self);
	// equals
	int (*eq)(const void* self, const void* b);
};


#endif