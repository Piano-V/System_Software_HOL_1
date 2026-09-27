#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

int main() {
    fd_set read_fds;
    struct timeval timeout;

    FD_ZERO(&read_fds);
    FD_SET(0, &read_fds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input (10 seconds)...\n");

    int result = select(1, &read_fds, NULL, NULL, &timeout);

    if (result == -1) {
        perror("select error");
        return 1;
    } else if (result == 0) {
        printf("Timeout: No data entered within 10 seconds.\n");
    } else {
        if (FD_ISSET(0, &read_fds)) {
            char buffer[256];
            ssize_t bytes = read(0, buffer, sizeof(buffer) - 1);
            if (bytes > 0) {
                buffer[bytes] = '\0';
                printf("Input received: %s", buffer);
            }
        }
    }

    return 0;
}