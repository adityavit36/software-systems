/*
============================================================================
Name : 23.c
Author : Aditya Sharma
Description : Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 10th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/stat.h>

int main() {
    struct rlimit rlim;
    if (getrlimit(RLIMIT_NOFILE, &rlim) == 0)
        printf("Maximum number of files that can be opened within the process: %ld\n", rlim.rlim_cur);
     else {
        perror("getrlimit");
        return 1;
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    struct stat st;
    if (fstat(pipe_fd[0], &st) == 0)
        printf("Size of the pipe (circular buffer): %ld bytes\n", st.st_blksize);
     else {
        perror("fstat");
        return 1;
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}

