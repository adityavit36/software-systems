/*
============================================================================
Name : 29.c
Author : Aditya Sharma
Description : Write a program to remove the message queue.
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
    if ((key = ftok("myfifo", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    // Get the ID of the existing message queue
    if ((msgqid = msgget(key, 0)) == -1) {
        perror("msgget");
        exit(1);
    }

    // Remove the message queue
    if (msgctl(msgqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    printf("Message Queue removed successfully.\n");

    return 0;
}

