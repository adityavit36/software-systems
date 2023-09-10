/*
============================================================================
Name : 18.c
Author : Aditya Sharma
Description : Write a program to perform Record locking.
a. Implement write lock
b. Implement read lock
Create three records in a file. Whenever you access a particular record, first lock it then modify/access
to avoid race condition.

Date: 24th Aug, 2023.
============================================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct Record {
    int id;
    char data[256];
};

void acquireWriteLock(int fd, int recordNum) {
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = recordNum * sizeof(struct Record);
    fl.l_len = sizeof(struct Record);
    fl.l_pid = getpid();

    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        printf("Error acquiring write lock\n");
	exit(EXIT_FAILURE);
    }
}

void acquireReadLock(int fd, int recordNum) {
    struct flock fl;
    fl.l_type = F_RDLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = recordNum * sizeof(struct Record);
    fl.l_len = sizeof(struct Record);
    fl.l_pid = getpid();

    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        printf("Error acquiring read lock\n");
	exit(EXIT_FAILURE);
    }
}

void releaseLock(int fd, int recordNum) {
    struct flock fl;
    fl.l_type = F_UNLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = recordNum * sizeof(struct Record);
    fl.l_len = sizeof(struct Record);
    fl.l_pid = getpid();

    if (fcntl(fd, F_SETLK, &fl) == -1) {
        printf("Error releasing lock\n");
	exit(EXIT_FAILURE);
    }
}

int main() {
    int fd = open("records.txt", O_RDWR | O_CREAT);
    if (fd == -1) {
        printf("Error opening file\n");
	exit(EXIT_FAILURE);
    }
    struct Record records[3];
    for (int i = 0; i < 3; ++i) {
        records[i].id = i + 1;
        printf("Enter the data for Records[%d]\n", i + 1);
        gets(records[i].data);
        write(fd, &records[i], sizeof(struct Record));
    }
    
    while (1) {
    printf("Do You want to Read or Write the Record. Enter 1 for Write or 0 for Read or 2 for Break\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
	 int recordNum;
	 printf("Enter the Record Num to Write\n");
	 scanf("%d", &recordNum);
	 acquireWriteLock(fd, recordNum);
	 printf("Write lock acquired for record %d. Modifying record...\n", recordNum);
	 lseek(fd, recordNum * sizeof(struct Record), SEEK_SET);
	 read(fd, &records[recordNum], sizeof(struct Record));
	 printf("Enter the data for Records[%d]\n", recordNum);
	 if (getchar())	 gets(records[recordNum].data);
	 lseek(fd, recordNum * sizeof(struct Record), SEEK_SET);
	 write(fd, &records[recordNum], sizeof(struct Record));
	 printf("Record modified.\n");
	 if (getchar())
	 releaseLock(fd, recordNum);
    }
    if (choice == 0) {
	 int recordNum;
	 printf("Enter the Record Num to Read\n");
	 scanf("%d", &recordNum);
	 acquireReadLock(fd, recordNum);
	 printf("Read lock acquired for record %d. Accessing record...\n", recordNum);
	 lseek(fd, recordNum * sizeof(struct Record), SEEK_SET);
	 read(fd, &records[recordNum], sizeof(struct Record));
         printf("Record %d: ID = %d, Data = %s\n", recordNum, records[recordNum].id, records[recordNum].data);
	 if (getchar())
	 releaseLock(fd, recordNum);
    }
    if (choice == 2) 
	break;
   }
    close(fd);
    return 0;
}
