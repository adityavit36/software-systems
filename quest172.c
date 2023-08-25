#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void perform_write_lock(int fd) {
    struct flock lock;
    lock.l_type = F_WRLCK;  
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        printf("Error acquiring write lock");
        exit(EXIT_FAILURE);
    }
    printf("Write lock acquired\n");
}

void release_lock(int fd) {
    struct flock lock;
    lock.l_type = F_UNLCK;   
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;       
    lock.l_pid = getpid();

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        printf("Error releasing lock");
        exit(EXIT_FAILURE);
    }

    printf("Lock released\n");
}

int main() {
    int fd = open("ticket.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    perform_write_lock(fd);

    int ticketNumber;

    if (read(fd, &ticketNumber, sizeof(ticketNumber)) == -1) {
        printf("Error reading ticket number");
        close(fd);
        return EXIT_FAILURE;
    }

    ticketNumber++; 
    if (lseek(fd, 0, SEEK_SET) == -1) {
        printf("Error seeking to the beginning of the file");
        close(fd);
        return EXIT_FAILURE;
    }

    if (write(fd, &ticketNumber, sizeof(ticketNumber)) == -1) {
        printf("Error writing ticket number");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("New ticket number: %d\n", ticketNumber);
    
    if(getchar())  
    release_lock(fd);
    close(fd);

    return 0;
}

