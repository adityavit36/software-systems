/*
============================================================================
Name : 15.c
Author : Aditya Sharma
Description :Write a program to display the environmental variable of the user (use environ)
Date: 24th Aug, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    extern char **environ; 


    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    return 0;
}

