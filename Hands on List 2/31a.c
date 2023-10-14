/*
============================================================================
Name : 31a.c
Author : Aditya Sharma
Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
Date: 10th Oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

int main() {
    sem_t binarySemaphore;

    if (sem_init(&binarySemaphore, 0, 1) == -1) {
        perror("sem_init");
        exit(1);
    }

    printf("Binary semaphore created and initialized.\n");
    sem_destroy(&binarySemaphore);

    return 0;
}

