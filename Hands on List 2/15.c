/*
============================================================================
Name : 15.c
Author : Aditya Sharma
Description : Write a simple program to send some data from parent to the child process.
Date: 10th Oct, 2023.
============================================================================
*/

#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main(void) { 
    int fd[2],i,j;
    char buff[80];
    pipe(fd);
    if (fork()){
 	close(fd[0]); 
	printf("Enter the Message for Child: ");
	scanf("%[^\n]",buff);
	write(fd[1],buff,sizeof(buff));
    }
    else {
	    close(fd[1]);
	    read(fd[0],buff,sizeof(buff));
	    printf("Message from Parent:%s\n", buff);
    }
    wait(0);
    return 0;
}
