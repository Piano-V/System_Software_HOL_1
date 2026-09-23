#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        char usage_msg[] = "Usage: ./q7_cp <source_file> <dest_file>\n";
        write(STDERR_FILENO, usage_msg, sizeof(usage_msg) - 1);
        return 1;
    }

    const char *src_path = argv[1];
    const char *dest_path = argv[2];

    // Open source file in read only mode
    int src_fd = open(src_path, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    // Open destination file, create if it doesnt exist, truncate if it does
    // Mode 0644 gives rw-r--r-- permissions
    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening/creating destination file");
        close(src_fd);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    // Read from source and write to destination in chunks
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("Error");
    } else {
        const char success_msg[] = "File copied successfully \n";
        write(STDOUT_FILENO, success_msg, sizeof(success_msg) - 1);
    }

    close(src_fd);
    close(dest_fd);

    return 0;
}