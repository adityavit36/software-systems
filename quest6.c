#include <unistd.h> 

int main() {
    char buffer[1024]; 
    ssize_t bytesRead; 
    while ((bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    return 0;
}
