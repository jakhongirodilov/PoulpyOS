#include "../bin/bash.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../libc/mem.h"
#include "../cpu/types.h"
#include "../cpu/timer.h" 
#include "../libc/string.h"
#include "../util/util.h"
#include <stddef.h>

void addition_command(char* args) {
    // Skip the command part to get to the arguments
    args += 4; // Skip past "add "
    int num1, num2;
    parse_two_integers(args, &num1, &num2);

    int result = num1 + num2;
    char result_str[32];
    itoa_simple(result, result_str); // Assuming itoa_simple correctly formats the integer

    strcat(result_str, "\r\n");
    pprint(result_str);
}

void multiplication_command(char* args) {
    // Skip the command part to get to the arguments
    args += 9; // Skip past "multiply "
    int num1, num2;
    parse_two_integers(args, &num1, &num2);

    int result = num1 * num2;
    char result_str[32];
    itoa_simple(result, result_str); // Assuming itoa_simple correctly formats the integer

    strcat(result_str, "\r\n");
    pprint(result_str);
}