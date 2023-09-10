/*
============================================================================
Name : 6.c
Author : Aditya Sharma
Description : Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls 
Date: 24th Aug, 2023
============================================================================
*/

#include <unistd.h>

int main(void) {
    char buffer[1024]; 
    // fd = 0 for STDIN_FILENO and fd = 1 for STDOUT_FILENO  
    while(read(STDIN_FILENO, buffer, 1024) > 0)  // read till end of user input is reached. 
    write(STDOUT_FILENO, buffer, 1024);
    return 0;
}
