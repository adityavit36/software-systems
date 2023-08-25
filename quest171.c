#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("ticket.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }

    int ticketNumber; // Initial ticket number
    printf("Enter Ticket Number\n"); 
    scanf("%d", &ticketNumber);
    // Write the ticket number to the file
    if (write(fd, &ticketNumber, sizeof(ticketNumber)) == -1) {
        printf("Error writing ticket number");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Ticket number %d reserved.\n", ticketNumber);

    close(fd);
    return 0;
}

