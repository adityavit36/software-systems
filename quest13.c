#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    fd_set fds;
    struct timeval timeout;

    // Clear the file descriptor set
    FD_ZERO(&fds);

    // Add STDIN (file descriptor 0) to the set
    FD_SET(0, &fds);

    // Set the timeout to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input on STDIN for 10 seconds...\n");

    // Wait for input on STDIN or timeout
    int result = select(1, &fds, NULL, NULL, &timeout);

    if (result == -1) {
        printf("select");
        return 1;
    }
    else if (result == 0)  printf("No data available within 10 seconds.\n");

    else {
        if (FD_ISSET(0, &fds)) {
            printf("Data is available within 10 seconds.\n");  // Read the available data from STDIN
            char input[100];
            fgets(input, sizeof(input), stdin);
            printf("Input received: %s", input);
        }
    }

    return 0;
}
