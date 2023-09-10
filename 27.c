/*
============================================================================
Name : Quest27.c
Author : Aditya Sharma

Description : Write a program to execute ls -Rl by the following system calls
a. execl
b. execlp
c. execled. execv
e. execvp

Date: 7th Sept, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Using execl:\n");
    if (!fork()) {        // Child process
        execl("/bin/ls", "ls", "-Rl", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    wait(NULL); // Parent process is waiting for child process to finish execution

    printf("\nUsing execlp:\n");
    if (!fork()) {        // Child process
        execlp("ls", "ls", "-Rl", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    wait(NULL);

    printf("\nUsing execle:\n");
    if (!fork()) {        // Child process
        char* envp[] = {NULL}; // Empty environment
        execle("/bin/ls", "ls", "-Rl", NULL, envp);
        perror("execle");
        exit(EXIT_FAILURE);
    }
    wait(NULL);

    printf("\nUsing execv:\n");
    if (!fork()) {        // Child process
        char* argv[] = {"ls", "-Rl", NULL};
        execv("/bin/ls", argv);
        perror("execv");
        exit(EXIT_FAILURE);
    }
    wait(NULL);

    printf("\nUsing execvp:\n");
    if (!fork()) {  // Child process
        char* argv[] = {"ls", "-Rl", NULL};
        execvp("ls", argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    wait(NULL);

    return 0;
}
