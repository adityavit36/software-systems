/*
============================================================================
Name : 22.c
Author : Aditya Sharma
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
size of a pipe (circular buffer).
Date: 10th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

int main() {
    int fd;
    fd_set fds;
    struct timeval timeout;

    char fifoName[] = "myfifo"; // Change this to the name of your FIFO
    int bufferSize = 256; // Set your desired buffer size

    // Open the FIFO for reading
    fd = open("myfifo2", O_RDONLY);
    if (fd == -1) {
        perror("Error opening FIFO for reading");
        exit(1);
    }

    // Clear the set and add the file descriptor for the FIFO
    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    // Set the timeout to 10 seconds (10 seconds, 0 microseconds)
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    // Use select to wait for data to be written into the FIFO
    int ready = select(fd + 1, &fds, NULL, NULL, &timeout);

    if (ready == -1) {
        perror("select");
        exit(1);
    } else if (ready == 0) {
        printf("Timeout: No data written into the FIFO within 10 seconds.\n");
    } else {
        // Data is available to be read from the FIFO
        char buffer[bufferSize];
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            printf("Data received from FIFO: %s\n", buffer);
        }
    }

    // Close the FIFO
    close(fd);

    return 0;
}

