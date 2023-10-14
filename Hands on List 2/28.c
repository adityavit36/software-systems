/*
============================================================================
Name : 28.c
Author : Aditya Sharma
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 10th Oct, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgqid;

    // Generate a unique key for the message queue
    if ((key = ftok("21.c", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    // Get the ID of the existing message queue
    if ((msgqid = msgget(key, 0)) == -1) {
        perror("msgget");
        exit(1);
    }

    struct msqid_ds msq_info;

    // Get the current permission and information of the message queue
    if (msgctl(msgqid, IPC_STAT, &msq_info) == -1) {
        perror("msgctl (IPC_STAT)");
        exit(1);
    }

    // Change the permission to allow read, write, and execute for the owner and read for others
    msq_info.msg_perm.mode = 0644;

    // Set the updated permission and information back to the message queue
    if (msgctl(msgqid, IPC_SET, &msq_info) == -1) {
        perror("msgctl (IPC_SET)");
        exit(1);
    }

    printf("Message Queue permission changed successfully.\n");

    return 0;
}
