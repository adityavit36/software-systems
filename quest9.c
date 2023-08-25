#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_file_info(const char *filename) {
    struct stat file_stat;

    if (stat(filename, &file_stat) == -1) {
       // perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("File Information for: %s\n", filename);
    printf("Inode: %ld \n",file_stat.st_ino);
    printf("Number of Hard Links: %ld \n",file_stat.st_nlink);
    printf("UID: %u \n",file_stat.st_uid);
    printf("GID: %u \n",file_stat.st_gid);
    printf("Size: %ld bytes \n",file_stat.st_size);
    printf("Block Size: %ld bytes \n ",file_stat.st_blksize);
    printf("Number of Blocks: %ld \n ",file_stat.st_blocks);
    printf("Time of Last Access: %s ",ctime(&file_stat.st_atime));
    printf("Time of Last Modification: %s ",ctime(&file_stat.st_mtime));
    printf("Time of Last Change: %s ",ctime(&file_stat.st_ctime));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    print_file_info(argv[1]);
    return EXIT_SUCCESS;
}
