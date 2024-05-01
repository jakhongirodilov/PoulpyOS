#ifndef UTIL_H
#define UTIL_H

// Convert integer value to a null-terminated string using the specified base
// and stores the result in the array given by str parameter.
char* itoa(int value, char* str, int base);
char* itoa_simple(int value, char* str);

#endif // UTIL_H

