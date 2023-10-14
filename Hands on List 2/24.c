/*
============================================================================
Name : 24.c
Author : Aditya Sharma
Description : Write a program to create a message queue and print the key and message queue id
Date: 10th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

int main() {
    key_t key;
    int msgqid;

    // Generate a unique key for the message queue
    if ((key = ftok("21.c", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a new message queue or get the ID of an existing one
    if ((msgqid = msgget(key, 0666 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgqid);

    return 0;
}
