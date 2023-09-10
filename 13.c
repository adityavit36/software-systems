/*
============================================================================
Name : 13.c
Author : Aditya Sharma
Description : Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to
verify whether the data is available within 10 seconds or not (check in $man 2 select).

Date: 24th Aug, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    fd_set rfds;
    struct timeval timeout;

    FD_ZERO(&rfds);

    FD_SET(0, &rfds);
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input on STDIN for 10 seconds...\n");

    int result = select(1, &rfds, NULL, NULL, &timeout);

    if (result == -1) {
        printf("select");
        return 1;
    }
    else if (result == 0)  printf("No data available within 10 seconds.\n");

    else
      if(FD_ISSET(0, &rfds)) {
         printf("Data is available within 10 seconds.\n");
         char input[100];
         fgets(input, sizeof(input), stdin);
         printf("Input received: %s", input);
      }
 
    return 0;
}
