/*
============================================================================
Name : 14.c
Author : Aditya Sharma
Description : Write a program to find the type of a file.
a. Input should be taken from command line.
b. program should be able to identify any type of a file.

Date: 24th Aug, 2023.
============================================================================
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Arguments are no sufficient, : %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    struct stat file_info;

    if (stat(file_path, &file_info) == -1) {
        printf("Unable to get Metadata for file\n");
        return 1;
    }

    if (S_ISREG(file_info.st_mode))  printf("Input File path is Regular file\n");

    else if (S_ISDIR(file_info.st_mode)) printf("Input File path is a Directory\n");
 
    else printf("Unknown file type\n");
   
    return 0;
}

