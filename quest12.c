#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *file_path = "test_file.txt";

    int fd_read = open(file_path, O_RDONLY);
    if (fd_read == -1) {
        printf("Unable to Open File in Read Mode");
        return 1;
    }

    int fd_write = open(file_path, O_WRONLY);
    if (fd_write == -1) {
        printf("Unable to Open File in Write Mode");
        return 1;
    }

    int flags_read = fcntl(fd_read, F_GETFL);
    if (flags_read == -1) {
        close(fd_read);
        close(fd_write);
        return 1;
    }

    int flags_write = fcntl(fd_write, F_GETFL);
    if (flags_write == -1) {
        close(fd_read);
        close(fd_write);
        return 1;
    }

    printf("Get File Status Value %d\n", flags_read);
    if (flags_read & O_RDONLY)
        printf("Read descriptor is in read mode.\n");
    else 
        printf("Read descriptor is not in read mode.\n");

    printf("Get File Status Value %d %d\n", flags_write,O_WRONLY);
    if (flags_write & O_WRONLY)
        printf("Write descriptor is in write mode.\n");
     else
        printf("Write descriptor is not in write mode.\n");

    close(fd_read);
    close(fd_write);
    return 0;
}
