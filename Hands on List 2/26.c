/*
============================================================================
Name : 26.c
Author : Aditya Sharma
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 10th Oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

struct msgbuf {
    long mtype;
    char mtext[256];
};

int main() {
    key_t key;
    int msgqid;
    struct msgbuf message;
    int msgtype = 1;

    // Generate a unique key for the message queue
    if ((key = ftok("myfifo", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    // Get the ID of the existing message queue or create a new one if it doesn't exist
    if ((msgqid = msgget(key, 0666 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    // Prepare the message to be sent
    message.mtype = msgtype;
    strcpy(message.mtext, "Hello, Message Queue!");

    // Send the message to the message queue
    if (msgsnd(msgqid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent to the queue.\n");

    return 0;
}

