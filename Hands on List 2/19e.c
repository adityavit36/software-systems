/*
============================================================================
Name : 19e.c
Author : Aditya Sharma
Description : Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function
Date: 10th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    if (mkfifo("myfifo", 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    return 0;
}

