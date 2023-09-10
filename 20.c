/*
============================================================================
Name : 20.c
Author : Aditya Sharma
Description : Write a C program to find priority of program and modifying it with nice command
Date: 7th Sept, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
   int niceV;
   int pid = getpid();
   niceV = getpriority(PRIO_PROCESS,0);
   printf("pid : %d, nice: %d\n",pid,niceV);
   getchar(); // To hold the screen, waiting to display the output on other terminal.
   nice(5); // Incremented the priority of the process by 5 
   niceV = getpriority(PRIO_PROCESS, 0); 
   printf("pid : %d, nice: %d\n",pid,niceV);
   getchar();
   return 0;
}

