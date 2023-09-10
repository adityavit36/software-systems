/*
============================================================================
Name : 5b.c
Author : Aditya Sharma
Description : Write a program to create five new files with infinite loop. Execute the program in the background
and check the file descriptor table at /proc/pid/fd.
Date: 24th Aug, 2023.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    while (1){}
    return 0;
}


