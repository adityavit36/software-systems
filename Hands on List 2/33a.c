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
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(clientAddr);

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(1);
    }

    // Initialize server address and port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Change this to your desired port
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding socket");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 10) == -1) {
        perror("Error listening for connections");
        exit(1);
    }

    printf("Server listening on port 8080. Waiting for connections...\n");

    // Accept incoming connections
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrSize);
    if (clientSocket == -1) {
        perror("Error accepting connection");
        exit(1);
    }

    printf("Client connected. Type 'exit' to quit.\n");

    while (1) {
        char buffer[256];
        // Receive data from the client
        if (recv(clientSocket, buffer, sizeof(buffer), 0) == 0) {
            perror("Client disconnected");
            close(clientSocket);
            close(serverSocket);
            exit(1);
        }
        printf("Client: %s", buffer);

        // Check if the server wants to exit
        if (strcmp(buffer, "exit\n") == 0) {
            close(clientSocket);
            close(serverSocket);
            exit(0);
        }

        // Send data to the client
        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(clientSocket, buffer, strlen(buffer), 0);
    }

    return 0;
}
