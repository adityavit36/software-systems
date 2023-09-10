/*
============================================================================
Name : 19.c
Author : Aditya Sharma
Description : Write a program to find out time taken to execute getpid system call. Use time stamp counter.
Date: 7th Sept, 2023.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>

unsigned long long rdtsc() {
	unsigned long long dst;
	__asm__ __volatile__("rdtsc":"=A"(dst));
	return dst;
}

int main(void) {

long long int start = rdtsc();
printf("Parent Process Id :%d ",getpid());
long long int end = rdtsc();

printf("Time Taken to execute Child and Parent Process is = %llu \n",end-start);
return 0;
}
