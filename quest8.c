/*
============================================================================
Name : Quest8.c
Author : Aditya Sharma
Description :Write a program to open a file in read only mode, read line by line and display each line as it is read.
Close the file when end of file is reached.

Date: 24th Aug, 2023.
============================================================================
*/



#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read and display each line until the end of the file is reached
    char line[256];  // Assuming a maximum line length of 255 characters
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    // Close the file
    fclose(file);
    return 0;
}
