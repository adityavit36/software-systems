/*
============================================================================
Name : 17.c
Author : Aditya Sharma
Description : Write a program to execute ls -l | wc.
a. use dup
b. use dup2
c. use fcntl
Date: 10th Oct, 2023.
============================================================================
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(void) {
    int fd[2];
    pipe(fd);
    if(!fork()) { 
        close(1);
        close(fd[0]);
        dup(fd[1]);
        execlp("ls","ls","-l", (char*) NULL);
     }
     else {
        close(0);
        close(fd[1]);
        dup(fd[0]);
        execlp("wc","wc",(char*) NULL);
     }
     return 0;
}
