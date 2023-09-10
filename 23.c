/*
============================================================================
Name : 23.c 
Author : Aditya Sharma
Description : Write a program to create a Zombie state of the running program.
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
    if (child_pid == 0) 
       printf("Child process (PID %d) is running with parent id (PID %d).\n",getpid(),getppid());
    
    else {
        printf("Parent process (PID %d) is running.\n", getpid());
        sleep(5);
	printf("Process (PID %d) is out of sleep.\n", getpid());
	wait(0);
    }
    return 0;
}

