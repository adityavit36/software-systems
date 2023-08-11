#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    char *filename = "sample_file2.txt";
    int fd;

    fd = open(filename, O_RDWR | O_EXCL);

    if (fd == -1) {
        if (errno == EEXIST) {
            printf("File already exists. Opening in read-write mode...\n");
            fd = open(filename, O_RDWR);
        }
       	else {
            perror("Error while opening the file");
            return 1;
        }
    }
    else 
        printf("File created just now and  opened successfully in read-write mode.\n");
    close(fd);
    return 0;
}

