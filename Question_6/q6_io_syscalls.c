#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    ssize_t bytes_written;

    // Prompt user on STDOUT
    const char prompt[] = "Type input and press Enter (Ctrl+D to exit):\n";
    write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);

    // Loop reading from STDIN (fd 0) until EOF or error
    while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0){
        
        // Write the exact number of bytes read directly to STDOUT (fd 1)
        bytes_written = write(STDOUT_FILENO, buffer, bytes_read);

        if (bytes_written == -1) {
            const char err_msg[] = "Write error\n";
            write(STDERR_FILENO, err_msg, sizeof(err_msg) - 1);
            return 1;
        }
    }

    if (bytes_read == -1) {
        const char err_msg[] = "Read error\n";
        write(STDERR_FILENO, err_msg, sizeof(err_msg) - 1);
        return 1;
    }

    return 0;
}