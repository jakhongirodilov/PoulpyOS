#include "bash.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../libc/mem.h"
#include "../cpu/types.h"
#include "../cpu/timer.h" 
#include "../libc/string.h"
#include "../util/util.h"
#include <stddef.h>


void printCLI(const char *cmd){

    //Clear the current line
    clearLastLine();

    //Print the command
    changeCurrentColor(MAGENTA);
    pprint("\r$>");
    changeCurrentColor(WHITE);
    pprint(cmd);
}

void computeChar(char *cmd, char toInsert, uint8_t *runCommandFlag){

    //If this is an error
    if(toInsert == '\0' || toInsert == 0x01)
        return;

    //If this is a backapce
    if(toInsert == '\b'){

        //If the cmd is already empty
        if(strlen(cmd) <= 0) return;

        //Remove the last char
        *(cmd+strlen(cmd)-1) = '\0';

    }else if(toInsert == '\r'){ //If this is enter 
        
        *runCommandFlag = 1;
        
    }else{//Add the char to the string

        //If the command as reached maxsize
        if(strlen(cmd)+1 > MAX_COMMAND_SIZE)
            return;
            
        cmd[strlen(cmd)] = (uint8_t) toInsert;
    }

    //Print the new line
    printCLI(cmd);
}

void printTree(){

    //Top
    int star = 1;
    for(int i = 0;i<15;i++){
        changeCurrentColor(i%2 ? WHITE : MAGENTA);
        for(int j = 15-i;j>0;j--){
            pprint(" ");
        }
        for(int j = 0;j<star;j++){
            pprint("*");
        }
        star += 2;
        pprint("\r\n");
    }

    //Bottom
    for(int i = 0;i<3;i++){

        for(int j = 0;j<14;j++)
            pprintChar(' ');
        for(int j = 0;j<3;j++)
            pprintChar('*');

        pprint("\r\n");
        
    }

}

void printLyricText(const char *text){

    //While lyrics are not over
    while(*text){

        //Set the correct color
        if(*text == 'A')
            changeCurrentColor(YELLOW);
        else
            changeCurrentColor(WHITE);

        //Print a line
        while((*text) != '\n'){
            pprintChar(*text);
            text++;
        }

        pprintChar(*(text++));
        
        //Wait for enter input
        char c = 0;
        while(c != '\r')
            getKey(&c);

    }
}

void echo_command(char *input) {
    // Find the first space to skip the "echo" command itself
    char *text = strchr(input, ' ');
    if (text) {
        // Move past the space to print the remaining text
        text++;  // Increment to start from next character after space
        if (*text) { // Check if there's text after space
            pprint(text);
        }
    }
    pprint("\r\n"); // Ensure newline is printed whether text is present or not
}



void print_uptime() {
    unsigned int total_seconds = get_system_uptime();
    unsigned int hours = total_seconds / 3600;
    unsigned int minutes = (total_seconds % 3600) / 60;
    unsigned int seconds = total_seconds % 60;

    char buffer[50];
    strcpy(buffer, "Uptime: ");
    itoa(hours, buffer + strlen(buffer), 10);
    strcat(buffer, ":");
    itoa(minutes, buffer + strlen(buffer), 10);
    strcat(buffer, ":");
    itoa(seconds, buffer + strlen(buffer), 10);
    strcat(buffer, "\r\n");
    pprint(buffer);
}

void runCommand(char *cmd) {
    pprint("\r\n");

    if (strlen(cmd) == 0)
        return;

    if (strncmp(cmd, "echo ", 5) == 0) {
        echo_command(cmd);
    } else if (strcmp(cmd, "echo") == 0) { 
        pprint("\r\n");
    } else if (strcmp(cmd, "hello") == 0) {
        pprint("Welcome to Poulpy-OS !!\r\n");
    } else if (strcmp(cmd, "uptime") == 0) {
        print_uptime();
    } else if (strcmp(cmd, "tree") == 0) {
        printTree();
    } else if (strcmp(cmd, "Johnny") == 0) {
        printLyricText(lyrics);
    } else if (strcmp(cmd, "help") == 0) {
        pprint("Supported commands: \r\n - tree \r\n - hello \r\n - echo \r\n - uptime \r\n - help \r\n");
    } else {
        pprint("No such command\r\n");
    }
}


void bash(){
    while (1)
    {   
        //Init
        char cmd[MAX_COMMAND_SIZE];
        memset(cmd,0,MAX_COMMAND_SIZE);
        
        char c = 0;
        uint8_t runCommandFlag = 0;

        //Print the shell
        printCLI(cmd);
        
        while(!runCommandFlag){

            //Wait for the next char
            while(getKey(&c) == -1);

            //Compute the next char
            computeChar(cmd,c,&runCommandFlag);
        }

        runCommand(cmd);

    }
}