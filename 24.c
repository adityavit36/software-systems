/*
============================================================================
Name : Quest24.c
Author : Aditya Sharma
Description : Write a program to create an orphan process.
Date: 7th Sept, 2023.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    child_pid = fork();

    if (child_pid < 0) {
        printf("Error in Creating Child Process\n");
        exit(1);
    }

    if (child_pid == 0) {
       printf("Child process (PID %d) is running with parent id (PID %d).\n",getpid(),getppid());
       sleep(5); 
       printf("Child process (PID %d) is now orphaned with Root as Parent (PID %d).\n",getpid(),getppid());
    }
    else {
	printf("Parent process (PID %d) is running.\n", getpid());
        printf("Parent process is terminating.\n");
    }
    return 0;
}
