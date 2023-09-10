/*
============================================================================
Name : Quest16.c
Author : Aditya Sharma
Description : Write a program to perform mandatory locking.
a. Implement write lock
b. Implement read lock

Date: 24th Aug, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int reader_count = 0;
void acquireWriteLock(int fd) {
    struct flock write_lock;
    write_lock.l_type = F_WRLCK;   
    write_lock.l_whence = SEEK_SET;
    write_lock.l_start = 0;
    write_lock.l_len = 0;       
    write_lock.l_pid = getpid();

    if (fcntl(fd, F_SETLKW, &write_lock) == -1) {
        printf("Error acquiring write lock");
        exit(EXIT_FAILURE);
    }
}

void acquireReaderLock(int fd) {
    struct flock read_lock;
    read_lock.l_type = F_RDLCK;
    read_lock.l_whence = SEEK_SET;
    read_lock.l_start = 0;
    read_lock.l_len = 0;
    read_lock.l_pid = getpid();

    if (fcntl(fd, F_SETLKW, &read_lock) == -1) {
        printf("Error acquiring read lock\n");
    }

    printf("Read lock acquired. Performing read operation...\n");
   

    reader_count++;
}


void releaseLock(int fd) {
    struct flock release_lock;
    release_lock.l_type = F_UNLCK;
    release_lock.l_whence = SEEK_SET;
    release_lock.l_start = 0;
    release_lock.l_len = 0;
    release_lock.l_pid = getpid();

    if (fcntl(fd, F_SETLK, &release_lock) == -1) {
       printf("Error releasing lock");
       exit(EXIT_FAILURE);
    }
   // printf("Reader_count %d\n", reader_count);
    if (reader_count > 0) 
	     reader_count--;
}

int main() {
    int fd = open("data.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }
    while (1) {
       int choice;
       printf("Enter Your Choice\n"); 
       scanf("%d", &choice);
       if(choice == 0) {
	  if (reader_count == 0) {
 	      acquireWriteLock(fd);
              printf("Write lock acquired. Performing write operation...\n");
	      printf("Write operation complete.\n");
	      if(getchar()) 
		 releaseLock(fd);
          }
	  else
	      printf("Reader counter is not Zero, Write lock Cannot be Acquired\n");
       }
       if(choice == 1) {
	  if (reader_count != 0) {
	      printf("Are You Interested in acquaring the lock. Enter 0 for No and 1 for Yes.\n");
	      int sc;
              scanf("%d", &sc);
	      if(sc == 1)  releaseLock(fd);
	  }
          acquireReaderLock(fd);
	  printf("Do You Want to Release the Reader Lock. Enter 0 for  No and 1 for Yes. \n"); 
	  int sc; 
	  scanf("%d", &sc);
	  if (sc == 1)
	  releaseLock(fd);
	  else continue;
       }
       if (choice == 2) break;
    }
    close(fd);
    return 0;
}
