#ifndef UTIL_H
#define UTIL_H
#include <stdlib.h>
#include <stdio.h>

void* emalloc(size_t size);
void initialize_f(double ***f, int N);
void initialize_u(double ***u, int N, int start_T);

#endif /* UTIL_H */