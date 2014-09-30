#include "new.h"
#include "string.h"
#include <stdio.h>


int main(void) {
	void* a = construct(string, "aaa");
	void* b = construct(string, "aab");

	string_concatc(a, "bbb");
	string_concatc(a, "ccc");
	string_concatc(a, ":D");
	string_concats(a, b);
	printf("%s", string_get_text(a));
	deconstruct(a);
	deconstruct(b);
	return 0;
}