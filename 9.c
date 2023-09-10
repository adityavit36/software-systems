/*
============================================================================
Name : 9.c
Author : Aditya Sharma
Description : Write a program to print the following information about a given file.
a. inode
b. number of hard links
c. uid
d. gid
e. size
f. block size
g. number of blocks
h. time of last access
i. time of last modification
j. time of last change
Date: 24th Aug, 2023.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_file_info(const char *filename) {
    struct stat status;

    if (stat(filename, &status) == -1) 
        exit(EXIT_FAILURE);

    printf("File Information for: %s\n", filename);
    printf("Inode: %ld \n",status.st_ino);
    printf("Number of Hard Links: %ld \n",status.st_nlink);
    printf("UID: %u \n",status.st_uid);
    printf("GID: %u \n",status.st_gid);
    printf("Size: %ld bytes \n",status.st_size);
    printf("Block Size: %ld bytes \n ",status.st_blksize);
    printf("Number of Blocks: %ld \n ",status.st_blocks);
    printf("Time of Last Access: %s ",ctime(&status.st_atime));
    printf("Time of Last Modification: %s ",ctime(&status.st_mtime));
    printf("Time of Last Change: %s ",ctime(&status.st_ctime));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    print_file_info(argv[1]);
    return EXIT_SUCCESS;
}
