/*
============================================================================
Name : 25.c
Author : Aditya Sharma
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
Date: 10th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main() {
    int msqid;
    key_t key;
    struct msqid_ds msq_attr;

    // Generate a unique key for the message queue
    key = ftok("24.c", 'A'); // Change the path and key as needed

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create the message queue with read and write permissions
    msqid = msgget(key, IPC_CREAT | IPC_EXCL | 0666);

    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    if (msgctl(msqid, IPC_STAT, &msq_attr) == -1) {
        perror("msgctl");
        exit(1);
    }


    printf("Access Permission: %o\n", msq_attr.msg_perm.mode);
    printf("UID: %d\n", msq_attr.msg_perm.uid);
    printf("GID: %d\n", msq_attr.msg_perm.gid);
    printf("Last Message Sent Time: %s", ctime(&msq_attr.msg_stime));
    printf("Last Message Received Time: %s", ctime(&msq_attr.msg_rtime));
    printf("Last Change Time: %s", ctime(&msq_attr.msg_ctime));
    printf("Size of the Queue: %lu bytes\n", msq_attr.__msg_cbytes);
    printf("Number of Messages in the Queue: %lu\n", msq_attr.msg_qnum);
    printf("Maximum Number of Bytes Allowed: %lu\n", msq_attr.msg_qbytes);
    printf("PID of Last msgsnd: %d\n", msq_attr.msg_lspid);
    printf("PID of Last msgrcv: %d\n", msq_attr.msg_lrpid);
    return 0;
}
