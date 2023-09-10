/*
============================================================================
Name : 26.c
Author : Aditya Sharma
Description : Write a c program to execute an executable program. 
Date: 7th Sept, 2023.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char name[] = "Aditya";
    int pipefd[2];
   
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();
    
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (child_pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execl("./a.out", "a.out", name, NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    else {
        close(pipefd[1]);
        char buffer[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) write(STDOUT_FILENO, buffer, bytes_read);
 	wait(NULL);
	close(pipefd[0]);
    }
    return 0;
}
