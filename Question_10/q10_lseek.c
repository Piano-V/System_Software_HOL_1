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

    // Write first 10 bytes as 'AAAAAAAAAA'
    char buf1[10] = "AAAAAAAAAA";
    if (write(fd, buf1, 10) != 10) {
        perror("Error writing first 10 bytes");
        close(fd);
        return 1;
    }
    printf("Wrote first 10 bytes ('A's). Current position: 10\n");

    // Move file pointer forward by 10 bytes from current position
    off_t new_offset = lseek(fd, 10, SEEK_CUR);
    if (new_offset == (off_t)-1) {
        perror("Error seeking file offset");
        close(fd);
        return 1;
    }

    // Check and print the return value of lseek
    printf("Return value of lseek(): %ld (offset from beginning of file)\n", (long)new_offset);

    // Write second 10 bytes as 'BBBBBBBBBB'
    char buf2[10] = "BBBBBBBBBB";
    if (write(fd, buf2, 10) != 10) {
        perror("Error writing second 10 bytes");
        close(fd);
        return 1;
    }
    printf("Wrote second 10 bytes ('B's). Total file size should now be 30 bytes.\n");

    close(fd);
    return 0;
}