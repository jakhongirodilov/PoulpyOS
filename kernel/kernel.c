#include "../drivers/screen.h"
#include "../libc/mem.h"
#include "../libc/string.h"
#include "../cpu/isr.h"
#include "../drivers/keyboard.h"
#include "../bin/bash.h"
#include "../util/util.h"


void memory_management_demo() {
    pprint("Memory Management Demo\r\n");

    // Example of allocating an array of integers
    int *array = (int*) malloc(25 * sizeof(int));
    if (!array) {
        pprint("Failed to allocate memory for array\r\n");
        return;
    }

    // Initialize array with values and print them
    char buf[10];  // Buffer to hold the converted integer string
    for (int i = 0; i < 25; i++) {
        array[i] = i * i;
        itoa(array[i], buf, 10);
        pprint(buf);
        pprint(" ");
    }
    pprint("\r\n");

    // Example of freeing memory
    free(array);
    pprint("Memory has been freed.\r\n");
}

void poulpy() {
    isr_install();
    init_timer(20);
    clearScreen();
    
    // memory_management_demo();  // Run the memory management demo
    
    changeCurrentColor(MAGENTA);
    pprint("=================================================================\r\n");
    pprint("====================== Welcome to PoulpyOS ======================\r\n");
    pprint("=================================================================\r\n");
    pprint("======= type 'help' to see the list of available commands =======\r\n");
    changeCurrentColor(WHITE);
    
    init_keyboard();
    bash();    
}

