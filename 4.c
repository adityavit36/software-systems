/*
============================================================================
Name : Quest4.c
Author : Aditya Sharma
Description : Write a program to open an existing file with read write mode. Try O_EXCL flag also. 
Date: 24th Aug, 2023.
============================================================================
*/


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd;
    fd = open("sample_file2.txt", O_RDWR | O_EXCL);
    if (fd == -1) {
        if (errno == EEXIST) {
            printf("File already exists. Opening in read-write mode...\n");
            fd = open("sample_file2.txt", O_RDWR);
        }
       	else {
            printf("Error while opening the file");
            return 1;
        }
    }
    else 
            printf("File created just now and  opened successfully in read-write mode.\n");
    close(fd);
    return 0;
}

