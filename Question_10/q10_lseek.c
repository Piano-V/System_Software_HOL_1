#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "seek_test.txt";

    // Open file in read write mode, create if absent, truncate if present
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening/creating file");
        return 1;
    }

    char buf1[10] = "AAAAAAAAAA";
    if (write(fd, buf1, 10) != 10) {
        perror("Error writing first 10 bytes");
        close(fd);
        return 1;
    }
    printf("Wrote first 10 bytes. Current position: 10\n");

    // move file pointer forward by 10 bytes from current position
    int new_offset = lseek(fd, 10, SEEK_CUR);
    printf("Return value of lseek(): %d \n", new_offset);

    char buf2[10] = "BBBBBBBBBB";
    if (write(fd, buf2, 10) != 10) {
        perror("Error writing second 10 bytes");
        close(fd);
        return 1;
    }
    printf("Wrote second 10 bytes of B \n");

    close(fd);
    return 0;
}