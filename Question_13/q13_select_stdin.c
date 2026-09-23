#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

#define BUFFER_SIZE 256

int main() {
    fd_set read_fds;
    struct timeval timeout;

    // Clear the file descriptor set
    FD_ZERO(&read_fds);

    // Add STDIN (file descriptor 0) to the set
    FD_SET(STDIN_FILENO, &read_fds);

    // Configure 10 second timeout
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for user input from STDIN (10 sec timeout)...\n");

    int result = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);

    if (result == -1) {
        perror("select() error");
        return 1;
    } else if (result == 0) {
        printf("\n[Timeout] No data entered within 10 seconds. Exiting\n");
    } else {
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            char buffer[BUFFER_SIZE];
            ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';
                printf("[Success] Data entered: %s", buffer);
            } else if (bytes_read == 0) {
                printf("[Notice] EOF detected.\n");
            } else {
                perror("read() error");
            }
        }
    }

    return 0;
}