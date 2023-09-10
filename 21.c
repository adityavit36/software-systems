/*
============================================================================
Name : 21.c
Author : Aditya Sharma
Description : Write a program, call fork and print the parent and child process id.
Date: 7th Sept, 2023.
============================================================================
*/

#include<stdio.h> 
#include <stdlib.h> 
#include<unistd.h> 

int main(void) {
	if (!fork()) 
		printf("This is Child Process PID(%d)\n", getpid());
	else 
		printf("This is Parent Process PID(%d)\n", getpid());
	return 0;
}
