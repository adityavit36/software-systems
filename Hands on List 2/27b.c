/*
============================================================================
Name : 27.c
Author : Aditya Sharma
Description : Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
Date: 10th Oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

struct msg_buffer {
    long msg_type;
    char message[100];
};

int main() {
    key_t key = ftok("/tmp", 'A'); // Use the same key as the one used to send messages
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("Error creating or accessing message queue");
        exit(1);
    }

    struct msg_buffer message;
    int result = msgrcv(msgid, &message, sizeof(message.message), 1, IPC_NOWAIT);

    if (result == -1) {
        if (errno == ENOMSG) 
            printf("No message in the queue (IPC_NOWAIT)\n");
         else 
            perror("Error receiving message");
        
    } 
    else 
        printf("Received message: %s\n", message.message);
    
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

