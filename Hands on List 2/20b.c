/*
============================================================================
Name : 20b.c
Author : Aditya Sharma
Description : Write two programs so that both can communicate by FIFO -Use one way communication
Date: 10th Oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main(void) {
    int fd = open("myfifo",O_RDONLY);
    char buff[80];
    read(fd,buff,sizeof(buff));
    printf("The text from file: %s\n",buff);
    close(fd);
    return 0;
}
