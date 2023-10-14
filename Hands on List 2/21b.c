/*
============================================================================
Name : 21b.c
Author : Aditya Sharma
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 10th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char fifoName[] = "myfifo3";
    int fd;
    char buffer[100];

    // Open the FIFO for reading
    fd = open(fifoName, O_RDONLY);
    if (fd == -1) {
        perror("Error opening FIFO for reading");
        exit(1);
    }

    // Read data from the FIFO
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));

    if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the string
        printf("Message received from FIFO: %s\n", buffer);
    } else {
        perror("Error reading from FIFO");
    }

    // Close the FIFO
    close(fd);

    // Remove the FIFO
    if (unlink(fifoName) == -1) {
        perror("Error removing FIFO");
    } else {
        printf("FIFO removed.\n");
    }

    return 0;
}

