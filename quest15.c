#include <stdio.h>
#include <stdlib.h>

int main() {
    extern char **environ;  // Declare the external environment variable array

    // Iterate through the environment variables
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    return 0;
}

