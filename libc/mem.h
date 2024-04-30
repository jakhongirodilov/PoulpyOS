#ifndef LIBC_MEM_H
#define LIBC_MEM_H

#include "../cpu/types.h"

void *memcpy(char *dst, const char *src, int n);
void *memset(void *s, int c, unsigned int len);
void *malloc(unsigned int size);
void free(void *ptr);

#endif // LIBC_MEM_H

