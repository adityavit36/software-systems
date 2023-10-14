/*
============================================================================
Name : 20.c
Author : Aditya Sharma
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 10th Oct, 2023.
============================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>

int main() {
	mkfifo("myfifo",0666);
	int fd = open("myfifo",O_WRONLY);
        printf("Enter the Text\n");
        char buff[80];
	scanf("%[^\n]",buff);
	write(fd,buff,sizeof(buff));
        close(fd);
	return 0;	
}
