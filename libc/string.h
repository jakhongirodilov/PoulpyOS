#ifndef STRING_H
#define STRING_H
#pragma once
#include <stddef.h> 

int strcmp( const char * first, const char * second );
int strncmp(const char *s1, const char *s2, size_t n);
int strlen( const char *s);
char *strchr(const char *s, int c);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
// char *itoa(int value, char *str, int base);

#endif