/*
============================================================================
Name : Quest30.c
Author : Aditya Sharma
Description : To run a script at a specific time using a Daemon process.
Date: 7th Sept, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main() {
  time_t now = time(NULL);

  struct tm *tm = localtime(&now);
  tm->tm_hour = 18;
  tm->tm_min = 25;
  tm->tm_sec = 0;

  time_t desired_time = mktime(tm);
  
  if (!fork()) {
      umask(0);
      chdir("/");
      setsid();
      while (time(NULL) < mktime(tm)) 
 	   sleep(1);
      int retval = system("/home/aditya/sslab/sample_shell.sh");
      if (retval == -1) {
	  printf("Error in File");
	  exit(1); 
       }

      return 0;
  }
  else
	  exit(0);
}
