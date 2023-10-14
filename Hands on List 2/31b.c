/*
============================================================================
Name : 31b.c
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
    sem_t countingSemaphore;
    int initialValue = 5; // Change this to the desired initial value

    // Initialize a counting semaphore with the specified initial value
    if (sem_init(&countingSemaphore, 0, initialValue) == -1) {
        perror("sem_init");
        exit(1);
    }

    printf("Counting semaphore created and initialized with initial value: %d\n", initialValue);

    // Perform some operations with the counting semaphore (e.g., wait and post)

    // Destroy the semaphore when done
    sem_destroy(&countingSemaphore);

    return 0;
}

