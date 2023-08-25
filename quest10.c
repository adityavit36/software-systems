#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {   // Open the file in read-write mode or create if it doesn't exist
    int fileDescriptor = open("data.txt", O_RDWR | O_CREAT);
    
    if (fileDescriptor == -1) {
        printf("Error opening the file \n");
        return 1;
    }

    // Write 10 bytes to the file
    const char* data1 = "abcdefghij";
    ssize_t bytesWritten1 = write(fileDescriptor, data1, 10);

    if (bytesWritten1 != 10) {
        printf("Error writing data to the file\n");
        close(fileDescriptor);
        return 1;
    } // Move the file pointer by 10 bytes using lseek
 
    off_t newPosition = lseek(fileDescriptor, 10, SEEK_CUR);

    if (newPosition == -1) {
        printf("Error using lseek\n");
        close(fileDescriptor);
        return 1;
    }    // Write another 10 bytes to the file

    const char* data2 = "ABCDEFGHIJ";
    ssize_t bytesWritten2 = write(fileDescriptor, data2, 10);

    if (bytesWritten2 != 10) {
        printf("Error writing data to the file");
        close(fileDescriptor);
        return 1;
    }

    // Close the file
    close(fileDescriptor);

    return 0;
}

