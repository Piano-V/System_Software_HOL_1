#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "dup2_test.txt";

    int fd1 = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Explicitly target descriptor number 10
    int target_fd = 10;
    int fd2 = dup2(fd1, target_fd);

    printf("Original FD: %d, Target FD assigned by dup2: %d\n", fd1, fd2);

    const char *msg1 = "Line 1 written via fd1\n";
    write(fd1, msg1, strlen(msg1));

    const char *msg2 = "Line 2 written via target_fd (dup2)\n";
    write(fd2, msg2, strlen(msg2));

    close(fd1);
    close(fd2);

    printf("Check contents: cat %s\n", filename);
    return 0;
}