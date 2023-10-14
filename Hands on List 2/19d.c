/*
============================================================================
Name : 19d.c
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

#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int result = mknod("myfifo", S_IFIFO | 0666, 0);
    if (result == -1) {
        perror("mknod");
        exit(EXIT_FAILURE);
    }

    return 0;
}
