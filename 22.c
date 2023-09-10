/*
============================================================================
Name : 22.c
Author : Aditya Sharma
Description : Write a program, open a file, call fork, and then write to the file by both the child as well as the
parent processes. Check output of the file.
Date: 7th Sept, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h> 
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void) {
	int fd;
        char data[256];	
	fd = open("text_file1.txt", O_RDWR | O_CREAT);
	if (fd == -1) {
	  printf("Error in Opening file \n");
	  return 1;
	}
	if(!fork()) {
	 printf("Child Process with PID (%d) is writing on file\n", getpid());
//	 printf("Enter the data you want to enter from child process\n");
//	 gets(data);
	 write(fd,"My Name is Aditya Sharma",sizeof("My Name is Aditya Sharma"));
        }
	else {
        wait(0);
	printf("Parent Process with PID (%d) is writing on file\n", getpid());
//        printf("Enter the data you want to enter from parent process\n");
//	gets(data);
        write(fd,"MTech IIITB",sizeof("MTech IIITB"));
	}
        return 0;
}
