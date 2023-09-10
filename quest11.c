/*
============================================================================
Name : Quest11.c
Author : Aditya Sharma
Description : Write a program to open a file, duplicate the file descriptor and append the file with both the
descriptors and check whether the file is updated properly or not.
a. use dup
b. use dup2
c. use fcntl

Date: 24th Aug, 2023.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char content[256];
    printf("Enter The String \n");
    fgets(content,256,stdin);
    int fd = open("test_file.txt", O_WRONLY | O_APPEND | O_CREAT);
    if (fd == -1) {
        printf("File Opening Error");
        return 1;
    }

    int dup_fd = dup(fd);
    if (dup_fd == -1) {
        printf("File Duplicate Error");
        close(fd);
        return 1;
    }
 
    int dup_fd2 = dup2(fd,5);
    if (dup_fd2 == -1) {
        printf("File Duplicate Error");
        close(fd);
        return 1;
    }

    printf("File Descriptor %d and Duplicate file Descriptor %d and Another Duplicate File Descriptor %d\n", fd, dup_fd, dup_fd2);
//    lseek(fd,0,SEEK_SET);
    if (write(fd, content, strlen(content)) == -1) {
        printf("Write Cannot Happen");
        close(fd);
        close(dup_fd);
        return 1;
    }
  //  lseek(dup_fd,0,SEEK_SET);
    if (write(dup_fd, content, strlen(content)) == -1) {
        printf("Write Cannot Happen by Duplicate File descriptor");
        close(fd);
        close(dup_fd);
        return 1;
    }
   // lseek(dup_fd2,0,SEEK_SET);
    if (write(dup_fd2, content, strlen(content)) == -1) {
        printf("Write Cannot Happen");
        close(fd);
        close(dup_fd);
	close(dup_fd2);
        return 1;
    }

    close(fd);
    close(dup_fd);
    close(dup_fd2);
    FILE *file = fopen("test_file.txt" , "r");
    if (file == NULL)  return 1;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) printf("%s", buffer);

    fclose(file);
    return 0;
}
