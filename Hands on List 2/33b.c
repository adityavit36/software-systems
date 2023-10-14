/*
============================================================================
Name : 33.c
Author : Aditya Sharma
Description : Write a program to communicate between two machines using socket.
Date: 10th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(1);
    }

    // Initialize server address and port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Change this to the server's port
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Change this to the server's IP

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to the server");
        exit(1);
    }

    printf("Connected to the server. Type 'exit' to quit.\n");

    while (1) {
        char buffer[256];  // Send data to the server
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(clientSocket, buffer, strlen(buffer), 0); // Receive data from the server
        if (recv(clientSocket, buffer, sizeof(buffer), 0) == 0) {
            perror("Server disconnected");
            close(clientSocket);
            exit(1);
        }
        printf("Server: %s", buffer); // Check if the client wants to exit
        if (strcmp(buffer, "exit\n") == 0) {
            close(clientSocket);
            exit(0);
        }
    }
    return 0;
}
