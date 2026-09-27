#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0) {
        if (write(1, buffer, bytes_read) == -1) {
            perror("write error");
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("read error");
        return 1;
    }

    return 0;
}