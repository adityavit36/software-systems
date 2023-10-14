/*
============================================================================
Name : 21.c
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

    // Create a FIFO (named pipe)
    if (mkfifo(fifoName, 0666) == -1) {
        perror("Error creating FIFO");
        exit(1);
    }

    printf("FIFO created.\n");

    // Open the FIFO for writing
    fd = open(fifoName, O_WRONLY);
    if (fd == -1) {
        perror("Error opening FIFO for writing");
        exit(1);
    }

    // Write data to the FIFO
    char message[] = "Hello, FIFO!";
    write(fd, message, strlen(message) + 1);

    printf("Message sent to FIFO: %s\n", message);

    // Close the FIFO
    close(fd);

    return 0;
}

