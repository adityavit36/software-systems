/*
============================================================================
Name : Quest29.c
Author : Aditya Sharma
Description : Write a C program to get scheduling policy and modify the scheduling policy (SCHED_FIFO,SCHED_RR)
Date: 7th Sept, 2023.
============================================================================
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int policy;
    struct sched_param param;
    int pid = getpid(); 
    int get_policy = sched_getscheduler(pid); // Get Scheduling policy of calling process
    if (get_policy == -1) {
        perror("sched_getscheduler");
        exit(EXIT_FAILURE);
    }
    // Get the current scheduling parameters
    if (sched_getparam(pid, &param) == -1) {
        perror("sched_getparam");
        exit(EXIT_FAILURE);
    }
    printf("Current scheduling policy: ");
    switch (get_policy) {
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }
    printf("Current priority: %d\n", param.sched_priority);
 //   struct sched_param new_param;
   // new_param.sched_priority = 50; // Set the priority for SCHED_FIFO
     param.sched_priority = 50;
    if (sched_setscheduler(pid, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler");
        exit(EXIT_FAILURE);
    }
    printf("\nScheduling policy changed to SCHED_FIFO\n");
    get_policy = sched_getscheduler(0);
    if (get_policy == -1) {
        perror("sched_getscheduler");
        exit(EXIT_FAILURE);
    }
    printf("New scheduling policy: ");
    switch (get_policy) {
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }
    return 0;
}
