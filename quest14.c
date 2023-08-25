#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    struct stat file_info;

    if (stat(file_path, &file_info) == -1) {
        printf("stat\n");
        return 1;
    }

    if (S_ISREG(file_info.st_mode)) {
        printf("Regular file\n");
    } else if (S_ISDIR(file_info.st_mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(file_info.st_mode)) {
        printf("Symbolic link\n");
    } else if (S_ISCHR(file_info.st_mode)) {
        printf("Character special file\n");
    } else if (S_ISBLK(file_info.st_mode)) {
        printf("Block special file\n");
    } else if (S_ISFIFO(file_info.st_mode)) {
        printf("FIFO or pipe\n");
    } else if (S_ISSOCK(file_info.st_mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown file type\n");
    }

    return 0;
}

