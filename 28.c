/*
============================================================================
Name : Quest28.c
Author : Aditya Sharma
Description : Write a program to get maximum and minimum real time priority.
Date: 7th Sept, 2023.
============================================================================
*/

#include <stdio.h>
#include <sched.h>

int main() {
    int Max,Min;

    Max = sched_get_priority_max(SCHED_RR);
    if (Max == -1) {
        perror("sched_get_priority_max");
        return 1;
    }

    Min = sched_get_priority_min(SCHED_RR);
    if (Min == -1) {
        perror("sched_get_priority_min");
        return 1;
    }

    printf("Maximum real-time priority: %d\n", Max);
    printf("Minimum real-time priority: %d\n", Min);

    return 0;
}

