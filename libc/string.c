#include "string.h"
#include "../drivers/screen.h"
#include "../util/util.h"
#include <stddef.h>


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

void parse_two_integers(const char* input, int* num1, int* num2) {
    while (*input && *input == ' ') input++;  // Skip leading spaces

    // Convert the first number
    char* next_part;
    *num1 = simple_atoi(input, &next_part);

    while (*next_part && *next_part == ' ') next_part++;  // Skip spaces between numbers

    // Convert the second number
    *num2 = simple_atoi(next_part, NULL);  // We don't need the end pointer here
}

int simple_atoi(const char* str, char** endptr) {
    int result = 0;
    int sign = 1;

    // Handle negative numbers
    if (*str == '-') {
        sign = -1;
        str++;
    }

    // Convert number
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    if (endptr) {
        *endptr = (char *)str;
    }

    return result * sign;
}