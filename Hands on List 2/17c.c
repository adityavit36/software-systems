/*
============================================================================
Name : 17c.c
Author : Aditya Sharma
Description : Write a program to execute ls -l | wc.
a. use dup
b. use dup2
c. use fcntl
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
    if (child_pid == 0) { // Child process
        // Close the write end of the pipe
        close(pipefd[1]); 
	// Redirect the standard input to come from the pipe
        if (fcntl(pipefd[0], F_DUPFD, 0) == -1) {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]); // Execute the "wc" command
        execlp("wc", "wc", NULL);
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }
    else { // Parent process // Close the read end of the pipe
        close(pipefd[0]);// Redirect the standard output to go to the pipe
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
