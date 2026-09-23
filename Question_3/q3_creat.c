#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "test_creat.txt";

    // 0644 gives:
    // Read & write to owner(6)
    // Read only to group (4)
    // Read only to others (4)
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