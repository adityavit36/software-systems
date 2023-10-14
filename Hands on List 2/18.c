/*
============================================================================
Name : 18.c
Author : Aditya Sharma
Description : Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
size of a pipe (circular buffer).
Date: 10th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int pipefd[2];
    pid_t child_pid; // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (child_pid == 0) {
        close(pipefd[1]);
        if (fcntl(pipefd[0], F_DUPFD, 0) == -1) {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);
        execlp("wc", "wc", NULL);
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }
    else {
        close(pipefd[0]);
        if (fcntl(pipefd[1], F_DUPFD, 0) == -1) {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }
    return 0;
}
