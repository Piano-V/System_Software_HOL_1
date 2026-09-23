#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "fcntl_dup_test.txt";

    int fd1 = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // F_DUPFD finds lowest available FD >= 20
    int fd2 = fcntl(fd1, F_DUPFD, 20);

    printf("Original FD: %d, Duplicated FD via fcntl: %d\n", fd1, fd2);

    const char *msg1 = "Appended via original descriptor\n";
    write(fd1, msg1, strlen(msg1));

    const char *msg2 = "Appended via fcntl duplicated descriptor\n";
    write(fd2, msg2, strlen(msg2));

    close(fd1);
    close(fd2);

    printf("Check contents: cat %s\n", filename);
    return 0;
}