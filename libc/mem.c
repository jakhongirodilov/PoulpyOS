#include "mem.h"
#include <stddef.h> // Include standard definitions

#define HEAP_SIZE 1024*64  // Example size: 64KB
static unsigned char heap[HEAP_SIZE];
static unsigned int heap_index = 0;

void *malloc(unsigned int size) {
    if (heap_index + size > HEAP_SIZE) return NULL; // Check if there is enough space left
    void *ptr = &heap[heap_index];
    heap_index += size; // Advance the heap index
    return ptr;
}

void free(void *ptr) {
    // Simple allocator does not handle free
}

void *memcpy(char *dst, const char *src, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
    return dst;
}

void *memset(void *s, int c, unsigned int len) {
    unsigned char *p = (unsigned char *)s;
    while (len--) {
        *p++ = (unsigned char)c;
    }
    return s;
}

