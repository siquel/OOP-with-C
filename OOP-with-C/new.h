#ifndef NEW_H
#define NEW_H

void* construct(const void* type, ...);
void deconstruct(void* type);
int equals(const void* a, const void* b);

#endif