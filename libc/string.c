#include "string.h"
#include "../drivers/screen.h"
#include <stddef.h>

// char* itoa(int value, char* str, int base) {
//     char* rc;
//     char* ptr;
//     char* low;
//     // Check for supported base.
//     if (base < 2 || base > 36) {
//         *str = '\0';
//         return str;
//     }
//     rc = ptr = str;
//     // Set '-' for negative decimals.
//     if (value < 0 && base == 10) {
//         *ptr++ = '-';
//     }
//     // Remember where the numbers start.
//     low = ptr;
//     // The actual conversion.
//     do {
//         // Modulo is negative for negative value. This trick makes abs() unnecessary.
//         *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + value % base];
//         value /= base;
//     } while (value);
//     // Terminating the string.
//     *ptr-- = '\0';
//     // Invert the numbers.
//     while (low < ptr) {
//         char tmp = *low;
//         *low++ = *ptr;
//         *ptr-- = tmp;
//     }
//     return rc;
// }


int strcmp(const char *first, const char *second) {
    while (*first && (*first == *second)) {
        first++;
        second++;
    }
    return *(const unsigned char*)first - *(const unsigned char*)second;
}

int strlen(const char *s){

    int i = 0;
    while(*(s+i)) i++;

    return i;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    while (n && *s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
        --n;
    }
    if (n == 0) {
        return 0;
    } else {
        return (*(unsigned char *)s1 - *(unsigned char *)s2);
    }
}

char *strchr(const char *s, int c) {
    while (*s != (char)c) {
        if (!*s++) {
            return NULL;
        }
    }
    return (char *)s;
}

char* strcpy(char* dest, const char* src) {
    char* saved = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest = 0;
    return saved;
}

char* strcat(char* dest, const char* src) {
    char* saved = dest;
    while (*dest) {
        dest++;
    }
    while (*src) {
        *dest++ = *src++;
    }
    *dest = 0;
    return saved;
}

