/*
============================================================================
Name : 16.c
Author : Aditya Sharma
Description : Write a program to send and receive data from parent to child vice versa. Use two way
communication.
Date: 10th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int parent_to_child_pipe[2];
    int child_to_parent_pipe[2];
    pid_t child_pid;

    if (pipe(parent_to_child_pipe) == -1 || pipe(child_to_parent_pipe) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        close(parent_to_child_pipe[1]); // Close the write end of parent-to-child pipe
        close(child_to_parent_pipe[0]); // Close the read end of child-to-parent pipe

        char parent_message[100];
        char child_message[100];
        ssize_t bytes_read;
        // Read from the parent and print it
        bytes_read = read(parent_to_child_pipe[0], parent_message, sizeof(parent_message));
        if (bytes_read > 0) {
            parent_message[bytes_read] = '\0';
            printf("Child received: %s\n", parent_message);
        }

        // Send a response to the parent
        char response[100];
	scanf("%[^\n]",response);
        write(child_to_parent_pipe[1], response, strlen(response));

        close(parent_to_child_pipe[0]);
        close(child_to_parent_pipe[1]);
        _exit(EXIT_SUCCESS);
    } 
    else { // Parent process
        close(parent_to_child_pipe[0]); // Close the read end of parent-to-child pipe
        close(child_to_parent_pipe[1]); // Close the write end of child-to-parent pipe

        char message_to_child[100];
        char child_response[100];
        ssize_t bytes_read;
	
	scanf("%[^\n]",message_to_child); // Send data to the child and receive its response
        write(parent_to_child_pipe[1], message_to_child, strlen(message_to_child));
        bytes_read = read(child_to_parent_pipe[0], child_response, sizeof(child_response));
        if (bytes_read > 0) {
            child_response[bytes_read] = '\0';
            printf("Parent received from child: %s\n", child_response);
        }

        close(parent_to_child_pipe[1]);
        close(child_to_parent_pipe[0]);

        // Wait for the child to finish
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
    return 0;
}

