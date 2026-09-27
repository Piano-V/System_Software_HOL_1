#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "test_creat.txt";
    int fd = creat(filename, 0644);

    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }

    printf("File '%s' created successfully!\n", filename);
    printf("Assigned File Descriptor value: %d\n", fd);

    
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}