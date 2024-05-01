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

void parse_two_integers(const char* input, int* num1, int* num2);
int simple_atoi(const char* str, char** endptr);

#endif