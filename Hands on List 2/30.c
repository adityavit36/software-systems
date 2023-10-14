/*
============================================================================
Name : 30.c
Author : Aditya Sharma
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
Date: 10th Oct, 2023.
============================================================================
*/


#include <sys/types.h> 
#include <sys/ipc.h>   
#include <sys/shm.h>   
#include <unistd.h>    
#include <stdio.h>     

void main()
{
    key_t shmKey;      
    int shmIdentifier; 
    ssize_t shmSize = 20;
    char *shmPointer, *rdOnlyShmPointer;

    shmKey = ftok(".", 1);

    if (shmKey == -1)
    {
        perror("Error while computing key!");
        _exit(0);
    }

    shmIdentifier = shmget(shmKey, shmSize, IPC_CREAT | 0700);

    if (shmIdentifier == -1)
    {
        perror("Error while getting Shared Memory!");
        _exit(0);
    }
    shmPointer = shmat(shmIdentifier, (void *)0, 0);

    if (*shmPointer == -1)
    {
        perror("Error while attaching address space!");
        _exit(0);
    }

    printf("Press enter to write to the shared memory!\n");
    getchar();

    sprintf(shmPointer, "Hi, I'm Aditya Sharma");

    printf("Press enter to read from the shared memory!\n");
    getchar();

    printf("Data from shared memory: %s\n", shmPointer); 

    rdOnlyShmPointer = shmat(shmIdentifier, (void *)0, SHM_RDONLY);
    if (*rdOnlyShmPointer == -1)
    {
        perror("Error while attaching address space!");
        _exit(0);
    }

    printf("Press enter to read from the shared memory!\n");
    getchar();

    printf("Data from shared memory: %s\n", rdOnlyShmPointer); 

    printf("Detaching pointer to shared memory!\n");
    shmdt(shmPointer);       
    shmdt(rdOnlyShmPointer); 

    printf("Press enter to delete the shared memory!\n");
    getchar();

    shmctl(shmIdentifier, IPC_RMID, NULL);

}
