#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r"); // Open the file in read-only mode
    if (file == NULL) {
      //  perror("fopen");
        return EXIT_FAILURE;
    }

    char buffer[1024]; // Buffer to hold each line
    while (fgets(buffer, sizeof(buffer), file) != NULL)
        printf("%s", buffer); // Display the read line
    
    if (feof(file)) {
        printf("End of file reached.\n");
    }

    fclose(file); // Close the file
    return EXIT_SUCCESS;
}

