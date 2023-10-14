/*
============================================================================
Name : 14.c
Author : Aditya Sharma
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.
Date: 10th Oct, 2023.
============================================================================
*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 

int main(void) {
	int i,j,fd[2];
	char buf[80];
	i = pipe(fd);
	printf("i = %d\n",i);
	j = write(fd[1],"Hello, World\n",sizeof("Hello, World\n"));
	read(fd[0],buf,j);
	printf("From Pipe: %s\n", buf);
	return 0;
}
